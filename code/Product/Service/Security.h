/*基于捂脸猫FaceCat框架 v1.0 https://github.com/FaceCat007/facecat.git
 1.创始人-矿洞程序员-上海宁米科技创始人-脉脉KOL-陶德 (微信号:suade1984);
 2.联合创始人-上海宁米科技创始人-袁立涛(微信号:wx627378127);
 3.联合创始人-肖添龙(微信号:xiaotianlong_luu);
 4.联合开发者-陈晓阳(微信号:chenxiaoyangzxy)，助理-朱炜(微信号:cnnic_zhu);
 5.该程序开源协议为BSD，欢迎对我们的创业活动进行各种支持，欢迎更多开发者加入。
 */

#ifndef __SECURITY_H__
#define __SECURITY_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "..\\..\\CStr.h"

static String CLOSE = L"CLOSE";
static String OPEN = L"OPEN";
static String HIGH = L"HIGH";
static String LOW = L"LOW";
static String VOL = L"VOL";
static String AMOUNT = L"AMOUNT";
static String AVGPRICE = L"AVGPRICE";
static int CLOSE_INDEX = 0;
static int OPEN_INDEX = 1;
static int HIGH_INDEX = 2;
static int LOW_INDEX = 3;
static int VOL_INDEX = 4;
static int AMOUNT_INDEX = 5;

class Security{
public:
	Security();
	String m_code;
	String m_name;
	String m_pingyin;
	int m_status;
	string m_sCode;
	int m_type;
};

class SecurityData{
public:
	SecurityData();
	double m_avgPrice;
	double m_date;
	double m_open;
	double m_high;
	double m_low;
	double m_close;
	double m_volume;
	double m_amount;
	void copy(SecurityData *data){
		m_avgPrice = data->m_avgPrice;
		m_date = data->m_date;
		m_open = data->m_open;
		m_high = data->m_high;
		m_low = data->m_low;
		m_close = data->m_close;
		m_volume = data->m_volume;
		m_amount = data->m_amount;
	}
};

class SecurityLatestData{
public:
	SecurityLatestData();
	double m_amount;
    int m_buyVolume1;
    int m_buyVolume2;
    int m_buyVolume3;
    int m_buyVolume4;
    int m_buyVolume5;
    double m_buyPrice1;
    double m_buyPrice2;
    double m_buyPrice3;
    double m_buyPrice4;
    double m_buyPrice5;
    double m_close;
    double m_date;
    double m_high;
	int m_innerVol;
    double m_lastClose;
    double m_low;
    double m_open;
	double m_openInterest;
	int m_outerVol;
    String m_securityCode;
    int m_sellVolume1;
    int m_sellVolume2;
    int m_sellVolume3;
    int m_sellVolume4;
    int m_sellVolume5;
    double m_sellPrice1;
    double m_sellPrice2;
    double m_sellPrice3;
    double m_sellPrice4;
    double m_sellPrice5;
	double m_settlePrice;
	double m_turnoverRate;
    double m_volume;

	void copy(SecurityLatestData *data){
		if (!data) return;
        m_amount = data->m_amount;
        m_buyVolume1 = data->m_buyVolume1;
        m_buyVolume2 = data->m_buyVolume2;
        m_buyVolume3 = data->m_buyVolume3;
        m_buyVolume4 = data->m_buyVolume4;
        m_buyVolume5 = data->m_buyVolume5;
        m_buyPrice1 = data->m_buyPrice1;
        m_buyPrice2 = data->m_buyPrice2;
        m_buyPrice3 = data->m_buyPrice3;
        m_buyPrice4 = data->m_buyPrice4;
        m_buyPrice5 = data->m_buyPrice5;
        m_close = data->m_close;
        m_date = data->m_date;
        m_high = data->m_high;
        m_innerVol = data->m_innerVol;
        m_lastClose = data->m_lastClose;
        m_low = data->m_low;
        m_open = data->m_open;
		m_openInterest = data->m_openInterest;
		m_outerVol = data->m_outerVol;
        m_securityCode = data->m_securityCode;
        m_sellVolume1 = data->m_sellVolume1;
        m_sellVolume2 = data->m_sellVolume2;
        m_sellVolume3 = data->m_sellVolume3;
        m_sellVolume4 = data->m_sellVolume4;
        m_sellVolume5 = data->m_sellVolume5;
        m_sellPrice1 = data->m_sellPrice1;
        m_sellPrice2 = data->m_sellPrice2;
        m_sellPrice3 = data->m_sellPrice3;
        m_sellPrice4 = data->m_sellPrice4;
        m_sellPrice5 = data->m_sellPrice5;
		m_settlePrice = data->m_settlePrice;
		m_turnoverRate = data->m_turnoverRate;
        m_volume = data->m_volume;
	}

	bool equal(SecurityLatestData *data){
		if (!data) return false;
        if (m_amount == data->m_amount
        && m_buyVolume1 == data->m_buyVolume1
        && m_buyVolume2 == data->m_buyVolume2
        && m_buyVolume3 == data->m_buyVolume3
        && m_buyVolume4 == data->m_buyVolume4
        && m_buyVolume5 == data->m_buyVolume5
        && m_buyPrice1 == data->m_buyPrice1
        && m_buyPrice2 == data->m_buyPrice2
        && m_buyPrice3 == data->m_buyPrice3
        && m_buyPrice4 == data->m_buyPrice4
        && m_buyPrice5 == data->m_buyPrice5
        && m_close == data->m_close
        && m_date == data->m_date
        && m_high == data->m_high
        && m_innerVol == data->m_innerVol
        && m_lastClose == data->m_lastClose
        && m_low == data->m_low
        && m_open == data->m_open
		&& m_openInterest == data->m_openInterest
		&& m_outerVol == data->m_outerVol
        && m_securityCode == data->m_securityCode
        && m_sellVolume1 == data->m_sellVolume1
        && m_sellVolume2 == data->m_sellVolume2
        && m_sellVolume3 == data->m_sellVolume3
        && m_sellVolume4 == data->m_sellVolume4
        && m_sellVolume5 == data->m_sellVolume5
        && m_sellPrice1 == data->m_sellPrice1
        && m_sellPrice2 == data->m_sellPrice2
        && m_sellPrice3 == data->m_sellPrice3
        && m_sellPrice4 == data->m_sellPrice4
        && m_sellPrice5 == data->m_sellPrice5
		&& m_settlePrice == data->m_settlePrice
		&& m_turnoverRate == data->m_turnoverRate
        && m_volume == data->m_volume){
            return true;
        }
		return false;
	}
};
#endif