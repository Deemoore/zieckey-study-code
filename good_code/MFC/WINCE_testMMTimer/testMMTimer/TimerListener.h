#pragma once
/********************************************************************
created:	2006/03/24
filename: 	CTimerListener
author:		goman
purpose:	the interface  to listen CMMTimers's call back.
*********************************************************************/
class CTimerListener
{
public:
	CTimerListener(void) {};
	virtual ~CTimerListener(void) {};
	virtual void OnMMTimer(int nTimerID) = 0;	//该函数是在异步线程中被调用，注意线程安全问题
};
