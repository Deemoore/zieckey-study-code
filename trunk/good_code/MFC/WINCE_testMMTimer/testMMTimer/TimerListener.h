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
	~CTimerListener(void) {};
	virtual void OnMMTimer(int nTimerID) = 0;	
};
