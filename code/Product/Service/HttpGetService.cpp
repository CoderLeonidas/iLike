#include "HttpGetService.h"
#include "..\\..\\CStr.h"
#include "..\\..\\CurlHttp.h"

namespace FaceCat{
    string HttpGetService::get(const string url){
		CurlHttp *http = CurlHttp::getInstance(0);
		return http->get(url, false, 10000);
    }
}
