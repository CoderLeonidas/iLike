/*****************************************************************************\
*                                                                             *
* UIXmlEx.h -  UI xml extension functions, types, and definitions.            *
*                                                                             *
*               Version 1.00  ★★★                                          *
*                                                                             *
*               Copyright (c) 2016-2016, MainFrame. All rights reserved.         *
*               Created by Lord 2016/12/24.                                   *
*                                                                             *
******************************************************************************/

#ifndef __UIXMLEX_H__
#define __UIXMLEX_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "..\\..\\Xml\\UIXml.h"
#include <atlstr.h>  
#import <msxml3.dll>
#include "WindowEx.h"

namespace OwLib
{
	#define HRCALL(a, errmsg) \
	do { \
		hr = (a); \
		if (FAILED(hr)) { \
			dprintf( "%s:%d  HRCALL Failed: %s\n  0x%.8x = %s\n", \
					__FILE__, __LINE__, errmsg, hr, #a ); \
			goto clean; \
		} \
	} while (0)

	class UIXmlEx : public UIXmlA
	{	
	protected:
		map<String, ControlA*> m_controlsMap;
		map<String, TabPageA*> m_tempTabPages;
	public:
		UIXmlEx();
		virtual ~UIXmlEx();
	public:
		//自动选中第一行
		void AutoSelectFirstRow(GridA *grid);
		//自动选中最后一行
		void AutoSelectLastRow(GridA *grid);
		//创建控件
		virtual ControlA* CreateControl(IXMLDOMNode *node, const String& type);
		//查找控件
		virtual ControlA* FindControl(const String& name);
		//获取列的索引
		int GetColumnsIndex(GridA *grid, map<int, GridColumn*> *columnsIndex);
		//加载数据
		virtual void LoadData();
		//加载文件
		virtual void LoadFile(const String& fileName, ControlA *control);
		//控件被添加方法
		virtual void OnAddControl(ControlA *control, IXMLDOMNode *node);
		//移除控件
		void RemoveTempControls();
	};

    class WindowXmlEx : public UIXmlEx
	{
    public:
        ControlInvokeEvent m_invokeEvent;
		bool m_isClosing;
		bool m_isWinForm;
        WindowEx *m_window;
		//WinForm *m_winForm;
    private:
        static void ClickButton(void *sender, const POINT& mp, MouseButtonsA button, int clicks, int delta, void *pInvoke);
        static void Invoke(void *sender, void *args, void *pInvoke);
        void RegisterEvents(ControlA *control);
	public:
		WindowXmlEx();
		virtual ~WindowXmlEx();
		bool IsWinForm();
		void SetIsWinForm(bool isWinForm);
        WindowEx* GetWindow();
	public:
		virtual void Close();
        virtual void Load(NativeBase *native, String xmlName, String windowName);
        void OnInvoke(void *args);
		virtual void Show();
		virtual void ShowDialog();
	};
}
#endif