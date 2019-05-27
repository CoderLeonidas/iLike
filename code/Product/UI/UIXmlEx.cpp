#include "..\\..\\stdafx.h"
#include "UIXmlEx.h"
#include "RibbonButton.h"
#include "WindowEx.h"
#include "WindowButton.h"
#include "BarrageDiv.h"
#include "..\\Script\\FaceCatScript.h"
#include "..\\Service\\DataCenter.h"

namespace FaceCat{
	UIXmlEx::UIXmlEx(){
	}

	UIXmlEx::~UIXmlEx(){
		m_controlsMap.clear();
		m_tempTabPages.clear();
	}

	void UIXmlEx::autoSelectFirstRow(FCGrid *grid){
		int rowsSize = (int)grid->m_rows.size();
		if(rowsSize > 0){
			ArrayList<FCGridRow*> selectedRows = grid->getSelectedRows();
			int selectedRowsSize = (int)selectedRows.size();
			if(selectedRowsSize == 0){
				selectedRows.add(grid->m_rows.get(0));
				grid->setSelectedRows(selectedRows);
			}
		}
	}

	void UIXmlEx::autoSelectLastRow(FCGrid *grid){
		int rowsSize = (int)grid->m_rows.size();
		if(rowsSize > 0){
			ArrayList<FCGridRow*> selectedRows;
			selectedRows.add(grid->m_rows.get(rowsSize - 1));
			grid->setSelectedRows(selectedRows);
		}
	}

	FCView* UIXmlEx::createControl(IXMLDOMNode *node, const String& type){
		if(type == L"barragediv"){
			return new BarrageDiv;
		}
        else if (type == L"ribbonbutton"){
            return new RibbonButton;
        }
        else if (type == L"windowex"){
            return new WindowEx;
        }
		else{
			return FCUIXml::createControl(node, type);
		}
	}

	FCView* UIXmlEx::findControl(const String& name){
		FCView *control = 0;
		map<String, FCView*>::iterator sIter = m_controlsMap.find(name);
		if(sIter != m_controlsMap.end()){
			control = sIter->second;
		}
		if(!control){
			control = FCUIXml::findControl(name);
			m_controlsMap[name] = control;
		}
		if(!control){
			control = m_native->findControl(name);
			m_controlsMap[name] = control;
		}
		return control;
	}

	int UIXmlEx::getColumnsIndex(FCGrid *grid, map<int, FCGridColumn*> *columnsIndex){
		for(int c = 0; c < grid->m_columns.size(); c++){
			FCGridColumn *column = grid->m_columns.get(c);
			String columnName = column->getName();
			int columnNameSize = (int)columnName.size();
			String numStr = L"";
			for(int i = 0; i < columnNameSize; i++){
				String sz = columnName.substr(i, 1);
				if(sz == L"0" || sz == L"1" || sz == L"2" || sz == L"3" || sz == L"4" || 
					sz == L"5" || sz == L"6" || sz == L"7" || sz == L"8" || sz == L"9"){
					numStr += sz;
				}
			}
			(*columnsIndex)[FCStr::convertStrToInt(numStr.c_str())] = column;
		}
		return 1;
	}

	void UIXmlEx::loadData(){
	}

	void UIXmlEx::loadFile(const String& fileName, FCView *control){
		m_controlsMap.clear();
		FCUIXml::loadFile(fileName, control);
		m_tempTabPages.clear();
	}

	void UIXmlEx::onAddControl(FCView *control, IXMLDOMNode *node){
		m_controlsMap[control->getName()] = control;
		FCUIXml::onAddControl(control, node);
	}

