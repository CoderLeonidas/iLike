#include "..\\..\\stdafx.h"
#include "WinHostEx.h"

WinHostEx::WinHostEx(){
}

WinHostEx::~WinHostEx(){
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FCView* WinHostEx::createInternalControl(FCView *parent, const String& clsid){
	FCCalendar *calendar = dynamic_cast<FCCalendar*>(parent);
    if (calendar){
        if (clsid == L"datetitle"){
            return new DateTitle(calendar);
        }
        else if (clsid == L"headdiv"){
            HeadDiv *headDiv = new HeadDiv(calendar);
            headDiv->setWidth(parent->getWidth());
            headDiv->setDock(FCDockStyle_Top);
            return headDiv;
        }
        else if (clsid == L"lastbutton"){
            return new ArrowButton(calendar);
        }
        else if (clsid == L"nextbutton"){
            ArrowButton *nextBtn = new ArrowButton(calendar);
            nextBtn->setToLast(false);
            return nextBtn;
        }
    }
    FCSplitLayoutDiv *splitLayoutDiv = dynamic_cast<FCSplitLayoutDiv*>(parent);
    if (splitLayoutDiv){
        if (clsid == L"splitter"){
            FCButton *splitter = new FCButton;
			splitter->setBackColor(FCCOLORS_BACKCOLOR);
            FCSize size = {5, 5};
            splitter->setSize(size);
            return splitter;
        }
    }
    FCScrollBar *scrollBar = dynamic_cast<FCScrollBar*>(parent);
    if (scrollBar){
		scrollBar->setBackColor(FCColor_None);
        if (clsid == L"addbutton"){
            RibbonButton *addButton = new RibbonButton;
            FCSize size ={15, 15};
            addButton->setSize(size);
			if (dynamic_cast<FCHScrollBar*>(scrollBar)){
                addButton->setArrowType(2);
            }
            else{
                addButton->setArrowType(4);
            }
            return addButton;
        }
        else if (clsid == L"backbutton"){
            FCButton *backButton = new FCButton;
			backButton->setBackColor(FCColor_None);
            return backButton;
        }
        else if (clsid == L"scrollbutton"){
            FCButton *scrollButton = new FCButton;
            scrollButton->setAllowDrag(true);
			scrollButton->setBackColor(FCCOLORS_BACKCOLOR3);
            return scrollButton;
        }
        else if (clsid == L"reducebutton"){
            RibbonButton *reduceButton = new RibbonButton;
            FCSize size ={15, 15};
            reduceButton->setSize(size);
			if (dynamic_cast<FCHScrollBar*>(scrollBar)){
                reduceButton->setArrowType(1);
            }
            else{
                reduceButton->setArrowType(3);
            }
            return reduceButton;
        }
    }
    FCTabPage *tabPage = dynamic_cast<FCTabPage*>(parent);
    if (tabPage){
        if (clsid == L"headerbutton"){
            RibbonButton *button = new RibbonButton;
            button->setAllowDrag(true);
            FCSize size ={100, 20};
            button->setSize(size);
			button->setTabClose(true);
            return button;
        }
    }
    FCComboBox *comboBox = dynamic_cast<FCComboBox*>(parent);
    if (comboBox){
        if (clsid == L"dropdownbutton"){
            RibbonButton *dropDownButton = new RibbonButton;
			dropDownButton->setArrowType(4);
			dropDownButton->setDisplayOffset(false);
            int width = comboBox->getWidth();
            int height = comboBox->getHeight();
            FCPoint location ={width - 16, 0};
            dropDownButton->setLocation(location);
            FCSize size ={16, height};
            dropDownButton->setSize(size);
            return dropDownButton;
        }
        else if (clsid == L"dropdownmenu"){
            FCComboBoxMenu *comboBoxMenu = new FCComboBoxMenu;
            comboBoxMenu->setComboBox(comboBox);
            comboBoxMenu->setPopup(true);
            FCSize size ={100, 200};
            comboBoxMenu->setSize(size);
            return comboBoxMenu;
        }
    }
    FCDateTimePicker *datePicker = dynamic_cast<FCDateTimePicker*>(parent);
    if (datePicker){
        if (clsid == L"dropdownbutton"){
            RibbonButton *dropDownButton = new RibbonButton;
			dropDownButton->setArrowType(4);
            dropDownButton->setDisplayOffset(false);
            int width = datePicker->getWidth();
            int height = datePicker->getHeight();
            FCPoint location ={width - 16, 0};
            dropDownButton->setLocation(location);
            FCSize size ={16, height};
            dropDownButton->setSize(size);
            return dropDownButton;
        }
        else if (clsid == L"dropdownmenu"){
            FCMenu *dropDownMenu = new FCMenu();
            FCPadding padding(1);
            dropDownMenu->setPadding(padding);
            dropDownMenu->setPopup(true);
            FCSize size ={200, 200};
            dropDownMenu->setSize(size);
            return dropDownMenu;
        }
    }
    FCSpin *spin = dynamic_cast<FCSpin*>(parent);
    if (spin){
        if (clsid == L"downbutton"){
            RibbonButton *downButton = new RibbonButton;
			downButton->setArrowType(4);
			downButton->setDisplayOffset(false);
            FCSize size ={16, 16};
            downButton->setSize(size);
            return downButton;
        }
        else if (clsid == L"upbutton"){
            RibbonButton *upButton = new RibbonButton;
			upButton->setArrowType(3);
			upButton->setDisplayOffset(false);
            FCSize size ={16, 16};
            upButton->setSize(size);
            return upButton;
        }
    }
	FCDiv *div = dynamic_cast<FCDiv*>(parent);
    if (div){
        if (clsid == L"hscrollbar"){
            FCHScrollBar *hScrollBar = new FCHScrollBar;
            hScrollBar->setVisible(false);
            FCSize size ={13, 13};
            hScrollBar->setSize(size);
            return hScrollBar;
        }
        else if (clsid == L"vscrollbar"){
            FCVScrollBar *vScrollBar = new FCVScrollBar;
            vScrollBar->setVisible(false);
            FCSize size ={13, 13};
            vScrollBar->setSize(size);
            return vScrollBar;
        }
    }
	FCGrid *grid = dynamic_cast<FCGrid*>(parent);
	if(grid){
		if(clsid == L"edittextbox"){
			FCTextBox *editTextBox = new FCTextBox;
			editTextBox->setBackColor(FCCOLORS_BACKCOLOR4);
			return editTextBox;
		}
	}
    return 0;
}