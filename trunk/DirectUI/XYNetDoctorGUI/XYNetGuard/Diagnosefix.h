#pragma once
#include "XYNetGuard.h"


const COLORREF BACKGROUND_COLOR=RGB(0xfb,0xfc,0xfd);

enum {
	WMH_INIT_SCAN = WM_USER + 0x100,
	WMH_SCAN_START,
	WMH_SCAN_DONE,
	WMH_REPAIR_DONE,
	WMH_SCAN_FIXED_BEGIN,
	WMH_SCAN_FIXED_DONE,
	WMH_SCAN_SOFT_BEGIN,
	WMH_SCAN_SOFT_DONE,
	WMH_VULFIX_BASE = WM_USER + 0x200,
	
	WMH_LISTEX_HOVERCHANGED = WM_USER + 0x300,
	WMH_LISTEX_LINK
};

enum TScanSoftState{
	SCANSTATE_DISPLAY,
	SCANSTATE_SCANNING,
	SCANSTATE_REPAIRING,
};

enum TRepairSubState{
	REPAIRSTATE_ING,
	REPAIRSTATE_DONE,
	REPAIRSTATE_DONE_PART,
	REPAIRSTATE_FAIL,
};


enum TSoftVulStatus
{
	VUL_UPDATE,
	VUL_COM_DISABLED,
	VUL_DISABLE_COM,
};

static UINT _SoftVulStatusOP[] = 
{
	5071,
	5072,
	5073
};
static CBkStringArray SoftVulStatusOP(_SoftVulStatusOP);

static UINT _SoftVulStatusDesc[] = 
{
    5074,
    5075,
    5076
};
static CBkStringArray SoftVulStatusDesc(_SoftVulStatusDesc);

enum TIMER_TYPE
{
	TIMER_RUNNING = 1,
	TIMER_SHUTDOWN_PROMPT,
};