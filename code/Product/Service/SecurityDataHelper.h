/*��������èFaceCat��� v1.0 https://github.com/FaceCat007/facecat.git
 1.��ʼ��-�󶴳���Ա-�Ϻ����׿Ƽ���ʼ��-����KOL-�յ� (΢�ź�:suade1984);
 2.���ϴ�ʼ��-�Ϻ����׿Ƽ���ʼ��-Ԭ����(΢�ź�:wx627378127);
 3.���ϴ�ʼ��-Ф����(΢�ź�:xiaotianlong_luu);
 4.���Ͽ�����-������(΢�ź�:chenxiaoyangzxy)������-���(΢�ź�:cnnic_zhu);
 5.�ó���ԴЭ��ΪBSD����ӭ�����ǵĴ�ҵ����и���֧�֣���ӭ���࿪���߼��롣
 */

#ifndef __SECURITYDATAHELPER_H__
#define __SECURITYDATAHELPER_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "Security.h"
#include "DataCenter.h"


class SecurityDataHelper{
public:
	SecurityDataHelper();
	virtual ~SecurityDataHelper();
public:
	static void bindHistoryDatas(FCChart *chart, FCDataTable *dataSource, vector<FCScript*> *indicators, int *fields, vector<SecurityData*> *historyDatas);
	static void bindHistoryVolAndAmountDatas(FCChart *chart, FCDataTable *dataSource, int *fields, vector<SecurityData> *historyDatas);
	static void createDataSource(FCChart *chart);
	static FCScript* createIndicator(FCChart *chart, FCDataTable *dataSource, const String& text, const String& parameters);
	static int dayOfWeek(int y, int m, int d);
	static int insertData(FCChart *chart, FCDataTable *dataSource, int *fields, SecurityData *securityData);
	static int insertLatestData(FCChart *chart, FCDataTable *dataSource, vector<FCScript*> *indicators, int *fields, SecurityData *latestData);
};

#endif