#include	"StdAfx.h"
#include	"mmTimers.h"
#pragma comment(lib,"Winmm.lib");
int MMRecoder::nRes = 0;
CMMTimers::CMMTimers() : timerRes(0), timerId(0)
{

	TIMECAPS	tc;

	UINT resolution = 5;
	if (TIMERR_NOERROR == timeGetDevCaps(&tc,sizeof(TIMECAPS)))
	{
		timerRes = min(max(tc.wPeriodMin,resolution),tc.wPeriodMax);
		timeBeginPeriod(timerRes);
	}
	m_pListener = NULL;
}


CMMTimers::~CMMTimers()
{
	stopTimer();
	if (0 != timerRes)
	{
		timeEndPeriod(timerRes);
		timerRes = 0;
	}
}


extern "C"
void
CALLBACK
internalTimerProc(UINT id,UINT msg,DWORD dwUser,DWORD dw1,DWORD dw2)
{
	//CMMTimers *	timer = (CMMTimers *)dwUser;

	MMRecoder *pRecoder = (MMRecoder *) dwUser;
	CMMTimers *timer = pRecoder->pMMTimer;
	int nID = pRecoder->nID;
	if( timer->m_pListener != NULL )
	{
		timer->m_pListener->OnMMTimer(nID);
	}
	else
	{
		timer->timerProc();
	}
}


bool CMMTimers::startTimer(UINT period,CTimerListener *pListener,int nTimerID,bool oneShot)
{
	bool		res = false;
	MMRESULT	result;

	if(MMRecoder::nRes > Max_Timer)
	{
		return FALSE;
	}

	m_Recoder[MMRecoder::nRes].nID = nTimerID;
	m_Recoder[MMRecoder::nRes].pMMTimer = this;
	m_pListener = pListener;
	result = timeSetEvent(period,timerRes,internalTimerProc,(DWORD)&m_Recoder[MMRecoder::nRes],oneShot ? TIME_ONESHOT : TIME_PERIODIC);
	if (NULL != result)
	{
		timerId = (UINT)result;
		m_mapTimerID[nTimerID] = timerId;
		res = true;
	}
	MMRecoder::nRes++;
	return res;
}


bool CMMTimers::stopTimer()
{
	MMRESULT	result = -1;

	POSITION pos = m_mapTimerID.GetStartPosition();
	int nKey;
	int nValue;
	while (pos != NULL)
	{
		m_mapTimerID.GetNextAssoc( pos, nKey, nValue);
		result = timeKillEvent(nValue);
		m_mapTimerID.RemoveKey( nKey );
	}
	return TIMERR_NOERROR == result;
}
bool CMMTimers::stopTimer(int nTimerID)
{
	int nValue ;//= m_mapTimerID[nTimerID];
	MMRESULT	result = -1;
	if( m_mapTimerID.Lookup(nTimerID,nValue) )
	{

		result = timeKillEvent(nValue);
		m_mapTimerID.RemoveKey(nTimerID);
	}

	return TIMERR_NOERROR == result;
}

void CMMTimers::timerProc() 
{

}


