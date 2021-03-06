/*捂脸猫FaceCat框架 v1.0
 1.创始人-矿洞程序员-上海宁米科技创始人-脉脉KOL-陶德 (微信号:suade1984);
 2.联合创始人-上海宁米科技创始人-袁立涛(微信号:wx627378127);
 3.联合创始人-肖添龙(微信号:xiaotianlong_luu);
 4.联合开发者-陈晓阳(微信号:chenxiaoyangzxy)，助理-朱炜(微信号:cnnic_zhu)
 5.该框架开源协议为BSD，欢迎对我们的创业活动进行各种支持，欢迎更多开发者加入。
 包含C/C++,Java,C#,iOS,MacOS,Linux六个版本的图形和通讯服务框架。
 */

#pragma once
typedef std::wstring String;
typedef long long Long;
typedef void* Object;

#include "FCPaint.h"
#include "FCView.h"
#include "GdiPaint.h"
#include "GdiPlusPaint.h"
#include "FCStr.h"
#include "FCNative.h"
#include "FCHost.h"
#include "WinHost.h"
#include "FCBinary.h"
#include "FCLock.h"
#include "FCFile.h"
#include "..\\btn\\FCButton.h"
#include "..\\btn\\FCCheckBox.h"
#include "..\\btn\\FCRadioButton.h"
#include "..\\date\\ArrowButton.h"
#include "..\\date\\CYears.h"
#include "..\\date\\CDay.h"
#include "..\\date\\CMonth.h"
#include "..\\date\\CYear.h"
#include "..\\date\\DateTitle.h"
#include "..\\date\\DayButton.h"
#include "..\\date\\DayDiv.h"
#include "..\\date\\HeadDiv.h"
#include "..\\date\\MonthButton.h"
#include "..\\date\\MonthDiv.h"
#include "..\\date\\YearButton.h"
#include "..\\date\\YearDiv.h"
#include "..\\date\\FCCalendar.h"
#include "..\\chart\\BaseShape.h"
#include "..\\chart\\ChartDiv.h"
#include "..\\chart\\FCChart.h"
#include "..\\chart\\FCPlot.h"
#include "..\\chart\\CrossLine.h"
#include "..\\chart\\CrossLineTip.h"
#include "..\\chart\\FCDataTable.h"
#include "..\\chart\\ChartToolTip.h"
#include "..\\chart\\Enums.h"
#include "..\\chart\\ScaleGrid.h"
#include "..\\chart\\HScale.h"
#include "..\\chart\\FCPlot.h"
#include "..\\chart\\SelectArea.h"
#include "..\\chart\\ChartTitleBar.h"
#include "..\\chart\\VScale.h"
#include "..\\chart\\FCScript.h"
#include "..\\grid\\FCGridCell.h"
#include "..\\grid\\FCGridCellExtends.h"
#include "..\\grid\\FCGridColumn.h"
#include "..\\grid\\FCGridEnums.h"
#include "..\\grid\\FCGridRow.h"
#include "..\\grid\\FCGrid.h"
#include "..\\grid\\FCBandedGrid.h"
#include "..\\grid\\FCBandedGridColumn.h"
#include "..\\grid\\FCGridBand.h"
#include "..\\div\\FCDiv.h"
#include "..\\div\\FCGroupBox.h"
#include "..\\div\\FCLayoutDiv.h"
#include "..\\div\\FCSplitLayoutDiv.h"
#include "..\\div\\FCTableLayoutDiv.h"
#include "..\\div\\FCMenu.h"
#include "..\\div\\FCMenuItem.h"
#include "..\\scroll\\FCHScrollBar.h"
#include "..\\scroll\\FCScrollBar.h"
#include "..\\scroll\\FCVScrollBar.h"
#include "..\\tab\\FCTabControl.h"
#include "..\\tab\\FCTabPage.h"
#include "..\\input\\FCComboBox.h"
#include "..\\input\\FCDateTimePicker.h"
#include "..\\input\\FCSpin.h"
#include "..\\input\\FCTextBox.h"
#include "..\\grid\\FCTree.h"
#include "..\\grid\\FCTreeNode.h"
#include "..\\Label\\FCLabel.h"
#include "..\\Label\\FCLinkLabel.h"
#include "..\\div\\FCWindow.h"
#include "..\\div\\FCWindow.h"
#include "..\\chart\\PExtend.h"

using namespace FaceCat;