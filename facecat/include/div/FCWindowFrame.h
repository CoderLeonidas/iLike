/*����èFaceCat��� v1.0
 1.��ʼ��-�󶴳���Ա-�Ϻ����׿Ƽ���ʼ��-����KOL-�յ� (΢�ź�:suade1984);
 2.���ϴ�ʼ��-�Ϻ����׿Ƽ���ʼ��-Ԭ����(΢�ź�:wx627378127);
 3.���ϴ�ʼ��-Ф����(΢�ź�:xiaotianlong_luu);
 4.���Ͽ�����-������(΢�ź�:chenxiaoyangzxy)������-���(΢�ź�:cnnic_zhu)
 5.�ÿ�ܿ�ԴЭ��ΪBSD����ӭ�����ǵĴ�ҵ����и���֧�֣���ӭ���࿪���߼��롣
 ����C/C++,Java,C#,iOS,MacOS,Linux�����汾��ͼ�κ�ͨѶ�����ܡ�
 */

#ifndef __FCWINDOWFRAME_H__
#define __FCWINDOWFRAME_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "FCWindow.h"

namespace FaceCat
{
	/*
	* ����߽�
	*/
	class FCWindowFrame : public FCView{
	public:
	    /**
		 * ����ؼ��߽�
		 */
		FCWindowFrame();
		/*
		* ��������
		*/
		virtual ~FCWindowFrame();
	public:
		/**
		* �Ƿ��������
		* @param  point  ����
		*/
		virtual bool containsPoint(const FCPoint& point);
		/**
		 * ��ȡ�ؼ�����
		 */
		virtual String getControlType();
		/**
		 * �ػ淽��
		 */
		virtual void invalidate();
		/**
		* ���Ʊ�������
		* @param  paint ��ͼ����
		* @param  clipRect   �ü�����
		*/
		virtual void onPaintBackground(FCPaint *paint, const FCRect& clipRect);
	};
}
#endif