#pragma once
#include "afxwin.h"
#include "Socket.h"


// udpClientDlg �Ի���

class tcpClientDlg : public CDialogEx
{
	DECLARE_DYNAMIC(tcpClientDlg)

public:
	tcpClientDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~tcpClientDlg();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	// ���ӵ��ķ������˵�ַ
	CString Server_ip;
	// ���͵��Ķ˿�
	int port;
	CString loger;
	// ���͵�ָ��
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
