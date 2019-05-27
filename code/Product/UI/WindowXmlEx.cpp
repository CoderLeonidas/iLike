#include "..\\..\\stdafx.h"
#include "UIXmlEx.h"
#include "RibbonButton.h"
#include "WindowEx.h"
#include "BarrageDiv.h"
#include "..\\Script\\GaiaScript.h"
#include "..\\Service\\DataCenter.h"

namespace OwLib
{
	UIXmlEx::UIXmlEx()
	{
	}

	UIXmlEx::~UIXmlEx()
	{
		m_controlsMap.clear();
		m_tempTabPages.clear();
	}

	void UIXmlEx::AutoSelectFirstRow(GridA *grid)
	{
		int rowsSize = (int)grid->m_rows.size();
		if(rowsSize > 0)
		{
			vector<GridRow*> selectedRows = grid->GetSelectedRows();
			int selectedRowsSize = (int)selectedRows.size();
			if(selectedRowsSize == 0)
			{
				selectedRows.push_back(grid->m_rows[0]);
				grid->SetSelectedRows(selectedRows);
			}
		}
	}

	void UIXmlEx::AutoSelectLastRow(GridA *grid)
	{
		int rowsSize = (int)grid->m_rows.size();
		if(rowsSize > 0)
		{
			vector<GridRow*> selectedRows;
			selectedRows.push_back(grid->m_rows[rowsSize - 1]);
			grid->SetSelectedRows(selectedRows);
		}
	}

	ControlA* UIXmlEx::CreateControl(IXMLDOMNode *node, const String& type)
	{
		if(type == L"barragediv")
		{
			return new BarrageDiv;
		}
        else if (type == L"ribbonbutton")
        {
            return new RibbonButton;
        }
        else if (type == L"windowex")
        {
            return new WindowEx;
        }
		else
		{
			return UIXmlA::CreateControl(node, type);
		}
	}

	ControlA* UIXmlEx::FindControl(const String& name)
	{
		ControlA *control = 0;
		map<String, ControlA*>::iterator sIter = m_controlsMap.find(name);
		if(sIter != m_controlsMap.end())
		{
			control = sIter->second;
		}
		if(!control)
		{
			control = UIXmlA::FindControl(name);
			m_controlsMap[name] = control;
		}
		if(!control)
		{
			control = m_native->FindControl(name);
			m_controlsMap[name] = control;
		}
		return control;
	}

	int UIXmlEx::GetColumnsIndex(GridA *grid, map<int, GridColumn*> *columnsIndex)
	{
		vector<GridColumn*>::iterator sIter = grid->m_columns.begin();
		for(; sIter != grid->m_columns.end(); ++sIter)
		{
			GridColumn *column = *sIter;
			String columnName = column->GetName();
			int columnNameSize = (int)columnName.size();
			String numStr = L"";
			for(int i = 0; i < columnNameSize; i++)
			{
				String sz = columnName.substr(i, 1);
				if(sz == L"0" || sz == L"1" || sz == L"2" || sz == L"3" || sz == L"4" || 
					sz == L"5" || sz == L"6" || sz == L"7" || sz == L"8" || sz == L"9")
				{
					numStr += sz;
				}
			}
			(*columnsIndex)[CStrA::ConvertStrToInt(numStr.c_str())] = column;
		}
		return 1;
	}

	void UIXmlEx::LoadData()
	{
	}

	void UIXmlEx::LoadFile(const String& fileName, ControlA *control)
	{
		m_controlsMap.clear();
		UIXmlA::LoadFile(fileName, control);
		m_tempTabPages.clear();
	}

	void UIXmlEx::OnAddControl(ControlA *control, IXMLDOMNode *node)
	{
		m_controlsMap[control->GetName()] = control;
		UIXmlA::OnAddControl(control, node);
	}

