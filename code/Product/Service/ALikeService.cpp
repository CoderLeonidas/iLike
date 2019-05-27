#include "..\\..\\stdafx.h"
#include "ALikeService.h"
#include "DataCenter.h"
#include "HttpGetService.h"

namespace FaceCat{
	inline double myatof(char* sptr, int len){
		double temp = 10;
		double ans = 0;
		int i = 0;
		for(i = 0; i < len; i++){
			if(sptr[i] == '.'){
				i++;
				break;
			}
			ans = ans * 10 + (sptr[i] - '0');
		}
		for(; i < len; i++){
			ans = ans + (sptr[i] - '0') / temp;
			temp *= 10;
		}
		return ans;
	}

	inline int myatoi(char* sptr, int startPos, int endPos){
		int ans = 0;
		for(int i = startPos; i <= endPos; i++){
			ans = ans * 10 + (sptr[i] - '0');
		}
		return ans;
	}

	void readHistoryDatasFromFile(int type, const string& fpath, double *datas, int *datasSize){
		int fileLength = FCFile::getFileLength(fpath.c_str());
		char *szContent = new char[fileLength + 1];
		memset(szContent, '\0', fileLength + 1);
		ifstream fs(fpath.c_str(), ios::in); 
		if(fs){
			if(fileLength > 0){
				while(!fs.eof()){
					fs.read(szContent, fileLength); 
				}
			}
			fs.close();
		}
		char temp[100] ={0};
		int pos = 0;
		int isN = type;
		bool endWithZero = false;
		string dateStr;
		int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
		double date = 0;
		int sIndex = 0;
		int eIndex = 0;
		int delTimes = 2;
		for(int i = 0; i < fileLength ; i++){
			if(szContent[i] == '\n'){
				sIndex = i + 1;
				delTimes--;
				if(delTimes == 0){
					break;
				}
			}
		}
		for(int i = fileLength - 1; i >= 0; i--){
			if(szContent[i] == '\n'){
				eIndex = i;
				break;
			}
		}
		for(int i = sIndex; i < eIndex ; i++){
			char ch = szContent[i];
			if(ch == ',' || ch == '\n'){
				if(isN > 0){
					if(type == 2 && isN == 2){
						dateStr = temp;
					}
					else{		
						if(dateStr != ""){		
							sscanf_s(dateStr.c_str(), "%4d-%2d-%2d", &year, &month, &day);
							sscanf_s(temp, "%2d:%2d:%2d", &hour, &minute, &second);
							dateStr = "";
							date = FCStr::getDateNum(year, month, day, hour, minute, second, 0);
							datas[*datasSize] = date;
							*datasSize = *datasSize + 1;
						}
						else{
							sscanf_s(temp, "%4d-%2d-%2d", &year, &month, &day);
							date = FCStr::getDateNum(year, month, day, 0, 0, 0, 0);
							datas[*datasSize] = date;
							*datasSize = *datasSize + 1;
						}
					}
					memset(temp, 0, pos);
					isN--;
				}
				else{
					datas[*datasSize] = atof(temp);
					*datasSize = *datasSize + 1;
					memset(temp, 0, pos);
					if(ch == '\n'){
						isN = type;
					}
				}
				pos = 0;
			}
			else{
				if(ch == 0){
					endWithZero = true;
					break;
				}
				temp[pos] = ch;
				pos++;
			}
		}
		//if(!endWithZero || (pos - 1 >= 0 && temp[pos - 1] != 0))
		//{
		//	double d = atof(temp);
		//	datas->push_back(d);
		//}
		delete[] szContent;
	}

	SecurityData** readHistoryDatasFromFile(string code, int *count){
		string fileName = code;
		if (fileName.find(".") != -1){
			fileName = fileName.substr(fileName.find('.') + 1) + fileName.substr(0, fileName.find('.'));
		}
		fileName += ".txt";
		string filePath = DataCenter::getAppPath() + "\\day\\" + fileName;
		double *values = new double[7 * 8000];
		int datasSize = 0;
		int fieldLen = 7;
		readHistoryDatasFromFile(1, filePath, values, &datasSize);
		int mod = (int)datasSize % fieldLen;
		*count = (int)datasSize / fieldLen;
		SecurityData **datas = new SecurityData*[*count + 1];
		if(mod == 0){
			int pos = 0;
			for(int i = 0; i < *count; i++){
				SecurityData *data = new SecurityData();				
				data->m_date = values[i * fieldLen];
				data->m_open =  values[i * fieldLen + 1];				
				data->m_high =  values[i * fieldLen + 2];				
				data->m_low =  values[i * fieldLen + 3];				
				data->m_close =  values[i * fieldLen + 4];				
				data->m_volume =  values[i * fieldLen + 5];				
				data->m_amount =  values[i * fieldLen + 6];	
				datas[pos] = data;
				pos++;
			}
		}
		datas[*count] = new SecurityData;
		delete[] values;
		values = 0;
		return datas;
	}	

