/*基于捂脸猫FaceCat框架 v1.0 https://github.com/FaceCat007/facecat.git
 1.创始人-矿洞程序员-上海宁米科技创始人-脉脉KOL-陶德 (微信号:suade1984);
 2.联合创始人-上海宁米科技创始人-袁立涛(微信号:wx627378127);
 3.联合创始人-肖添龙(微信号:xiaotianlong_luu);
 4.联合开发者-陈晓阳(微信号:chenxiaoyangzxy)，助理-朱炜(微信号:cnnic_zhu);
 5.该程序开源协议为BSD，欢迎对我们的创业活动进行各种支持，欢迎更多开发者加入。
 */

#ifndef __BARRAGEDIV__H__
#define __BARRAGEDIV__H__
#pragma once
#include "..\\..\\stdafx.h"

class Barrage{
private:
	Long m_color;
	FCFont *m_font;
	int m_mode;
	FCRect m_rect;
	int m_speed;
	String m_text;
	int m_tick;
public:
	Barrage();
	virtual ~Barrage();
	Long getColor();
	void setColor(Long color);
	FCFont* getFont();
	void setFONT(FCFont *font);
	int getMode();
	void setMode(int mode);
	int getSpeed();
	void setSpeed(int speed);
	FCRect getRect();
	void setRect(const FCRect& rect);
	String getText();
	void setText(const String& text);
	int getTick();
	void setTick(int tick);
public:
	void calculate();
};

class BarrageDiv : public FCView{
private:
	vector<Barrage*> m_barrages;
	map<FCView*, int> m_directionX;
	map<FCView*, int> m_directionY;
	map<FCView*, FCPoint> m_oldLocations;
	map<FCView*, int> m_speeds;
	vector<FCView*> m_subControls;
	Long m_sysColors[6];
	int m_tick;
	int m_tick2;
	int m_timerID;
private:
	FCLock m_lock;
public:
	BarrageDiv();
	~BarrageDiv();
public:
	void addBarrage(Barrage *barrage);
	virtual bool containsPoint(const FCPoint& point);
	void getSubControls(FCView *control);
	virtual void onLoad();
	virtual void onPaintBackground(FCPaint* paint, const FCRect& clipRect);
	virtual void onTimer(int timerID);
};

#endif