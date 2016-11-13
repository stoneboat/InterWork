// udpClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "work1.h"
#include "udpClientDlg.h"
#include "afxdialogex.h"


// udpClientDlg 对话框

IMPLEMENT_DYNAMIC(udpClientDlg, CDialogEx)

udpClientDlg::udpClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, Server_ip(_T(""))
	, Server_port(0)
	, command(_T(""))
	, response(_T(""))
{

	EnableAutomation();

}

udpClientDlg::~udpClientDlg()
{
}

void udpClientDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void udpClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Server_ip);
	DDX_Text(pDX, IDC_EDIT4, Server_port);
	DDX_Text(pDX, IDC_EDIT5, command);
	DDX_Text(pDX, IDC_EDIT6, response);
}
BOOL udpClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	UpdateData(TRUE);
	Server_ip = _T("127.0.0.1");
	Server_port = 2000;
	command = _T("");
	response = _T("");
	socket_client.SetParentDlg(this, 2);
	UpdateData(FALSE);
	int erro = socket_client.Create(2500, SOCK_DGRAM);
	if (!erro)
	{
		UINT uErr = GetLastError();
		TCHAR szError[256];
		wsprintf(szError, "Send Socket Create() failed: %d", uErr);
		AfxMessageBox(szError);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(udpClientDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &udpClientDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(udpClientDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IudpClientDlg 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {59D78B4C-6C7A-4A5A-AEC2-5B176B9924D5}
static const IID IID_IudpClientDlg =
{ 0x59D78B4C, 0x6C7A, 0x4A5A, { 0xAE, 0xC2, 0x5B, 0x17, 0x6B, 0x99, 0x24, 0xD5 } };

BEGIN_INTERFACE_MAP(udpClientDlg, CDialogEx)
	INTERFACE_PART(udpClientDlg, IID_IudpClientDlg, Dispatch)
END_INTERFACE_MAP()


// udpClientDlg 消息处理程序


void udpClientDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int l = strlen(command);
	int x = socket_client.SendTo(command, l, Server_port, Server_ip);
	if (l == x) {
		command = _T("发送失败");
	}
}
void udpClientDlg::OnReceive() {
	UpdateData(TRUE);
	char *pBuf = new char[1025];
	int iLen;
	CString server_ip;
	UINT server_port;
	iLen = socket_client.ReceiveFrom(pBuf, 1024, server_ip, server_port);
	/*if (server_ip!= Server_ip||server_port!=Server_port)
	{
		TCHAR szError[256];
		wsprintf(szError, "illegal packet form %s ip,%d port", server_ip,server_port);
		AfxMessageBox(szError);
	}*/
	if (iLen == SOCKET_ERROR)
		response = _T("接受响应失败");
	else
	{
		pBuf[iLen] = NULL;
		response = pBuf;
	}
	delete pBuf;
	UpdateData(FALSE);
}