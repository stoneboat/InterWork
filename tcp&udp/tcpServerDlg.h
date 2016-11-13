#pragma once
#include "afxwin.h"
#include "Socket.h"

// udpServerDlg 对话框

class tcpServerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(tcpServerDlg)

public:
	tcpServerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~tcpServerDlg();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CButton listen_button;
	CButton stop_button;

	void OnAccept();
	void OnClose();
	void OnReceive();
private:
	CString client_strIP;
	Socket socket_Listener;
	/* 只生成一个交互者，这里只是暂时的功用*/
	Socket socket_service;
public:
	// 监听端口
	int port;
	// 服务器日志
	CString loger;
	time_t nowtime;
};