	int getLatestDataBySinaStr(String str, int formatType, SecurityLatestData *data){
		ArrayList<String> strs = FCStr::split(str, L",");
		int strLen = (int)strs.size();
		int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
		bool szIndex = false;
		for(int j = 0; j < strLen; j++){
			String str2 = strs.get(j);
			switch(j){
			case 0:{
					data->m_securityCode = FCStrEx::convertSinaCodeToDBCode(str2);
					if(data->m_securityCode.find(L"399") == 0){
						szIndex = true;
					}
					break;
				}
			case 1:
				data->m_open = FCStr::convertStrToDouble(str2.c_str());
				break;
			case 2:
				data->m_lastClose = FCStr::convertStrToDouble(str2.c_str());
				break;
			case 3:
				data->m_close = FCStr::convertStrToDouble(str2.c_str());
				break;
			case 4:
				data->m_high = FCStr::convertStrToDouble(str2.c_str());
				break;
			case 5:
				data->m_low = FCStr::convertStrToDouble(str2.c_str());
				break;
			case 8:
				data->m_volume = FCStr::convertStrToDouble(str2.c_str());
				if(szIndex){
					data->m_volume /= 100;
				}
				break;
			case 9:
				data->m_amount = FCStr::convertStrToDouble(str2.c_str());
				break;
			case 10:
				if(formatType == 0){
					data->m_buyVolume1 = FCStr::convertStrToInt(str2.c_str());
				}
				break;
			case 11:
				if(formatType == 0){
					data->m_buyPrice1 = FCStr::convertStrToDouble(str2.c_str());
				}
				break;
			case 12:
				if(formatType == 0){
					data->m_buyVolume2 = FCStr::convertStrToInt(str2.c_str());
				}
				break;
			case 13:
				if(formatType == 0){
					data->m_buyPrice2 = FCStr::convertStrToDouble(str2.c_str());
				}
				break;
			case 14:
				if(formatType == 0){
					data->m_buyVolume3 = FCStr::convertStrToInt(str2.c_str());
				}
				break;
			case 15:
				if(formatType == 0){
					data->m_buyPrice3 = FCStr::convertStrToDouble(str2.c_str());
				}
				break;
			case 16:
				if(formatType == 0){
					data->m_buyVolume4 = FCStr::convertStrToInt(str2.c_str());
				}
				break;
			case 17:
				if(formatType == 0){
					data->m_buyPrice4 = FCStr::convertStrToDouble(str2.c_str());
				}
				break;
			case 18:
				if(formatType == 0){
					data->m_buyVolume5 = FCStr::convertStrToInt(str2.c_str());
				}
				break;
			case 19:
				if(formatType == 0){
					data->m_buyPrice5 = FCStr::convertStrToDouble(str2.c_str());
				}
				break;
			case 20:
				if(formatType == 0){
					data->m_sellVolume1 = FCStr::convertStrToInt(str2.c_str());
				}
				break;
			case 21:
				if(formatType == 0){
					data->m_sellPrice1 = FCStr::convertStrToDouble(str2.c_str());
				}
				break;
			case 22:
				if(formatType == 0){
					data->m_sellVolume2 = FCStr::convertStrToInt(str2.c_str());
				}
				break;
			case 23:
				if(formatType == 0){
					data->m_sellPrice2 = FCStr::convertStrToDouble(str2.c_str());
				}
				break;
			case 24:
				if(formatType == 0){
					data->m_sellVolume3 = FCStr::convertStrToInt(str2.c_str());
				}
				break;
			case 25:
				if(formatType == 0){
					data->m_sellPrice3 = FCStr::convertStrToDouble(str2.c_str());
				}
				break;
			case 26:
				if(formatType == 0){
					data->m_sellVolume4 = FCStr::convertStrToInt(str2.c_str());
				}
				break;
			case 27:
				if(formatType == 0){
					data->m_sellPrice4 = FCStr::convertStrToDouble(str2.c_str());
				}
				break;
			case 28:
				if(formatType == 0){
					data->m_sellVolume5 = FCStr::convertStrToInt(str2.c_str());
				}
				break;
			case 29:
				if(formatType == 0){
					data->m_sellPrice5 = FCStr::convertStrToDouble(str2.c_str());
				}
				break;
			case 30:{
					ArrayList<String> dateStrs = FCStr::split(str2, L"-");
					if(dateStrs.size() >= 3){
						year = FCStr::convertStrToInt(dateStrs.get(0).c_str());
						month = FCStr::convertStrToInt(dateStrs.get(1).c_str());
						day = FCStr::convertStrToInt(dateStrs.get(2).c_str());
					}
					dateStrs.clear();
					break;
				}
			case 31:{
					ArrayList<String> hourStrs = FCStr::split(str2, L":");
					if(hourStrs.size() >= 3){
						hour = FCStr::convertStrToInt(hourStrs.get(0).c_str());
						minute = FCStr::convertStrToInt(hourStrs.get(1).c_str());
						second = FCStr::convertStrToInt(hourStrs.get(2).c_str());
					}
					hourStrs.clear();
					break;
				}
			}
		}
		data->m_date = FCStr::getDateNum(year, month, day, hour, minute, second, 0);
		if(data->m_close != 0){
			if (data->m_open == 0){
				data->m_open = data->m_close;
			}
			if (data->m_high == 0){
				data->m_high = data->m_close;
			}
			if (data->m_low == 0){
				data->m_low = data->m_low;
			}
		}
		return 1;
	}

