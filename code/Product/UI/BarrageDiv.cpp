#include "..\\..\\stdafx.h"
#include "BarrageDiv.h"
#include "RibbonButton.h"

Barrage::Barrage(){
	m_color = 0;
	m_font = new FCFont(L"SimSun", 40, true, false, false);
	m_mode = 0;
	m_rect.left = 0;
	m_rect.top = 0;
	m_rect.right = 0;
	m_rect.bottom = 0;
	m_speed = 2;
	m_text = L"";
	m_tick = 200;
}

Barrage::~Barrage(){
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Long Barrage::getColor(){
	return m_color;
}

void Barrage::setColor(Long color){
	m_color = color;
}

FCFont* Barrage::getFont(){
	return m_font;
}

void Barrage::setFONT(FCFont *font){
	m_font->copy(font);
}

int Barrage::getMode(){
	return m_mode;
}

void Barrage::setMode(int mode){
	m_mode = mode;
}

int Barrage::getSpeed(){
	return m_speed;
}

void Barrage::setSpeed(int speed){
	m_speed = speed;
}

FCRect Barrage::getRect(){
	return m_rect;
}

void Barrage::setRect(const FCRect& rect){
	m_rect = rect;
}

String Barrage::getText(){
	return m_text;
}

void Barrage::setText(const String& text){
	m_text = text;
}

int Barrage::getTick(){
	return m_tick;
}

void Barrage::setTick(int tick){
	m_tick = tick;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Barrage::calculate(){
    m_rect.left -= m_speed;
    m_rect.right -= m_speed;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BarrageDiv::BarrageDiv(){
	m_sysColors[0] = FCColor::argb(255, 255, 255);
	m_sysColors[1] = FCColor::argb(255,255,0);
	m_sysColors[2] = FCColor::argb(255, 0, 255);
    m_sysColors[3] = FCColor::argb(0, 255, 0);
	m_sysColors[4] = FCColor::argb(82, 255, 255);
	m_sysColors[5] = FCColor::argb(255, 82, 82);
	m_tick = 0;
	m_tick2 = 0;
	m_timerID = getNewTimerID();
	setBackColor(FCColor_None);
}

BarrageDiv::~BarrageDiv(){
	stopTimer(m_timerID);
	m_lock.lock();
	vector<Barrage*>::iterator sIter = m_barrages.begin();
	for(; sIter != m_barrages.end(); ++sIter){
		delete *sIter;
	}
	m_barrages.clear();
	m_lock.unLock();
	m_directionX.clear();
	m_directionY.clear();
	m_oldLocations.clear();
	m_speeds.clear();
	m_subControls.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BarrageDiv::addBarrage(Barrage *barrage){
	barrage->setColor(m_sysColors[m_tick % 6]);
	int width = getWidth(), height = getHeight();
	if(height < 100){
		height = 100;
	}
	int mode = barrage->getMode();
	if(barrage->getMode() == 0){
		FCRect rect ={width, rand() % (height - 20), width, 0};
		barrage->setRect(rect);
	}
	else{
		int left = 0, top = 0;
		if(width > 200){
			left = rand() % (width - 200);
		}
		if(height > 200){
			top = rand() & (height - 200);
		}
		FCRect rect ={left, top, left, 0};
		barrage->setRect(rect);
	}
	m_lock.lock();
	m_barrages.push_back(barrage);
	m_lock.unLock();
	m_tick++;
}

bool BarrageDiv::containsPoint(const FCPoint& point){
	return false;
}

void BarrageDiv::getSubControls(FCView *control){
	ArrayList<FCView*> controls;
	if(control){
		controls = control->getControls();
	}
	else{
		controls = m_native->getControls();
	}
	int controlsSize = (int)controls.size();
	for(int i = 0; i < controlsSize; i++){
		FCView *subControl = controls.get(i);
		if(subControl->isVisible()){
			if(subControl->getParent() && subControl->getControlType() != L"HScrollBar" && subControl->getControlType() != L"VScrollBar"
				&& subControl->getControlType() != L"SplitLayoutDiv" && subControl->getControlType() != L"TabControl" && subControl->getControlType() != L"TabPage"
				&& subControl->getControlType() != L"Grid" && subControl->getControlType() != L"Div"){
				m_subControls.push_back(subControl);
			}
			if(subControl->getControlType() == L"Grid"){
				dynamic_cast<FCGrid*>(subControl)->beginUpdate();
			}
			getSubControls(subControl);
		}
	}
}

void BarrageDiv::onLoad(){
	FCView::onLoad();
	startTimer(m_timerID, 1);
}

void BarrageDiv::onPaintBackground(FCPaint *paint, const FCRect& clipRect){
	FCView::onPaintBackground(paint, clipRect);
	m_lock.lock();
	vector<Barrage*>::iterator sIter = m_barrages.begin();
	for(; sIter != m_barrages.end(); ++sIter){
		Barrage *brg = *sIter;
		FCFont* font = brg->getFont();
		FCRect rect = brg->getRect();
		String str = brg->getText();
		FCSize size = paint->textSize(str.c_str(), font);
		rect.right = rect.left + size.cx;
		rect.bottom = rect.top + size.cy;
		brg->setRect(rect);
		Long color = brg->getColor();
        int mode = brg->getMode();
        if (mode == 1){
            int a = 0, r = 0, g = 0, b = 0;
			FCColor::toArgb(0, color, &a, &r, &g, &b);
            a = a * brg->getTick() / 400;
			color = FCColor::argb(a, r, g, b);
        }
		paint->drawText(str.c_str(), color, font, rect);	
	}
	m_lock.unLock();
	if(m_tick2 > 1500){
		vector<FCPoint> points;
		map<FCView*, FCPoint>::iterator sIter = m_oldLocations.begin();
		for(; sIter != m_oldLocations.end(); ++sIter){
			FCView *control = sIter->first;
			FCSize size = sIter->first->getSize();
			FCPoint mp ={0, 0};
			FCPoint location = control->pointToNative(mp);
			int oX = location.x + size.cx / 2;
			int oY = location.y + size.cy / 2;
			FCPoint oP ={oX, oY};
			points.push_back(oP);
		}
		int pointsSize = (int)points.size();
		for(int i = 0; i < pointsSize; i++){
			FCPoint pA = points[i];
			for(int j = 0; j < pointsSize; j++){
				FCPoint pB = points[j];
				if(pA.x != pB.x && pA.y != pB.y){
					if(abs(pA.x - pB.x) < 100 && abs(pA.y - pB.y) < 100){
						paint->drawLine(FCColor::argb(50, 43, 138, 195), 5, 0, pA.x, pA.y, pB.x, pB.y);
					}
				}
			}
		}
		points.clear();
	}
}

void BarrageDiv::onTimer(int timerID){
	FCView::onTimer(timerID);
    if (m_timerID == timerID){
		bool paint = false;
		m_lock.lock();
		int barragesSize = (int)m_barrages.size();
		int width = getWidth(), height = getHeight();
		if(barragesSize > 0){
			for(int i = 0; i < barragesSize; i++){
				Barrage *brg = m_barrages[i];
				int mode = brg->getMode();
				if(mode == 0){
					if(brg->getRect().right < 0){
						m_barrages.erase(m_barrages.begin() + i);
						i--;
						barragesSize--;
					}
					else{
						brg->calculate();
					}
					paint = true;
				}
				else if(mode == 1){
					int tick = brg->getTick();
					tick--;
					if(tick <= 0){
						m_barrages.erase(m_barrages.begin() + i);
						i--;
						barragesSize--;
						paint = true;
					}
					else{
						brg->setTick(tick);
					}
					if(tick % 20 == 0){
						paint = true;
					}
				}
			}
		}
		m_lock.unLock();
		m_tick2++;
		if(m_tick2 > 700){
			m_directionX.clear();
			m_directionY.clear();
			bool reset = true;
			map<FCView*, FCPoint>::iterator sIter = m_oldLocations.begin();
			for(; sIter != m_oldLocations.end(); ++sIter){
				FCPoint oldLocation = sIter->second;
				FCPoint nowLocation = sIter->first->getLocation();
				FCPoint newLocation ={oldLocation.x, oldLocation.y};
				if(oldLocation.x != nowLocation.x){
					reset = false;
					if(abs(oldLocation.x - nowLocation.x) < 20){
						newLocation.x = oldLocation.x;
					}
					else if(oldLocation.x > nowLocation.x){
						newLocation.x = nowLocation.x + abs(oldLocation.x - nowLocation.x) / 8;
					}
					else if(oldLocation.x < nowLocation.x){
						newLocation.x = nowLocation.x - abs(oldLocation.x - nowLocation.x) / 8;
					}
				}
				if(oldLocation.y != nowLocation.y){
					reset = false;
					if(abs(oldLocation.y - nowLocation.y) < 20){
						newLocation.y = oldLocation.y;
					}
					else if(oldLocation.y > nowLocation.y){
						newLocation.y = nowLocation.y + abs(oldLocation.y - nowLocation.y) / 8;
					}
					else if(oldLocation.y < nowLocation.y){
						newLocation.y = nowLocation.y - abs(oldLocation.y - nowLocation.y) / 8;
					}
				}
				sIter->first->setLocation(newLocation);
			}
			if(reset){
				m_oldLocations.clear();
				int controlsSize = (int)m_subControls.size();
				for(int i = 0; i < controlsSize; i++){
					FCView *subControl = m_subControls[i];
					if(subControl->getControlType() == L"Grid"){
						dynamic_cast<FCGrid*>(subControl)->endUpdate();
					}
				}
				m_speeds.clear();
				m_subControls.clear();
				m_tick2 = 0;
			}
			paint = true;
		}
		else if(m_tick2 > 500){
			if((int)m_subControls.size() == 0){
				getSubControls(0);
			}
			int controlsSize = (int)m_subControls.size();
			for(int i = 0; i < controlsSize; i++){
				FCView *control = m_subControls[i];
				FCPoint location = control->getLocation();
				if(m_directionX.find(control) == m_directionX.end()){
					m_directionX[control] = rand() % 2;
					m_directionY[control] = rand() % 2;
					m_oldLocations[control] = location;
					m_speeds[control] = rand() % 5 + 1;
				}
				int dX = m_directionX[control];
				if(dX == 0){
					location.x -= m_speeds[control];
				}
				else if(dX == 1){
					location.x += m_speeds[control];
				}
				int dY = m_directionY[control];
				if(dY == 0){
					location.y -= m_speeds[control];
				}
				else if(dY == 1){
					location.y += m_speeds[control];
				}
				FCRect bounds = control->getParent()->getDisplayRect();
				if(location.x < bounds.left){
					dX = 1;
				}
				if(location.y < bounds.top){
					dY = 1;
				}
				if(location.x > bounds.right - control->getWidth()){
					dX = 0;
				}
				if(location.y > bounds.bottom - control->getHeight()){
					dY = 0;
				}
				m_directionX[control] = dX;
				m_directionY[control] = dY;
				control->setLocation(location);
			}
			paint = true;
		}
		if(paint){
			invalidate();
		}
	}
}