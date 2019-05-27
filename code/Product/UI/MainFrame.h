/*��������èFaceCat��� v1.0 https://github.com/FaceCat007/facecat.git
 1.��ʼ��-�󶴳���Ա-�Ϻ����׿Ƽ���ʼ��-����KOL-�յ� (΢�ź�:suade1984);
 2.���ϴ�ʼ��-�Ϻ����׿Ƽ���ʼ��-Ԭ����(΢�ź�:wx627378127);
 3.���ϴ�ʼ��-Ф����(΢�ź�:xiaotianlong_luu);
 4.���Ͽ�����-������(΢�ź�:chenxiaoyangzxy)������-���(΢�ź�:cnnic_zhu);
 5.�ó���ԴЭ��ΪBSD����ӭ�����ǵĴ�ҵ����и���֧�֣���ӭ���࿪���߼��롣
 */

#ifndef __FUTURE_H__
#define __FUTURE_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "GdiPlusPaintEx.h"
#include "UIXmlEx.h"
#include "WinHostEx.h"
#include "..\\Service\\ALikeService.h"

using namespace FaceCat;
//���׿ؼ�
class MainFrame : public UIXmlEx{
public:
	FCChart *m_chartLeft;
	FCChart *m_chartRight;
	FCChart *m_chartScope;
	WinHost *m_host;
	HWND m_hWnd;
	vector<LikeDataInfo> m_likeDataInfos;
	double m_scaleFactor;
	FCGrid *m_tableCodes;
	FCGrid *m_tableCodes2;
	FCGrid *m_tableResults;
	int m_timerID;
	FCTextBox *m_txtCode;
	FCTextBox *m_txtCode2;
private:
	//ѡ�иı��¼�
	static void checkedChangedEvent(void *sender, void *pInvoke);
	//��ť�������
	static void clickButton(void *sender, FCTouchInfo touchInfo, void *pInvoke);	
	//��Ԫ�����¼�
	static void gridCellClickEvent(void *sender, FCGridCell *cell, FCTouchInfo touchInfo, void *pInvoke);
	//ע���¼�
	void registerEvents(FCView *control);
	//��ҳ��ѡ�иı��¼�
	static void selectedTabPageChangedEvent(void *sender, void *pInvoke);
	//�ı��ı��¼�
	static void textChangedEvent(void *sender, void *pInvoke);
	//����¼�
	static void timerEvent(void *sender, int timerID, void *pInvoke);
public:
	MainFrame(HWND hWnd);
	virtual ~MainFrame();
	//��������
	double getScaleFactor();
	void setScaleFactor(double scaleFactor);
public:
	//�˳�
	void exit();
	//�����Ƿ�������ʾ
	bool isWindowShowing();
	//����Xml
	void load(const String& xmlPath);
	//��������
	virtual void loadData();
	//�������Ŵ�С
	void resetScaleSize(FCSize clientSize);
	//��ʾ��ʾ��
	int showMessageBox(const String& text, const String& caption, UINT uType);
	//��Ϣѭ��
	int wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	//����ʷ����
	void bindHistoryDatas(const String& code, int index);
	//�󶨽����
	void bindResultTable(const String& code);
	//��ģ�����
	void bindSandBoxTable(vector<LikeDataInfo> *likeDataInfos);
	//��ʼ��ͼ��
	void initChart(FCChart *chart);
	//ѡ�иı��¼�
	void onCheckedChangedEvent(void *sender);
	//��Ԫ�����¼�
	void onGridCellClickEvent(void *sender, FCGridCell *cell, FCTouchInfo touchInfo);
	//��ҳ��ѡ�иı䷽��
	void onSelectedTabPageChangedEvent();
	//�ı��ı��¼�
	void onTextChangedEvent(void *sender);
	//����¼�
	void onTimerEvent(void *sender, int timerID);
	//��ʼ����
	void start();
	//��ʼ����
	void startSearch();
};
#endif