	int getLatestDatasBySinaStr(String str, int formatType, vector<SecurityLatestData> *datas){
		ArrayList<String> strs = FCStr::split(str, L";\n");
		int strLen = (int)strs.size();
		for(int i = 0; i < strLen; i++){
			SecurityLatestData latestData;
            String dataStr = strs.get(i);
            getLatestDataBySinaStr(strs.get(i), formatType, &latestData);
			if(latestData.m_date > 0){
				datas->push_back(latestData);
			}
		}
		strs.clear();
		return 1;
	}

	String getSinaLatestDatasStrByCodes(string codes){
		String wCode = FCStr::stringTowstring(codes);
		ArrayList<String> strs = FCStr::split(wCode, L",");
		int strLen = (int)strs.size();
		vector<string> sinaCodes;
        for (int i = 0; i < strLen; i++){
            String postCode = strs.get(i);
			sinaCodes.push_back(FCStr::wstringTostring(postCode));
        }
        string requestCode = "";
        int sinaCodesSize = (int)sinaCodes.size();
        for (int i = 0; i < sinaCodesSize; i++){
            String postCode = strs.get(i);
			requestCode += FCStrEx::convertDBCodeToSinaCode(FCStr::wstringTostring(postCode));
            if (i != strLen - 1){
                requestCode += ",";
            }
        }
        string result = "";
        if (sinaCodesSize > 0){
            string url = "http://hq.sinajs.cn/list=" + requestCode;
			result = HttpGetService::get(url);
        }
		String wResult = FCStr::stringTowstring(result);
		strs.clear();
		return wResult;
	}


/////////////////////////////////////////////////////////////////////////////////////////////////

	SecurityHistoryData::SecurityHistoryData(){
		m_datas = 0;
		m_datasMa = 0;
		m_datasRate = 0;
		m_datasSize = 0;
		m_oldDatasSize = 0;
		m_security = 0;
		m_startIndex = -1;
	}

