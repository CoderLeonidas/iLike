#include "..\\..\\stdafx.h"
#include "MainFrame.h"
#include "..\\Service\\DataCenter.h"
#include "..\\Service\\SecurityDataHelper.h"

void MainFrame::checkedChangedEvent(void *sender, void *pInvoke){
	MainFrame *mainFrame = (MainFrame*)pInvoke;
	mainFrame->onCheckedChangedEvent(sender);
}

void MainFrame::clickButton(void *sender, FCTouchInfo touchInfo, void *pInvoke){
	if (touchInfo.m_firstTouch && touchInfo.m_clicks == 1){
		MainFrame *mainFrame = (MainFrame*)pInvoke;
		FCView *control = (FCView*)sender;
		String name = control->getName();
		if(name == L"btnStart"){
			mainFrame->start();
		}
		else if(name == L"btnSearch"){
			mainFrame->startSearch();
		}
	}
}

void MainFrame::gridCellClickEvent(void *sender, FCGridCell *cell, FCTouchInfo touchInfo, void *pInvoke){
	MainFrame *mainFrame = (MainFrame*)pInvoke;
	mainFrame->onGridCellClickEvent(sender, cell, touchInfo);
}

void MainFrame::registerEvents(FCView *control){
	FCTouchEvent clickEvent = &clickButton;
	ArrayList<FCView*> controls = control->m_controls;
	for(int c = 0; c < controls.size(); c++){
		FCView *subControl = controls.get(c);
		FCButton *button = dynamic_cast<FCButton*>(subControl);
		FCCheckBox *checkBox = dynamic_cast<FCCheckBox*>(subControl);
		FCGridColumn *column = dynamic_cast<FCGridColumn*>(subControl);
		FCGrid *grid = dynamic_cast<FCGrid*>(subControl);
        if (column){
			column->setAllowDrag(true);
            column->setAllowResize(true);
			column->setBackColor(FCCOLORS_BACKCOLOR);
			column->setBorderColor(FCCOLORS_LINECOLOR2);
            column->setTextColor(FCCOLORS_FORECOLOR);
        }
		else if(checkBox){
			checkBox->setButtonBackColor(FCCOLORS_BACKCOLOR);
		}
		else if(button){
			button->addEvent(clickEvent, FCEventID::CLICK, this);
		}
		else if(grid){
			grid->setBackColor(FCColor_None);
			grid->setGridLineColor(FCColor_None);
			FCGridRowStyle rowStyle;
			rowStyle.setBackColor(FCColor_None);
			rowStyle.setSelectedBackColor(FCCOLORS_SELECTEDROWCOLOR);
			rowStyle.setHoveredBackColor(FCCOLORS_HOVEREDROWCOLOR);
			FCFont font(L"Arial", 14, false, false, false);
			rowStyle.setFont(&font);
			grid->setRowStyle(&rowStyle);
		}
		else{
			if(subControl->getControlType() == L"Div" || subControl->getControlType() == L"TabControl"
				|| subControl->getControlType() == L"TabPage" 
				|| subControl->getControlType() == L"SplitLayoutDiv"){
				subControl->setBackColor(FCColor_None);
			}
		}
		registerEvents(subControl);
	}
}

void MainFrame::selectedTabPageChangedEvent(void *sender, void *pInvoke){
	MainFrame *mainFrame = (MainFrame*)pInvoke;
	mainFrame->onSelectedTabPageChangedEvent();
}

void MainFrame::textChangedEvent(void *sender, void *pInvoke){
	MainFrame *mainFrame = (MainFrame*)pInvoke;
	mainFrame->onTextChangedEvent(sender);
}

