#pragma once
# include "Socket.h"

// udpServerDlg �Ի���

class udpServerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(udpServerDlg)

public:
	udpServerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~udpServerDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
