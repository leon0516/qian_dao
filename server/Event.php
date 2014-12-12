<?php
/**
 * 聊天逻辑，使用的协议是 文本+回车
 * 测试方法 运行
 * telnet ip 8480
 * 可以开启多个telnet窗口，窗口间可以互相聊天
 * 
 * websocket协议的聊天室见workerman-chat及workerman-todpole
 * 
 * @author walkor <walkor@workerman.net>
 */

use \Lib\Context;
use \Lib\Gateway;
use \Lib\StatisticClient;
use \Lib\Store;
use \Protocols\GatewayProtocol;
use \Protocols\TextProtocol;
use \Protocols\JsonProtocol;
use \Lib\Db;

class Event
{
    /**
     * 网关有消息时，判断消息是否完整
     */
    public static function onGatewayMessage($buffer)
    {
		if($buffer[0]=='{'){
			 return JsonProtocol::check($buffer);
		}
		else{
			 return TextProtocol::check($buffer);
		}
	}
   /**
    * 有消息时触发该方法
    * @param int $client_id 发消息的client_id
    * @param string $message 消息
    * @return void
    */
   public static function onMessage($client_id, $message)
   {
	$db = \Lib\Db::instance('tc504'); 
	$nowtime=idate("U");
	$ok = "right";
	$error="error";
	$sqlok="sql right!";
	$sqlerror="sql error!";
		if ($message[0]=='{'){
			$message = JsonProtocol::decode($message);
			$sqldidian=$message['ID'];
			$sqlshidu=$message['humidity'];
			$sqlwendu=$message['temperature'];
			$insert_id = $db->insert('wenshidu')->cols(array('didian'=>$sqldidian, 'shidu'=>$sqlshidu, 'wendu'=>$sqlwendu, 'time'=>$nowtime))->query();
			GateWay::sendToClient($client_id,TextProtocol::encode($insert_id));
		}
		else{
			$message = TextProtocol::decode($message);
			
			$commend = trim($message);
			$ret = $db->select('ui_cardid')->from('tbl_user')->where("ui_cardid = '$commend' ")->single();
			if($commend===$ret){
				$insert_id = $db->insert('tbl_log')->cols(array('log_card'=>$commend, 'log_time'=>$nowtime))->query();
					if($insert_id===1){
					GateWay::sendToClient($client_id,TextProtocol::encode($sqlok));
					}
					else{
					GateWay::sendToClient($client_id,TextProtocol::encode($sqlerror));
					}
			}
			else {
				 GateWay::sendToClient($client_id,TextProtocol::encode($error));	
			}	
		}
   }
   
   /**
    * 当用户断开连接时触发的方法
    * @param integer $client_id 断开连接的用户id
    * @return void
    */
   public static function onClose($client_id)
   {
       // 广播 xxx 退出了
       GateWay::sendToAll(TextProtocol::encode("{$_SESSION['name']}[$client_id] logout"));
   }
}
