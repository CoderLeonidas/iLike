/*基于捂脸猫FaceCat框架 v1.0 https://github.com/FaceCat007/facecat.git
 1.创始人-矿洞程序员-上海宁米科技创始人-脉脉KOL-陶德 (微信号:suade1984);
 2.联合创始人-上海宁米科技创始人-袁立涛(微信号:wx627378127);
 3.联合创始人-肖添龙(微信号:xiaotianlong_luu);
 4.联合开发者-陈晓阳(微信号:chenxiaoyangzxy)，助理-朱炜(微信号:cnnic_zhu);
 5.该程序开源协议为BSD，欢迎对我们的创业活动进行各种支持，欢迎更多开发者加入。
 */

#ifndef __CDRAW_H__
#define __CDRAW_H__
#pragma once
#include "..\\..\\stdafx.h"

#define FCCOLORS_USERCOLOR (Long)-200000000100
#define FCCOLORS_BACKCOLOR FCCOLORS_USERCOLOR - 1
#define FCCOLORS_BACKCOLOR2 FCCOLORS_USERCOLOR - 2
#define FCCOLORS_BACKCOLOR3 FCCOLORS_USERCOLOR - 3
#define FCCOLORS_BACKCOLOR4 FCCOLORS_USERCOLOR - 4
#define FCCOLORS_BACKCOLOR5 FCCOLORS_USERCOLOR - 5
#define FCCOLORS_BACKCOLOR6 FCCOLORS_USERCOLOR - 6
#define FCCOLORS_BACKCOLOR7 FCCOLORS_USERCOLOR - 7
#define FCCOLORS_BACKCOLOR8 FCCOLORS_USERCOLOR - 8
#define FCCOLORS_BACKCOLOR9 FCCOLORS_USERCOLOR - 9
#define FCCOLORS_FORECOLOR FCCOLORS_USERCOLOR - 100
#define FCCOLORS_FORECOLOR2 FCCOLORS_USERCOLOR - 101
#define FCCOLORS_FORECOLOR3 FCCOLORS_USERCOLOR - 102
#define FCCOLORS_LINECOLOR FCCOLORS_USERCOLOR - 200
#define FCCOLORS_LINECOLOR2 FCCOLORS_USERCOLOR - 201
#define FCCOLORS_LINECOLOR3 FCCOLORS_USERCOLOR - 202
#define FCCOLORS_LINECOLOR4 FCCOLORS_USERCOLOR - 203
#define FCCOLORS_LINECOLOR5 FCCOLORS_USERCOLOR - 204
#define FCCOLORS_MIDCOLOR FCCOLORS_USERCOLOR - 300
#define FCCOLORS_UPCOLOR FCCOLORS_USERCOLOR - 301
#define FCCOLORS_UPCOLOR2 FCCOLORS_USERCOLOR - 302
#define FCCOLORS_DOWNCOLOR FCCOLORS_USERCOLOR - 303
#define FCCOLORS_SELECTEDROWCOLOR FCCOLORS_USERCOLOR - 400
#define FCCOLORS_HOVEREDROWCOLOR FCCOLORS_USERCOLOR - 401
#define FCCOLORS_WINDOWFORECOLOR FCCOLORS_USERCOLOR - 500
#define FCCOLORS_WINDOWBACKCOLOR FCCOLORS_USERCOLOR - 501
#define FCCOLORS_WINDOWBACKCOLOR2 FCCOLORS_USERCOLOR - 502
#define FCCOLORS_WINDOWBACKCOLOR3 FCCOLORS_USERCOLOR - 503
#define FCCOLORS_WINDOWCONTENTBACKCOLOR FCCOLORS_USERCOLOR - 506

class FCDraw{
public:
	//获取黑色
	static Long getBlackColor(Long color);
	//获取白色
	static Long getWhiteColor(Long color);
	//绘制文字
	static void drawText(FCPaint *paint, LPCTSTR strText, Long dwPenColor, FCFont *font, int x, int y);
	//绘制带下划线的数字
	static int drawUnderLineNum(FCPaint *paint, double value, int digit, FCFont *font, Long fontColor, bool zeroAsEmpty, int x, int y);
	//获取价格颜色
	static Long getPriceColor(double price, double comparePrice);
};
#endif