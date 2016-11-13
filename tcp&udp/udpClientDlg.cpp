// udpClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "work1.h"
#include "udpClientDlg.h"
#include "afxdialogex.h"


// udpClientDlg �Ի���

IMPLEMENT_DYNAMIC(udpClientDlg, CDialogEx)

udpClientDlg::udpClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, Server_ip(_T(""))
	, Server_port(0)
	, command(_T(""))
	, response(_T(""))
{

	EnableAutomation();

}

udpClientDlg::~udpClientDlg()
{
}

void udpClientDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void udpClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Server_ip);
	DDX_Text(pDX, IDC_EDIT4, Server_port);
	DDX_Text(pDX, IDC_EDIT5, command);
	DDX_Text(pDX, IDC_EDIT6, response);
}
BOOL udpClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	UpdateData(TRUE);
	Server_ip = _T("127.0.0.1");
	Server_port = 2000;
	command = _T("");
	response = _T("");
	socket_client.SetParentDlg(this, 2);
	UpdateData(FALSE);
	int erro = socket_client.Create(2500, SOCK_DGRAM);
	if (!erro)
	{
		UINT uErr = GetLastError();
		TCHAR szError[256];
		wsprintf(szError, "Send Socket Create() failed: %d", uErr);
		AfxMessageBox(szError);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(udpClientDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &udpClientDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(udpClientDlg, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IudpClientDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {59D78B4C-6C7A-4A5A-AEC2-5B176B9924D5}
static const IID IID_IudpClientDlg =
{ 0x59D78B4C, 0x6C7A, 0x4A5A, { 0xAE, 0xC2, 0x5B, 0x17, 0x6B, 0x99, 0x24, 0xD5 } };

BEGIN_INTERFACE_MAP(udpClientDlg, CDialogEx)
	INTERFACE_PART(udpClientDlg, IID_IudpClientDlg, Dispatch)
END_INTERFACE_MAP()


// udpClientDlg ��Ϣ�������


void udpClientDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int l = strlen(command);
	int x = socket_client.SendTo(command, l, Server_port, Server_ip);
	if (l == x) {
		command = _T("����ʧ��");
	}
}
void udpClientDlg::OnReceive() {
	UpdateData(TRUE);
	char *pBuf = new char[1025];
	int iLen;
	CString server_ip;
	UINT server_port;
	iLen = socket_client.ReceiveFrom(pBuf, 1024, server_ip, server_port);
	/*if (server_ip!= Server_ip||server_port!=Server_port)
	{
		TCHAR szError[256];
		wsprintf(szError, "illegal packet form %s ip,%d port", server_ip,server_port);
		AfxMessageBox(szError);
	}*/
	if (iLen == SOCKET_ERROR)
		response = _T("������Ӧʧ��");
	else
	{
		pBuf[iLen] = NULL;
		response = pBuf;
	}
	delete pBuf;
	UpdateData(FALSE);
}