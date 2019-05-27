/*基于捂脸猫FaceCat框架 v1.0 https://github.com/FaceCat007/facecat.git
 1.创始人-矿洞程序员-上海宁米科技创始人-脉脉KOL-陶德 (微信号:suade1984);
 2.联合创始人-上海宁米科技创始人-袁立涛(微信号:wx627378127);
 3.联合创始人-肖添龙(微信号:xiaotianlong_luu);
 4.联合开发者-陈晓阳(微信号:chenxiaoyangzxy)，助理-朱炜(微信号:cnnic_zhu);
 5.该程序开源协议为BSD，欢迎对我们的创业活动进行各种支持，欢迎更多开发者加入。
 */

#ifndef __WINDOWBUTTON_H__
#define __WINDOWBUTTON_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "FCDraw.h"

typedef enum WindowButtonStyle{
	WindowButtonStyle_Close,
	WindowButtonStyle_Max,
	WindowButtonStyle_Min,
	WindowButtonStyle_Restore
};

class WindowButton : public FCButton{
private:
	bool m_isEllipse;
	WindowButtonStyle m_style;
public:
	WindowButton();
	virtual ~WindowButton();
	bool isEllipse();
	void setEllipse(bool isEllipse);
	WindowButtonStyle getStyle();
	void setStyle(WindowButtonStyle style);
public:
	virtual Long getPaintingBackColor();
	virtual void onPaintBackground(FCPaint *paint, const FCRect& clipRect);
	virtual void onPaintBorder(FCPaint *paint, const FCRect& clipRect);
};

#endif