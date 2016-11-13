// consoleWin.cpp : 实现文件
//

#include "stdafx.h"
#include "work1.h"
#include "consoleWin.h"
#include "afxdialogex.h"

#include "tcpServerDlg.h"
#include "tcpClientDlg.h"
#include "udpServerDlg.h"
#include "udpClientDlg.h"


// consoleWin 对话框

IMPLEMENT_DYNAMIC(consoleWin, CDialogEx)

consoleWin::consoleWin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	
}

consoleWin::~consoleWin()
{
}

void consoleWin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, server_factory);
}


BEGIN_MESSAGE_MAP(consoleWin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &consoleWin::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &consoleWin::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &consoleWin::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &consoleWin::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &consoleWin::OnBnClickedButton5)
END_MESSAGE_MAP()


// consoleWin 消息处理程序


void consoleWin::OnBnClickedButton1()
{
	tcpServerDlg*  serverDlg = new tcpServerDlg(this);
	serverDlg->Create(IDD_DIALOG2, this);
	serverDlg->ShowWindow(SW_SHOW);
	//serverDlg.UpdateWindow();
	//udpServerDlg  serverDlg;
	//serverDlg.DoModal();
}
BOOL consoleWin::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog

									// TODO: Add extra initialization here
	SetDlgItemText(IDC_BUTTON1, _T("生成tcp服务器"));
	SetDlgItemText(IDC_BUTTON2, _T("生成tcp客户端"));
	SetDlgItemText(IDC_BUTTON3, _T("退出"));
	this->SetWindowText(_T("tcp/udp监听器"));
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void consoleWin::OnBnClickedButton3()
{
	this->CDialog::EndDialog(IDCANCEL);
}


void consoleWin::OnBnClickedButton2()
{
	tcpClientDlg*  clientDlg = new tcpClientDlg(this);
	clientDlg->Create(IDD_DIALOG3, this);
	clientDlg->ShowWindow(SW_SHOW);
	//udpClientDlg  clientDlg;
	//clientDlg.DoModal();
}


void consoleWin::OnBnClickedButton4()
{
	udpServerDlg*  serverDlg = new udpServerDlg(this);
	serverDlg->Create(IDD_DIALOG5, this);
	serverDlg->ShowWindow(SW_SHOW);
}


void consoleWin::OnBnClickedButton5()
{
	udpClientDlg*  clientDlg = new udpClientDlg(this);
	clientDlg->Create(IDD_DIALOG4, this);
	clientDlg->ShowWindow(SW_SHOW);
}
