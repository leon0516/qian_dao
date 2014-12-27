/*
Navicat MySQL Data Transfer

Source Server         : TC504
Source Server Version : 50518
Source Host           : leonmysql.mysql.rds.aliyuncs.com:3306
Source Database       : tc504

Target Server Type    : MYSQL
Target Server Version : 50518
File Encoding         : 65001

Date: 2014-12-27 15:06:34
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for tbl_class
-- ----------------------------
DROP TABLE IF EXISTS `tbl_class`;
CREATE TABLE `tbl_class` (
  `class_id` int(11) NOT NULL,
  `class_name` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`class_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for tbl_errorlog
-- ----------------------------
DROP TABLE IF EXISTS `tbl_errorlog`;
CREATE TABLE `tbl_errorlog` (
  `log_id` int(11) NOT NULL AUTO_INCREMENT,
  `log_card` varchar(20) NOT NULL,
  `log_time` int(11) NOT NULL COMMENT '时间戳格式',
  `log_doorno` varchar(20) NOT NULL,
  `log_result` smallint(3) NOT NULL,
  PRIMARY KEY (`log_id`)
) ENGINE=InnoDB AUTO_INCREMENT=1381 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for tbl_log
-- ----------------------------
DROP TABLE IF EXISTS `tbl_log`;
CREATE TABLE `tbl_log` (
  `log_id` int(32) unsigned NOT NULL AUTO_INCREMENT,
  `log_card` varchar(20) NOT NULL,
  `log_time` int(11) NOT NULL COMMENT '时间戳格式',
  `log_doorno` varchar(10) NOT NULL,
  `log_result` smallint(3) NOT NULL,
  PRIMARY KEY (`log_id`)
) ENGINE=InnoDB AUTO_INCREMENT=464 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for tbl_pow
-- ----------------------------
DROP TABLE IF EXISTS `tbl_pow`;
CREATE TABLE `tbl_pow` (
  `pow_bit` smallint(8) NOT NULL,
  `pow_name` varchar(255) NOT NULL,
  PRIMARY KEY (`pow_bit`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for tbl_rst
-- ----------------------------
DROP TABLE IF EXISTS `tbl_rst`;
CREATE TABLE `tbl_rst` (
  `rst_id` smallint(3) NOT NULL,
  `rst_name` varchar(15) DEFAULT NULL,
  `rst_detail` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`rst_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for tbl_sex
-- ----------------------------
DROP TABLE IF EXISTS `tbl_sex`;
CREATE TABLE `tbl_sex` (
  `sex_id` smallint(1) NOT NULL,
  `sex_name` varchar(255) NOT NULL,
  PRIMARY KEY (`sex_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for tbl_type
-- ----------------------------
DROP TABLE IF EXISTS `tbl_type`;
CREATE TABLE `tbl_type` (
  `type_id` smallint(6) NOT NULL,
  `type_name` varchar(255) NOT NULL,
  PRIMARY KEY (`type_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for tbl_user
-- ----------------------------
DROP TABLE IF EXISTS `tbl_user`;
CREATE TABLE `tbl_user` (
  `ui_stuid` varchar(15) NOT NULL,
  `ui_cardid` varchar(20) NOT NULL,
  `ui_name` varchar(10) NOT NULL,
  `ui_class` int(20) DEFAULT NULL,
  `ui_sex` smallint(1) NOT NULL,
  `ui_power` int(11) NOT NULL,
  `ui_type` smallint(3) NOT NULL,
  `ui_com` text NOT NULL,
  PRIMARY KEY (`ui_stuid`),
  UNIQUE KEY `uuu` (`ui_stuid`),
  UNIQUE KEY `uuu2` (`ui_cardid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


-- ----------------------------
-- Table structure for wenshidu
-- ----------------------------
DROP TABLE IF EXISTS `wenshidu`;
CREATE TABLE `wenshidu` (
  `didian` varchar(255) NOT NULL,
  `shidu` int(255) NOT NULL,
  `wendu` int(255) NOT NULL,
  `time` int(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
