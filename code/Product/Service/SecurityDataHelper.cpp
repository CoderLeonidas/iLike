#include "..\\..\\stdafx.h"
#include "SecurityDataHelper.h"
#include "IndicatorData.h"

SecurityDataHelper::SecurityDataHelper(){
}

SecurityDataHelper::~SecurityDataHelper(){
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SecurityDataHelper::bindHistoryDatas(FCChart *chart, FCDataTable *dataSource, vector<FCScript*> *indicators, int *fields, vector<SecurityData*> *historyDatas){
	dataSource->clear();
	int size = (int)historyDatas->size();
	dataSource->setRowsCapacity(size + 10);
	dataSource->setRowsGrowStep(100);
	int columnsCount = dataSource->columnsCount();
	for (int i = 0; i < size; i++){
		SecurityData *securityData = (*historyDatas)[i];
		if(dataSource == chart->getDataSource()){
			insertData(chart, dataSource, fields, securityData);
		}
		else{
			double *ary = new double[columnsCount];
			ary[0] = securityData->m_close;
			ary[1] = securityData->m_high;
			ary[2] = securityData->m_low;
			ary[3] = securityData->m_open;
			ary[4] = securityData->m_volume;
			for (int j = 5; j < columnsCount; j++){
				ary[j] = dataSource->NaN;
			}
			dataSource->addRow((double)securityData->m_date, ary, columnsCount);
		}
	}
	int indicatorsSize = (int)indicators->size();
	for (int i = 0; i < indicatorsSize; i++){
		(*indicators)[i]->onCalculate(0);
	}
}

void SecurityDataHelper::bindHistoryVolAndAmountDatas(FCChart *chart, FCDataTable *dataSource, int *fields, vector<SecurityData> *historyDatas){
	dataSource->clear();
	int size = (int)historyDatas->size();
	dataSource->setRowsCapacity(size + 10);
	dataSource->setRowsGrowStep(100);
	int columnsCount = dataSource->columnsCount();
	for (int i = 0; i < size; i++){
		SecurityData securityData = (*historyDatas)[i];
		double *ary = new double[columnsCount];
		ary[0] = securityData.m_volume;
		ary[1] = securityData.m_amount;
		dataSource->addRow((double)securityData.m_date, ary, columnsCount);
	}
}

void SecurityDataHelper::createDataSource(FCChart *chart){
	FCDataTable *dataSource = chart->getDataSource();
    dataSource->addColumn(CLOSE_INDEX);
    dataSource->addColumn(HIGH_INDEX);
    dataSource->addColumn(LOW_INDEX);
    dataSource->addColumn(OPEN_INDEX);
    dataSource->addColumn(VOL_INDEX);
	dataSource->addColumn(AMOUNT_INDEX);
}

FCScript* SecurityDataHelper::createIndicator(FCChart *chart, FCDataTable *dataSource, const String& text, const String& parameters){
     FCScript *indicator = new FCScript;
    indicator->setDataSource(dataSource);
    indicator->setName(L"");
    //indicator->setFullName(L"");
	if(dataSource){
		indicator->setSourceField(CLOSE, CLOSE_INDEX);
		indicator->setSourceField(HIGH, HIGH_INDEX);
		indicator->setSourceField(LOW, LOW_INDEX);
		indicator->setSourceField(OPEN, OPEN_INDEX);
		indicator->setSourceField(VOL, VOL_INDEX);
		indicator->setSourceField(AMOUNT, AMOUNT_INDEX);
		indicator->setSourceField(CLOSE.substr(0, 1), CLOSE_INDEX);
		indicator->setSourceField(HIGH.substr(0, 1), HIGH_INDEX);
		indicator->setSourceField(LOW.substr(0, 1), LOW_INDEX);
		indicator->setSourceField(OPEN.substr(0, 1), OPEN_INDEX);
		indicator->setSourceField(VOL.substr(0, 1), VOL_INDEX);
		indicator->setSourceField(AMOUNT.substr(0, 1), AMOUNT_INDEX);
	}
    IndicatorData *indicatorData = new IndicatorData();
    indicatorData->m_parameters = parameters;
    indicatorData->m_script = text;
    indicator->setTag(indicatorData);
    String constValue = L"";
    if ((int)parameters.length() > 0){
        ArrayList<String> strs = FCStr::split(parameters, L";");
        int strsSize = (int)strs.size();
        for (int i = 0; i < strsSize; i++){
            String str = strs.get(i);
            ArrayList<String> strs2 = FCStr::split(str, L",");
            constValue += L"const " + strs2.get(0) + L":" + strs2.get(3) + L";";
            strs2.clear();
        }
        strs.clear();
    }
    if ((int)text.length() > 0){
        indicator->setScript(constValue + text);
    }
    return indicator;
}

int SecurityDataHelper::dayOfWeek(int y, int m, int d){
	if (m == 1 || m == 2){
		m += 12;
		y--;
	}
	return (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
}

int SecurityDataHelper::insertData(FCChart *chart, FCDataTable *dataSource, int *fields, SecurityData *securityData){
	double close = securityData->m_close, high = securityData->m_high, low = securityData->m_low, open = securityData->m_open, volume = securityData->m_volume, amount = securityData->m_amount;
    if (volume > 0 || close > 0){
        if (high == 0){
            high = close;
        }
        if (low == 0){
            low = close;
        }
        if (open == 0){
            open = close;
        }
    }
    else{
        close = dataSource->NaN;
        high = dataSource->NaN;
        low = dataSource->NaN;
        open = dataSource->NaN;
        volume = dataSource->NaN;
    }
	double date = (double)securityData->m_date;
    dataSource->set(date, fields[4], volume);
    int index = dataSource->getRowIndex(date);
    dataSource->set2(index, fields[0], close);
    dataSource->set2(index, fields[1], high);
    dataSource->set2(index, fields[2], low);
    dataSource->set2(index, fields[3], open);
	dataSource->set2(index, fields[5], amount);
    return index;
}

int SecurityDataHelper::insertLatestData(FCChart *chart, FCDataTable *dataSource, vector<FCScript*> *indicators, int *fields, SecurityData *latestData){
	if(latestData->m_close > 0 && latestData->m_volume > 0){
		int indicatorsSize = (int)indicators->size();
		int index = insertData(chart, dataSource, fields, latestData);
		for (int i = 0; i < indicatorsSize; i++){
			(*indicators)[i]->onCalculate(index);
		}   
		return index;
	}
	else{
		return -1;
	}
}