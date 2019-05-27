#include "stdafx.h"
#include "CStr.h"

int FCStrEx::compress2(Byte *data, uLong ndata, Byte *zdata, uLong *nzdata){
	return compress(zdata, nzdata, data, ndata);
}

String FCStrEx::convertThousands(double value, int digit){
	if(digit == 0){
		double newValue = FCStr::round(value);
		if(abs(newValue - value) < 1){
			value = newValue;
		}
	}
	wchar_t szValue[100] = {0};
	_stprintf_s(szValue, 99, L"%I64d", (Long)abs(value));
	String str = szValue;
	int strSize = (int)str.size();
	String result = L"";
	for(int i = 0; i < strSize; i++){
		result = str[strSize - i - 1] + result;
		if(i != strSize - 1 && (i > 0 && (i + 1) % 3 == 0)){
			result = L"," + result;
		}
	}
	if(value < 0){
		result = L"-" + result;
	}
	if(digit > 0){
		FCStr::getValueByDigit(value, digit, szValue);
		String dszValue = szValue;
		if((int)dszValue.find(L".") != -1){
			result += L"." + dszValue.substr((int)dszValue.find(L".") + 1);
		}
	}
	return result;
}

string FCStrEx::convertDBCodeToFileName(const string& code){
	string fileName = code;
	if (fileName.find(".") != -1){
        fileName = fileName.substr(fileName.find('.') + 1) + fileName.substr(0, fileName.find('.'));
    }
	fileName += ".txt";
	return fileName;
}

string FCStrEx::convertDBCodeToSinaCode(const string& code){
	string securityCode = code;
	int index = (int)securityCode.find(".SH");
    if (index > 0){
        securityCode = "sh" + securityCode.substr(0, securityCode.find("."));
    }
    else{
        securityCode = "sz" + securityCode.substr(0, securityCode.find("."));
    }
	return securityCode;
}

string FCStrEx::convertDBCodeToTencentCode(const string& code){
	string securityCode = code;
	int index = (int)securityCode.find(".");
	if(index > 0){
		index = (int)securityCode.find(".SH");
		if (index > 0){
			securityCode = "sh" + securityCode.substr(0, securityCode.find("."));
		}
		else{
			securityCode = "sz" + securityCode.substr(0, securityCode.find("."));
		}
	}
	return securityCode;
}

String FCStrEx::convertSinaCodeToDBCode(const String& code){
	int equalIndex = (int)code.find(L"=");
	int startIndex = (int)code.find(L"var hq_str_") + 11;
	String securityCode = equalIndex > 0 ?code.substr(startIndex, equalIndex - startIndex) : code;
	if ((int)securityCode.find(L"sh") == 0 || (int)securityCode.find(L"SH") == 0){
		securityCode = securityCode.substr(2) + L".SH";
	}
	else if ((int)securityCode.find(L"sz") == 0 || (int)securityCode.find(L"SZ") == 0){
		securityCode = securityCode.substr(2) + L".SZ";
	}
	return securityCode;
}

String FCStrEx::convertTencentCodeToDBCode(const String& code){
	int equalIndex = (int)code.find(L'=');
	String securityCode = equalIndex > 0 ? code.substr(0, equalIndex) : code;
	if ((int)securityCode.find(L"v_sh") == 0){
		securityCode = securityCode.substr(4) + L".SH";
	}
	else if ((int)securityCode.find(L"v_sz") == 0){
		securityCode = securityCode.substr(4) + L".SZ";
	}
	return securityCode;
}

int FCStrEx::deCompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata){
	return uncompress(data, ndata, zdata, nzdata);
}

String FCStrEx::getDBString(const String& strSrc){
	String str = FCStr::replace(strSrc, L"'", L"''");
	return str;
}

string FCStrEx::getGuid(){
	static char buf[64] = {0};
	GUID guid;
	if (S_OK == ::CoCreateGuid(&guid)){
		_snprintf(buf, sizeof(buf)
			, "{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}"
			, guid.Data1
			, guid.Data2
			, guid.Data3
			, guid.Data4[0], guid.Data4[1]
		, guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
		, guid.Data4[6], guid.Data4[7]
		);
	}
	return buf;
}

