/*基于捂脸猫FaceCat框架 v1.0 https://github.com/FaceCat007/facecat.git
 1.创始人-矿洞程序员-上海宁米科技创始人-脉脉KOL-陶德 (微信号:suade1984);
 2.联合创始人-上海宁米科技创始人-袁立涛(微信号:wx627378127);
 3.联合创始人-肖添龙(微信号:xiaotianlong_luu);
 4.联合开发者-陈晓阳(微信号:chenxiaoyangzxy)，助理-朱炜(微信号:cnnic_zhu);
 5.该程序开源协议为BSD，欢迎对我们的创业活动进行各种支持，欢迎更多开发者加入。
 */

#ifndef __RIBBONBUTTON_H__
#define __RIBBONBUTTON_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "FCDraw.h"
#include "GdiPlusPaintEx.h"

//透明按钮
class RibbonButton : public FCButton{
private:
	int m_arrowType;
	bool m_isClose;
	bool m_isTabClose;
	bool m_selected;
public:
	RibbonButton();
	virtual ~RibbonButton();
	//箭头形状
	int getArrowType();
	void setArrowType(int arrowType);
	//是否关闭按钮
	bool isClose();
	void setClose(bool isClose);
	//是否多页夹的关闭按钮
	bool isTabClose();
	void setTabClose(bool isTabClose);
	//是否选中
	void setSelected(bool selected);
	bool isSelected();
public:
	//获取要绘制的前景色
	virtual Long getPaintingTextColor();
	//鼠标点击方法
	virtual void onDoubleClick(FCTouchInfo touchInfo);
	//重绘背景色方法
	virtual void onPaintBackground(FCPaint *paint, const FCRect& clipRect);
};
#endif