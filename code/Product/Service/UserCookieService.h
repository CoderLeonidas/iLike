/*基于捂脸猫FaceCat框架 v1.0 https://github.com/FaceCat007/facecat.git
 1.创始人-矿洞程序员-上海宁米科技创始人-脉脉KOL-陶德 (微信号:suade1984);
 2.联合创始人-上海宁米科技创始人-袁立涛(微信号:wx627378127);
 3.联合创始人-肖添龙(微信号:xiaotianlong_luu);
 4.联合开发者-陈晓阳(微信号:chenxiaoyangzxy)，助理-朱炜(微信号:cnnic_zhu);
 5.该程序开源协议为BSD，欢迎对我们的创业活动进行各种支持，欢迎更多开发者加入。
 */

#ifndef __USERCOOKIESERVICE_H__
#define __USERCOOKIESERVICE_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "DataCenter.h"

//用户Cookie
class UserCookie{
public:
	UserCookie();
	String m_key; //键
	int m_userID; //用户ID
	String m_value; //值
};

//用户Cookie服务
class UserCookieService{
private:
	string m_createTableSQL;
	String m_dataBasePath;
	int m_userID;
public:
	UserCookieService();
	virtual ~UserCookieService();
	//用户ID
	int getUserID();
	void setUserID(int userID);
public:
	//添加Cookie
	int addCookie(UserCookie *cookie);
	//创建表
	void createTable();
	//删除Cookie
	int deleteCookie(String key);
	//获取Cookie
	int getCookie(String key, UserCookie *cookie);
	//更新Cookie
	void updateCookie(UserCookie *cookie);
};

#endif