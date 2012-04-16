#pragma once
#include "MMTimers.h"

/********************************************************************
created:	2006/03/24
filename: 	CTimeAgent
author:		goman
purpose:	the Agent of CMMTimers.
*********************************************************************/
class CTimeAgent : public CTimerListener
{
public:
	CTimeAgent(void);
	~CTimeAgent(void);
public:
	virtual void OnMMTimer(int nTimerID);
	void StartTimer(int nDelay,int nTimerID);
	void StopTimer(int nTimerID);
protected:
	CMMTimers m_Timer;
};
