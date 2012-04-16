#ifndef	___multimedia_timers___
#define	___multimedia_timers___

/********************************************************************
	created:	2006/03/24
	filename: 	CMMTimers
	author:		goman
	purpose:	millisecond Timer.
	            the default Minimum timer resolution is 5.
*********************************************************************/

#include "stdafx.h"
#include	<mmsystem.h>
#include    <afxtempl.h>
#include    "TimerListener.h"
#define  Max_Timer 5
class CMMTimers;
struct MMRecoder {
	CMMTimers *pMMTimer;
	int nID;
	static int nRes;
};

class CMMTimers
{
public:
	CMMTimers();
	virtual ~CMMTimers();

	UINT	getTimerRes() { return timerRes; };

	bool	startTimer(UINT period,CTimerListener *pListener = NULL,int nTimerID = 1,bool oneShot = FALSE);
	bool	stopTimer();
	bool    stopTimer(int nTimerID);
	void    timerProc();
	CTimerListener *m_pListener;

protected:
	UINT	timerRes;
	UINT	timerId;
	UINT    timerId2;
	MMRecoder m_Recoder[Max_Timer] ;
	
	CMap<int,int,int,int> m_mapTimerID;
};


#endif