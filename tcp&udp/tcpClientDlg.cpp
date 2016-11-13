// udpClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "work1.h"
#include "tcpClientDlg.h"
#include "afxdialogex.h"
#include "timeStamp.h"
#include "protocal.h"
#include <string>
#include <sstream>


// udpClientDlg �Ի���

IMPLEMENT_DYNAMIC(tcpClientDlg, CDialogEx)

tcpClientDlg::tcpClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, Server_ip(_T(""))
	, port(0)
	, loger(_T(""))
	, command(_T(""))
{

	EnableAutomation();

}

tcpClientDlg::~tcpClientDlg()
{
}

void tcpClientDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void tcpClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Server_ip);
	DDX_Text(pDX, IDC_EDIT2, port);
	DDX_Text(pDX, IDC_EDIT3, loger);
	DDX_Text(pDX, IDC_EDIT4, command);
	DDX_Control(pDX, IDC_BUTTON1, connect_button);
	DDX_Control(pDX, IDC_BUTTON2, stop_button);
	DDX_Control(pDX, IDC_BUTTON3, command_button);
}

BOOL tcpClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog

	// TODO: Add extra initialization here
	SetDlgItemText(IDC_STATIC6, _T("ip��ַ"));
	SetDlgItemText(IDC_STATIC4, _T("�˿�"));
	SetDlgItemText(IDC_STATIC2, _T("״̬"));
	SetDlgItemText(IDC_STATIC3, _T("��־"));
	SetDlgItemText(IDC_STATIC5, _T("δ����"));
	SetDlgItemText(IDC_BUTTON1, _T("����"));
	SetDlgItemText(IDC_BUTTON2, _T("�ж�"));
	SetDlgItemText(IDC_BUTTON3, _T("�����"));
	this->SetWindowText(_T("tcp�ͻ���"));
	Server_ip = _T("127.0.0.1");
	port = 2000;
	loger = _T("");
	command = _T("");
	socket_client.SetParentDlg(this,0);
	UpdateData(FALSE);
	//socket_Listener.SetParentDlg(this);
	//socket_service.SetParentDlg(this);
	connect_button.EnableWindow(TRUE);
	stop_button.EnableWindow(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(tcpClientDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &tcpClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &tcpClientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &tcpClientDlg::OnBnClickedButton3)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(tcpClientDlg, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IudpClientDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {E526F0FD-5249-41B0-A3D3-50111778DF0D}
static const IID IID_IudpClientDlg =
{ 0xE526F0FD, 0x5249, 0x41B0, { 0xA3, 0xD3, 0x50, 0x11, 0x17, 0x78, 0xDF, 0xD } };

BEGIN_INTERFACE_MAP(tcpClientDlg, CDialogEx)
	INTERFACE_PART(tcpClientDlg, IID_IudpClientDlg, Dispatch)
END_INTERFACE_MAP()


// udpClientDlg ��Ϣ�������


void tcpClientDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	SetDlgItemText(IDC_STATIC5, _T("������"));
	socket_client.Create();
	socket_client.Connect(Server_ip, port);
	/*if (socket_client.Connect(Server_ip,port) == 0)
	{
		UINT uErr = GetLastError();
		TCHAR szError[256];
		wsprintf(szError, "Server Receive Socket Create() failed: %d", uErr);
		AfxMessageBox(szError);
		timeStamp ts;
		loger.Insert(loger.GetLength(), ts.getNow());   //display in server
		std::string digit;
		std::stringstream ss;
		ss << port;
		ss >> digit;
		CT2CA pszConvertedAnsiString(Server_ip);
		std::string ms = "����ip " + std::string(pszConvertedAnsiString)+"�˿� " + digit + "ʧ��";
		loger.Insert(loger.GetLength(), CString(ms.c_str()));
		loger += _T("\r\n");
		socket_client.Close();
	}*/
	
	socket_client.Send("tcp client 001", strlen("tcp client 001"));
	UpdateData(FALSE);
	connect_button.EnableWindow(FALSE);
	stop_button.EnableWindow(TRUE);
}


void tcpClientDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	socket_client.Close();
	SetDlgItemText(IDC_STATIC5, _T("δ����"));
	timeStamp ts;
	loger.Insert(loger.GetLength(), ts.getNow());
	CString temp = _T("�˳���ip ") + Server_ip + _T("����");
	loger.Insert(loger.GetLength(), temp);
	loger += _T("\r\n");
	UpdateData(FALSE);
	connect_button.EnableWindow(TRUE);
	stop_button.EnableWindow(FALSE);
}
void tcpClientDlg::OnConnect() {
	UpdateData(TRUE);
	timeStamp ts;
	loger.Insert(loger.GetLength(), ts.getNow());   //display in server
	std::string digit;
	std::stringstream ss;
	ss << port;
	ss >> digit;
	CT2CA pszConvertedAnsiString(Server_ip);
	std::string ms = "����ip " + std::string(pszConvertedAnsiString) + "�˿� " + digit + "�ɹ�";
	loger.Insert(loger.GetLength(), CString(ms.c_str()));
	loger += _T("\r\n");
	UpdateData(FALSE);
}
void tcpClientDlg::OnClose() {
	UpdateData(TRUE);
	timeStamp ts;
	loger.Insert(loger.GetLength(), ts.getNow());
	CString temp = _T("��ip ") + Server_ip + _T("�����ж� ");
	loger.Insert(loger.GetLength(), temp);
	loger += _T("\r\n");
	UpdateData(FALSE);
	OnBnClickedButton2();
}
void tcpClientDlg::OnReceive() {
	UpdateData(TRUE);
	char *pBuf = new char[1025];
	CString strData;
	int iLen;
	iLen = socket_client.Receive(pBuf, 1024);
	if (iLen == SOCKET_ERROR)
	{
		timeStamp ts;
		loger.Insert(loger.GetLength(), ts.getNow());
		CString temp = _T("���շ���������Ϣʧ�� ");
		loger.Insert(loger.GetLength(), temp);
		loger += _T("\r\n");
	}
	else
	{
		pBuf[iLen] = NULL;
		strData = pBuf;
		if (strData.Compare(protocal_table[1]) == 0)
		{
		}//���ְ��յ�
		else {
			timeStamp ts;
			loger.Insert(loger.GetLength(), ts.getNow());
			CString temp = _T("�յ���������Ӧ ")+ strData;
			loger.Insert(loger.GetLength(), temp);
			loger += _T("\r\n");
		}
		UpdateData(FALSE);
		delete pBuf;
	}
}

void tcpClientDlg::OnBnClickedButton3()
{
	// �����õ����ݣ����Ұ����ݷ���ȥ
	UpdateData(TRUE);
	int l = strlen(command);
	int error = socket_client.Send(command, strlen(command));
	if (error != l) {
		timeStamp ts;
		loger.Insert(loger.GetLength(), ts.getNow());
		CString temp = _T("��������˷�����Ϣʧ�� ");
		loger.Insert(loger.GetLength(), temp);
		loger += _T("\r\n");
	}
	else {
		timeStamp ts;
		loger.Insert(loger.GetLength(), ts.getNow());
		CString temp = _T("��������˷������� ")+command;
		loger.Insert(loger.GetLength(), temp);
		loger += _T("\r\n");
	}
	UpdateData(FALSE);
}
