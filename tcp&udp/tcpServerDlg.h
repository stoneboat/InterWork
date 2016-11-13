#pragma once
#include "afxwin.h"
#include "Socket.h"

// udpServerDlg �Ի���

class tcpServerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(tcpServerDlg)

public:
	tcpServerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~tcpServerDlg();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
	/* ֻ����һ�������ߣ�����ֻ����ʱ�Ĺ���*/
	Socket socket_service;
public:
	// �����˿�
	int port;
	// ��������־
	CString loger;
	time_t nowtime;
};
