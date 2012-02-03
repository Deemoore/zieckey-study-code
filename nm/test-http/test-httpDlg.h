// test-httpDlg.h : 头文件
//

#pragma once

#include "net/include/exp.h"
#include "logic/include/exp.h"

// CtesthttpDlg 对话框
class CtesthttpDlg : public CDialog
{
// 构造
public:
	CtesthttpDlg(CWnd* pParent = NULL);	// 标准构造函数
    ~CtesthttpDlg()
    {
        delete logic_manager_;
        logic_manager_ = NULL;
    }

// 对话框数据
	enum { IDD = IDD_TESTHTTP_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持



    //////////////////////////////////////////////////////////////////////////
    class MyListener : public net::CURLWork::Listener
    {
    public:
        MyListener(CtesthttpDlg* dlg) : dlg_(dlg){}

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

            nm::model::ListUMSBaseUserinfo user_info_list;
            dlg_->logic_manager_->GetUserCenter()->ParseRespMsg(data, ss, user_info_list);
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

    private:
        CtesthttpDlg* dlg_;
    };
    typedef osl::RefPtr<MyListener> MyListenerPtr;

private:
    MyListenerPtr       listener_;
    nm::LogicManager*   logic_manager_;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton1();

    void Test_All();

    void Test_CharsetEncodingConvert();
    void Test_AsyncCURLWork();
    void Test_ParseIpAndURI();

    void Test_Login();
};