	void UIXmlEx::removeTempControls(){
		vector<String> tabPageNames;
		map<String, FCView*>::iterator sIter = m_controlsMap.begin();
		for(; sIter != m_controlsMap.end(); ++sIter){
			FCView *control = sIter->second;
			FCTabPage *tabPage = dynamic_cast<FCTabPage*>(control);
			if(tabPage){
				control->getParent()->removeControl(control);
				tabPageNames.push_back(sIter->first);
				m_tempTabPages[sIter->first] = tabPage;
				tabPage->setTabControl(0);
			}
		}
		vector<String>::iterator sIter2 = tabPageNames.begin();
		for(; sIter2 != tabPageNames.end(); ++sIter2){
			sIter = m_controlsMap.find(*sIter2);
			if(sIter != m_controlsMap.end()){
				m_controlsMap.erase(sIter);
			}
		}
		tabPageNames.clear();
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void WindowXmlEx::clickButton(void *sender, FCTouchInfo touchInfo, void *pInvoke){
		if (touchInfo.m_firstTouch && touchInfo.m_clicks == 1){
            FCView *control = (FCView*)sender;
            WindowXmlEx *windowXmlEx = (WindowXmlEx*)pInvoke;
            if(windowXmlEx->getWindow() && control == windowXmlEx->getWindow()->getCloseButton()){
                windowXmlEx->close();
            }
        }
    }

    
    void WindowXmlEx::invoke(void *sender, void *args, void *pInvoke){
        WindowXmlEx *windowXmlEx = (WindowXmlEx*)pInvoke;
        windowXmlEx->onInvoke(args);
    }
    
    void WindowXmlEx::registerEvents(FCView *control){
        FCTouchEvent clickButtonEvent = &clickButton;
        ArrayList<FCView*> controls = control->m_controls;
        for(int c = 0; c < controls.size(); c++){
            FCView *subControl = controls.get(c);
            FCButton *button = dynamic_cast<FCButton*>(subControl);
            if(button){
                button->addEvent((void*)clickButtonEvent, FCEventID::CLICK, this);
            }
            registerEvents(subControl);
        }
    }
    
    WindowXmlEx::WindowXmlEx(){
        m_invokeEvent = 0;
		m_isClosing = false;
		m_isWinForm = false;
        m_native = 0;
        m_window = 0;
		m_winForm = 0;
	}
    
	WindowXmlEx::~WindowXmlEx(){
		if(m_window){
			delete m_window;
			m_window = 0;
		}
        m_native = 0;
		m_winForm = 0;
	}

	bool WindowXmlEx::isWinForm(){
		return m_isWinForm;
	}

	void WindowXmlEx::setIsWinForm(bool isWinForm){
		m_isWinForm = isWinForm;
	}
    
    WindowEx* WindowXmlEx::getWindow(){
        return m_window;
    }
    
	void WindowXmlEx::close(){
		m_isClosing = true;
        m_window->invoke((void*)-10000);
	}
    
    void WindowXmlEx::load(FCNative *native, String xmlName, String windowName){
        setNative(native);
        m_native = native;
        string appPath = DataCenter::getAppPath();
        String wAppPath = FCStr::stringTowstring(appPath);
        String xmlPath = wAppPath + L"\\config\\" + xmlName + L".xml";
        setScript(new FaceCatScript(this));
        loadFile(xmlPath, 0);
        m_window = dynamic_cast<WindowEx*>(findControl(windowName));
        m_invokeEvent = &invoke;
        m_window->addEvent((void*)m_invokeEvent, FCEventID::INVOKE, this);
        registerEvents(m_window);
    }
    
    void WindowXmlEx::onInvoke(void *args){
        int state = (int)args;
        if (state == -10000){
			if(m_window){
				m_invokeEvent = 0;
				m_window->close();
			}
			m_native->m_draggingControl = 0;
			m_native->m_focusedControl = 0;
			m_native->m_touchDownControl = 0;
			m_native->m_touchMoveControl = 0;
			FCNative *native = m_native;
            native->invalidate();
			delete this;
        }
    }
    
	void WindowXmlEx::show(){
		FCPoint location ={-m_window->getWidth(), -m_window->getHeight()};
		m_window->setLocation(location);
		m_window->animateShow(false);
		m_window->invalidate();
	}

	void WindowXmlEx::showDialog(){
		FCPoint location ={-m_window->getWidth(), -m_window->getHeight()};
		m_window->setLocation(location);
		m_window->animateShow(true);
		m_window->invalidate();
	}
}