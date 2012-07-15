/*********************************************************************************************************
   class CLrc applys to SSShow V5.5:  http://down1.tomore.com/tools/20070105/2007010500262026968.rar   
----------------------------------------------------------------------------------------------------------
   MSN:   weishuishusheng@hotmail.com 2007-1-1
   Open:  load a lrc file and save records to m_recordArray
   GetTxt:  Get the Current lrc txt
   
************************************************************************************************************/
#include "stdafx.h"
#include "Lrc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLrc::CLrc()
{

}

CLrc::~CLrc()
{
   Free();
}

BOOL CLrc::Open(CString strFile)
{
	char* pFileTxt =0;
	CFile lrcFile;
	if(!lrcFile.Open(strFile.GetBuffer(0),CFile::modeRead)) return FALSE;
	int len =lrcFile.GetLength();
	if(len<=0) 
	{
		lrcFile.Close();
		return FALSE;
	}
    pFileTxt =new char[len];
	memset(pFileTxt,0,len);
    if(lrcFile.Read(pFileTxt,len)>0)
	{
		
		CString strtmp =pFileTxt;
		
		int ilen =strtmp.GetLength();
		for(int k=ilen-1; k>0; k--)
		{
			if(strtmp.GetAt(k)=='[' && strtmp.GetAt(k-1)!=']' && strtmp.GetAt(k-1)!=0x0a)
			{
				strtmp.Insert(k,L"\r\n");
			}
		}
		

	CString strFilePath= strtmp.GetBuffer(0);
	char FilePath[2560];
	memset( FilePath, 0, 2560 );
	WideCharToMultiByte( CP_ACP, 0, strFilePath, -1, FilePath, 2560, NULL, NULL);




		
		char* pToken =strtok(FilePath,"\r\n");
		while (pToken) 
		{
			//每个Token就是一行
			TLrcRecord* pTmpRecord[20];
			int iTmpRecord=0;
			int istart=0,iend=-1,iTxtStart=-1;
			CString strLine =pToken;
			strLine.Replace(L" ",L"");  //trim space
			strLine.Replace(L"\t",L"");  //trim \t
			for(int i=0; i<20; i++)
			{
				pTmpRecord[i] =0;
			}
			while((istart=strLine.Find(L"[",iend+1))!=-1)
			{
				char strMi[3],strSec[3],strmSec[3];
				iend =strLine.Find(L"]",istart+1);
				if(iend== -1) break;
				if( iend-istart!=9 ) continue;
				strMi[0] = strLine.GetAt(istart+1);
				strMi[1] = strLine.GetAt(istart+2);
				strSec[0] = strLine.GetAt(istart+4);
				strSec[1] = strLine.GetAt(istart+5);
				strmSec[0] =strLine.GetAt(istart+7);
				strmSec[1] =strLine.GetAt(istart+8);              
				if(iTmpRecord>=20) break;
				pTmpRecord[iTmpRecord] =new TLrcRecord;
				pTmpRecord[iTmpRecord]->m_time = 
					((strMi[0]-'0')*10+(strMi[1]-'0'))*60*100 +
					((strSec[0]-'0')*10+(strSec[1]-'0'))*100 +
					((strmSec[0]-'0')*10+(strmSec[1]-'0'));
				iTmpRecord++;
				iTxtStart =iend+1;
			}
			if(iTxtStart!=-1)
			{//插入排序
				for(int i=0; i< iTmpRecord;  i++)   
				{
					int j=0;
					while (j<m_recordArray.GetSize() && pTmpRecord[i]->m_time > m_recordArray[j]->m_time)  j++;
					pTmpRecord[i]->m_str =strLine.Right(strLine.GetLength()-iTxtStart);
					m_recordArray.InsertAt(j,pTmpRecord[i],1);
				}
				
			}
			pToken =strtok(NULL,"\r\n");
		}
	}
	lrcFile.Close();
	delete[] pFileTxt;
	return TRUE;
}

void CLrc::Free()
{
	for(int i=0; i<m_recordArray.GetSize();i++)
	{
		delete m_recordArray[i];
	}
	m_recordArray.RemoveAll();
}

CString CLrc::GetTxt(UINT time)
{
	int i =0; 
	while((i<m_recordArray.GetSize()) && (time >= m_recordArray[i]->m_time))
	{
		i ++;
	}

	if(i-1 >=0) return m_recordArray[i-1]->m_str;
	
	return "";
}
