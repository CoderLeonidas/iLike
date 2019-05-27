/*��������èFaceCat��� v1.0 https://github.com/FaceCat007/facecat.git
 1.��ʼ��-�󶴳���Ա-�Ϻ����׿Ƽ���ʼ��-����KOL-�յ� (΢�ź�:suade1984);
 2.���ϴ�ʼ��-�Ϻ����׿Ƽ���ʼ��-Ԭ����(΢�ź�:wx627378127);
 3.���ϴ�ʼ��-Ф����(΢�ź�:xiaotianlong_luu);
 4.���Ͽ�����-������(΢�ź�:chenxiaoyangzxy)������-���(΢�ź�:cnnic_zhu);
 5.�ó���ԴЭ��ΪBSD����ӭ�����ǵĴ�ҵ����и���֧�֣���ӭ���࿪���߼��롣
 */

#ifndef __CUPDATE_H__
#define __CUPDATE_H__
#pragma once
#include "stdafx.h"
#include "CurlHttp.h"
#include "Decode7z.h"
#pragma comment(lib,"Version.lib") 

class CUpdate{
private:
	wstring m_deCompressDir;
	wstring m_downLoadDir;
	bool m_isOk;
	wstring m_path;
	HANDLE m_thread;
	wstring m_tempFileName;
	wstring m_url;
	wstring m_verUrl;
private:
	wstring getLocalVersion();
	wstring getRemoteVersion();
	static int showProgress(void *ptr, double rDlTotal, double rDlNow, double rUlTotal, double rUlNow);
	static DWORD WINAPI update(LPVOID lpParam);
public:
	CUpdate();
	virtual ~CUpdate();
	wstring getDeCompressDir();
	void setDecompressDir(wstring deCompressDir);
	wstring getDownLoadDir();
	void setDownLoadDir(wstring downLoadDir);
	wstring getPath();
	void setPath(wstring path);
	wstring getTempFileName();
	void setTempFileName(wstring tempFileName);
	wstring getUrl();
	void setUrl(wstring url);
	wstring getVerUrl();
	void setVerUrl(wstring verUrl);
public:
	bool needUpdate();
	virtual void onUpdateEnd();
	virtual void onUpdateFail();
	virtual void onUpdateStart();
	virtual void onUpdating(double now, double total);
	void startUpdate();
	void stopUpdate();;
public:
	void run();
};

#endif