/*基于捂脸猫FaceCat框架 v1.0 https://github.com/FaceCat007/facecat.git
 1.创始人-矿洞程序员-上海宁米科技创始人-脉脉KOL-陶德 (微信号:suade1984);
 2.联合创始人-上海宁米科技创始人-袁立涛(微信号:wx627378127);
 3.联合创始人-肖添龙(微信号:xiaotianlong_luu);
 4.联合开发者-陈晓阳(微信号:chenxiaoyangzxy)，助理-朱炜(微信号:cnnic_zhu);
 5.该程序开源协议为BSD，欢迎对我们的创业活动进行各种支持，欢迎更多开发者加入。
 */

#ifndef __FCSTRA_H__
#define __FCSTRA_H__
#pragma once
#include "stdafx.h"
#include "objbase.h"
#pragma comment(lib,"ole32.lib") 
#include "..\\third_party\\zlib\zlib.h"
#include "..\\third_party\\zlib\zconf.h"
#pragma comment(lib,"..\\libs\\zlib1.lib") 

/*
* 字符串处理
*/
class FCStrEx{
public:
	//压缩字符串
	static int compress2(Byte *data, uLong ndata, Byte *zdata, uLong *nzdata);
	//转化为千分位
	static String convertThousands(double value, int digit);
	//数据库代码转为文件名
	static string convertDBCodeToFileName(const string& code);
	//数据库代码转为新浪代码
	static string convertDBCodeToSinaCode(const string& code);
	//数据库代码转为腾讯代码
	static string convertDBCodeToTencentCode(const string& code);
	//新浪代码转为数据库代码
	static String convertSinaCodeToDBCode(const String& code);
	//腾讯代码转为数据库代码
	static String convertTencentCodeToDBCode(const String& code);
	//解压缩字符串
	static int deCompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);
	//获取数据库字符串
	static String getDBString(const String& strSrc);
	//获取唯一标识
	static string getGuid();
	//获取格式化日期
	static void getFormatDate(double date, wchar_t *str);
	//获取格式化日期
	static String getFormatDate(const String& format, int year, int month, int day, int hour, int minute, int second);
	//获取格式化日期
	static String getFormatDate(const String& format, int year, int month, int day, int hour, int minute, int second, int msec);
	//获取字符串的空间
	static int getStringCapacity(const string& str);
	//获取宽字符串的空间
	static int getWStringCapacity(const String& str);
	// GZIP压缩数据
	static int gZCompress(Byte *data, uLong ndata, Byte *zdata, uLong *nzdata);
	// GZIP解压缩数据
	static int gZDeCompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);
};
#endif