void MainFrame::timerEvent(void *sender, int timerID, void *pInvoke){
	MainFrame *mainFrame = (MainFrame*)pInvoke;
	mainFrame->onTimerEvent(sender, timerID);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame(HWND hWnd){
	m_chartLeft = 0;
	m_chartRight = 0;
	m_chartScope = 0;
	m_host = 0;
	m_hWnd = hWnd;
	m_scaleFactor = 1;
	m_tableCodes = 0;
	m_tableResults = 0;
	m_timerID = FCView::getNewTimerID();
	m_txtCode = 0;
}

MainFrame::~MainFrame(){
	m_chartLeft = 0;
	m_chartRight = 0;
	m_chartScope = 0;
	m_host = 0;
	m_hWnd = 0;
	m_tableCodes = 0;
	m_tableResults = 0;
	m_txtCode = 0;
}

double MainFrame::getScaleFactor(){
	return m_scaleFactor;
}

void MainFrame::setScaleFactor(double scaleFactor){
	m_scaleFactor = scaleFactor;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainFrame::exit(){
}

bool MainFrame::isWindowShowing(){
	ArrayList<FCView*> controls = getNative()->getControls();
	for(int c = 0; c < controls.size(); c++){
        FCWindowFrame *frame = dynamic_cast<FCWindowFrame*>(controls.get(c));
        if (frame){
			return true;
		}
	}
	return false;
}

void MainFrame::load(const String& xmlPath){
	m_host = dynamic_cast<WinHost*>(getNative()->getHost());
	loadFile(xmlPath, 0);
	FCView *control = getNative()->getControls().get(0);
	control->setBackColor(FCCOLORS_BACKCOLOR9);
	registerEvents(control);
	DataCenter::startService();
	ALikeService *aLikeService = DataCenter::getALikeService();
	DataCenter::setMainUI(this);
	m_tableCodes = getGrid(L"tableCodes");
	m_tableCodes->addEvent(&gridCellClickEvent, FCEventID::GRIDCELLCLICK, this);
	m_tableCodes2 = getGrid(L"tableCodes2");
	m_tableCodes2->addEvent(&gridCellClickEvent, FCEventID::GRIDCELLCLICK, this);
	m_tableResults = getGrid(L"tableResults");
	m_tableResults->addEvent(&gridCellClickEvent, FCEventID::GRIDCELLCLICK, this);
	m_txtCode = getTextBox(L"txtCode");
	m_txtCode->addEvent(&textChangedEvent, FCEventID::TEXTCHANGED, this);
	m_txtCode2 = getTextBox(L"txtCode2");
	m_txtCode2->addEvent(&textChangedEvent, FCEventID::TEXTCHANGED, this);
	m_tableCodes->beginUpdate();
	map<String, SecurityHistoryData*>::iterator sIter = aLikeService->m_historyDatas.begin();
	for(; sIter != aLikeService->m_historyDatas.end(); ++sIter){
		String code = sIter->first;
		FCGridRow *row = new FCGridRow;
		m_tableCodes->addRow(row);
		FCGridStringCell *cell = new FCGridStringCell(code);
		row->addCell(0, cell);
		FCGridCellStyle *cellStyle = new FCGridCellStyle;
		cellStyle->setTextColor(FCCOLORS_FORECOLOR3);
		row->getCell(0)->setStyle(cellStyle);
		FCGridIntCell *cell2 = new FCGridIntCell;
		row->addCell(1, cell2);
	}
	m_tableCodes->endUpdate();
	m_tableCodes->invalidate();
	m_chartLeft = dynamic_cast<FCChart*>(findControl(L"chartLeft"));
	m_chartRight = dynamic_cast<FCChart*>(findControl(L"chartRight"));
	m_chartScope = dynamic_cast<FCChart*>(findControl(L"chartScope"));
	initChart(m_chartLeft);
	initChart(m_chartRight);
	initChart(m_chartScope);
	m_tableCodes->addEvent(&timerEvent, FCEventID::TIMER, this);
	FCCheckBox *cbNext = getCheckBox(L"cbNext");
	cbNext->addEvent(&checkedChangedEvent, FCEventID::CHECKEDCHANGED, this);
	getTabControl(L"tabChart")->addEvent(&selectedTabPageChangedEvent, FCEventID::SELECTEDTABPAGECHANGED, this);
}

void MainFrame::loadData(){
}

void MainFrame::resetScaleSize(FCSize clientSize){
	FCNative *native = getNative();
	if(native){
		FCSize nativeSize = native->getDisplaySize();
        ArrayList<FCView*> controls = native->getControls();
		for(int c = 0; c < controls.size(); c++){
            FCWindowFrame *frame = dynamic_cast<FCWindowFrame*>(controls.get(c));
            if (frame){
                WindowEx *window = dynamic_cast<WindowEx*>(frame->m_controls.get(0));
                if (window && !window->isAnimateMoving()){
                    FCPoint location = window->getLocation();
                    if (location.x < 10 || location.x > nativeSize.cx - 10){
                        location.x = 0;
                    }
                    if (location.y < 30 || location.y > nativeSize.cy - 30){
                        location.y = 0;
                    }
                    window->setLocation(location);
                }
            }
        }
		FCSize scaleSize ={(int)(clientSize.cx * m_scaleFactor), (int)(clientSize.cy * m_scaleFactor)};
		native->setScaleSize(scaleSize);
		native->update();
		native->invalidate();
	}
}

int MainFrame::showMessageBox(const String& text, const String& caption, UINT uType){
	return MessageBox(m_hWnd, text.c_str(), caption.c_str(), uType);
}

int MainFrame::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	if(m_host && m_host->onMessage(hWnd, message, wParam, lParam)){
		return 1;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainFrame::bindHistoryDatas(const String& code, int index){
	ALikeService *aLikeService = DataCenter::getALikeService();
	if ((int)m_likeDataInfos.size() > 0){
        if (index >= (int)m_likeDataInfos.size()){
            index = m_likeDataInfos.size() - 1;
        }
        LikeDataInfo &likeDataInfo = m_likeDataInfos[index];
        SecurityHistoryData *left = aLikeService->m_historyDatas[likeDataInfo.m_leftCode];
        SecurityHistoryData *right = aLikeService->m_historyDatas[likeDataInfo.m_rightCode];
		getLabel(L"lblStock1")->setText(left->m_security->m_code);
		getLabel(L"lblStock2")->setText(right->m_security->m_code);
        vector<SecurityData*> leftDatas;
        vector<SecurityData*> rightDatas;
		int leftDatasSize = (int)left->m_datasSize;
		FCCheckBox *cbNext = getCheckBox(L"cbNext");
		for(int i = 0; i < leftDatasSize; i++){
			SecurityData *data = left->m_datas[i];
			if(cbNext->isChecked()){
				if (data->m_date >= likeDataInfo.m_leftStartDate){
					leftDatas.push_back(data);
				}
			}
			else{
				if (data->m_date >= likeDataInfo.m_leftStartDate && data->m_date <= likeDataInfo.m_leftStopDate){
					leftDatas.push_back(data);
				}
			}
        }
		int rightDatasSize = (int)right->m_datasSize;
        for(int i = 0; i < rightDatasSize; i++){
			SecurityData *data = right->m_datas[i];
			if(cbNext->isChecked()){
				if (data->m_date >= likeDataInfo.m_rightStartDate){
					rightDatas.push_back(data);
				}
			}
			else{
				if (data->m_date >= likeDataInfo.m_rightStartDate && data->m_date <= likeDataInfo.m_rightStopDate){
					rightDatas.push_back(data);
				}
			}
        }
		if((int)leftDatas.size() > 0 && (int)rightDatas.size() > 0){
			int fields[6];
			fields[0] = CLOSE_INDEX;
			fields[1] = HIGH_INDEX;
			fields[2] = LOW_INDEX;
			fields[3] = OPEN_INDEX;
			fields[4] = VOL_INDEX;
			fields[5] = AMOUNT_INDEX;
			vector<FCScript*> indicators;
			SecurityDataHelper::bindHistoryDatas(m_chartLeft, m_chartLeft->getDataSource(), &indicators, fields, &leftDatas);
			SecurityDataHelper::bindHistoryDatas(m_chartRight, m_chartRight->getDataSource(), &indicators, fields, &rightDatas);
			leftDatas.clear();
			rightDatas.clear();
			FCDataTable *leftDataSource = m_chartLeft->getDataSource();
			BarShape *leftBar = dynamic_cast<BarShape*>(m_chartLeft->getDivs().get(1)->getShapes(SortType_ASC).get(0));
			int rowsSize = leftDataSource->rowsCount();
			for (int i = 0; i < rowsSize; i++){
				double volume = leftDataSource->get2(i, VOL_INDEX);
				double close = leftDataSource->get2(i, CLOSE_INDEX);
				double open = leftDataSource->get2(i, OPEN_INDEX);
				if (close >= open){
					leftDataSource->set2(i, leftBar->getStyleField(), 1);
					leftDataSource->set2(i, leftBar->getColorField(), FCCOLORS_UPCOLOR);
				}
				else{
					leftDataSource->set2(i, leftBar->getStyleField(), 0);
					leftDataSource->set2(i, leftBar->getColorField(), FCCOLORS_DOWNCOLOR);
				}
			}
			FCDataTable *rightDataSource = m_chartRight->getDataSource();
			BarShape *rightBar = dynamic_cast<BarShape*>(m_chartRight->getDivs().get(1)->getShapes(SortType_ASC).get(0));
			rowsSize = rightDataSource->rowsCount();
			for (int i = 0; i < rowsSize; i++){
				double volume = rightDataSource->get2(i, VOL_INDEX);
				double close = rightDataSource->get2(i, CLOSE_INDEX);
				double open = rightDataSource->get2(i, OPEN_INDEX);
				if (close >= open){
					rightDataSource->set2(i, rightBar->getStyleField(), 1);
					rightDataSource->set2(i, rightBar->getColorField(), FCCOLORS_UPCOLOR);
				}
				else{
					rightDataSource->set2(i, rightBar->getStyleField(), 0);
					rightDataSource->set2(i, rightBar->getColorField(), FCCOLORS_DOWNCOLOR);
				}
			}
			m_chartLeft->update();
			m_chartRight->update();
			m_chartLeft->scrollLeftToBegin();
			m_chartRight->scrollLeftToBegin();
			m_chartLeft->update();
			m_chartRight->update();
			getNative()->invalidate();
		}
		else{
			m_chartLeft->clear();
			m_chartRight->clear();
			m_chartLeft->update();
			m_chartRight->update();
			getNative()->invalidate();
		}
    }
	else{
		m_chartLeft->clear();
		m_chartRight->clear();
		m_chartLeft->update();
		m_chartRight->update();
		getNative()->invalidate();
	}
}

void MainFrame::bindResultTable(const String& code){
	ALikeService *aLikeService = DataCenter::getALikeService();
	m_tableResults->clearRows();
	m_tableResults->beginUpdate();
	int score = 0;
	vector<LikeDataInfo>::iterator sIter = m_likeDataInfos.begin();
	int count = 0;
	for(; sIter != m_likeDataInfos.end(); ++sIter){
		LikeDataInfo &likeDataInfo = *sIter;
		FCGridRow *row = new FCGridRow;
		m_tableResults->addRow(row);
		FCGridIntCell *cell = new FCGridIntCell();
		cell->setInt((int)likeDataInfo.m_score);
		row->addCell(0, cell);
		FCGridCellStyle *cellStyle1 = new FCGridCellStyle;
		if((int)likeDataInfo.m_score > aLikeService->getMaxScore()){
			cellStyle1->setTextColor(FCCOLORS_UPCOLOR);
		}
		else{
			cellStyle1->setTextColor(FCCOLORS_DOWNCOLOR);
		}
		cell->getRow()->getCell(0)->setStyle(cellStyle1);
		FCGridStringCell *cell2 = new FCGridStringCell(likeDataInfo.m_rightCode.c_str());
		row->addCell(1, cell2);
		FCGridCellStyle *cellStyle2 = new FCGridCellStyle;
		cellStyle2->setTextColor(FCCOLORS_FORECOLOR3);
		row->getCell(1)->setStyle(cellStyle2);
		count++;
		if(count > 10){
			break;
		}
	}
	if((int)m_likeDataInfos.size() > 0){
		score = m_likeDataInfos[0].m_score;
	}
	m_tableResults->endUpdate();
	ArrayList<FCGridRow*> selectedRows;
	if((int)m_tableResults->m_rows.size() > 0){
		selectedRows.add(m_tableResults->m_rows.get(0));
	}
	m_tableResults->setSelectedRows(selectedRows);
	m_tableResults->invalidate();
}

void MainFrame::bindSandBoxTable(vector<LikeDataInfo> *likeDataInfos){
	m_tableCodes2->clearRows();
	m_tableCodes2->beginUpdate();
	vector<LikeDataInfo>::iterator sIter = likeDataInfos->begin();
	int count = 0;
	for(; sIter != likeDataInfos->end(); ++sIter){
		LikeDataInfo &likeDataInfo = *sIter;
		FCGridRow *row = new FCGridRow;
		m_tableCodes2->addRow(row);
		FCGridStringCell *cell = new FCGridStringCell(likeDataInfo.m_rightCode);
		row->addCell(0, cell);
		FCGridDoubleCell *cell2 = new FCGridDoubleCell(likeDataInfo.m_diffRange);
		row->addCell(1, cell2);
		FCGridDoubleCell *cell3 = new FCGridDoubleCell(likeDataInfo.m_rightStartDate);
		row->addCell(2, cell3);
		FCGridDoubleCell *cell4 = new FCGridDoubleCell(likeDataInfo.m_rightStopDate);
		row->addCell(3, cell4);
	}
	m_tableCodes2->endUpdate();
	ArrayList<FCGridRow*> selectedRows;
	if((int)m_tableCodes2->m_rows.size() > 0){
		selectedRows.add(m_tableCodes2->m_rows.get(0));
	}
	m_tableCodes2->setSelectedRows(selectedRows);
	m_tableCodes2->invalidate();
}

void MainFrame::initChart(FCChart *chart){
	FCDataTable *dataSource = chart->getDataSource();
	chart->setBackColor(FCCOLORS_BACKCOLOR4);
	chart->setBorderColor(FCCOLORS_LINECOLOR4);
	chart->setCanMoveShape(true);
	chart->setScrollAddSpeed(true);
	chart->setLeftVScaleWidth(85);
	chart->setRightVScaleWidth(85);
	chart->setHScalePixel(10);
	chart->setHScaleFieldText(L"日期");
	ChartDiv *candleDiv = chart->getDivs().get(0);
	candleDiv->getTitleBar()->setText(L"日线");
	candleDiv->getVGrid()->setVisible(true);
	candleDiv->getLeftVScale()->setNumberStyle(NumberStyle_Underline);
	candleDiv->getLeftVScale()->setPaddingTop(2);
	candleDiv->getLeftVScale()->setPaddingBottom(2);
	FCFont vFont(L"Arial", 14, false, false, false);
	candleDiv->getLeftVScale()->setFont(&vFont);
	candleDiv->getRightVScale()->setNumberStyle(NumberStyle_Underline);
	candleDiv->getRightVScale()->setFont(&vFont);
	candleDiv->getRightVScale()->setPaddingTop(2);
    candleDiv->getRightVScale()->setPaddingBottom(2);
	ChartTitle *priceTitle = new ChartTitle(CLOSE_INDEX, L"CLOSE", FCCOLORS_FORECOLOR, 2, true);
    priceTitle->setFieldTextMode(TextMode_Value);
    candleDiv->getTitleBar()->Titles.add(priceTitle);
	CandleShape *candle = new CandleShape;
	candleDiv->addShape(candle);
	candleDiv->setBackColor(FCCOLORS_BACKCOLOR4);
	candle->setCloseField(CLOSE_INDEX);
	candle->setOpenField(OPEN_INDEX);
	candle->setHighField(HIGH_INDEX);
	candle->setLowField(LOW_INDEX);
	candle->setCloseFieldText(L"收盘");
	candle->setHighFieldText(L"最高");
	candle->setLowFieldText(L"最低");
	candle->setOpenFieldText(L"开盘");
	ChartDiv *volumeDiv = chart->getDivs().get(1);
	volumeDiv->setBackColor(FCCOLORS_BACKCOLOR4);
	volumeDiv->getVGrid()->setDistance(30);
	volumeDiv->getLeftVScale()->setDigit(0);
	volumeDiv->getLeftVScale()->setFont(&vFont);
	volumeDiv->getRightVScale()->setDigit(0);
	volumeDiv->getRightVScale()->setFont(&vFont);
	BarShape *bar = new BarShape;
	int styleField = dataSource->AUTOFIELD();
	int colorField = dataSource->AUTOFIELD();
	bar->setColorField(colorField);
	bar->setStyleField(styleField);
	bar->setFieldName(VOL_INDEX);
	bar->setFieldText(VOL);
	volumeDiv->addShape(bar);
	volumeDiv->getTitleBar()->setText(L"成交量");
	ChartTitle *barTitle = new ChartTitle(VOL_INDEX, L"成交量", bar->getDownColor(), 0, true);
	barTitle->setFieldTextMode(TextMode_Value);
	volumeDiv->getTitleBar()->Titles.add(barTitle);
	candleDiv->getHScale()->setVisible(false);
	candleDiv->getHScale()->setHeight(0);
	volumeDiv->getHScale()->setVisible(true);
	volumeDiv->getHScale()->setHeight(22);
	volumeDiv->getLeftVScale()->setTextColor(FCCOLORS_FORECOLOR2);
	volumeDiv->getRightVScale()->setTextColor(FCCOLORS_FORECOLOR2);
	dataSource->addColumn(CLOSE_INDEX);
	dataSource->addColumn(OPEN_INDEX);
	dataSource->addColumn(HIGH_INDEX);
	dataSource->addColumn(LOW_INDEX);
	dataSource->addColumn(VOL_INDEX);
	dataSource->addColumn(AMOUNT_INDEX);
	dataSource->addColumn(colorField);
	dataSource->addColumn(styleField);
	dataSource->setColsCapacity(16);
	dataSource->setColsGrowStep(4);
}

void MainFrame::onCheckedChangedEvent(void *sender){
	ArrayList<FCGridRow*> selectedRows = m_tableCodes->getSelectedRows();
	int selectedRowsSize = (int)selectedRows.size();
	if(selectedRowsSize > 0){
		String code = selectedRows.get(0)->getCell(0)->getText();
		ArrayList<FCGridRow*> selectedRows2 = m_tableResults->getSelectedRows();
		int index = 0;
		if((int)selectedRows2.size() > 0){
			index = selectedRows2.get(0)->getIndex();
		}
		bindHistoryDatas(code, index);
	}
}

void MainFrame::onGridCellClickEvent(void *sender, FCGridCell *cell, FCTouchInfo touchInfo){
	ALikeService *aLikeService = DataCenter::getALikeService();
	if(aLikeService->isCompleted()){
		if(cell->getGrid() == m_tableCodes){
			String code = cell->getRow()->getCell(0)->getText();
			if(getTabControl(L"tabChart")->getSelectedIndex() == 0){
				FCSpin *spinN = getSpin(L"spinN");
				FCSpin *spinM = getSpin(L"spinM");
				aLikeService->setN((int)spinN->getValue());
				aLikeService->setM((int)spinM->getValue());
				aLikeService->m_historyDatas[code]->m_startIndex = -1;
				aLikeService->start(code, &m_likeDataInfos);
				bindHistoryDatas(code, 0);
				bindResultTable(code);
				FCGridCellStyle *cellStyle = new FCGridCellStyle;
				int score = 0;
				if ((int)m_likeDataInfos.size() > 0){
					score = m_likeDataInfos[0].m_score;
				}
				if(score > aLikeService->getMaxScore()){
					cellStyle->setTextColor(FCCOLORS_UPCOLOR);
				}
				else{
					cellStyle->setTextColor(FCCOLORS_DOWNCOLOR);
				}
				cell->getRow()->getCell(1)->setStyle(cellStyle);
				cell->getRow()->getCell(1)->setInt(score);
			}
			m_chartScope->clear();
			m_chartScope->update();
			int fields[6];
			fields[0] = CLOSE_INDEX;
			fields[1] = HIGH_INDEX;
			fields[2] = LOW_INDEX;
			fields[3] = OPEN_INDEX;
			fields[4] = VOL_INDEX;
			fields[5] = AMOUNT_INDEX;
			vector<SecurityData*> historyDatas;
			int historyDatasSize = (int)aLikeService->m_historyDatas[code]->m_datasSize;
			for(int i = 0; i < historyDatasSize; i++){
				historyDatas.push_back(aLikeService->m_historyDatas[code]->m_datas[i]);
			}
			vector<FCScript*> indicators;
			SecurityDataHelper::bindHistoryDatas(m_chartScope, m_chartScope->getDataSource(), &indicators, fields, &historyDatas);
			FCDataTable *dataSource = m_chartScope->getDataSource();
			BarShape *scopeBar = dynamic_cast<BarShape*>(m_chartScope->getDivs().get(1)->getShapes(SortType_ASC).get(0));
			int rowsSize = dataSource->rowsCount();
			for (int i = 0; i < rowsSize; i++){
				double volume = dataSource->get2(i, VOL_INDEX);
				double close = dataSource->get2(i, CLOSE_INDEX);
				double open = dataSource->get2(i, OPEN_INDEX);
				if (close >= open){
					dataSource->set2(i, scopeBar->getStyleField(), 1);
					dataSource->set2(i, scopeBar->getColorField(), FCCOLORS_UPCOLOR);
				}
				else{
					dataSource->set2(i, scopeBar->getStyleField(), 0);
					dataSource->set2(i, scopeBar->getColorField(), FCCOLORS_DOWNCOLOR);
				}
			}
			m_chartScope->update();
			m_chartScope->invalidate();
		}
		else if(cell->getGrid() == m_tableCodes2){
			String code = cell->getRow()->getCell(0)->getText();
			double startDate = cell->getRow()->getCell(2)->getDouble();
			double endDate = cell->getRow()->getCell(3)->getDouble();
			m_chartScope->clear();
			m_chartScope->update();
			int fields[6];
			fields[0] = CLOSE_INDEX;
			fields[1] = HIGH_INDEX;
			fields[2] = LOW_INDEX;
			fields[3] = OPEN_INDEX;
			fields[4] = VOL_INDEX;
			fields[5] = AMOUNT_INDEX;
			vector<SecurityData*> historyDatas;
			int historyDatasSize = (int)aLikeService->m_historyDatas[code]->m_datasSize;
			for(int i = 0; i < historyDatasSize; i++){
				SecurityData *securityData = aLikeService->m_historyDatas[code]->m_datas[i];
				if(securityData->m_date >= startDate && securityData->m_date <= endDate){
					historyDatas.push_back(securityData);
				}
			}
			vector<FCScript*> indicators;
			SecurityDataHelper::bindHistoryDatas(m_chartScope, m_chartScope->getDataSource(), &indicators, fields, &historyDatas);
			FCDataTable *dataSource = m_chartScope->getDataSource();
			BarShape *scopeBar = dynamic_cast<BarShape*>(m_chartScope->getDivs().get(1)->getShapes(SortType_ASC).get(0));
			int rowsSize = dataSource->rowsCount();
			for (int i = 0; i < rowsSize; i++){
				double volume = dataSource->get2(i, VOL_INDEX);
				double close = dataSource->get2(i, CLOSE_INDEX);
				double open = dataSource->get2(i, OPEN_INDEX);
				if (close >= open){
					dataSource->set2(i, scopeBar->getStyleField(), 1);
					dataSource->set2(i, scopeBar->getColorField(), FCCOLORS_UPCOLOR);
				}
				else{
					dataSource->set2(i, scopeBar->getStyleField(), 0);
					dataSource->set2(i, scopeBar->getColorField(), FCCOLORS_DOWNCOLOR);
				}
			}
			m_chartScope->update();
			m_chartScope->invalidate();
		}
		else if(cell->getGrid() == m_tableResults){
			bindHistoryDatas(m_tableCodes->getSelectedRows().get(0)->getCell(0)->getText(), cell->getRow()->getIndex());
		}
	}
}

void MainFrame::onSelectedTabPageChangedEvent(){
	if(getTabControl(L"tabChart")->getSelectedIndex() == 0){
		ArrayList<ChartDiv*> divs = m_chartScope->getDivs();
		for(int c = 0; c < divs.size(); c++){
			ChartDiv *div = divs.get(c);
			SelectArea *selectArea = div->getSelectArea();
			if(selectArea->isVisible()){
				FCGrid *selectedGrid = m_tableCodes;
				if(getTabControl(L"tabCodes")->getSelectedIndex() == 1){
					selectedGrid = m_tableCodes2;
				}
				ArrayList<FCGridRow*> selectedRows = selectedGrid->getSelectedRows();
				int selectedRowsSize = (int)selectedRows.size();
				if(selectedRowsSize > 0){
					String code = selectedRows.get(0)->getCell(0)->getText();
					ALikeService *aLikeService = DataCenter::getALikeService();
					FCRect bounds = selectArea->getBounds();
					FCPoint sPoint ={bounds.left, bounds.top};
					int sIndex = m_chartScope->getIndex(sPoint);
					FCPoint ePoint ={bounds.right, bounds.top};
					int eIndex = m_chartScope->getIndex(ePoint);
					if(eIndex > sIndex){
						double startDate = m_chartScope->getDataSource()->getXValue(sIndex);
						int startIndex = 0;
						int historyDatasSize = (int)aLikeService->m_historyDatas[code]->m_datasSize;
						for(startIndex = 0; startIndex < historyDatasSize; startIndex++){
							SecurityData *securityData = aLikeService->m_historyDatas[code]->m_datas[startIndex];
							if(securityData->m_date >= startDate){
								break;
							}
						}
						aLikeService->m_historyDatas[code]->m_startIndex = startIndex;
						aLikeService->setM(eIndex - sIndex + 1);
						aLikeService->start(code, &m_likeDataInfos);
						bindHistoryDatas(code, 0);
						bindResultTable(code);
					}
				}
				break;
			}
		}
	}
}

void MainFrame::onTextChangedEvent(void *sender){
	if(sender == m_txtCode){
		String text = m_txtCode->getText();
		ArrayList<FCGridRow*> rows = m_tableCodes->m_rows;
		for(int r = 0; r < rows.size(); r++){
			FCGridRow *row = rows.get(r);
			String cellText = row->getCell(0)->getText();
			if((int)cellText.length() == 0 || (int)cellText.find(text) == 0){
				row->setVisible(true);
			}
			else{
				row->setVisible(false);
			}
		}
		m_tableCodes->update();
		m_tableCodes->invalidate();
	}
	else if(sender == m_txtCode2){
		String text = m_txtCode2->getText();
		ArrayList<FCGridRow*> rows = m_tableCodes2->m_rows;
		for(int r = 0; r < rows.size(); r++){
			FCGridRow *row = rows.get(r);
			String cellText = row->getCell(0)->getText();
			if((int)cellText.length() == 0 || (int)cellText.find(text) == 0){
				row->setVisible(true);
			}
			else{
				row->setVisible(false);
			}
		}
		m_tableCodes2->update();
		m_tableCodes2->invalidate();
	}
}

void MainFrame::onTimerEvent(void *sender, int timerID){
	ALikeService *aLikeService = DataCenter::getALikeService();
	FCButton *btnStart = getButton(L"btnStart");
	if(aLikeService->getCurCount() > 0){
		wchar_t sz[1024] ={0};
		_stprintf_s(sz, 1023, L"%d/%d", aLikeService->getCurCount(), (int)aLikeService->m_historyDatas.size());
		btnStart->setText(sz);
		btnStart->invalidate();
	}
	else if(aLikeService->getCurCount() == -1){
		ArrayList<FCGridRow*> rows = m_tableCodes->m_rows;
		for(int r = 0; r < rows.size(); r++){
			FCGridRow *row = rows.get(r);
			String code = row->getCell(0)->getText();
			int score = 0;
			aLikeService->getData(code, &m_likeDataInfos);
			if(m_likeDataInfos.size() > 0){
				score = m_likeDataInfos[0].m_score;
			}
			FCGridCellStyle *cellStyle = new FCGridCellStyle;
			if(score > aLikeService->getMaxScore()){
				cellStyle->setTextColor(FCCOLORS_UPCOLOR);
			}
			else{
				cellStyle->setTextColor(FCCOLORS_DOWNCOLOR);
			}
			row->getCell(1)->setStyle(cellStyle);
			row->getCell(1)->setInt(score);
		}
		btnStart->setText(L"全面相似对比");
		getNative()->invalidate();
		m_tableCodes->stopTimer(m_timerID);
	}
}

void MainFrame::start(){
	ALikeService *aLikeService = DataCenter::getALikeService();
	if(aLikeService->isCompleted()){
		getTabControl(L"tabCodes")->setSelectedIndex(0);
		FCSpin *spinN = getSpin(L"spinN");
		FCSpin *spinM = getSpin(L"spinM");
		aLikeService->setN((int)spinN->getValue());
		aLikeService->setM((int)spinM->getValue());
		FCSpin *spinThreads = getSpin(L"spinThreads");
		aLikeService->setThreads((int)spinThreads->getValue());
		aLikeService->start();
		m_tableCodes->startTimer(m_timerID, 1000);
	}
}

void MainFrame::startSearch(){
	ALikeService *aLikeService = DataCenter::getALikeService();
	if(aLikeService->isCompleted()){
		getTabControl(L"tabChart")->setSelectedIndex(1);
		getTabControl(L"tabCodes")->setSelectedIndex(1);
		FCSpin *spinN = getSpin(L"spinN");
		FCSpin *spinM = getSpin(L"spinM");
		FCSpin *spinRangeMax = getSpin(L"spinRangeMax");
		FCSpin *spinRangeMin = getSpin(L"spinRangeMin");
		FCSpin *spinSwingDown = getSpin(L"spinSwingDown");
		FCSpin *spinSwingUp = getSpin(L"spinSwingUp");
		aLikeService->setN((int)spinN->getValue());
		aLikeService->setM((int)spinM->getValue());
		FCSpin *spinThreads = getSpin(L"spinThreads");
		aLikeService->setThreads((int)spinThreads->getValue());
		aLikeService->sandBoxInfo->m_rangeMax = spinRangeMax->getValue() / 100;
		aLikeService->sandBoxInfo->m_rangeMin = spinRangeMin->getValue() / 100;
		aLikeService->sandBoxInfo->m_swingDown = spinSwingDown->getValue() / 100;
		aLikeService->sandBoxInfo->m_swingUp = spinSwingUp->getValue() / 100;
		aLikeService->startSandBox((int)spinM->getValue(), &m_likeDataInfos);
		bindSandBoxTable(&m_likeDataInfos);
	}
}