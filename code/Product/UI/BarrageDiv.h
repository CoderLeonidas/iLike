/*��������èFaceCat��� v1.0 https://github.com/FaceCat007/facecat.git
 1.��ʼ��-�󶴳���Ա-�Ϻ����׿Ƽ���ʼ��-����KOL-�յ� (΢�ź�:suade1984);
 2.���ϴ�ʼ��-�Ϻ����׿Ƽ���ʼ��-Ԭ����(΢�ź�:wx627378127);
 3.���ϴ�ʼ��-Ф����(΢�ź�:xiaotianlong_luu);
 4.���Ͽ�����-������(΢�ź�:chenxiaoyangzxy)������-���(΢�ź�:cnnic_zhu);
 5.�ó���ԴЭ��ΪBSD����ӭ�����ǵĴ�ҵ����и���֧�֣���ӭ���࿪���߼��롣
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