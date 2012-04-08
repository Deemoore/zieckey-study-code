 如何使用CCeButtonST v1.2控件，以及相应的wincore错误
2008-05-16 10:36 492人阅读 评论(0) 收藏 举报
先下载CCeButtonST v1.2控件，在下面的地址上
http://www.codeproject.com/KB/mobile/ccebuttonst.aspx
 
建立mytbtn工程
 
在工程里面添加两个文件CeBtnST.h , CeBtnST.cpp
 
在mytbtnDlg.h中添加 #include “CeBtnST.h”
 
在 mytbtnDlg.h : header file
添加按钮定义，一定要放在afx_data之间，这样才不会有错误
 
 
在BOOL CMytbtnDlg::OnInitDialog() 中
 
出现问题的时候，参考这个文档
http://www.cppblog.com/milkyway/archive/2007/05/29/25039.html
避免运行时警告:Assertion Failed, WINCORE.CPP--Line 348,349,4199
      编译环境: EVC4.0+SP4
      由于在对话框中加入了自定义绘图控件,初始化与声明不合适导致此程序运行时出现三个ASSERT警告.
      解决办法参考: http://support.microsoft.com/kb/113421/en-us
      具体步骤:
 1.在对话框资源里加入自定义控件, 设置属性,注意ID设为IDC_XXX的XXX和类名一致.
  2.在对话框类中添加成员变量,特别注意应该放在以下字段中,而不是普通的程序变量中
                                 // Dialog Data
                                      //{{AFX_DATA(CVoltagecontrolDlg)
                                          enum { IDD = IDD_VOLTAGECONTROL_DIALOG };
                                          ....
                                        CLineChartCtrl  m_LineChart;     
                                        //}}AFX_DATA
3.在XXDlg.cpp中,不要重复关联控件ID和成员变量,在CDialog::DoDataExchange(pDX)里定义了DDX_Control(pDX, IDC_LineChartCtrl, m_LineChart);就不要在CDialog::OnInitDialog();再使用m_LineChart.SubclassDlgItem(IDC_LineChartCtrl, this);   与DDX重复关联了.
主要错误在于: 混淆了程序变量与控件变量, 并且重复关联控件ID与变量.