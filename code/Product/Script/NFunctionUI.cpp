#include "..\\..\\stdafx.h"
#include "NFunctionUI.h"
#include "FaceCatScript.h"
#include "..\\UI\\UIXmlEx.h"
#include "NFunctionUI.h"
#include "..\\Service\\UserCookieService.h"
#include "..\\Service\\DataCenter.h"


static String FUNCTIONS = L"GETPROPERTY,SETPROPERTY,GETSENDER,ALERT,INVALIDATE,SHOWWINDOW,CLOSEWINDOW,STARTTIMER,STOPTIMER,GETCOOKIE,SETCOOKIE,SHOWRIGHTMENU,ADDBARRAGE";
static String PREFIX = L"";
static int STARTINDEX = 2000;

NFunctionUI::NFunctionUI(FCScript *indicator, int cid, const String& name, FCUIXml *xml){
    m_indicator = indicator;
    m_ID = cid;
    m_name = name;
    m_xml = xml;
}

NFunctionUI::~NFunctionUI(){
    m_indicator = 0;
    m_xml = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NFunctionUI::addFunctions(FCScript *indicator, FCUIXml *xml){
    ArrayList<String> functions = FCStr::split(FUNCTIONS, L",");
    int functionsSize = (int)functions.size();
    for (int i = 0; i < functionsSize; i++){
        indicator->addFunction(new NFunctionUI(indicator, STARTINDEX + i, PREFIX + functions.get(i), xml));
    }
    functions.clear();
}

double NFunctionUI::onCalculate(CVariable *var){
    switch (var->m_functionID){
        case 2000:
            return GETPROPERTY(var);
        case 2001:
            return SETPROPERTY(var);
        case 2002:
            return GETSENDER(var);
        case 2003:
            return ALERT(var);
        case 2004:
            return INVALIDATE(var);
        case 2005:
            return SHOWWINDOW(var);
        case 2006:
            return CLOSEWINDOW(var);
        case 2007:
            return STARTTIMER(var);
        case 2008:
            return STOPTIMER(var);
        case 2009:
            return GETCOOKIE(var);
        case 2010:
            return SETCOOKIE(var);
        case 2011:
            return SHOWRIGHTMENU(var);
        case 2012:
            return ADDBARRAGE(var);
        default:
            return 0;
    }
}

double NFunctionUI::ADDBARRAGE(CVariable *var){
    return 1;
}

double NFunctionUI::ALERT(CVariable *var){
	return 0;
}

double NFunctionUI::CLOSEWINDOW(CVariable *var){
	WindowXmlEx *windowXmlEx = dynamic_cast<WindowXmlEx*>(m_xml);
	if (windowXmlEx){
		windowXmlEx->close();
	}
	return 0;
}

double NFunctionUI::GETCOOKIE(CVariable *var){
    String cookieName = m_indicator->getText(var->m_parameters[1]);
	UserCookieService *cookieService = DataCenter::getUserCookieService();
    UserCookie cookie;
    if (cookieService->getCookie(cookieName, &cookie) > 0){
        CVariable newVar;
		newVar.m_indicator = m_indicator;
		newVar.m_expression = L"'" + cookie.m_value + L"'";
        m_indicator->setVariable(var->m_parameters[0], &newVar);
        return 1;
    }
    return 0;
}

double NFunctionUI::GETPROPERTY(CVariable *var){
    FaceCatScript *script = dynamic_cast<FaceCatScript*>(m_xml->getScript());
    String name = m_indicator->getText(var->m_parameters[1]);
    String propertyName = m_indicator->getText(var->m_parameters[2]);
    String text = script->getProperty(name, propertyName);
    CVariable newVar;
	newVar.m_indicator = m_indicator;
    newVar.m_expression = L"'" + text + L"'";
    m_indicator->setVariable(var->m_parameters[0], &newVar);
    return 0;
}

double NFunctionUI::GETSENDER(CVariable *var){
    FaceCatScript *script = dynamic_cast<FaceCatScript*>(m_xml->getScript());
    String text = script->getSender();
    CVariable newVar;
	newVar.m_indicator = m_indicator;
    newVar.m_expression = L"'" + text + L"'";
    m_indicator->setVariable(var->m_parameters[0], &newVar);
    return 0;
}

double NFunctionUI::INVALIDATE(CVariable *var){
    if (m_xml){
        int pLen = var->m_parameters ? var->m_parametersLength : 0;
        if (pLen == 0){
            m_xml->getNative()->invalidate();
        }
        else{
            FCView *control = m_xml->findControl(m_indicator->getText(var->m_parameters[0]));
            if (control){
                control->invalidate();
            }
        }
    }
    return 0;
}

double NFunctionUI::SETCOOKIE(CVariable *var){
    String cookieName = m_indicator->getText(var->m_parameters[0]);
    UserCookieService *cookieService = DataCenter::getUserCookieService();
    UserCookie cookie;
    cookie.m_key = cookieName;
    cookie.m_value = m_indicator->getText(var->m_parameters[1]);
    return cookieService->addCookie(&cookie);
}

double NFunctionUI::SETPROPERTY(CVariable *var){
    FaceCatScript *script = dynamic_cast<FaceCatScript*>(m_xml->getScript());
    String name = m_indicator->getText(var->m_parameters[0]);
    String propertyName = m_indicator->getText(var->m_parameters[1]);
    String propertyValue = m_indicator->getText(var->m_parameters[2]);
    script->setProperty(name, propertyName, propertyValue);
    return 0;
}

double NFunctionUI::SHOWRIGHTMENU(CVariable *var){
    FaceCatScript *script = dynamic_cast<FaceCatScript*>(m_xml->getScript());
    FCNative *native = m_xml->getNative();
    FCView *control = m_xml->findControl(script->getSender());
    int clx = native->clientX(control);
    int cly = native->clientY(control);
    FCMenu *menu = m_xml->getMenu(m_indicator->getText(var->m_parameters[0]));
	FCPoint mp = {clx, cly + control->getHeight()};
	menu->setLocation(mp);
    menu->setVisible(true);
    menu->setFocused(true);
    menu->bringToFront();
    native->invalidate();
    return 0;
}

double NFunctionUI::SHOWWINDOW(CVariable *var){
	return 0;
}

double NFunctionUI::STARTTIMER(CVariable *var){
    FCView *control = m_xml->findControl(m_indicator->getText(var->m_parameters[0]));
    control->startTimer((int)m_indicator->getValue(var->m_parameters[1]), (int)m_indicator->getValue(var->m_parameters[2]));
    return 0;
}

double NFunctionUI::STOPTIMER(CVariable *var){
    FCView *control = m_xml->findControl(m_indicator->getText(var->m_parameters[0]));
    control->stopTimer((int)m_indicator->getValue(var->m_parameters[1]));
    return 0;
}