void FCStrEx::getFormatDate(double date, wchar_t *str){

	int year = 0,month = 0,day = 0,hour = 0,minute = 0,second = 0,msecond = 0;
	FCStr::getDateByNum(date, &year, &month, &day, &hour, &minute, &second, &msecond);
	_stprintf_s(str, 99, L"%d/%d/%d", year, month, day);
}

String FCStrEx::getFormatDate(const String& format, int year, int month, int day, int hour, int minute, int second){
	static wchar_t str[100] = {0};
	_stprintf_s(str, 99, format.c_str(), year, month, day, hour, minute, second);
	return str;
}

String FCStrEx::getFormatDate(const String& format, int year, int month, int day, int hour, int minute, int second, int msec){
	static wchar_t str[100] = {0};
	_stprintf_s(str, 99, format.c_str(), year, month, day, hour, minute, second, msec);
	return str;
}

int FCStrEx::getStringCapacity(const string& str){
	return (int)str.length() + 1 + sizeof(Long);
}

int FCStrEx::getWStringCapacity(const String& str){
	return ((int)str.length() + 1) * 2 + sizeof(Long);
}

/* compress gzip data */
/* data 原数据 ndata 原数据长度 zdata 压缩后数据 nzdata 压缩后长度 */
int FCStrEx::gZCompress(Byte *data, uLong ndata, Byte *zdata, uLong *nzdata){
	z_stream c_stream;
	int err = 0;

	if(data && ndata > 0) {
		c_stream.zalloc = Z_NULL;
		c_stream.zfree = Z_NULL;
		c_stream.opaque = Z_NULL;
		//只有设置为MAX_WBITS + 16才能在在压缩文本中带header和trailer
		if(deflateInit2(&c_stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
			MAX_WBITS + 16, 6, Z_DEFAULT_STRATEGY) != Z_OK) {
			return -1;
		}

		c_stream.next_in  = data;
		c_stream.avail_in  = ndata;
		c_stream.next_out = zdata;
		c_stream.avail_out  = *nzdata;
		while(c_stream.avail_in != 0 && c_stream.total_out < *nzdata) {
			if(deflate(&c_stream, Z_NO_FLUSH) != Z_OK) {
				return -1;
			}
		}

		if(c_stream.avail_in != 0) {
			return c_stream.avail_in;
		}

		for(;;) {
			if((err = deflate(&c_stream, Z_FINISH)) == Z_STREAM_END){
				break;
			}
			if(err != Z_OK){
				return -1;
			}
		}

		if(deflateEnd(&c_stream) != Z_OK){
			return -1;
		}
		*nzdata = c_stream.total_out;
		return 0;
	}
	return -1;
}

/* Uncompress gzip data */
/* zdata 数据 nzdata 原数据长度 data 解压后数据 ndata 解压后长度 */
int FCStrEx::gZDeCompress(Byte *zdata, uLong nzdata, Byte *data, uLong *ndata){
	int err = 0;
	z_stream d_stream = {0}; /* decompression stream */
	static char dummy_head[2] = {
		0x8 + 0x7 * 0x10,
		(((0x8 + 0x7 * 0x10) * 0x100 + 30) / 31 * 31) & 0xFF,
	};

	d_stream.zalloc = Z_NULL;
	d_stream.zfree = Z_NULL;
	d_stream.opaque = Z_NULL;
	d_stream.next_in  = zdata;
	d_stream.avail_in = 0;
	d_stream.next_out = data;
	//只有设置为MAX_WBITS + 16才能在解压带header和trailer的文本
	if(inflateInit2(&d_stream, MAX_WBITS + 16) != Z_OK) {
		return -1;
	}

	//if(inflateInit2(&d_stream, 47) != Z_OK) return -1;
	while(d_stream.total_out < *ndata && d_stream.total_in < nzdata) {
		d_stream.avail_in = d_stream.avail_out = 1; /* force small buffers */
		if((err = inflate(&d_stream, Z_NO_FLUSH)) == Z_STREAM_END){
			break;
		}
		if(err != Z_OK) {
			if(err == Z_DATA_ERROR){
				d_stream.next_in = (Bytef*) dummy_head;
				d_stream.avail_in = sizeof(dummy_head);

				if((err = inflate(&d_stream, Z_NO_FLUSH)) != Z_OK){
					return -1;
				}
			} else
			{
				return -1;
			}
		}
	}
	if(inflateEnd(&d_stream) != Z_OK){
		return -1;
	}
	*ndata = d_stream.total_out;
	return 0;
}