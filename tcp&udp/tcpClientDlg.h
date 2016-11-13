#pragma once
#include "afxwin.h"
#include "Socket.h"


// udpClientDlg 对话框

class tcpClientDlg : public CDialogEx
{
	DECLARE_DYNAMIC(tcpClientDlg)

public:
	tcpClientDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~tcpClientDlg();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	// 连接到的服务器端地址
	CString Server_ip;
	// 发送到的端口
	int port;
	CString loger;
	// 发送的指令
	CString command;
	CButton connect_button;
	CButton stop_button;
	CButton command_button;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

	void OnConnect();
	void OnClose();
	void OnReceive();
private:
	Socket socket_client;
public:
	afx_msg void OnBnClickedButton3();
};
