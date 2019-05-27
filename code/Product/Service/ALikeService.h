/*��������èFaceCat��� v1.0 https://github.com/FaceCat007/facecat.git
 1.��ʼ��-�󶴳���Ա-�Ϻ����׿Ƽ���ʼ��-����KOL-�յ� (΢�ź�:suade1984);
 2.���ϴ�ʼ��-�Ϻ����׿Ƽ���ʼ��-Ԭ����(΢�ź�:wx627378127);
 3.���ϴ�ʼ��-Ф����(΢�ź�:xiaotianlong_luu);
 4.���Ͽ�����-������(΢�ź�:chenxiaoyangzxy)������-���(΢�ź�:cnnic_zhu);
 5.�ó���ԴЭ��ΪBSD����ӭ�����ǵĴ�ҵ����и���֧�֣���ӭ���࿪���߼��롣
 */


#ifndef __ALIKESERVICE_H__
#define __ALIKESERVICE_H__
#pragma once
#include "..\\..\\stdafx.h"
#include <time.h>
#include "Security.h"
#include "MultiThreadWork.h"

namespace FaceCat{
	class SecurityHistoryData{
	public:
		SecurityData **m_datas;
		double *m_datasMa;
		double *m_datasRate;
		int m_datasSize;
		int m_oldDatasSize;
		Security *m_security;
		int m_startIndex;
	public:
		SecurityHistoryData();
		virtual ~SecurityHistoryData();
	};

	class WorkDataInfoEx : public WorkDataInfo{
	public:
		SecurityHistoryData *m_left;
	public:
		WorkDataInfoEx();
		virtual ~WorkDataInfoEx();
	};

	class LikeDataInfo{
	public:
		double m_diffRange;
        String m_leftCode;
        double m_leftStartDate;
        double m_leftStopDate;
        String m_rightCode;
        double m_rightStartDate;
        double m_rightStopDate;
        int m_score;
	public:
		LikeDataInfo();
		virtual ~LikeDataInfo();
	};

	class SandBoxInfo{
	public:
		double m_rangeMax;
		double m_rangeMin;
		double m_swingDown;
		double m_swingUp;
	public:
		SandBoxInfo();
		virtual ~SandBoxInfo();
	};

	class ALikeService : public BaseWork{
	public:
		bool m_completed;
		int m_curCount;
		FCLock m_lock;
		int m_n;
		int m_m;
		int m_maxCount;
		int m_maxScore;
		SandBoxInfo *sandBoxInfo;
	public:
		map<String, SecurityHistoryData*> m_historyDatas;
		map<String, vector<LikeDataInfo>> m_likeDataInfos;
	public:
		static bool likeDataInfoScore1Compare(LikeDataInfo x, LikeDataInfo y);
	public:
		ALikeService();
		virtual ~ALikeService();
		bool isCompleted();
		int getCurCount();
		int getN();
		void setN(int n);
		int getM();
		void setM(int m);
		int getMaxCount();
		void setMaxCount(int maxCount);
		int getMaxScore();
		void setMaxScore(int maxScore);
	public:
		virtual void onWorkQuit(WorkDataInfo *dataInfo);
		virtual void onWorkStart(WorkDataInfo *dataInfo);
		virtual int onWorking(WorkDataInfo *dataInfo);
		virtual void start();
		virtual void start(const String& code, vector<LikeDataInfo> *likeDataInfos);
		virtual String startSandBox(int m, vector<LikeDataInfo> *likeDataInfos);
	public:
		bool getData(const String& code, vector<LikeDataInfo> *likeDataInfos);
		void loadDatas();
		void loadDatas2(int startIndex);
		void replaceNewData(const String &code, SecurityLatestData *latestData);
	};
}

#endif