/*��������èFaceCat��� v1.0 https://github.com/FaceCat007/facecat.git
 1.��ʼ��-�󶴳���Ա-�Ϻ����׿Ƽ���ʼ��-����KOL-�յ� (΢�ź�:suade1984);
 2.���ϴ�ʼ��-�Ϻ����׿Ƽ���ʼ��-Ԭ����(΢�ź�:wx627378127);
 3.���ϴ�ʼ��-Ф����(΢�ź�:xiaotianlong_luu);
 4.���Ͽ�����-������(΢�ź�:chenxiaoyangzxy)������-���(΢�ź�:cnnic_zhu);
 5.�ó���ԴЭ��ΪBSD����ӭ�����ǵĴ�ҵ����и���֧�֣���ӭ���࿪���߼��롣
 */

#ifndef __WINHOSTEX_H__
#define __WINHOSTEX_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "RibbonButton.h"
#include "GdiPlusPaintEx.h"

//�豸����
class WinHostEx : public WinHost{
public:
	WinHostEx();
	virtual ~WinHostEx();
public:
	//�����ڲ��ؼ�
	virtual FCView* createInternalControl(FCView *parent, const String& clsid);
};
#endif