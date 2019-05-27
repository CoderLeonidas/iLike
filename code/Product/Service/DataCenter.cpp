#include "..\\..\\stdafx.h"
#include "DataCenter.h"

static ALikeService *m_aLikeService = 0;
static bool m_isAppAlive = true;
static UIXmlEx *m_mainUI = 0;
static UserCookieService *m_userCookieService = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DataCenter::DataCenter(){
}

DataCenter::~DataCenter(){
}

void DataCenter::dprintf( char *format, ...){
	static char buf[1024];
	va_list args;
	va_start( args, format );
	vsprintf_s( buf, format, args );
	va_end( args);
	OutputDebugStringA( buf);
	printf("%s", buf);
}

IXMLDOMDocument* DataCenter::domFromCOM(){
   HRESULT hr;
   IXMLDOMDocument *pxmldoc = 0;
 
   hRCALL( CoCreateInstance(__uuidof(MSXML2::DOMDocument30),
				  NULL,
				  CLSCTX_INPROC_SERVER,
				  __uuidof(IXMLDOMDocument),
				  (void**)&pxmldoc),
				  "Create a new DOMDocument");
 
	hRCALL( pxmldoc->put_async(VARIANT_FALSE),
			"should never fail");
	hRCALL( pxmldoc->put_validateOnParse(VARIANT_FALSE),
			"should never fail");
	hRCALL( pxmldoc->put_resolveExternals(VARIANT_FALSE),
			"should never fail");
 
	return pxmldoc;
clean:
	if (pxmldoc){
		pxmldoc->Release();
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool DataCenter::isAppAlive(){
	return m_isAppAlive;
}
void DataCenter::setAppAlive(bool appAlive){
	m_isAppAlive = appAlive;
}

ALikeService* DataCenter::getALikeService(){
	return m_aLikeService;
}

string DataCenter::getAppPath(){   
    char exeFullPath[MAX_PATH]; 
    string strPath = "";
    GetModuleFileNameA(0, exeFullPath, MAX_PATH);
    strPath = (string)exeFullPath; 
    int pos = (int)strPath.find_last_of('\\', strPath.length());
    return strPath.substr(0, pos);
}

string DataCenter::getUserPath(){
	char buffer[1024] ={0};
	::GetEnvironmentVariableA("LOCALAPPDATA", buffer, 1024);
	string userPath = buffer;
	if(!FCFile::isDirectoryExist(userPath.c_str())){
		userPath = getAppPath();
	}
	else{
		userPath += "\\owfuture";
		if(!FCFile::isDirectoryExist(userPath.c_str())){
			FCFile::createDirectory(userPath.c_str());
		}
	}
	return userPath;
}

UserCookieService* DataCenter::getUserCookieService(){
	return m_userCookieService;
}

void DataCenter::setMainUI(UIXmlEx *mainUI){
	m_mainUI = mainUI;
}

UIXmlEx* DataCenter::getMainUI(){
	return m_mainUI;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DataCenter::startService(){
	m_aLikeService = new ALikeService;
	m_userCookieService = new UserCookieService;
}

