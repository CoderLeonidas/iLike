#include "..\\..\\stdafx.h"
#include "..\\..\\CStr.h"
#include "MultiThreadWork.h"

namespace FaceCat{
	DWORD WINAPI multiThreadStartWork(LPVOID lpParam){
		LPVOID *parameters = (LPVOID*)lpParam;
		MultiThreadWork *pool = (MultiThreadWork*)parameters[0];
		int id = (int)(parameters[1]);
		while(1){
			pool->onWork(id);
			::Sleep(1);
		}
		return 0;
	}

	MultiThreadWork::MultiThreadWork(){
		m_isRunning = false;
		m_quitEvent = 0;
		m_quitEventInvoke = 0;
		m_startEvent = 0;
		m_startEventInvoke = 0;
		m_workEvent = 0;
		m_workEventInvoke = 0;
	}

	MultiThreadWork::~MultiThreadWork(){
		map<int, vector<WorkDataInfo*>*>::iterator sIter = m_dataInfos.begin();
		for(; sIter != m_dataInfos.end(); ++sIter){
			vector<WorkDataInfo*> *dataInfos = sIter->second;
			vector<WorkDataInfo*>::iterator sIter2 = dataInfos->begin();
			for(; sIter2 != dataInfos->end(); ++sIter2){
				delete *sIter2;
			}
			dataInfos->clear();
			delete dataInfos;
		}
		m_dataInfos.clear();
        m_lock.lock();
		vector<WorkDataInfo*>::iterator sIter3 = m_messages.begin();
		for(; sIter3 != m_messages.end(); ++sIter3){
			delete *sIter3;
		}
		m_messages.clear();
		m_lock.unLock();
        m_quitEvent = 0;
		m_quitEventInvoke = 0;
        m_startEvent = 0;
		m_startEventInvoke = 0;
        m_lock.lock();
		vector<WorkDataInfo*>::iterator sIter4 = m_stopPushDatas.begin();
		for(; sIter4 != m_stopPushDatas.end(); ++sIter4){
			delete *sIter4;
		}
        m_stopPushDatas.clear();
        m_lock.unLock();
        m_workEvent = 0;
		m_workEventInvoke = 0;
	}

	bool MultiThreadWork::isRunning(){
		return m_isRunning;
	}

