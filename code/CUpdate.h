/*基于捂脸猫FaceCat框架 v1.0 https://github.com/FaceCat007/facecat.git
 1.创始人-矿洞程序员-上海宁米科技创始人-脉脉KOL-陶德 (微信号:suade1984);
 2.联合创始人-上海宁米科技创始人-袁立涛(微信号:wx627378127);
 3.联合创始人-肖添龙(微信号:xiaotianlong_luu);
 4.联合开发者-陈晓阳(微信号:chenxiaoyangzxy)，助理-朱炜(微信号:cnnic_zhu);
 5.该程序开源协议为BSD，欢迎对我们的创业活动进行各种支持，欢迎更多开发者加入。
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