/*基于捂脸猫FaceCat框架 v1.0 https://github.com/FaceCat007/facecat.git
 1.创始人-矿洞程序员-上海宁米科技创始人-脉脉KOL-陶德 (微信号:suade1984);
 2.联合创始人-上海宁米科技创始人-袁立涛(微信号:wx627378127);
 3.联合创始人-肖添龙(微信号:xiaotianlong_luu);
 4.联合开发者-陈晓阳(微信号:chenxiaoyangzxy)，助理-朱炜(微信号:cnnic_zhu);
 5.该程序开源协议为BSD，欢迎对我们的创业活动进行各种支持，欢迎更多开发者加入。
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