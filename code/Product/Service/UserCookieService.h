/*��������èFaceCat��� v1.0 https://github.com/FaceCat007/facecat.git
 1.��ʼ��-�󶴳���Ա-�Ϻ����׿Ƽ���ʼ��-����KOL-�յ� (΢�ź�:suade1984);
 2.���ϴ�ʼ��-�Ϻ����׿Ƽ���ʼ��-Ԭ����(΢�ź�:wx627378127);
 3.���ϴ�ʼ��-Ф����(΢�ź�:xiaotianlong_luu);
 4.���Ͽ�����-������(΢�ź�:chenxiaoyangzxy)������-���(΢�ź�:cnnic_zhu);
 5.�ó���ԴЭ��ΪBSD����ӭ�����ǵĴ�ҵ����и���֧�֣���ӭ���࿪���߼��롣
 */

#ifndef __USERCOOKIESERVICE_H__
#define __USERCOOKIESERVICE_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "DataCenter.h"

//�û�Cookie
class UserCookie{
public:
	UserCookie();
	String m_key; //��
	int m_userID; //�û�ID
	String m_value; //ֵ
};

//�û�Cookie����
class UserCookieService{
private:
	string m_createTableSQL;
	String m_dataBasePath;
	int m_userID;
public:
	UserCookieService();
	virtual ~UserCookieService();
	//�û�ID
	int getUserID();
	void setUserID(int userID);
public:
	//���Cookie
	int addCookie(UserCookie *cookie);
	//������
	void createTable();
	//ɾ��Cookie
	int deleteCookie(String key);
	//��ȡCookie
	int getCookie(String key, UserCookie *cookie);
	//����Cookie
	void updateCookie(UserCookie *cookie);
};

#endif