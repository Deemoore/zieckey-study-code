//////////////////////////////////////////////////////////////////////////
//   File Name: bkresutil.h
// Description: Beike Resource Helper
//     Creator: Zhang Xiaoxuan
//     Version: 2009.5.13 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once

#define BKRES_TYPE			_T("xml")
#define BKRES_PNG_TYPE		_T("png")

#ifdef _DEBUG
#ifdef _UNICODE 
#   define BKRES_ASSERT(expr, format, ...) \
    (void) ((!!(expr)) || \
    (1 != _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, format, __VA_ARGS__)) || \
    (_CrtDbgBreak(), 0))
#else
#   define BKRES_ASSERT(expr, format, ...) \
	(void) ((!!(expr)) || \
	(1 != _CrtDbgReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, format, __VA_ARGS__)) || \
	(_CrtDbgBreak(), 0))
#endif
#else
#   define BKRES_ASSERT
#endif

// ����ģʽ
// ��Դ����

class BkResManager
{
public:
	typedef enum SKIN_TYPE
	{
		SKIN_RES_EMB=0,
		SKIN_RES_DIR,
		SKIN_RES_DLL
	};

protected:
	CString			m_strResourcePath;
    HINSTANCE		m_hInstanceRes;
	SKIN_TYPE		m_stSkinType;

public:
    BkResManager()
        : m_hInstanceRes(NULL)
    {

    }

	static void SetSkinType(SKIN_TYPE stSkinType=SKIN_RES_EMB)
	{
		_Instance()->m_stSkinType = stSkinType;
	}

    static void SetResourcePath(LPCTSTR lpszPath)
    {
        _Instance()->m_strResourcePath = lpszPath;

		_Instance()->m_stSkinType = SKIN_RES_DIR;
    }

	// ��DLl�м���Ƥ��
    static void SetResourceDLL(LPCTSTR lpszPath)
    {
        if (_Instance()->m_hInstanceRes)
            ::FreeLibrary(_Instance()->m_hInstanceRes);

        _Instance()->m_hInstanceRes = ::LoadLibrary(lpszPath);

		_Instance()->m_stSkinType = SKIN_RES_DLL;
    }

