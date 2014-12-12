<?php 
namespace Protocols;

class JsonProtocol
{
   
    public static function check($buffer)
    {
        
		if($buffer[strlen($buffer)-1] === "\n")
		{
			return 0;
		}

		// 说明还有请求数据没收到，但是由于不知道还有多少数据没收到，所以只能返回1，因为有可能下一个字符就是\n
		return 1;
    }

    // 打包
    public static function encode($data)
    {
        // 选用json格式化数据
        return json_encode($data);
    }

    // 解包
    public static function decode($date)
    {
        return json_decode($date,true);
    }
}
