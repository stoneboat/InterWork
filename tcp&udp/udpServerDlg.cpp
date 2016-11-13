// udpServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "work1.h"
#include "udpServerDlg.h"
#include "afxdialogex.h"
#include "time.h"
#include "timeStamp.h"
#include "protocal.h"
#include <string>
#include <sstream>

// udpServerDlg 对话框

IMPLEMENT_DYNAMIC(udpServerDlg, CDialogEx)

udpServerDlg::udpServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG5, pParent)
	, loger(_T(""))
	, Server_port(0)
{

}

udpServerDlg::~udpServerDlg()
{
}

void udpServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, loger);
	DDX_Text(pDX, IDC_STATIC10, Server_port);
}


BEGIN_MESSAGE_MAP(udpServerDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL udpServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateData(TRUE);
	loger = _T("");
	socket_server.SetParentDlg(this, 3);
	srand((unsigned)time(NULL));
	Server_port = 2000 + rand() % 500;
	UpdateData(FALSE);
	int erro = socket_server.Create(Server_port, SOCK_DGRAM);
	if (!erro)
	{
		UINT uErr = GetLastError();
		TCHAR szError[256];
		wsprintf(szError, "Send Socket Create() failed: %d", uErr);
		AfxMessageBox(szError);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}
void udpServerDlg::OnReceive() {
	UpdateData(TRUE);
	char *pBuf = new char[1025];
	CString strData;
	int iLen;
	CString client_ip;
	UINT client_port;
	iLen = socket_server.ReceiveFrom(pBuf, 1024, client_ip, client_port);
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
		if (reducedCommand.Compare(protocal_table[2]) == 0)
		{ //date指令
			timeStamp ts;
			loger.Insert(loger.GetLength(), ts.getNow());   //display in server
			std::string digit;
			std::stringstream ss;
			ss << client_port;
			ss >> digit;
			CT2CA pszConvertedAnsiString(client_ip);
			std::string ms = "收到IP=" + std::string(pszConvertedAnsiString) + "端口=" + digit + "请求【";
			loger.Insert(loger.GetLength(), CString(ms.c_str()));
			loger.Insert(loger.GetLength(), strData);
			loger += _T("】，响应【");
			CString response = ts.getDate();
			loger += response;
			loger += _T("】");
			loger.Insert(loger.GetLength(), _T("\r\n"));
			socket_server.SendTo(response, strlen(response),client_port,client_ip);
		}
		else if (reducedCommand.Compare(protocal_table[3]) == 0)
		{ //time指令
			timeStamp ts;
			loger.Insert(loger.GetLength(), ts.getNow());   //display in server
			std::string digit;
			std::stringstream ss;
			ss << client_port;
			ss >> digit;
			CT2CA pszConvertedAnsiString(client_ip);
			std::string ms = "收到IP=" + std::string(pszConvertedAnsiString) + "端口=" + digit + "请求【";
			loger.Insert(loger.GetLength(), CString(ms.c_str()));
			loger.Insert(loger.GetLength(), strData);
			loger += _T("】，响应【");
			CString response = ts.getTime();
			loger += response;
			loger += _T("】");
			loger += _T("\r\n");
			socket_server.SendTo(response, strlen(response),client_port,client_ip);
		}
		else {//未识别指令
			timeStamp ts;
			loger.Insert(loger.GetLength(), ts.getNow());
			CString temp = _T("收到请求 ") + strData + _T("发生错误：未识别指令");
			loger.Insert(loger.GetLength(), temp);
			loger += _T("\r\n");
			socket_server.SendTo("fatal:undetifier command", strlen("fatal:undetifier command"),client_port,client_ip);
		}
		UpdateData(FALSE);
		delete pBuf;
	}
}

// udpServerDlg 消息处理程序
