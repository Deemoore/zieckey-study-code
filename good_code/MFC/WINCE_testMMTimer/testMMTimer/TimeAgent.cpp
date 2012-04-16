#include "StdAfx.h"
#include ".\timeagent.h"

CTimeAgent::CTimeAgent(void)
{
}

CTimeAgent::~CTimeAgent(void)
{
}

void CTimeAgent::OnMMTimer(int nTimerID)
{
	if( nTimerID == 1)
	{
		TRACE("aaa\n");
	}

	if( nTimerID == 2 )
	{
		TRACE("BBB\n");
	}
}

void CTimeAgent::StartTimer(int nDelay,int nTimerID)
{
	m_Timer.startTimer(nDelay,this,nTimerID);


}
void CTimeAgent::StopTimer(int nTimerID)
{
	m_Timer.stopTimer(nTimerID);
}
