/*��������èFaceCat��� v1.0 https://github.com/FaceCat007/facecat.git
 1.��ʼ��-�󶴳���Ա-�Ϻ����׿Ƽ���ʼ��-����KOL-�յ� (΢�ź�:suade1984);
 2.���ϴ�ʼ��-�Ϻ����׿Ƽ���ʼ��-Ԭ����(΢�ź�:wx627378127);
 3.���ϴ�ʼ��-Ф����(΢�ź�:xiaotianlong_luu);
 4.���Ͽ�����-������(΢�ź�:chenxiaoyangzxy)������-���(΢�ź�:cnnic_zhu);
 5.�ó���ԴЭ��ΪBSD����ӭ�����ǵĴ�ҵ����и���֧�֣���ӭ���࿪���߼��롣
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