	void UIXmlEx::RemoveTempControls()
	{
		vector<String> tabPageNames;
		map<String, ControlA*>::iterator sIter = m_controlsMap.begin();
		for(; sIter != m_controlsMap.end(); ++sIter)
		{
			ControlA *control = sIter->second;
			TabPageA *tabPage = dynamic_cast<TabPageA*>(control);
			if(tabPage)
			{
				control->GetParent()->RemoveControl(control);
				tabPageNames.push_back(sIter->first);
				m_tempTabPages[sIter->first] = tabPage;
				tabPage->SetTabControl(0);
			}
		}
		vector<String>::iterator sIter2 = tabPageNames.begin();
		for(; sIter2 != tabPageNames.end(); ++sIter2)
		{
			sIter = m_controlsMap.find(*sIter2);
			if(sIter != m_controlsMap.end())
			{
				m_controlsMap.erase(sIter);
			}
		}
		tabPageNames.clear();
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void WindowXmlEx::ClickButton(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke)
    {
        if (button == MouseButtonsA_Left && clicks == 1)
        {
            ControlA *control = (ControlA*)sender;
            WindowXmlEx *windowXmlEx = (WindowXmlEx*)pInvoke;
            if(windowXmlEx->GetWindow() && control == windowXmlEx->GetWindow()->GetCloseButton())
            {
                windowXmlEx->Close();
            }
        }
    }

    
    void WindowXmlEx::Invoke(void *sender, void *args, void *pInvoke)
    {
        WindowXmlEx *windowXmlEx = (WindowXmlEx*)pInvoke;
        windowXmlEx->OnInvoke(args);
    }
    
    void WindowXmlEx::RegisterEvents(ControlA *control)
    {
        ControlMouseEvent clickButtonEvent = &ClickButton;
        vector<ControlA*> controls = control->m_controls;
        vector<ControlA*>::iterator sIter = controls.begin();
        for(; sIter != controls.end(); ++sIter)
        {
            ControlA *subControl = *sIter;
            ButtonA *button = dynamic_cast<ButtonA*>(subControl);
            if(button)
            {
                button->RegisterEvent((void*)clickButtonEvent, EVENTID::CLICK, this);
            }
            RegisterEvents(subControl);
        }
    }
    
    WindowXmlEx::WindowXmlEx()
	{
        m_invokeEvent = 0;
		m_isClosing = false;
		m_isWinForm = false;
        m_native = 0;
        m_window = 0;
		//m_winForm = 0;
	}
    
	WindowXmlEx::~WindowXmlEx()
	{
		if(m_window)
		{
			delete m_window;
			m_window = 0;
		}
        m_native = 0;
		//m_winForm = 0;
	}

	bool WindowXmlEx::IsWinForm()
	{
		return m_isWinForm;
	}

	void WindowXmlEx::SetIsWinForm(bool isWinForm)
	{
		m_isWinForm = isWinForm;
	}
    
    WindowEx* WindowXmlEx::GetWindow()
    {
        return m_window;
    }
    
	void WindowXmlEx::Close()
	{
		m_isClosing = true;
        m_window->Invoke((void*)-10000);
	}
    
    void WindowXmlEx::Load(NativeBase *native, String xmlName, String windowName)
    {
        SetNative(native);
        m_native = native;
        string appPath = DataCenter::GetAppPath();
        String wAppPath = L"";
        CStr::stringTowstring(wAppPath, appPath);
        String xmlPath = wAppPath + L"\\config\\" + xmlName + L".xml";
        SetScript(new GaiaScript(this));
        LoadFile(xmlPath, 0);
        m_window = dynamic_cast<WindowEx*>(FindControl(windowName));
        m_invokeEvent = &Invoke;
        m_window->RegisterEvent((void*)m_invokeEvent, EVENTID::INVOKE, this);
        RegisterEvents(m_window);
    }
    
    void WindowXmlEx::OnInvoke(void *args)
    {
        int state = (int)args;
        if (state == -10000)
        {
			//if (m_winForm)
   //         {
   //             m_winForm->SetWindow(0);
   //             m_winForm->Close();
   //             m_winForm = 0;
   //         }
			if(m_window)
			{
				m_invokeEvent = 0;
				m_window->Close();
			}
			m_native->m_draggingControl = 0;
			m_native->m_focusedControl = 0;
			m_native->m_mouseDownControl = 0;
			m_native->m_mouseMoveControl = 0;
			NativeBase *native = m_native;
			delete this;
            native->Invalidate();
        }
    }
    
	void WindowXmlEx::Show()
	{
        POINT location = {-m_window->GetWidth(), -m_window->GetHeight()};
        m_window->SetLocation(location);
        m_window->AnimateShow(false);
        m_window->Invalidate();
	}

	void WindowXmlEx::ShowDialog()
	{
		POINT location = {-m_window->GetWidth(), -m_window->GetHeight()};
        m_window->SetLocation(location);
        m_window->AnimateShow(true);
        m_window->Invalidate();
	}
}