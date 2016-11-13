// udpSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "work1.h"
#include "Socket.h"
#include "tcpServerDlg.h"
#include  "tcpClientDlg.h"
#include "udpClientDlg.h"
#include "udpServerDlg.h"

// tcpSocket

Socket::Socket()
{
}

Socket::~Socket()
{
}
void Socket::SetParentDlg(CDialog *pDlg, int type)
{
	m_pDlg = pDlg;
	DialogType = type;
}
void Socket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	if (nErrorCode == 0)
	{
		((tcpServerDlg*)m_pDlg)->OnAccept();
	}
	CAsyncSocket::OnAccept(nErrorCode);
}
void Socket::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	if (nErrorCode == 0 || nErrorCode == 10053)//10053 是由于我直接关闭客户端连接造成的
	{
		if (DialogType == 1)
		    ((tcpServerDlg*)m_pDlg)->OnClose();
		if (DialogType == 0)
			((tcpClientDlg*)m_pDlg)->OnClose();
		
	}


	CAsyncSocket::OnClose(nErrorCode);
}
void Socket::OnConnect(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	if (nErrorCode == 0)
	{
		((tcpClientDlg*)m_pDlg)->OnConnect();
	}


	CAsyncSocket::OnConnect(nErrorCode);
}
void Socket::OnReceive(int nErrorCode) {
	if (nErrorCode == 0)
	{
		if(DialogType==1)
		  ((tcpServerDlg*)m_pDlg)->OnReceive();
		if (DialogType == 0)
			((tcpClientDlg*)m_pDlg)->OnReceive();
		if (DialogType == 3)
			((udpServerDlg*)m_pDlg)->OnReceive();
		if (DialogType == 2)
			((udpClientDlg*)m_pDlg)->OnReceive();
	}

	CAsyncSocket::OnReceive(nErrorCode);
}

void Socket::OnSend(int nErrorCode) {
	if (nErrorCode) {
		TCHAR szError[256];
		wsprintf(szError, "Send Socket Create() failed: %d", nErrorCode);
		AfxMessageBox(szError);
	}
	CAsyncSocket::OnSend(nErrorCode);
}
// tcpSocket 成员函数
