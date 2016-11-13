// tcpServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "work1.h"
#include "tcpServerDlg.h"
#include "afxdialogex.h"
#include "timeStamp.h"
#include "protocal.h"
#include <string>
#include <sstream>

// udpServerDlg 对话框

IMPLEMENT_DYNAMIC(tcpServerDlg, CDialogEx)

tcpServerDlg::tcpServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, port(0)
	, loger(_T(""))
{

	EnableAutomation();

}

tcpServerDlg::~tcpServerDlg()
{
}

void tcpServerDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void tcpServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT2, server_status);
	DDX_Control(pDX, IDC_BUTTON1, listen_button);
	DDX_Control(pDX, IDC_BUTTON2, stop_button);
	DDX_Text(pDX, IDC_EDIT1, port);
	//  DDX_Control(pDX, IDC_EDIT3, server_loger);
	DDX_Text(pDX, IDC_EDIT2, loger);
}
BOOL tcpServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog

	// TODO: Add extra initialization here
	SetDlgItemText(IDC_STATIC1, _T("端口"));
	SetDlgItemText(IDC_STATIC2, _T("状态"));
	SetDlgItemText(IDC_STATIC3, _T("日志"));
	SetDlgItemText(IDC_STATIC4, _T("未连接"));
	SetDlgItemText(IDC_BUTTON1, _T("监听"));
	SetDlgItemText(IDC_BUTTON2, _T("中断"));
	this->SetWindowText(_T("tcp服务器"));
	port = 2000;
	loger = _T("");
	UpdateData(FALSE);
	socket_Listener.SetParentDlg(this,1);
	socket_service.SetParentDlg(this,1);
	listen_button.EnableWindow(TRUE);
	stop_button.EnableWindow(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(tcpServerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &tcpServerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &tcpServerDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(tcpServerDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IudpServerDlg 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {EC578B9D-1F6A-4004-8E2B-C1469BF0C82D}
static const IID IID_IudpServerDlg =
{ 0xEC578B9D, 0x1F6A, 0x4004, { 0x8E, 0x2B, 0xC1, 0x46, 0x9B, 0xF0, 0xC8, 0x2D } };

BEGIN_INTERFACE_MAP(tcpServerDlg, CDialogEx)
	INTERFACE_PART(tcpServerDlg, IID_IudpServerDlg, Dispatch)
END_INTERFACE_MAP()


// udpServerDlg 消息处理程序


void tcpServerDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	socket_service.Close();
	socket_Listener.Close();
	SetDlgItemText(IDC_STATIC4, _T("未连接"));
	UpdateData(FALSE);
	listen_button.EnableWindow(TRUE);
	stop_button.EnableWindow(FALSE);
}


void tcpServerDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	SetDlgItemText(IDC_STATIC4, _T("已连接"));
	//port.SetWindowText(_T("ABC")); //設定
	//CString strSource;
	//port.GetWindowText(strSource);
	socket_Listener.Create(port);
	if (socket_Listener.Listen() == FALSE)
	{
		UINT uErr = GetLastError();
		TCHAR szError[256];
		wsprintf(szError, "Server Receive Socket Create() failed: %d", uErr);
		AfxMessageBox(szError);
		timeStamp ts;
		loger.Insert(loger.GetLength(), ts.getNow());   //display in server
		std::string digit;
		std::stringstream ss;
		ss << port;
		ss >> digit;
		std::string ms = "监听端口" + digit + "失败，可能已被占用，请换一个端口";
		loger.Insert(loger.GetLength(), CString(ms.c_str()));
		loger += _T("\r\n");
		socket_Listener.Close();
	}
	else {
		timeStamp ts;
		loger.Insert(loger.GetLength(), ts.getNow());   //display in server
		std::string digit;
		std::stringstream ss;
		ss << port;
		ss >> digit;
		std::string ms = "开始成功监听端口： " + digit;
		loger.Insert(loger.GetLength(), CString(ms.c_str()));
		loger += _T("\r\n");
	}
	//m_status = "Listening For Connections!!!";*/
	UpdateData(FALSE);
	listen_button.EnableWindow(FALSE);
	stop_button.EnableWindow(TRUE);
}

void tcpServerDlg::OnAccept()
{
	UpdateData(TRUE);
	UINT send_port;
	if (socket_Listener.Accept(socket_service))
	{
		socket_service.GetSockName(client_strIP, send_port);
		std::string temp2;
		std::stringstream ss;
		ss << send_port;
		ss >> temp2;
		timeStamp ts;
		loger.Insert(loger.GetLength(), ts.getNow());  
		CString temp = _T("和ip ")+ client_strIP + _T("端口为  ") + temp2.c_str()+ _T("连接成功 ");
		loger.Insert(loger.GetLength(), temp);
		loger += _T("\r\n");
		socket_service.Send("tcp Server 001", strlen("tcp Server 001"));
		UpdateData(FALSE);
	}

	else
	{
		socket_service.GetSockName(client_strIP, send_port);
		timeStamp ts;
		loger.Insert(loger.GetLength(), ts.getNow());
		CString temp = _T("和ip ") + client_strIP + _T("连接失败 ");
		loger.Insert(loger.GetLength(), temp);
		loger += _T("\r\n");
		UpdateData(FALSE);
	}
}

void tcpServerDlg::OnClose()
{
	UINT port;
	UpdateData(TRUE);
	timeStamp ts;
	loger.Insert(loger.GetLength(), ts.getNow());
	CString temp = _T("和ip ") + client_strIP + _T("连接中断 ");
	loger.Insert(loger.GetLength(), temp);
	loger += _T("\r\n");
	UpdateData(FALSE);
	OnBnClickedButton2();
}

void tcpServerDlg::OnReceive() {
	UpdateData(TRUE);
	char *pBuf = new char[1025];
	CString strData;
	int iLen;
	iLen = socket_service.Receive(pBuf, 1024);
	if (iLen == SOCKET_ERROR)
	{
		timeStamp ts;
		loger.Insert(loger.GetLength(), ts.getNow());
		CString temp = _T("接收客户端消息失败 ");
		loger.Insert(loger.GetLength(), temp);
		loger += _T("\r\n");
	}
	else
	{
		pBuf[iLen] = NULL;
		strData = pBuf;
		CString reducedCommand = strData;
		reducedCommand.MakeUpper();
		if (strData.Compare(protocal_table[0]) == 0)
		{ //握手包收到
		}else if (reducedCommand.Compare(protocal_table[2]) == 0)
		{ //date指令
			timeStamp ts;
			loger.Insert(loger.GetLength(), ts.getNow());
			CString response = ts.getDate();
			CString temp = _T("收到请求 ") + strData + _T("响应为  ") + response;
			loger.Insert(loger.GetLength(), temp);
			loger += _T("\r\n");
			socket_service.Send(response, strlen(response));
		}else if (reducedCommand.Compare(protocal_table[3]) == 0)
		{ //time指令
			timeStamp ts;
			loger.Insert(loger.GetLength(), ts.getNow());
			CString response = ts.getTime();
			CString temp = _T("收到请求 ") + strData + _T("响应为  ") + response;
			loger.Insert(loger.GetLength(), temp);
			loger += _T("\r\n");
			socket_service.Send(response, strlen(response));
		}
		else {//未识别指令
			timeStamp ts;
			loger.Insert(loger.GetLength(), ts.getNow());
			CString temp = _T("收到请求 ") + strData + _T("发生错误：未识别指令");
			loger.Insert(loger.GetLength(), temp);
			loger += _T("\r\n");
			socket_service.Send("fatal:undetifier command", strlen("fatal:undetifier command"));
		}
		UpdateData(FALSE);
		delete pBuf;
	}
}