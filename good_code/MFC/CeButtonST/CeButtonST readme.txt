 ���ʹ��CCeButtonST v1.2�ؼ����Լ���Ӧ��wincore����
2008-05-16 10:36 492���Ķ� ����(0) �ղ� �ٱ�
������CCeButtonST v1.2�ؼ���������ĵ�ַ��
http://www.codeproject.com/KB/mobile/ccebuttonst.aspx
 
����mytbtn����
 
�ڹ���������������ļ�CeBtnST.h , CeBtnST.cpp
 
��mytbtnDlg.h����� #include ��CeBtnST.h��
 
�� mytbtnDlg.h : header file
��Ӱ�ť���壬һ��Ҫ����afx_data֮�䣬�����Ų����д���
 
 
��BOOL CMytbtnDlg::OnInitDialog() ��
 
���������ʱ�򣬲ο�����ĵ�
http://www.cppblog.com/milkyway/archive/2007/05/29/25039.html
��������ʱ����:Assertion Failed, WINCORE.CPP--Line 348,349,4199
      ���뻷��: EVC4.0+SP4
      �����ڶԻ����м������Զ����ͼ�ؼ�,��ʼ�������������ʵ��´˳�������ʱ��������ASSERT����.
      ����취�ο�: http://support.microsoft.com/kb/113421/en-us
      ���岽��:
 1.�ڶԻ�����Դ������Զ���ؼ�, ��������,ע��ID��ΪIDC_XXX��XXX������һ��.
  2.�ڶԻ���������ӳ�Ա����,�ر�ע��Ӧ�÷��������ֶ���,��������ͨ�ĳ��������
                                 // Dialog Data
                                      //{{AFX_DATA(CVoltagecontrolDlg)
                                          enum { IDD = IDD_VOLTAGECONTROL_DIALOG };
                                          ....
                                        CLineChartCtrl  m_LineChart;     
                                        //}}AFX_DATA
3.��XXDlg.cpp��,��Ҫ�ظ������ؼ�ID�ͳ�Ա����,��CDialog::DoDataExchange(pDX)�ﶨ����DDX_Control(pDX, IDC_LineChartCtrl, m_LineChart);�Ͳ�Ҫ��CDialog::OnInitDialog();��ʹ��m_LineChart.SubclassDlgItem(IDC_LineChartCtrl, this);   ��DDX�ظ�������.
��Ҫ��������: �����˳��������ؼ�����, �����ظ������ؼ�ID�����.