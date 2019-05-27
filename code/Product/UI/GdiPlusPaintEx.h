/*��������èFaceCat��� v1.0 https://github.com/FaceCat007/facecat.git
 1.��ʼ��-�󶴳���Ա-�Ϻ����׿Ƽ���ʼ��-����KOL-�յ� (΢�ź�:suade1984);
 2.���ϴ�ʼ��-�Ϻ����׿Ƽ���ʼ��-Ԭ����(΢�ź�:wx627378127);
 3.���ϴ�ʼ��-Ф����(΢�ź�:xiaotianlong_luu);
 4.���Ͽ�����-������(΢�ź�:chenxiaoyangzxy)������-���(΢�ź�:cnnic_zhu);
 5.�ó���ԴЭ��ΪBSD����ӭ�����ǵĴ�ҵ����и���֧�֣���ӭ���࿪���߼��롣
 */

#ifndef __GDIPLUSPAINTEX_H__
#define __GDIPLUSPAINTEX_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "FCDraw.h"

//GDI+��ͼ��չ
class GdiPlusPaintEx:public GdiPlusPaint{
private:
	bool m_supportTransparent;
	int m_rotateAngle;
public:
	GdiPlusPaintEx();
	virtual ~GdiPlusPaintEx();
public:
	//��ʼ��ͼ
	virtual void beginPaint(HDC hDC, const FCRect& wRect, const FCRect& pRect);
	//�����е�Ӱ������
	virtual void drawTextEx(LPCWSTR strText, Long dwPenColor, FCFont *font, const FCRect& rect);
	//��ȡ��ɫ
	virtual Long getColor(Long dwPenColor);
	//������ת�Ƕ�
	virtual void setRotateAngle(int rotateAngle);
	//�����Ƿ�֧��͸��ɫ
	virtual void setSupportTransparent(bool supportTransparent);
	//�Ƿ�֧��͸��ɫ
	virtual bool supportTransparent();
};
#endif