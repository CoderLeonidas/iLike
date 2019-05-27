/*基于捂脸猫FaceCat框架 v1.0 https://github.com/FaceCat007/facecat.git
 1.创始人-矿洞程序员-上海宁米科技创始人-脉脉KOL-陶德 (微信号:suade1984);
 2.联合创始人-上海宁米科技创始人-袁立涛(微信号:wx627378127);
 3.联合创始人-肖添龙(微信号:xiaotianlong_luu);
 4.联合开发者-陈晓阳(微信号:chenxiaoyangzxy)，助理-朱炜(微信号:cnnic_zhu);
 5.该程序开源协议为BSD，欢迎对我们的创业活动进行各种支持，欢迎更多开发者加入。
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
//交易控件
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
	//选中改变事件
	static void checkedChangedEvent(void *sender, void *pInvoke);
	//按钮点击方法
	static void clickButton(void *sender, FCTouchInfo touchInfo, void *pInvoke);	
	//单元格点击事件
	static void gridCellClickEvent(void *sender, FCGridCell *cell, FCTouchInfo touchInfo, void *pInvoke);
	//注册事件
	void registerEvents(FCView *control);
	//多页夹选中改变事件
	static void selectedTabPageChangedEvent(void *sender, void *pInvoke);
	//文本改变事件
	static void textChangedEvent(void *sender, void *pInvoke);
	//秒表事件
	static void timerEvent(void *sender, int timerID, void *pInvoke);
public:
	MainFrame(HWND hWnd);
	virtual ~MainFrame();
	//缩放因子
	double getScaleFactor();
	void setScaleFactor(double scaleFactor);
public:
	//退出
	void exit();
	//窗体是否正在显示
	bool isWindowShowing();
	//加载Xml
	void load(const String& xmlPath);
	//加载数据
	virtual void loadData();
	//调整缩放大小
	void resetScaleSize(FCSize clientSize);
	//显示提示框
	int showMessageBox(const String& text, const String& caption, UINT uType);
	//消息循环
	int wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	//绑定历史数据
	void bindHistoryDatas(const String& code, int index);
	//绑定结果表
	void bindResultTable(const String& code);
	//绑定模拟码表
	void bindSandBoxTable(vector<LikeDataInfo> *likeDataInfos);
	//初始化图形
	void initChart(FCChart *chart);
	//选中改变事件
	void onCheckedChangedEvent(void *sender);
	//单元格点击事件
	void onGridCellClickEvent(void *sender, FCGridCell *cell, FCTouchInfo touchInfo);
	//多页夹选中改变方法
	void onSelectedTabPageChangedEvent();
	//文本改变事件
	void onTextChangedEvent(void *sender);
	//秒表事件
	void onTimerEvent(void *sender, int timerID);
	//开始方法
	void start();
	//开始搜索
	void startSearch();
};
#endif