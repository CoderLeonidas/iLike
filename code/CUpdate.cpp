#include "stdafx.h"
#include "CUpdate.h"

wstring CUpdate::getLocalVersion(){
	wchar_t *pBuf = 0; 
	wchar_t szVersion[100] = {0};
	VS_FIXEDFILEINFO  *pVsInfo = 0; 
	unsigned int iFileInfoSize = sizeof(VS_FIXEDFILEINFO); 
	int iVerInfoSize = GetFileVersionInfoSize(m_path.c_str(), 0); 
	if(iVerInfoSize != 0) { 
		pBuf =  new wchar_t[iVerInfoSize]; 
		if(GetFileVersionInfo(m_path.c_str(), 0, iVerInfoSize, pBuf)) { 
			if(VerQueryValue(pBuf, L"\0", (void **)&pVsInfo, &iFileInfoSize)){ 
				_stprintf_s(szVersion, L"%d.%d.%d.%d", HIWORD(pVsInfo->dwFileVersionMS), LOWORD(pVsInfo->dwFileVersionMS), 
					HIWORD(pVsInfo->dwFileVersionLS), LOWORD(pVsInfo->dwFileVersionLS)); 
			} 
		} 
		delete pBuf; 
		pBuf = 0;
	} 
	return szVersion; 
}

wstring CUpdate::getRemoteVersion(){
	wstring wRemoteVersion = L"";
	if((int)m_verUrl.length() > 0){
		string sVerUrl = FCStr::wstringTostring(m_verUrl);
		string remoteVersion = CurlHttp::getInstance()->get(sVerUrl, false, 5);
		wRemoteVersion = FCStr::stringTowstring(remoteVersion);
	}
	return wRemoteVersion;
}

int CUpdate::showProgress(void *ptr, double rDlTotal, double rDlNow, double rUlTotal, double rUlNow){
	CUpdate *update = (CUpdate*)ptr;
	if(rDlTotal > 0){
		update->onUpdating(rDlNow, rDlTotal);
	}
	else if(rUlTotal > 0){
		update->onUpdating(rUlNow, rUlTotal);
	}
	return 1;
}

DWORD WINAPI CUpdate::update(LPVOID lpParam){
	CUpdate *update = (CUpdate*)lpParam;
	if(update){
		if(update->needUpdate()){
			update->onUpdateStart();
			string sdlDir = "", sUrl = "", tempFileName = "";
			sdlDir = FCStr::wstringTostring(update->getDownLoadDir());
			if(!FCFile::isDirectoryExist(sdlDir.c_str())){
				FCFile::createDirectory(sdlDir.c_str());
			}
			sUrl = FCStr::wstringTostring(update->getUrl());
			tempFileName = FCStr::wstringTostring(update->getTempFileName());
			CurlHttp *http = CurlHttp::getInstance();
			ProgressInfo progressInfo;
			progressInfo.m_ptr = update;
			progressInfo.m_fun = showProgress;
			string filePath = sdlDir + "\\" + tempFileName;
			string state = http->downloadFile(sUrl, filePath);
			if((int)state.length() > 0){
				update->onUpdateEnd();
			}
			else{
				update->onUpdateFail();
			}
		}
	}
	return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CUpdate::CUpdate(){
	m_deCompressDir = L"";
	m_downLoadDir = L"";
	m_isOk = false;
	m_path = L"";
	m_tempFileName = L"";
	m_thread = 0;
	m_url = L"";
	m_verUrl = L"";
}

CUpdate::~CUpdate(){
	m_thread = 0;
}

wstring CUpdate::getDeCompressDir(){
	return m_deCompressDir;
}

void CUpdate::setDecompressDir(wstring deCompressDir){
	m_deCompressDir = deCompressDir;
}

wstring CUpdate::getDownLoadDir(){
	return m_downLoadDir;
}

void CUpdate::setDownLoadDir(wstring downLoadDir){
	m_downLoadDir = downLoadDir;
}

wstring CUpdate::getPath(){
	return m_path;
}

void CUpdate::setPath(wstring path){
	m_path = path;
}

wstring CUpdate::getTempFileName(){
	return m_tempFileName;
}

void CUpdate::setTempFileName(wstring tempFileName){
	m_tempFileName = tempFileName;
}

wstring CUpdate::getUrl(){
	return m_url;
}

void CUpdate::setUrl(wstring url){
	m_url = url;
}

wstring CUpdate::getVerUrl(){
	return m_verUrl;
}

void CUpdate::setVerUrl(wstring verUrl){
	m_verUrl = verUrl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CUpdate::needUpdate(){
	return true;
	wstring localVersion = getLocalVersion();
	wstring remoteVersion = getRemoteVersion();
	if((int)remoteVersion.length() > 0){
		if(localVersion != remoteVersion){
			return true;
		}
	}
	return false;
}

void CUpdate::onUpdateEnd(){
	wstring packagePath = m_downLoadDir + L"\\" + m_tempFileName;
	string deCompressDir = FCStr::wstringTostring(m_deCompressDir);
	if(!FCFile::isDirectoryExist(deCompressDir.c_str())){
		FCFile::createDirectory(deCompressDir.c_str());
	}
	Decode7z::Decode(m_deCompressDir.c_str(), packagePath.c_str());
	m_isOk = true;
}

void CUpdate::onUpdateFail(){
}

void CUpdate::onUpdateStart(){
}

void CUpdate::onUpdating(double now, double total){
}

void CUpdate::startUpdate(){
	if(m_thread){
		::TerminateThread(m_thread, 0);
	}
	m_thread = ::CreateThread(0, 0, update, (LPVOID)this, 0, 0);
	CloseHandle(m_thread);
}

void CUpdate::stopUpdate(){
	if(m_thread){
		::TerminateThread(m_thread, 0);
	}
}

void CUpdate::run(){
	String wAppPath = FCStr::stringTowstring(FCStr::getAppPath()) + L"\\day";
	ArrayList<String> files;
	FCFile::getFiles(wAppPath, &files);
	if(files.size() < 10){
		setDecompressDir(wAppPath);
		setUrl(L"http://www.shningmi.com/upload/day.7z");
		setDownLoadDir(FCStr::stringTowstring(FCStr::getAppPath()) + L"\\data");
		setTempFileName(L"day.7z");
		startUpdate();
		while(!m_isOk){
			::Sleep(1000);
		}
	}
}