	SecurityHistoryData::~SecurityHistoryData(){
		if(m_security){
			delete m_security;
			m_security = 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	WorkDataInfoEx::WorkDataInfoEx(){
		m_left = 0;
	}

	WorkDataInfoEx::~WorkDataInfoEx(){
		m_left = 0;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	LikeDataInfo::LikeDataInfo(){
		m_diffRange = 0;
		m_leftCode = L"";
        m_leftStartDate = 0;
        m_leftStopDate = 0;
        m_rightCode = L"";
        m_rightStartDate = 0;
        m_rightStopDate = 0;
        m_score = 0;
	}

	LikeDataInfo::~LikeDataInfo(){
	}

	bool ALikeService::likeDataInfoScore1Compare(LikeDataInfo x, LikeDataInfo y){
		return x.m_score > y.m_score;  
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	SandBoxInfo::SandBoxInfo(){
		m_rangeMax = 0.051;
		m_rangeMin = 0.05;
		m_swingDown = 0;
		m_swingUp = 0;
	}

	SandBoxInfo::~SandBoxInfo(){
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ALikeService::ALikeService(){
		m_completed = true;
		m_curCount = 0;
		m_n = 5;
		m_m = 40;
		m_maxCount = 10000;
		m_maxScore = 100;
		sandBoxInfo = new SandBoxInfo;
		loadDatas();
		loadDatas2(0);
	}

	ALikeService::~ALikeService(){
		map<String, SecurityHistoryData*>::iterator sIter = m_historyDatas.begin();
		for(; sIter != m_historyDatas.end(); ++sIter){
			delete sIter->second;
		}
		m_historyDatas.clear();
	}

	bool ALikeService::isCompleted(){
		return m_completed;
	}

	int ALikeService::getCurCount(){
		return m_curCount;
	}

	int ALikeService::getN(){
		return m_n;
	}

	void ALikeService::setN(int n){
		m_n = n;
	}

	int ALikeService::getM(){
		return m_m;
	}

	void ALikeService::setM(int m){
		m_m = m;
	}

	int ALikeService::getMaxCount(){
		return m_maxCount;
	}

	void ALikeService::setMaxCount(int maxCount){
		m_maxCount = maxCount;
	}

	int ALikeService::getMaxScore(){
		return m_maxScore;
	}

	void ALikeService::setMaxScore(int maxScore){
		m_maxScore = maxScore;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	inline int checkLike(SecurityHistoryData *left, SecurityHistoryData *right, int startIndex, int m, int n, vector<LikeDataInfo> *likeInfos, double rate1, double rate2, double rate3, double maxScore){
		double filterScore = maxScore;
		int result = 0;
		int leftSize = (int)left->m_datasSize;
        int rightSize = (int)right->m_datasSize;
		if(m > leftSize){
			m = leftSize;
			filterScore /= 2;
			rate1 = 0.1;
			rate2 = 0.1;
		}
		if(m > rightSize){
			m = rightSize;
		}
		int leftStart = startIndex;
		if(leftStart == -1){
			leftStart = leftSize - m;
			if(leftStart < 0){
				leftStart = 0;
			}
		}
		int lLast = leftSize - 1, rCount = rightSize - m;
		if(rCount < 0){
			rCount = 0;
		}
		int likeSize = (int)likeInfos->size();
		SecurityData *leftStartData = 0;
		double lMa1_1 = 0;
		double lRate1 = 0;
		if(rCount > 0){
			leftStartData = left->m_datas[leftStart];
			lMa1_1 = left->m_datasMa[leftStart];
			lRate1 = left->m_datasRate[leftSize - 1];
		}
        for (int y = 0; y < rCount; y++){
			if(abs(lRate1 - right->m_datasRate[y + m]) < rate1){
				int score = 0;	
				double rMa2_1 = right->m_datasMa[y];
				for (int n = 0; n < m; n++){
					double diffRange = (left->m_datasMa[leftStart + n] - lMa1_1) / lMa1_1 - (right->m_datasMa[y + n] - rMa2_1) / rMa2_1;
					if(diffRange < 0){
						diffRange = -diffRange;
					}
					if(diffRange > rate2){
						score = 0;
						y += n + 1;
						break;
					}
					score += (rate2 - diffRange) / rate3;
				}
				if (score > filterScore){
					LikeDataInfo likeDataInfo;
					likeDataInfo.m_leftCode = left->m_security->m_code;
					likeDataInfo.m_leftStartDate = leftStartData->m_date;
					likeDataInfo.m_leftStopDate = left->m_datas[leftStart + m - 1]->m_date;
					likeDataInfo.m_rightCode = right->m_security->m_code;
					likeDataInfo.m_rightStartDate = right->m_datas[y]->m_date;
					likeDataInfo.m_rightStopDate = right->m_datas[y + m - 1]->m_date;
					likeDataInfo.m_score = score;
					likeInfos->push_back(likeDataInfo);
					likeSize = (int)likeInfos->size();
					result += 1;
				}
			}
        }
		return result;
	}

	inline int checkSandBox(SecurityHistoryData *right, int m, vector<LikeDataInfo> *likeInfos, double rangeMax, double rangeMin, double swingUp, double swingDown){
		double filterScore = 1000;
		int result = 0;
        int rightSize = (int)right->m_datasSize;
		if(m > rightSize){
			m = rightSize;
		}
		int rCount = rightSize - m;
		if(rCount < 0){
			rCount = 0;
		}
        for (int y = 0; y < rCount; y++){
			int rLast = y + m - 1;
			if(rLast > rCount){
				break;
			}
			double diffRange = 0;
			double sOpen = right->m_datas[y]->m_open;
			if(sOpen != 0){
				diffRange = (right->m_datas[rLast]->m_close - sOpen) / sOpen;
			}
			if(diffRange >= rangeMin && diffRange <= rangeMax){
				double nLow = 0, nHigh = 0;
				int nLowState = 0, nHighState = 0;
				bool isMatch = true;
				for (int n = 0; n < m; n++){
					SecurityData *nData = right->m_datas[y + n];
					if(nLowState == 0 || nLow > nData->m_low){
						nLow = nData->m_low;
						nLowState = 1;
					}
					if(nHighState == 0 || nHigh < nData->m_high){
						nHigh = nData->m_high;
						nHighState = 1;
					}
					double lowRange = abs((nLow - sOpen) / sOpen);
					double highRange = abs((nHigh - sOpen) / sOpen);
					if(lowRange > swingDown || highRange > swingUp){
						isMatch = false;
						break;
					}						
				}
				if(isMatch && diffRange != 0.0){
					LikeDataInfo likeDataInfo;
					likeDataInfo.m_leftCode = L"LEFT";
					likeDataInfo.m_rightCode = right->m_security->m_code;
					likeDataInfo.m_rightStartDate = right->m_datas[y]->m_date;
					likeDataInfo.m_rightStopDate = right->m_datas[y + m - 1]->m_date;
					likeDataInfo.m_diffRange = diffRange;
					likeInfos->push_back(likeDataInfo);
					result += 1;
				}
			}
        }
		return result;
	}

	void ALikeService::onWorkQuit(WorkDataInfo *dataInfo){
		delete dataInfo;
		dataInfo = 0;
	}

	void ALikeService::onWorkStart(WorkDataInfo *dataInfo){
		
	}

	int ALikeService::onWorking(WorkDataInfo *dataInfo){
		WorkDataInfoEx *workDataInfo = dynamic_cast<WorkDataInfoEx*>(dataInfo);
        int securitiesSize = (int)m_historyDatas.size();
        SecurityHistoryData *left = workDataInfo->m_left;
		vector<LikeDataInfo> likeDataInfos;
		DWORD d1 = ::GetTickCount();
		start(left->m_security->m_code, &likeDataInfos);
		m_lock.lock();
		m_likeDataInfos[left->m_security->m_code] = likeDataInfos;
		m_lock.unLock();
		string sCode = FCStr::wstringTostring(left->m_security->m_code);
		DWORD d2 = ::GetTickCount();
		char sz[1024] ={0};
		sprintf_s(sz, 1023, "%s,%d,%d\r\n", sCode.c_str(), (int)likeDataInfos.size(), (int)(d2 - d1));
		string sPath = DataCenter::getAppPath() + "\\my.txt";
		FCFile::append(sPath.c_str(), sz);
		if((int)likeDataInfos.size() == 0){
			sprintf_s(sz, 1023, "%s,%d,%d,%s\r\n", sCode.c_str(), (int)likeDataInfos.size(), (int)(d2 - d1), "ERROR");
			FCFile::append(sPath.c_str(), sz);
		}
		likeDataInfos.clear();
		string path = DataCenter::getAppPath() + "\\temp\\ContractList.txt";
		sCode += "\n";
		FCFile::append(path.c_str(), sCode.c_str());
		if(m_curCount > 0){
			m_curCount--;
			if(m_curCount == 0){
				m_completed = true;
				string path = DataCenter::getAppPath() + "\\temp\\StopContract.txt";
				FCFile::write(path.c_str(), "");
				m_curCount = -1;
			}
		}
        return 0;
	}

	void ALikeService::start(){
		string sPath = DataCenter::getAppPath() + "\\my.txt";
		FCFile::removeFile(sPath.c_str());
		string path = DataCenter::getAppPath() + "\\temp\\StartContract.txt";
		FCFile::write(path.c_str(), "");
		path = DataCenter::getAppPath() + "\\temp\\ContractList.txt";
		FCFile::write(path.c_str(), "");
		BaseWork::start();

		m_completed = false;
        int m_historyDatasSize = (int)m_historyDatas.size();
        vector<WorkDataInfo*> dataInfos;
        int i = 0;
        map<String, SecurityHistoryData*>::iterator sIter2 = m_historyDatas.begin();
		for(; sIter2 != m_historyDatas.end(); ++sIter2){
			SecurityHistoryData *left = sIter2->second;
            WorkDataInfoEx *workDataInfoEx = new WorkDataInfoEx;
            workDataInfoEx->m_left = left;
            workDataInfoEx->m_id = i;
            dataInfos.push_back(workDataInfoEx);
            i++;
		}
		m_curCount = (int)dataInfos.size();
        m_workThread->startWork(&dataInfos);
	}

	void ALikeService::start(const String& code, vector<LikeDataInfo> *likeDataInfos){
		likeDataInfos->clear();
		map<String, SecurityHistoryData*>::iterator sIter = m_historyDatas.find(code);
		if(sIter != m_historyDatas.end()){
			SecurityHistoryData *left = sIter->second;
			double rate1 = 0.05, rate2 = 0.05, rate3 = 0.001;
			map<String, SecurityHistoryData*>::iterator sIter = m_historyDatas.begin();
			int m_historyDatasSize = (int)m_historyDatas.size();
			int totalCount = 0;
			for(; sIter != m_historyDatas.end(); ++sIter){
				if (left != sIter->second){
					totalCount += checkLike(left, sIter->second, left->m_startIndex, m_m, m_n, likeDataInfos, rate1, rate2, rate3, m_maxScore);	
					//这里要用非线性函数
					if(totalCount > 100000){
						break;
					}
					else if(totalCount > 50000){
						rate1 = 0.03;
						rate2 = 0.03;
					}
					else if(totalCount > 30000){
						rate1 = 0.035;
						rate2 = 0.035;
					}
					else if(totalCount > 10000){
						rate1 = 0.04;
						rate2 = 0.04;
					}
					else if(totalCount > 5000){
						rate1 = 0.045;
						rate2 = 0.045;
					}
				}
			}
			if(totalCount < 10){
				rate1 = 0.1;
				rate2 = 0.1;
				likeDataInfos->clear();
				totalCount = 0;
				sIter = m_historyDatas.begin();
				for(; sIter != m_historyDatas.end(); ++sIter){
					if (left != sIter->second){
						totalCount += checkLike(left, sIter->second, left->m_startIndex, m_m, m_n, likeDataInfos, rate1, rate2, rate3, m_maxScore);
						if(totalCount > 100000){
							break;
						}
						else if(totalCount > 50000){
							rate1 = 0.06;
							rate2 = 0.06;
						}
						else if(totalCount > 30000){
							rate1 = 0.07;
							rate2 = 0.07;
						}
						else if(totalCount > 10000){
							rate1 = 0.08;
							rate2 = 0.08;
						}
						else if(totalCount > 5000){
							rate1 = 0.085;
							rate2 = 0.085;
						}
						else if(totalCount >1000){
							rate1 = 0.09;
							rate2 = 0.09;
						}
					}
				}
			}
		}
		//第二轮打分
		int likeDataInfosSize = (int)likeDataInfos->size();
		if(likeDataInfosSize > 0){
			int lSize = likeDataInfosSize;
			vector<int> likeIndexs;
			for(int i = 0; i < lSize; i++){
				likeIndexs.push_back(i);
			}
			while(lSize > 150){
				int scoreSum = 0;
				for(int i = 0; i < lSize; i++){
					LikeDataInfo &likeDataInfoCache = (*likeDataInfos)[likeIndexs[i]];
					scoreSum += likeDataInfoCache.m_score;
				}
				int avgScore = scoreSum / lSize;
				if(lSize > 1000){
					avgScore *= 1.1;
				}
				vector<int> newLikeIndexs;
				for (int i = 0; i < lSize; i++){
					LikeDataInfo &likeDataInfoCache = (*likeDataInfos)[likeIndexs[i]];
					if(likeDataInfoCache.m_score > avgScore){
						newLikeIndexs.push_back(likeIndexs[i]);
					}
					else{
						likeDataInfoCache.m_score = -1000000000;
					}
				}
				likeIndexs = newLikeIndexs;
				lSize = (int)likeIndexs.size();
			}
			vector<LikeDataInfo> newLikeDataInfo;
			for (int i = 0; i < lSize; i++){
				newLikeDataInfo.push_back((*likeDataInfos)[likeIndexs[i]]);
			}
			likeDataInfos->clear();
			for (int i = 0; i < lSize; i++){
				LikeDataInfo &likeDataInfoCache = newLikeDataInfo[i];
				SecurityHistoryData *left = m_historyDatas[likeDataInfoCache.m_leftCode];
				SecurityHistoryData *right = m_historyDatas[likeDataInfoCache.m_rightCode];
				vector<SecurityData*> leftDatas;
				vector<SecurityData*> rightDatas;
				int leftDatasSize = (int)left->m_datasSize;
				int rightDatasSize = (int)right->m_datasSize;
				for(int j = 0; j < leftDatasSize; j++){
					SecurityData *data = left->m_datas[j];
					if (data->m_date >= likeDataInfoCache.m_leftStartDate && data->m_date <= likeDataInfoCache.m_leftStopDate){
						leftDatas.push_back(data);
					}
				}
				for(int j = 0; j < rightDatasSize; j++){
					SecurityData *data = right->m_datas[j];
					if (data->m_date >= likeDataInfoCache.m_rightStartDate && data->m_date <= likeDataInfoCache.m_rightStopDate){
						rightDatas.push_back(data);
					}
				}
				leftDatasSize = (int)leftDatas.size();
				rightDatasSize = (int)rightDatas.size();
				int minSize = min(leftDatasSize, rightDatasSize);
				for(int j = 0; j < minSize; j++){
					//判断均线是否偏离严重
					double maRange1 = (left->m_datasMa[j] - left->m_datasMa[0]) / left->m_datasMa[0];
					double maRange2 = (right->m_datasMa[j] - right->m_datasMa[0]) / right->m_datasMa[0];
					double maRangeDiff = abs(maRange1 - maRange2);
					if(maRangeDiff > 0.03 && maRangeDiff < 1){
						likeDataInfoCache.m_score -= maRangeDiff / 0.001;
					}
				}
				double absRate = abs(left->m_datasRate[minSize - 1] - right->m_datasRate[minSize - 1]);
				if(absRate > 0 && absRate < 1){
					likeDataInfoCache.m_score += absRate / 0.001;
				}
				leftDatas.clear();
				rightDatas.clear();
			}
			sort(newLikeDataInfo.begin(), newLikeDataInfo.end(), likeDataInfoScore1Compare);
			likeDataInfos->clear();
			for (int i = 0; i < lSize; i++){
				likeDataInfos->push_back(newLikeDataInfo[i]);
			}
		}
	}

	String ALikeService::startSandBox(int m, vector<LikeDataInfo> *likeDataInfos){
		String str;
		int count = 0;
		map<String, SecurityHistoryData*>::iterator sIter = m_historyDatas.begin();
		for(; sIter != m_historyDatas.end(); ++sIter){
			count += checkSandBox(sIter->second, m, likeDataInfos, sandBoxInfo->m_rangeMax, sandBoxInfo->m_rangeMin, sandBoxInfo->m_swingUp, sandBoxInfo->m_swingDown);
		}
		int likeDataInfosSize = (int)likeDataInfos->size();
		for(int i = 0; i < likeDataInfosSize; i++){
			LikeDataInfo &likeDataInfo = (*likeDataInfos)[i];
			vector<SecurityData*> datas;
			str += likeDataInfo.m_rightCode + L"\r\n";
			int datasSize = m_historyDatas[likeDataInfo.m_rightCode]->m_datasSize;
			for(int j = 0; j < datasSize; j++){
				SecurityData *data = m_historyDatas[likeDataInfo.m_rightCode]->m_datas[j];
				if(data->m_date >= likeDataInfo.m_rightStartDate && data->m_date <= likeDataInfo.m_rightStopDate){
					datas.push_back(data);
				}
			}
			datasSize = (int)datas.size();
			for(int j = 0; j < datasSize; j++){
				SecurityData *data = datas[j];
				wchar_t sz[1024] ={0};
				_stprintf_s(sz, 1023, L"%f,%f,%f,%f,%f,%f", data->m_open, data->m_high, data->m_low, data->m_close, data->m_volume, data->m_amount);
				str += sz;
				str += L"\r\n";
			}
			if(i != likeDataInfosSize - 1){
				str += L"END\r\n";
			}
		}
		return str;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	bool ALikeService::getData(const String& code, vector<LikeDataInfo> *likeDataInfos){
		map<String, vector<LikeDataInfo>>::iterator sIter = m_likeDataInfos.find(code);
		if(sIter != m_likeDataInfos.end()){
			*likeDataInfos = sIter->second;
			return true;
		}
		return false;
	}

	void ALikeService::loadDatas(){
		vector<Security*> securities;
        ArrayList<string> files;
		string dir =  DataCenter::getAppPath() + "\\day";
		FCFile::getFiles(dir.c_str(), &files);
        int filesSize = (int)files.size();
        for (int i = 0; i < filesSize; i++){
            Security *security = new Security;
			string sCode = FCStr::replace(files.get(i).substr((int)files.get(i).rfind("\\") + 1), ".txt", "");
			security->m_code = FCStr::stringTowstring(sCode.substr(2) + "." + sCode.substr(0, 2));
			securities.push_back(security);
			if ((int)securities.size() >= m_maxCount){
				break;
			}
        }
		files.clear();
        dir = DataCenter::getAppPath() + "\\day";
        int securitiesSize = (int)securities.size();
        for (int i = 0; i < securitiesSize; i++){
            Security *security = securities[i];
            string path = dir + "\\";
            SecurityHistoryData *securityHistoryData = new SecurityHistoryData();
			string sCode = FCStr::wstringTostring(security->m_code);
			securityHistoryData->m_datas = readHistoryDatasFromFile(sCode, &securityHistoryData->m_datasSize);
			//StockService::getHistoryDatasByTdxStr2(sCode, path + FCStrEx::convertDBCodeToFileName(sCode), );
			int datasSize = (int)securityHistoryData->m_datasSize;
			securityHistoryData->m_oldDatasSize = datasSize;
			securityHistoryData->m_datasMa = new double[datasSize + 1];
			securityHistoryData->m_datasRate = new double[datasSize + 1];
			if(datasSize > 0){
				securityHistoryData->m_security = security;
				m_historyDatas[security->m_code] = securityHistoryData;
			}
			else{
				delete security;
				security = 0;
			}
        }
	}

	void ALikeService::loadDatas2(int startIndex){
		map<String, SecurityHistoryData*>::iterator sIter = m_historyDatas.begin();
		for(; sIter != m_historyDatas.end(); ++sIter){
			SecurityHistoryData *data = sIter->second;
			int num1 = m_n, num2 = m_m;
			int datasSize = (int)data->m_datasSize;
			for (int i = startIndex; i < datasSize; i++){
				SecurityData *sData = data->m_datas[i];
				double sum1 = 0;
				int n = num1;
				int sIndex = i - num1;
				if (sIndex < 0){
					n = num1 + sIndex + 1;
					sIndex = 0;
				}
				double max = 0, min = 0;
				for(int j = sIndex; j <= i; j++){
					if(j == sIndex){
						max = data->m_datas[j]->m_high;
						min = data->m_datas[j]->m_low;
					}
					else{
						if(max < data->m_datas[j]->m_high){
							max = data->m_datas[j]->m_high;
						}
						if(min > data->m_datas[j]->m_low){
							min = data->m_datas[j]->m_low;
						}
					}
					sum1 += data->m_datas[j]->m_close;
				}
				int sIndex2 = i - num2;
				if (sIndex2 < 0){
					sIndex2 = 0;
				}
				data->m_datasMa[i] = sum1 / n;
				if(data->m_datas[sIndex2]->m_close != 0){
					data->m_datasRate[i] = (data->m_datas[i]->m_close - data->m_datas[sIndex2]->m_open) / abs(data->m_datas[sIndex2]->m_open);
				}
			}
		}
	}

	void ALikeService::replaceNewData(const String &code, SecurityLatestData *latestData){
		int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0, ms = 0;
		FCStr::getDateByNum(latestData->m_date, &year, &month, &day, &hour, &minute, &second, &ms);
		double newData = FCStr::getDateNum(year, month, day, hour, minute, second, ms);
		map<String, SecurityHistoryData*>::iterator sIter = m_historyDatas.find(code);
		if(sIter != m_historyDatas.end()){
			SecurityHistoryData *data = sIter->second;
			SecurityData *securityData = 0;
			if(data->m_oldDatasSize == 0){
				securityData = data->m_datas[0];
				data->m_datasSize = 1;
			}
			else{
				if(newData != data->m_datas[data->m_oldDatasSize - 1]->m_date){
					securityData = data->m_datas[data->m_oldDatasSize];
					data->m_datasSize = data->m_oldDatasSize + 1;
				}
				else{
					securityData = data->m_datas[data->m_oldDatasSize - 1];
				}
			}
			securityData->m_date = newData;
			securityData->m_close = latestData->m_close;
			securityData->m_high = latestData->m_high;
			securityData->m_low = latestData->m_low;
			securityData->m_open = latestData->m_open;
			securityData->m_volume = latestData->m_volume;
			securityData->m_amount = latestData->m_amount;
			int startIndex = data->m_oldDatasSize - m_m;
			if(startIndex < 0){
				startIndex = 0;
			}
			loadDatas2(startIndex);
		}
	}
}