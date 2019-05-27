/*��������èFaceCat��� v1.0 https://github.com/FaceCat007/facecat.git
 1.��ʼ��-�󶴳���Ա-�Ϻ����׿Ƽ���ʼ��-����KOL-�յ� (΢�ź�:suade1984);
 2.���ϴ�ʼ��-�Ϻ����׿Ƽ���ʼ��-Ԭ����(΢�ź�:wx627378127);
 3.���ϴ�ʼ��-Ф����(΢�ź�:xiaotianlong_luu);
 4.���Ͽ�����-������(΢�ź�:chenxiaoyangzxy)������-���(΢�ź�:cnnic_zhu);
 5.�ó���ԴЭ��ΪBSD����ӭ�����ǵĴ�ҵ����и���֧�֣���ӭ���࿪���߼��롣
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
	//��ȡ��ɫ
	static Long getBlackColor(Long color);
	//��ȡ��ɫ
	static Long getWhiteColor(Long color);
	//��������
	static void drawText(FCPaint *paint, LPCTSTR strText, Long dwPenColor, FCFont *font, int x, int y);
	//���ƴ��»��ߵ�����
	static int drawUnderLineNum(FCPaint *paint, double value, int digit, FCFont *font, Long fontColor, bool zeroAsEmpty, int x, int y);
	//��ȡ�۸���ɫ
	static Long getPriceColor(double price, double comparePrice);
};
#endif