#pragma once
# include "Socket.h"

// udpClientDlg �Ի���

class udpClientDlg : public CDialogEx
{
	DECLARE_DYNAMIC(udpClientDlg)

public:
	udpClientDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~udpClientDlg();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CString Server_ip;
	int Server_port;
	CString command;
	CString response;
private:
	Socket socket_client;
public:
	afx_msg void OnBnClickedButton1();
	void OnReceive();
};
