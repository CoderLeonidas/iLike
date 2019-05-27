/*****************************************************************************\
*                                                                             *
* UpdateService.h -  Update functions, types, and definitions.                *
*                                                                             *
*               Version 1.00  ★★★                                          *
*                                                                             *
*               Copyright (c) 2016-2016, Future. All rights reserved.         *
*               Created by Lord 2016/3/10.                                    *
*                                                                             *
******************************************************************************/

#ifndef __UPDATESERVICE_H__
#define __UPDATESERVICE_H__
#pragma once
#include "..\\..\\stdafx.h" 
#include "..\\..\\CUpdate.h"

//自动更新服务
class UpdateService : public CUpdate
{
public:
	UpdateService();
	virtual ~UpdateService();
public:
	void GetDownLoadState(double *now, double *total);
	virtual void OnUpdateEnd();
	virtual void OnUpdateFail();
	virtual void OnUpdateStart();
	virtual void OnUpdating(double now, double total);
};

#endif