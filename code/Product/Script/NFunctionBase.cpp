#include "..\\..\\stdafx.h"
#include "NFunctionBase.h"
#include   "shellapi.h "

static String FUNCTIONS = L"IN,OUT,SLEEP,EXECUTE";
static String PREFIX = L"";
static int STARTINDEX = 1000;

NFunctionBase::NFunctionBase(FCScript *indicator, int cid, const String& name){
    m_indicator = indicator;
    m_ID = cid;
    m_name = name;
}

NFunctionBase::~NFunctionBase(){
    m_indicator = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NFunctionBase::addFunctions(FCScript *indicator){
    ArrayList<String> functions = FCStr::split(FUNCTIONS, L",");
    int functionsSize = (int)functions.size();
    for (int i = 0; i < functionsSize; i++){
        indicator->addFunction(new NFunctionBase(indicator, STARTINDEX + i, PREFIX + functions.get(i)));
    }
    functions.clear();
}

double NFunctionBase::onCalculate(CVariable *var){
    switch (var->m_functionID)
    {
        case 1000:
            return INPUT(var);
        case 1001:
            return OUTPUT(var);
        case 1002:
            return SLEEP(var);
		case 1003:
			return EXECUTE(var);
        default: return 0;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double NFunctionBase::EXECUTE(CVariable *var){
	ShellExecute(0, L"open", m_indicator->getText(var->m_parameters[0]).c_str(), L"", L" ",SW_SHOWNORMAL);
	return 0;
}

double NFunctionBase::INPUT(CVariable *var){
    return 0;
}

double NFunctionBase::OUTPUT(CVariable *var){
    return 0;
}

double NFunctionBase::SLEEP(CVariable *var){
    return 1;
}
