/*��������èFaceCat��� v1.0 https://github.com/FaceCat007/facecat.git
 1.��ʼ��-�󶴳���Ա-�Ϻ����׿Ƽ���ʼ��-����KOL-�յ� (΢�ź�:suade1984);
 2.���ϴ�ʼ��-�Ϻ����׿Ƽ���ʼ��-Ԭ����(΢�ź�:wx627378127);
 3.���ϴ�ʼ��-Ф����(΢�ź�:xiaotianlong_luu);
 4.���Ͽ�����-������(΢�ź�:chenxiaoyangzxy)������-���(΢�ź�:cnnic_zhu);
 5.�ó���ԴЭ��ΪBSD����ӭ�����ǵĴ�ҵ����и���֧�֣���ӭ���࿪���߼��롣
 */

#ifndef __UIXMLEX_H__
#define __UIXMLEX_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "..\\..\\..\\facecat\\include\\xml\\FCUIXml.h"
#include <atlstr.h>  
#import <msxml3.dll>
#include "WindowEx.h"

namespace FaceCat{
	#define hRCALL(a, errmsg) \
	do{ \
		hr = (a); \
		if (FAILED(hr)){ \
			dprintf( "%s:%d  HRCALL Failed: %s\n  0x%.8x = %s\n", \
					__FILE__, __LINE__, errmsg, hr, #a ); \
			goto clean; \
		} \
	} while (0)

	class UIXmlEx : public FCUIXml{	
	protected:
		map<String, FCView*> m_controlsMap;
		map<String, FCTabPage*> m_tempTabPages;
	public:
		UIXmlEx();
		virtual ~UIXmlEx();
	public:
		//�Զ�ѡ�е�һ��
		void autoSelectFirstRow(FCGrid *grid);
		//�Զ�ѡ�����һ��
		void autoSelectLastRow(FCGrid *grid);
		//�����ؼ�
		virtual FCView* createControl(IXMLDOMNode *node, const String& type);
		//���ҿؼ�
		virtual FCView* findControl(const String& name);
		//��ȡ�е�����
		int getColumnsIndex(FCGrid *grid, map<int, FCGridColumn*> *columnsIndex);
		//��������
		virtual void loadData();
		//�����ļ�
		virtual void loadFile(const String& fileName, FCView *control);
		//�ؼ�����ӷ���
		virtual void onAddControl(FCView *control, IXMLDOMNode *node);
		//�Ƴ��ؼ�
		void removeTempControls();
	};

	class WinForm;

    class WindowXmlEx : public UIXmlEx{
    public:
        FCInvokeEvent m_invokeEvent;
		bool m_isClosing;
		bool m_isWinForm;
        WindowEx *m_window;
		WinForm *m_winForm;
    private:
        static void clickButton(void *sender, FCTouchInfo touchInfo, void *pInvoke);
        static void invoke(void *sender, void *args, void *pInvoke);
        void registerEvents(FCView *control);
	public:
		WindowXmlEx();
		virtual ~WindowXmlEx();
		bool isWinForm();
		void setIsWinForm(bool isWinForm);
        WindowEx* getWindow();
	public:
		virtual void close();
        virtual void load(FCNative *native, String xmlName, String windowName);
        void onInvoke(void *args);
		virtual void show();
		virtual void showDialog();
	};
}
#endif