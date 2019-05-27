/*��������èFaceCat��� v1.0 https://github.com/FaceCat007/facecat.git
 1.��ʼ��-�󶴳���Ա-�Ϻ����׿Ƽ���ʼ��-����KOL-�յ� (΢�ź�:suade1984);
 2.���ϴ�ʼ��-�Ϻ����׿Ƽ���ʼ��-Ԭ����(΢�ź�:wx627378127);
 3.���ϴ�ʼ��-Ф����(΢�ź�:xiaotianlong_luu);
 4.���Ͽ�����-������(΢�ź�:chenxiaoyangzxy)������-���(΢�ź�:cnnic_zhu);
 5.�ó���ԴЭ��ΪBSD����ӭ�����ǵĴ�ҵ����и���֧�֣���ӭ���࿪���߼��롣
 */

#ifndef __CURLHTTP__H__
#define __CURLHTTP__H__
#pragma once
#include "stdafx.h"
#include "windef.h"
#include "..\\third_party\\curl\\curl.h"
#include "..\\third_party\\curl\\easy.h"
#include <Winsock2.h>
#include <Winldap.h>
#include <iostream>
#include "Winhttp.h"
#include <string>
using namespace std;

#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"Wldap32.lib")
#pragma comment(lib, "winhttp.lib")
#pragma comment(lib, "Advapi32.lib")

#define BUFFERLEN 1024

namespace FaceCat{
	typedef int (*progressFun)(void* ptr, double rDlTotal, double rDlNow, double rUlTotal, double rUlNow) ;

	struct FtpFile{
		const char *m_filename; 
		FILE *m_stream; 
	}; 

	struct CurlProxyInfo{
		CurlProxyInfo(){
			m_proxyType = CURLPROXY_HTTP;
		}
		void clear(){
			m_proxyType = CURLPROXY_HTTP;
			m_address.clear();
			m_port.clear();
			m_account.clear();
			m_pwd.clear();
			m_domain.clear();
		}
		curl_proxytype m_proxyType;
		string m_address;
		string m_port;
		string m_account;
		string m_pwd;
		string m_domain;
	};

	struct ProgressInfo{
		progressFun m_fun;
		void *m_ptr;
	};

	class CurlHttp{
	private:
		HWND m_hWnd;
		CURLcode m_lastErrorCode; 
		CurlProxyInfo *m_proxyInfo;
	private:
		FCLock m_Lock;
	private:
		static bool copyFileBite(FILE *src, long start, long size, FILE *dest);
		static size_t fRead(void *buffer, size_t size, size_t nmemb, void *user_p);
		static int fWrite(void *buffer, size_t size, size_t nmemb, void *stream);
		void getIeProxySet(long *type, char *server) const;
		static string readFromFile(const string& fileName, int& outLen);
		void setCurlProxy(CURL *curl);
		bool testProxy(CurlProxyInfo *proxyInfo, const string& url);
		int uploadFile(const string& fileName, const string& url) ;
		static int write(char *data, size_t size, size_t nmemb, string *writerData);   
	public:
		CurlHttp(HWND callhwnd);
		virtual ~CurlHttp();
		static CurlHttp* s_pHttp;
		static CurlHttp* getInstance(HWND m_hWnd = 0);
		static void releaseInstance();
		static void setCallHwnd(HWND m_hWnd);
	public:
		string downloadFile(string strFileUrl, string strFilePath, ProgressInfo *proParam = 0, int timeout = 600);
		string get(const string& url, bool isRan, int timeout = 10);
		void getIeProxySet(string *ip, int *port);
		CURLcode getLastErrorCode() const;
		string getIp();
		string parseURL2Ip(const string& url);
		string post(const string& url,void *content, long contentsize, int timeout = 10);
		string uploadBitFile(string strUploadUrl, string strUploadFileName, void *ptr);
	};
}
#endif