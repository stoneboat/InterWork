#pragma once
# include "Socket.h"

// udpServerDlg 对话框

class udpServerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(udpServerDlg)

public:
	udpServerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~udpServerDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString loger;
private:
	Socket socket_server;
public:
	int Server_port;
	void OnReceive();
};
