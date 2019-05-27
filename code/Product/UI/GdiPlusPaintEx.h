/*基于捂脸猫FaceCat框架 v1.0 https://github.com/FaceCat007/facecat.git
 1.创始人-矿洞程序员-上海宁米科技创始人-脉脉KOL-陶德 (微信号:suade1984);
 2.联合创始人-上海宁米科技创始人-袁立涛(微信号:wx627378127);
 3.联合创始人-肖添龙(微信号:xiaotianlong_luu);
 4.联合开发者-陈晓阳(微信号:chenxiaoyangzxy)，助理-朱炜(微信号:cnnic_zhu);
 5.该程序开源协议为BSD，欢迎对我们的创业活动进行各种支持，欢迎更多开发者加入。
 */

#ifndef __GDIPLUSPAINTEX_H__
#define __GDIPLUSPAINTEX_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "FCDraw.h"

//GDI+绘图扩展
class GdiPlusPaintEx:public GdiPlusPaint{
private:
	bool m_supportTransparent;
	int m_rotateAngle;
public:
	GdiPlusPaintEx();
	virtual ~GdiPlusPaintEx();
public:
	//开始绘图
	virtual void beginPaint(HDC hDC, const FCRect& wRect, const FCRect& pRect);
	//绘制有倒影的文字
	virtual void drawTextEx(LPCWSTR strText, Long dwPenColor, FCFont *font, const FCRect& rect);
	//获取颜色
	virtual Long getColor(Long dwPenColor);
	//设置旋转角度
	virtual void setRotateAngle(int rotateAngle);
	//设置是否支持透明色
	virtual void setSupportTransparent(bool supportTransparent);
	//是否支持透明色
	virtual bool supportTransparent();
};
#endif