	// ��uResIDָ���ĵ�XML�ļ����ص�strBuffRet��
    static BOOL LoadResource(UINT uResID, CStringA &strBuffRet, LPCTSTR lpszResType = BKRES_TYPE)
    {
        BOOL bRet = FALSE;

        if ((_Instance()->m_stSkinType == SKIN_RES_DIR) && (!_Instance()->m_strResourcePath.IsEmpty()))
        {
            CString strFileName;

            strFileName.Format(_T("%s\\%d.%s"), _Instance()->m_strResourcePath, uResID, lpszResType);

            HANDLE hFile = ::CreateFile(
                strFileName, GENERIC_READ, FILE_SHARE_READ, 
                NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (INVALID_HANDLE_VALUE != hFile)
            {
                DWORD dwSize = ::GetFileSize(hFile, NULL);
                if (0 != dwSize)
                {
                    DWORD dwRead = 0;
                    bRet = ::ReadFile(hFile, strBuffRet.GetBuffer(dwSize + 10), dwSize, &dwRead, NULL);
                    if (bRet && dwRead == dwSize)
                    {
                        strBuffRet.ReleaseBuffer(dwSize);
                        return TRUE;
                    }

                    strBuffRet.ReleaseBuffer(0);
                }

                ::CloseHandle(hFile);
            }
        }

		// ���Ӵ���ԴDLL�л�ȡ��Դ  --by �������� <jlbookworm@qq.com> 2011.01.06
		// �����������ԴDLL�������ԴDLL������ȡ
		if ((_Instance()->m_stSkinType == SKIN_RES_DLL) && (_Instance()->m_hInstanceRes))
		{
			// ����ԴDLL�л�ȡ��Դ���ӳ����Զ�����Դ�л�ȡ����Ҫ��ͬ��ʽHINSTANCE��һ��
			// __ImageBase��ʾ�������PE�ṹ�е�ImageBase��ͬ,Ҳ����Win32ģ�鿪ʼ����Ҳ����ģ��Ļ�ַ���Ǿ���HINSTANCE.
			HRSRC hRsrc = ::FindResource(_Instance()->m_hInstanceRes, MAKEINTRESOURCE(uResID), lpszResType);

			if (NULL == hRsrc)
				return FALSE;

			DWORD dwSize = ::SizeofResource(_Instance()->m_hInstanceRes, hRsrc); 
			if (0 == dwSize)
				return FALSE;

			HGLOBAL hGlobal = ::LoadResource(_Instance()->m_hInstanceRes, hRsrc); 
			if (NULL == hGlobal)
				return FALSE;

			LPVOID pBuffer = ::LockResource(hGlobal); 
			if (NULL == pBuffer)
				return FALSE;

			memcpy(strBuffRet.GetBuffer(dwSize + 1), pBuffer, dwSize);
			strBuffRet.ReleaseBuffer(dwSize);

			::FreeResource(hGlobal);

			return TRUE;
		}

        bRet = _LoadEmbedResource(uResID, strBuffRet, lpszResType);

        BKRES_ASSERT(bRet, _T("Failed loading %s %u"), lpszResType, uResID);

        return bRet;
    }

	// ��ȡHBITMAP
	// �����ж��Ƿ���������ԴĿ¼����������������ԴĿ¼������Դ
	// ����ж��Ƿ��������Զ�����ԴDLL���������������Զ�����ԴDLL�м���
	// ����δӳ�����ֱ�Ӽ���
    static BOOL LoadResource(UINT uResID, HBITMAP &hBitmap)
    {
        BOOL bRet = FALSE;

        if ((_Instance()->m_stSkinType == SKIN_RES_DIR) && (!_Instance()->m_strResourcePath.IsEmpty()))
        {
            CString strFileName;

            strFileName.Format(_T("%s\\%d.bmp"), _Instance()->m_strResourcePath, uResID);

            hBitmap = (HBITMAP)::LoadImage(NULL, strFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

            if (NULL != hBitmap)
                return TRUE;
        }

        if ((_Instance()->m_stSkinType == SKIN_RES_DLL) && (_Instance()->m_hInstanceRes))
        {
            hBitmap = ::LoadBitmap(_Instance()->m_hInstanceRes, MAKEINTRESOURCE(uResID));
            if (NULL != hBitmap)
                return TRUE;
        }

        hBitmap = ::LoadBitmap((HINSTANCE)&__ImageBase, MAKEINTRESOURCE(uResID));

        BKRES_ASSERT(NULL != hBitmap, _T("Failed loading bitmap %u"), uResID);

        return NULL != hBitmap;
    }

protected:

    static BkResManager* _Instance()
    {
        static BkResManager* s_pIns = new BkResManager;

        return s_pIns;
    }

	// �ӳ����л�ȡ�Զ�����Դ
    static BOOL _LoadEmbedResource(UINT uResID, CStringA &strRet, LPCTSTR lpszResType = BKRES_TYPE)
    {
		// __ImageBase��ʾ�������PE�ṹ�е�ImageBase��ͬ,Ҳ����Win32ģ�鿪ʼ����Ҳ����ģ��Ļ�ַ���Ǿ���HINSTANCE.
        HRSRC hRsrc = ::FindResource((HINSTANCE)&__ImageBase, MAKEINTRESOURCE(uResID), lpszResType);

        if (NULL == hRsrc)
            return FALSE;

        DWORD dwSize = ::SizeofResource((HINSTANCE)&__ImageBase, hRsrc); 
        if (0 == dwSize)
            return FALSE;

        HGLOBAL hGlobal = ::LoadResource((HINSTANCE)&__ImageBase, hRsrc); 
        if (NULL == hGlobal)
            return FALSE;

        LPVOID pBuffer = ::LockResource(hGlobal); 
        if (NULL == pBuffer)
            return FALSE;

        memcpy(strRet.GetBuffer(dwSize + 1), pBuffer, dwSize);
        strRet.ReleaseBuffer(dwSize);

        ::FreeResource(hGlobal);

        return TRUE;
    }
};
