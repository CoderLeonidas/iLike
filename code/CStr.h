/*��������èFaceCat��� v1.0 https://github.com/FaceCat007/facecat.git
 1.��ʼ��-�󶴳���Ա-�Ϻ����׿Ƽ���ʼ��-����KOL-�յ� (΢�ź�:suade1984);
 2.���ϴ�ʼ��-�Ϻ����׿Ƽ���ʼ��-Ԭ����(΢�ź�:wx627378127);
 3.���ϴ�ʼ��-Ф����(΢�ź�:xiaotianlong_luu);
 4.���Ͽ�����-������(΢�ź�:chenxiaoyangzxy)������-���(΢�ź�:cnnic_zhu);
 5.�ó���ԴЭ��ΪBSD����ӭ�����ǵĴ�ҵ����и���֧�֣���ӭ���࿪���߼��롣
 */

#ifndef __FCSTRA_H__
#define __FCSTRA_H__
#pragma once
#include "stdafx.h"
#include "objbase.h"
#pragma comment(lib,"ole32.lib") 
#include "..\\third_party\\zlib\zlib.h"
#include "..\\third_party\\zlib\zconf.h"
#pragma comment(lib,"..\\libs\\zlib1.lib") 

/*
* �ַ�������
*/
class FCStrEx{
public:
	//ѹ���ַ���
	static int compress2(Byte *data, uLong ndata, Byte *zdata, uLong *nzdata);
	//ת��Ϊǧ��λ
	static String convertThousands(double value, int digit);
	//���ݿ����תΪ�ļ���
	static string convertDBCodeToFileName(const string& code);
	//���ݿ����תΪ���˴���
	static string convertDBCodeToSinaCode(const string& code);
	//���ݿ����תΪ��Ѷ����
	static string convertDBCodeToTencentCode(const string& code);
	//���˴���תΪ���ݿ����
	static String convertSinaCodeToDBCode(const String& code);
	//��Ѷ����תΪ���ݿ����
	static String convertTencentCodeToDBCode(const String& code);
	//��ѹ���ַ���
	static int deCompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);
	//��ȡ���ݿ��ַ���
	static String getDBString(const String& strSrc);
	//��ȡΨһ��ʶ
	static string getGuid();
	//��ȡ��ʽ������
	static void getFormatDate(double date, wchar_t *str);
	//��ȡ��ʽ������
	static String getFormatDate(const String& format, int year, int month, int day, int hour, int minute, int second);
	//��ȡ��ʽ������
	static String getFormatDate(const String& format, int year, int month, int day, int hour, int minute, int second, int msec);
	//��ȡ�ַ����Ŀռ�
	static int getStringCapacity(const string& str);
	//��ȡ���ַ����Ŀռ�
	static int getWStringCapacity(const String& str);
	// GZIPѹ������
	static int gZCompress(Byte *data, uLong ndata, Byte *zdata, uLong *nzdata);
	// GZIP��ѹ������
	static int gZDeCompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata);
};
#endif