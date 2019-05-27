#include "..\\..\\stdafx.h"
#include "RibbonButton.h"

RibbonButton::RibbonButton(){
	m_arrowType = 0;
	m_isClose = false;
	m_isTabClose = false;
	m_selected = false;
	setBackColor(FCColor_None);
    setBorderColor(FCColor_None);
}

RibbonButton::~RibbonButton(){
}

int RibbonButton::getArrowType(){
	return m_arrowType;
}

void RibbonButton::setArrowType(int arrowType){
	m_arrowType = arrowType;
}

bool RibbonButton::isClose(){
	return m_isClose;
}

void RibbonButton::setClose(bool isClose){
	m_isClose = isClose;
}

bool RibbonButton::isTabClose(){
	return m_isTabClose;
}

void RibbonButton::setTabClose(bool isTabClose){
	m_isTabClose = isTabClose;
}

bool RibbonButton::isSelected(){
	FCView *parent = getParent();
    if (parent){
        FCTabControl *tabControl = dynamic_cast<FCTabControl*>(parent);
        if (tabControl){
            FCTabPage *selectedTabPage = tabControl->getSelectedTabPage();
            if (selectedTabPage){
                if (this == selectedTabPage->getHeaderButton()){
                    return true;
                }
            }
        }
		else{
			return m_selected;
		}
    }
    return false;
}

void RibbonButton::setSelected(bool selected){
	m_selected = selected;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Long RibbonButton::getPaintingTextColor(){
	if (isPaintEnabled(this)){
        return FCCOLORS_FORECOLOR;
    }
    else{
		return FCColor_DisabledText;;
    }
}

void RibbonButton::onDoubleClick(FCTouchInfo touchInfo){
	FCButton::onDoubleClick(touchInfo);
	FCPoint mp = touchInfo.m_firstPoint;
	if(!isDragging()){
		if(m_isTabClose){
			int width = getWidth(), height = getHeight();
			FCRect ellipseRect ={width - 20, 2, width - 5, height - 3};
			if(mp.x >= ellipseRect.left && mp.x <= ellipseRect.right
				&& mp.y >= ellipseRect.top && mp.y <= ellipseRect.bottom){
				FCView *parent = getParent();
				if (parent){
					FCTabControl *tabControl = dynamic_cast<FCTabControl*>(parent);
					if (tabControl){
						FCTabPage *tabPage = 0;
						ArrayList<FCTabPage*> tabPages = tabControl->m_tabPages;
						for(int t = 0; t < tabPages.size(); t++){
							FCTabPage *tp = tabPages.get(t);
							FCButton *headerButton = tp->getHeaderButton();
							if(headerButton == this){
								tabPage = tp;
								break;
							}
						}
						for(int t = 0; t < tabPages.size(); t++){
							FCTabPage *tp = tabPages.get(t);
							if(tp != tabPage && tp->getHeaderButton()->isVisible()){
								tabControl->setSelectedTabPage(tp);
								break;
							}
						}
						setVisible(false);
						tabControl->update();
						tabControl->invalidate();
					}
				}
			}
		}
	}
}

void RibbonButton::onPaintBackground(FCPaint *paint, const FCRect& clipRect){
	FCNative *native = getNative();
	int width = getWidth(), height = getHeight();
    int mw = width / 2, mh = height / 2;
	FCRect drawRect = {0, 0, width, height};
	int cornerRadius = 0;
    if (m_isClose){
        Long lineColor = FCCOLORS_LINECOLOR;
		FCRect ellipseRect ={1, 1, width - 2, height - 2};
        paint->fillEllipse(FCCOLORS_BACKCOLOR7, ellipseRect);
		FCDraw::drawText(paint, L"นุ", lineColor, getFont(), 5, 4);
    }
	else{
		cornerRadius = 4;
		if (m_arrowType > 0){
			cornerRadius = 0;
		}
		FCView *parent = getParent();
		if (parent){
			FCTabControl *tabControl = dynamic_cast<FCTabControl*>(parent);
			if (tabControl){
				cornerRadius = 0;
			}
		}
		if(cornerRadius > 0){
			paint->fillGradientRect(FCCOLORS_BACKCOLOR, FCCOLORS_BACKCOLOR2, drawRect, cornerRadius, 90);
			paint->drawRoundRect(FCColor_Border, 1, 0, drawRect, cornerRadius);
		}
		else{
			paint->fillGradientRect(FCCOLORS_BACKCOLOR, FCCOLORS_BACKCOLOR2, drawRect, cornerRadius, 90);
			paint->drawRect(FCColor_Border, 1, 0, drawRect);
		}
		cornerRadius = 0;
		if (m_arrowType > 0){
			FCPoint point1 ={0};
			FCPoint point2 ={0};
			FCPoint point3 ={0};
			int ts = min(mw, mh) / 2;
			switch (m_arrowType){
				case 1:
					point1.x = mw - ts;
					point1.y = mh;
					point2.x = mw + ts;
					point2.y = mh - ts;
					point3.x = mw + ts;
					point3.y = mh + ts;
					break;
				case 2:
					point1.x = mw + ts;
					point1.y = mh;
					point2.x = mw - ts;
					point2.y = mh - ts;
					point3.x = mw - ts;
					point3.y = mh + ts;
					break;
				case 3:
					point1.x = mw;
					point1.y = mh - ts;
					point2.x = mw - ts;
					point2.y = mh + ts;
					point3.x = mw + ts;
					point3.y = mh + ts;
					break;
				case 4:
					point1.x = mw;
					point1.y = mh + ts;
					point2.x = mw - ts;
					point2.y = mh - ts;
					point3.x = mw + ts;
					point3.y = mh - ts;
					break;
			}
			FCPoint points[3];
			points[0] = point1;
			points[1] = point2;
			points[2] = point3;
			paint->fillPolygon(FCCOLORS_FORECOLOR, points, 3);
		}
	}
	bool state = false;
	if (isSelected()){
		state = true;
		paint->fillRoundRect(FCCOLORS_BACKCOLOR3, drawRect, cornerRadius);
	}
	else if (this == native->getPushedControl()){
		state = true;
		paint->fillRoundRect(FCCOLORS_BACKCOLOR6, drawRect, cornerRadius);
	}
	else if (this == native->getHoveredControl()){
		state = true;
		paint->fillRoundRect(FCCOLORS_BACKCOLOR5, drawRect, cornerRadius);
	}
	if(state){
		if(cornerRadius > 0){
			paint->drawRoundRect(FCColor_Border, 2, 0, drawRect, cornerRadius);
		}
		else{
			paint->drawRect(FCColor_Border, 1, 0, drawRect);
		}
	}
	if(!isDragging()){
		if(m_isTabClose){
			if(this == native->getPushedControl() || this == native->getHoveredControl()){
				Long lineColor = FCCOLORS_LINECOLOR;
				FCRect ellipseRect ={width - 20, 2, width - 5, height - 3};
				paint->fillEllipse(FCCOLORS_BACKCOLOR7, ellipseRect);
				paint->drawLine(lineColor, 2, 0, ellipseRect.left + 4, ellipseRect.top + 4, ellipseRect.right - 5, ellipseRect.bottom - 4);
				paint->drawLine(lineColor, 2, 0, ellipseRect.left + 4, ellipseRect.bottom - 4, ellipseRect.right - 5, ellipseRect.top + 4);
			}
		}
	}
}

