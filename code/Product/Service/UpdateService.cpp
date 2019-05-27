#include "..\\..\\stdafx.h"
#include "UpdateService.h"
#include "DataCenter.h"
#include <shellapi.h>

UpdateService::UpdateService()
{
	wstring appPath = L"", userPath = L"";
	Str::stringTowstring(appPath, DataCenter::GetAppPath());
	Str::stringTowstring(userPath, DataCenter::GetUserPath());
	SetDecompressDir(userPath + L"\\update\\package");
	SetDownLoadDir(userPath + L"\\update");
	SetPath(appPath + L"\\owfuture.exe");
	SetTempFileName(L"owfuture.exe");
	SetUrl(L"http://180.166.213.18/download/owfuture/owfuture.exe");
	SetVerUrl(L"http://180.166.213.18/download/owfuture/version.txt");
}

UpdateService::~UpdateService()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpdateService::OnUpdateEnd()
{
	CUpdate::OnUpdateEnd();
	wchar_t szPath[255] = {0};
	_stprintf_s(szPath, 254, L"%s %s", L"autorun.exe", L"owfuture");
	STARTUPINFO si;
	memset(&si, 0, sizeof(STARTUPINFO));  
	si.cb = sizeof(STARTUPINFO);  
	si.dwFlags = STARTF_USESHOWWINDOW;  
	si.wShowWindow = SW_SHOW;  
	PROCESS_INFORMATION pi;
	if(CreateProcess(0, szPath, 0, 0, false, 0, 0, 0, &si, &pi)) 
	{
		exit(0);
	}
}

void UpdateService::OnUpdateFail()
{
	CUpdate::OnUpdateFail();
}

void UpdateService::OnUpdateStart()
{
	CUpdate::OnUpdateStart();
}

void UpdateService::OnUpdating(double now, double total)
{
	CUpdate::OnUpdating(now, total);
}