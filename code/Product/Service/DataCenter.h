/*��������èFaceCat��� v1.0 https://github.com/FaceCat007/facecat.git
 1.��ʼ��-�󶴳���Ա-�Ϻ����׿Ƽ���ʼ��-����KOL-�յ� (΢�ź�:suade1984);
 2.���ϴ�ʼ��-�Ϻ����׿Ƽ���ʼ��-Ԭ����(΢�ź�:wx627378127);
 3.���ϴ�ʼ��-Ф����(΢�ź�:xiaotianlong_luu);
 4.���Ͽ�����-������(΢�ź�:chenxiaoyangzxy)������-���(΢�ź�:cnnic_zhu);
 5.�ó���ԴЭ��ΪBSD����ӭ�����ǵĴ�ҵ����и���֧�֣���ӭ���࿪���߼��롣
 */

#ifndef __DATACENTERCT_H__
#define __DATACENTERCT_H__
#pragma once
#include "..\\..\\stdafx.h" 
#include <atlstr.h>  
#import <msxml3.dll>
#include "..\\UI\\UIXmlEx.h"
#include "UserCookieService.h"
#include "ALikeService.h"

#define hRCALL(a, errmsg) \
do{ \
    hr = (a); \
    if (FAILED(hr)){ \
        dprintf( "%s:%d  HRCALL Failed: %s\n  0x%.8x = %s\n", \
                __FILE__, __LINE__, errmsg, hr, #a ); \
        goto clean; \
    } \
} while (0)

class UserCookieService;

//�ͻ�����������
class DataCenter{
private:
	static void dprintf(char *format, ...);
	static IXMLDOMDocument* domFromCOM();
public:
	DataCenter();
	virtual ~DataCenter();
	//�����Ƿ��Ծ
	static bool isAppAlive();
	static void setAppAlive(bool appAlive);
	//��ȡ���Ʒ���
	static ALikeService* getALikeService();
	//��ȡ����·��
	static string getAppPath();
	//��ȡ�û��ļ���
	static string getUserPath();
	//��ȡ�û�Cookie����
	static UserCookieService* getUserCookieService();
	//��ȡ��Ҫ����
	static UIXmlEx* getMainUI();
	//������Ҫ����
	static void setMainUI(UIXmlEx *mainUI);
public:
	//��������
	static void startService();
};
#endif