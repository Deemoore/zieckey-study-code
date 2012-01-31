// net-ce-testDlg.h : ͷ�ļ�
//

#pragma once

#include "net/include/exp.h"

// CnetcetestDlg �Ի���
class CnetcetestDlg : public CDialog
{
// ����
public:
	CnetcetestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NETCETEST_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

    //////////////////////////////////////////////////////////////////////////
    class MyListener : public net::CURLWork::Listener, public osl::Object
    {
        H_REFERENCE_METHODS(osl::Object);
        //! \brief <b>Summary:</b>
        //! 	This function is called by CURLWork(observable) to notify
        //! Listeners that this curl work is done, and the received data
        //! from server is preserved in m_ptrRecvMDStream
        //! \note This function is called in another thread, you <b>MUST</b>
        //!     be care about the multi thread-safe problem
        //! \param  pw, the CURLWork which is listened by this listener.
        //! you can call CURLWork::getRecvDataStream() to get the server response string.
        virtual void onFinishOKT( net::CURLWork* pw )
        {
            osl::MemoryDataStream* recv_data = pw->getRecvDataStream();
            size_t ss = recv_data->size();
            const char* data = recv_data->data();
            fprintf(stderr, "%lu %s\n", ss, data);
        }


        //! \brief <b>Summary:</b>
        //! 	This function is called by CURLWork(observable) to notify
        //! Listeners that the work is no done because something error.
        //! \note This function is called in another thread, you <b>MUST</b>
        //!     be care about the multi thread-safe problem
        //! \param hec, error code
        //! \param errmsg, describes the error message
        //! \param pw, the CURLWork which is listened by this listener
        virtual void onFinishErrorT( net::HttpErrorCode hec, const osl::StringA& errmsg, net::CURLWork* pw )
        {
            fprintf(stderr, "%lu %s\n", hec, errmsg.c_str());
        }
    };
    typedef osl::RefPtr<MyListener> MyListenerPtr;
    MyListenerPtr listener_;


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()

    net::CURLServicePtr curl_service_;

};
