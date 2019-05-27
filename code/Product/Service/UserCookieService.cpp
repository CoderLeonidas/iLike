#include "..\\..\\stdafx.h"
#include "UserCookieService.h"
#include "..\\..\\..\\third_party\\SQLite\\sqlite3x.hpp"
using namespace sqlite3x;

UserCookie::UserCookie(){
	m_key = L"";
	m_userID = 0;
	m_value = L"";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UserCookieService::UserCookieService(){
	m_userID = 0;
	m_createTableSQL = "CREATE TABLE uSERCOOKIE(USERID INTEGER, KEY, VALUE, MODIFYTIME DATE, CREATETIME DATE)";
	string dataPath = DataCenter::getUserPath() + "\\data";
	if(!FCFile::isDirectoryExist(dataPath.c_str())){
		FCFile::createDirectory(dataPath.c_str());
	}
	string path = dataPath + "\\usercookies.db";
	m_dataBasePath = FCStr::stringTowstring(path);
	bool createDataBase = !FCFile::isFileExist(path.c_str());
	if(createDataBase){
		createTable();
	}
}

UserCookieService::~UserCookieService(){
}

int UserCookieService::getUserID(){
	return m_userID;
}

void UserCookieService::setUserID(int userID){
	m_userID = userID;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UserCookieService::createTable(){
	sqlite3_connection conn(m_dataBasePath.c_str());
	conn.executenonquery(m_createTableSQL.c_str());
	conn.close();
}

int UserCookieService::addCookie(UserCookie *cookie){
	UserCookie oldCookie;
	if(getCookie(cookie->m_key, &oldCookie)){
		updateCookie(cookie);
	}
	else{
		int iLen = sizeof(int) + FCStrEx::getWStringCapacity(cookie->m_key) + 200;
		wchar_t *sql = new wchar_t[iLen];
		memset(sql, 0, iLen * sizeof(wchar_t));
		_stprintf_s(sql, iLen - 1, L"INSERT INTO uSERCOOKIE(USERID, KEY, VALUE, MODIFYTIME, CREATETIME) values (%d, '%s', '%s', '1970-1-1','1970-1-1')",
			m_userID, FCStrEx::getDBString(cookie->m_key).c_str(), FCStrEx::getDBString(cookie->m_value).c_str());
		sqlite3_connection conn(m_dataBasePath.c_str());
		conn.executenonquery(sql);
		conn.close();
		delete[] sql;
		sql = 0;
	}
	return 1;
}

int UserCookieService::deleteCookie(String key){
	int iLen = sizeof(int)  + FCStrEx::getWStringCapacity(key) + 200;
	wchar_t *sql = new wchar_t[iLen];
	memset(sql, 0, iLen * sizeof(wchar_t));
	_stprintf_s(sql, iLen - 1, L"DELETE FROM USERCOOKIE WHERE USERID = %d AND KEY = '%s'", m_userID, FCStrEx::getDBString(key).c_str());
	sqlite3_connection conn(m_dataBasePath.c_str());
	conn.executenonquery(sql);
	conn.close();
	delete[] sql;
	sql = 0;
	return 1;
}

int UserCookieService::getCookie(String key, UserCookie *cookie){
	int state = 0;
	int iLen = sizeof(int) + FCStrEx::getWStringCapacity(cookie->m_key) + 200;
	wchar_t *sql = new wchar_t[iLen];
	memset(sql, 0, iLen * sizeof(wchar_t));
	_stprintf_s(sql, iLen - 1, L"SELECT * FROM USERCOOKIE WHERE USERID = %d AND KEY = '%s'", m_userID, FCStrEx::getDBString(key).c_str());
	sqlite3_connection conn(m_dataBasePath.c_str());
	sqlite3_command cmd(conn, sql);
	sqlite3_reader reader = cmd.executereader();
	while(reader.read()){
		cookie->m_userID = reader.getint(0);
		cookie->m_key = reader.getstring16(1);
		cookie->m_value = reader.getstring16(2);
		state = 1;
	}
	reader.close();
	delete[] sql;
	sql = 0;
	return state;
}

void UserCookieService::updateCookie(UserCookie *cookie){
	int iLen = sizeof(int) + FCStrEx::getWStringCapacity(cookie->m_key) + FCStrEx::getWStringCapacity(cookie->m_value) + 200;
	wchar_t *sql = new wchar_t[iLen];
	memset(sql, 0, iLen * sizeof(wchar_t));
	_stprintf_s(sql, iLen - 1, L"UPDATE USERCOOKIE SET VALUE = '%s' WHERE USERID = %d AND KEY = '%s'",
		FCStrEx::getDBString(cookie->m_value).c_str(), m_userID, FCStrEx::getDBString(cookie->m_key).c_str());
	sqlite3_connection conn(m_dataBasePath.c_str());
	conn.executenonquery(sql);
	conn.close();
	delete[] sql;
	sql = 0;
}