	void MultiThreadWork::setRunning(bool isRunning){
		m_isRunning = isRunning;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void MultiThreadWork::onWork(int id){
		m_lock.lock();
        int messagesSize = (int)m_messages.size();
        if (messagesSize > 0){
            for (int i = 0; i < messagesSize; i++){
                if (m_startEvent){
                    m_startEvent(m_messages[i], m_startEventInvoke);
                    m_dataInfos[id]->push_back(m_messages[i]);
					m_messages.erase(m_messages.begin() + i);
                    break;
                }
            }
        }
        m_lock.unLock();
        if (m_workEvent){
            vector<WorkDataInfo*> *dataInfos = m_dataInfos[id];
            int dataInfosSize = (int)dataInfos->size();
            vector<WorkDataInfo*> stopPushDatas;
            int stopPushDatasSize = (int)m_stopPushDatas.size();
            if (stopPushDatasSize > 0){
                m_lock.lock();
                stopPushDatasSize = (int)m_stopPushDatas.size();
                for (int i = 0; i < stopPushDatasSize; i++){
                    stopPushDatas.push_back(m_stopPushDatas[i]);
                }
                m_lock.unLock();
            }
            for (int i = 0; i < dataInfosSize; i++){
                WorkDataInfo *pushDataInfo = (*dataInfos)[i];
                pushDataInfo->m_threadID = id;
                int state = 0;
                if (stopPushDatasSize > 0){
                    for (int j = 0; j < stopPushDatasSize; j++){
                        WorkDataInfo *reqDataInfo = stopPushDatas[j];
                        if (reqDataInfo->m_id == pushDataInfo->m_id){
                            m_lock.lock();
                            int spdSize = (int)m_stopPushDatas.size();
                            for (int s = 0; s < spdSize; s++){
                                if (m_stopPushDatas[s]->m_id == reqDataInfo->m_id){
									m_stopPushDatas.erase(m_stopPushDatas.begin() + s);
									m_lock.unLock();
                                    break;
                                }
                            }
                            m_lock.unLock();
                            state = -1;
                        }
                    }
                }
                if (state == 0){
                     state = m_workEvent(pushDataInfo, m_workEventInvoke);
                }
                if (state <= 0){
                    if (m_quitEvent){
                        m_quitEvent(pushDataInfo, m_quitEventInvoke);
                    }
					dataInfos->erase(dataInfos->begin() + i);
                    i--;
                    dataInfosSize--;
                }
            }
        }
	}

	int MultiThreadWork::quitWork(WorkDataInfo *reqInfo){
		m_lock.lock();
        m_stopPushDatas.push_back(reqInfo);
        m_lock.unLock();
		return 0;
	}

	void MultiThreadWork::startWork(WorkDataInfo *dataInfo){
		m_lock.lock();
        m_messages.push_back(dataInfo);
        m_lock.unLock();
	}

	void MultiThreadWork::startWork(vector<WorkDataInfo*> *dataInfos){
		m_lock.lock();
		vector<WorkDataInfo*>::iterator sIter = dataInfos->begin();
		for(; sIter != dataInfos->end(); ++sIter){
			m_messages.push_back(*sIter);
		}
        m_lock.unLock();
	}

	void MultiThreadWork::registerQuitEvent(QuitWorkEventHandler quitEvent, void *pInvoke){
		m_quitEvent = quitEvent;
		m_quitEventInvoke = pInvoke;
	}

	void MultiThreadWork::registerRecvEvent(StartWorkEventHandler recvEvent, void *pInvoke){
		m_startEvent = recvEvent;
		m_startEventInvoke = pInvoke;
	}

	void MultiThreadWork::registerWorkEvent(WorkingEventHandler workEvent, void *pInvoke){
		m_workEvent = workEvent;
		m_workEventInvoke = pInvoke;
	}

	void MultiThreadWork::start(int size){
		if(!m_isRunning){
			m_isRunning = true;
			for(int i = 0; i < size; i++){
				vector<WorkDataInfo*> *datas = new vector<WorkDataInfo*>;
				m_dataInfos[i] = datas;
				LPVOID *parameters = new LPVOID[2];
				parameters[0] = this;
				parameters[1] = (LPVOID)i;
				HANDLE hThread = ::CreateThread(0, 0, multiThreadStartWork, (LPVOID)parameters, 0, NULL);
				m_threads.push_back(hThread);
			}
		}
	}

	void MultiThreadWork::stop(){
		m_isRunning = false;
        int threadsSize = (int)m_threads.size();
        for (int i = 0; i < threadsSize; i++){
			::TerminateThread(m_threads[i], 0);
        }
		m_threads.clear();
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void BaseWork::workQuit(WorkDataInfo *dataInfo, void *pInvoke){
		BaseWork *baseWork = (BaseWork*)pInvoke;
		baseWork->onWorkQuit(dataInfo);
	}

	void BaseWork::workStart(WorkDataInfo *dataInfo, void *pInvoke){
		BaseWork *baseWork = (BaseWork*)pInvoke;
		baseWork->onWorkStart(dataInfo);
	}

	int BaseWork::working(WorkDataInfo *dataInfo, void *pInvoke){
		BaseWork *baseWork = (BaseWork*)pInvoke;
		return baseWork->onWorking(dataInfo);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	BaseWork::BaseWork(){
		m_threads = 10;
		m_workThread = new MultiThreadWork;
        m_workThread->registerQuitEvent(&workQuit, this);
        m_workThread->registerRecvEvent(&workStart, this);
        m_workThread->registerWorkEvent(&working, this);
	}

	BaseWork::~BaseWork(){
		if(m_workThread){
			delete m_workThread;
			m_workThread = 0;
		}
	}

	bool BaseWork::isRunning(){
		return m_workThread->isRunning();
	}

	int BaseWork::getThreads(){
		return m_threads;
	}

	void BaseWork::setThreads(int threads){
		m_threads = threads;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void BaseWork::onWorkQuit(WorkDataInfo *dataInfo){
	}

	void BaseWork::onWorkStart(WorkDataInfo *dataInfo){
	}

	int BaseWork::onWorking(WorkDataInfo *dataInfo){
		return 1;
	}

	void BaseWork::start(){
		m_workThread->start(m_threads);
	}

	void BaseWork::stop(){
		m_workThread->stop();
	}
}