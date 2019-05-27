#include "..\\..\\stdafx.h"
#include "NFunctionEx.h"
#include "NFunctionBase.h"
#include "NFunctionUI.h"

static String FUNCTIONS = L"";

NFunctionEx::NFunctionEx(FCScript *indicator, int cid, const String& name, FCUIXml *xml){
    m_indicator = indicator;
    m_ID = cid;
    m_name = name;
    m_xml = xml;
}

NFunctionEx::~NFunctionEx(){
    m_indicator = 0;
    m_xml = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////

FCScript* NFunctionEx::createIndicator(const String& script, FCUIXml *xml){
    FCScript *indicator = new FCScript();
    FCDataTable *table = new FCDataTable;
    indicator->setDataSource(table);
    int index = 1000000;
    ArrayList<String> functions = FCStr::split(FUNCTIONS, L",");
    int functionsSize = (int)functions.size();
    for (int i = 0; i < functionsSize; i++){
        indicator->addFunction(new NFunctionEx(indicator, index + i, functions.get(i), xml));
    }
	NFunctionBase::addFunctions(indicator);
	NFunctionUI::addFunctions(indicator, xml);
    indicator->setScript(script);
    table->addColumn(0);
    table->set(0, 0, 0);
    indicator->onCalculate(0);
    functions.clear();
    return indicator;
}

double NFunctionEx::onCalculate(CVariable *var){
    switch (var->m_functionID){
        case 1000000:
            return 0;
        default:
            return 0;
    }
}
