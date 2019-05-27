/*基于捂脸猫FaceCat框架 v1.0 https://github.com/FaceCat007/facecat.git
 1.创始人-矿洞程序员-上海宁米科技创始人-脉脉KOL-陶德 (微信号:suade1984);
 2.联合创始人-上海宁米科技创始人-袁立涛(微信号:wx627378127);
 3.联合创始人-肖添龙(微信号:xiaotianlong_luu);
 4.联合开发者-陈晓阳(微信号:chenxiaoyangzxy)，助理-朱炜(微信号:cnnic_zhu);
 5.该程序开源协议为BSD，欢迎对我们的创业活动进行各种支持，欢迎更多开发者加入。
 */

#ifndef __DATACENTERCT_H__
#define __DATACENTERCT_H__
#pragma once
#include "..\\..\\stdafx.h" 
#include <atlstr.h>  
#import <msxml3.dll>
#include "..\\UI\\UIXmlEx.h"
#include "UserCookieService.h"
#include "ALikeService.h"

#define hRCALL(a, errmsg) \
do{ \
    hr = (a); \
    if (FAILED(hr)){ \
        dprintf( "%s:%d  HRCALL Failed: %s\n  0x%.8x = %s\n", \
                __FILE__, __LINE__, errmsg, hr, #a ); \
        goto clean; \
    } \
} while (0)

class UserCookieService;

//客户端数据中心
class DataCenter{
private:
	static void dprintf(char *format, ...);
	static IXMLDOMDocument* domFromCOM();
public:
	DataCenter();
	virtual ~DataCenter();
	//程序是否活跃
	static bool isAppAlive();
	static void setAppAlive(bool appAlive);
	//获取相似服务
	static ALikeService* getALikeService();
	//获取启动路径
	static string getAppPath();
	//获取用户文件夹
	static string getUserPath();
	//获取用户Cookie服务
	static UserCookieService* getUserCookieService();
	//获取主要界面
	static UIXmlEx* getMainUI();
	//设置主要界面
	static void setMainUI(UIXmlEx *mainUI);
public:
	//启动服务
	static void startService();
};
#endif