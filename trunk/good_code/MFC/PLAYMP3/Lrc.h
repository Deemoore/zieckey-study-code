
#if !defined(AFX_LRC_H__4AE2993A_1708_4662_9CDD_0F3ABEB1ECC6__INCLUDED_)
#define AFX_LRC_H__4AE2993A_1708_4662_9CDD_0F3ABEB1ECC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "afxtempl.h"

/*********************************************************************************************************
   class CLrc applys to SSShow V5.5:  http://down1.tomore.com/tools/20070105/2007010500262026968.rar   
----------------------------------------------------------------------------------------------------------
   MSN:   weishuishusheng@hotmail.com 2007-1-1
   Open:  load a lrc file and save records to m_recordArray
   GetTxt:  Get the Current lrc txt
   
************************************************************************************************************/

struct TLrcRecord
{
    UINT m_time;
    CString m_str;
};


class CLrc  
{
public:
	//取出指定时间Time应该播放的歌词
	CString GetTxt(UINT Time);
	//销毁LRC文件
	void Free();
	//载入LRC文件
	BOOL Open(CString strFile);
	CLrc();
	virtual ~CLrc();
public:	
	CArray<TLrcRecord*,TLrcRecord*> m_recordArray;
};

#endif // !defined(AFX_LRC_H__4AE2993A_1708_4662_9CDD_0F3ABEB1ECC6__INCLUDED_)
