/*��������èFaceCat��� v1.0 https://github.com/FaceCat007/facecat.git
 1.��ʼ��-�󶴳���Ա-�Ϻ����׿Ƽ���ʼ��-����KOL-�յ� (΢�ź�:suade1984);
 2.���ϴ�ʼ��-�Ϻ����׿Ƽ���ʼ��-Ԭ����(΢�ź�:wx627378127);
 3.���ϴ�ʼ��-Ф����(΢�ź�:xiaotianlong_luu);
 4.���Ͽ�����-������(΢�ź�:chenxiaoyangzxy)������-���(΢�ź�:cnnic_zhu);
 5.�ó���ԴЭ��ΪBSD����ӭ�����ǵĴ�ҵ����и���֧�֣���ӭ���࿪���߼��롣
 */

#ifndef __WINDOWEX_H__
#define __WINDOWEX_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "FCDraw.h"
#include "WindowButton.h"

typedef enum WindowStateA{
	WindowStateA_Max,
	WindowStateA_Min,
	WindowStateA_Normal
};

//�Զ��崰��
class WindowEx : public FCWindow{
private:
	int m_animateDirection;
	bool m_animateMoving;
	int m_animateType;
	WindowButton *m_closeButton;
	bool m_isChildWindow;
	WindowButton *m_maxOrRestoreButton;
	WindowButton *m_minButton;
	FCPoint m_normalLocation;
	FCSize m_normalSize;
	bool m_showMaxBox;
	bool m_showMinBox;
	int m_timerID;
	WindowStateA m_windowState;
private:
	static void clickButton(void *sender, FCTouchInfo touchInfo, void *pInvoke);
public:
	WindowEx();
	virtual ~WindowEx();
	//�Ƿ񶯻�
	bool isAnimateMoving();
	//�رհ�ť
	WindowButton* getCloseButton();
	void setCloseButton(WindowButton* closeButton);
	//�Ƿ��Ӵ���
	bool isChildWindow();
	void setChildWindow(bool isChildWindow);
	//��󻯰�ť
	WindowButton* getMaxOrRestoreButton();
	void setMaxOrRestoreButton(WindowButton *maxOrRestoreButton);
	//��С����ť
	WindowButton* getMinButton();
	void setMinButton(WindowButton *minButton);
	//�Ƿ���ʾ��󻯰�ť
	bool showMaxBox();
	void setShowMaxBox(bool showMaxBox);
	//�Ƿ���ʾ��С����ť
	bool showMinBox();
	void setShowMinBox(bool showMinBox);
	//����״̬
	WindowStateA getWindowState();
	void setWindowState(WindowStateA windowState);
public:
	//��������
	void animateHide();
	//������ʾ
	void animateShow(bool showDialog);
	//��ȡ����
	virtual void getProperty(const String& name, String *value, String *type);
	//��ȡ�����б�
	virtual ArrayList<String> getPropertyNames();
	//���
	void maxWindow();
	//���
	void maxOrRestore();
	//��С��
	void minWindow();
	//�ؼ���ӷ���
	virtual void onAdd();
	//�϶��ؼ���ʼ����
	virtual void onDragReady(FCPoint *startOffset);
	//�ػ汳������
	virtual void onPaintBackground(FCPaint *paint, const FCRect& clipRect);
	//�����
	virtual void onTimer(int timerID);
	//�ָ�
	void restore();
	//��������
	virtual void setProperty(const String& name, const String& value);
	//�ؼ����ָ��·���
	virtual void update();
};
#endif