#include "..\\..\\stdafx.h"
#include "Security.h"

Security::Security(){
	m_code = L"";
	m_name = L"";
	m_pingyin = L"";
	m_sCode = "";
	m_status = 0;
	m_type = 0;
}

SecurityData::SecurityData(){
	m_avgPrice = 0;
	m_date = 0;
	m_open = 0;
	m_high = 0;
	m_low = 0;
	m_close = 0;
	m_volume = 0;
	m_amount = 0;
}

SecurityLatestData::SecurityLatestData(){
	m_amount = 0;
    m_buyVolume1 = 0;
    m_buyVolume2 = 0;
    m_buyVolume3 = 0;
    m_buyVolume4 = 0;
    m_buyVolume5 = 0;
    m_buyPrice1 = 0;
    m_buyPrice2 = 0;
    m_buyPrice3 = 0;
    m_buyPrice4 = 0;
    m_buyPrice5 = 0;
    m_close = 0;
    m_date = 0;
    m_high = 0;
	m_innerVol = 0;
    m_lastClose = 0;
    m_low = 0;
    m_open = 0;
	m_openInterest = 0;
	m_outerVol = 0;
    m_securityCode = L"";
    m_sellVolume1 = 0;
    m_sellVolume2 = 0;
    m_sellVolume3 = 0;
    m_sellVolume4 = 0;
    m_sellVolume5 = 0;
    m_sellPrice1 = 0;
    m_sellPrice2 = 0;
    m_sellPrice3 = 0;
    m_sellPrice4 = 0;
    m_sellPrice5 = 0;
	m_settlePrice = 0;
	m_turnoverRate = 0;
    m_volume = 0;
}