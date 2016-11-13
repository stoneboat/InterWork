// tcpServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "work1.h"
#include "tcpServerDlg.h"
#include "afxdialogex.h"
#include "timeStamp.h"
#include "protocal.h"
#include <string>
#include <sstream>

// udpServerDlg �Ի���

IMPLEMENT_DYNAMIC(tcpServerDlg, CDialogEx)

tcpServerDlg::tcpServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, port(0)
	, loger(_T(""))
{

	EnableAutomation();

}

tcpServerDlg::~tcpServerDlg()
{
}

void tcpServerDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void tcpServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT2, server_status);
	DDX_Control(pDX, IDC_BUTTON1, listen_button);
	DDX_Control(pDX, IDC_BUTTON2, stop_button);
	DDX_Text(pDX, IDC_EDIT1, port);
	//  DDX_Control(pDX, IDC_EDIT3, server_loger);
	DDX_Text(pDX, IDC_EDIT2, loger);
}
BOOL tcpServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog

	// TODO: Add extra initialization here
	SetDlgItemText(IDC_STATIC1, _T("�˿�"));
	SetDlgItemText(IDC_STATIC2, _T("״̬"));
	SetDlgItemText(IDC_STATIC3, _T("��־"));
	SetDlgItemText(IDC_STATIC4, _T("δ����"));
	SetDlgItemText(IDC_BUTTON1, _T("����"));
	SetDlgItemText(IDC_BUTTON2, _T("�ж�"));
	this->SetWindowText(_T("tcp������"));
	port = 2000;
	loger = _T("");
	UpdateData(FALSE);
	socket_Listener.SetParentDlg(this,1);
	socket_service.SetParentDlg(this,1);
	listen_button.EnableWindow(TRUE);
	stop_button.EnableWindow(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(tcpServerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &tcpServerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &tcpServerDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(tcpServerDlg, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IudpServerDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {EC578B9D-1F6A-4004-8E2B-C1469BF0C82D}
static const IID IID_IudpServerDlg =
{ 0xEC578B9D, 0x1F6A, 0x4004, { 0x8E, 0x2B, 0xC1, 0x46, 0x9B, 0xF0, 0xC8, 0x2D } };

BEGIN_INTERFACE_MAP(tcpServerDlg, CDialogEx)
	INTERFACE_PART(tcpServerDlg, IID_IudpServerDlg, Dispatch)
END_INTERFACE_MAP()


// udpServerDlg ��Ϣ�������


void tcpServerDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	socket_service.Close();
	socket_Listener.Close();
	SetDlgItemText(IDC_STATIC4, _T("δ����"));
	UpdateData(FALSE);
	listen_button.EnableWindow(TRUE);
	stop_button.EnableWindow(FALSE);
}


void tcpServerDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	SetDlgItemText(IDC_STATIC4, _T("������"));
	//port.SetWindowText(_T("ABC")); //�O��
	//CString strSource;
	//port.GetWindowText(strSource);
	socket_Listener.Create(port);
	if (socket_Listener.Listen() == FALSE)
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
		std::string ms = "�����˿�" + digit + "ʧ�ܣ������ѱ�ռ�ã��뻻һ���˿�";
		loger.Insert(loger.GetLength(), CString(ms.c_str()));
		loger += _T("\r\n");
		socket_Listener.Close();
	}
	else {
		timeStamp ts;
		loger.Insert(loger.GetLength(), ts.getNow());   //display in server
		std::string digit;
		std::stringstream ss;
		ss << port;
		ss >> digit;
		std::string ms = "��ʼ�ɹ������˿ڣ� " + digit;
		loger.Insert(loger.GetLength(), CString(ms.c_str()));
		loger += _T("\r\n");
	}
	//m_status = "Listening For Connections!!!";*/
	UpdateData(FALSE);
	listen_button.EnableWindow(FALSE);
	stop_button.EnableWindow(TRUE);
}

void tcpServerDlg::OnAccept()
{
	UpdateData(TRUE);
	UINT send_port;
	if (socket_Listener.Accept(socket_service))
	{
		socket_service.GetSockName(client_strIP, send_port);
		std::string temp2;
		std::stringstream ss;
		ss << send_port;
		ss >> temp2;
		timeStamp ts;
		loger.Insert(loger.GetLength(), ts.getNow());  
		CString temp = _T("��ip ")+ client_strIP + _T("�˿�Ϊ  ") + temp2.c_str()+ _T("���ӳɹ� ");
		loger.Insert(loger.GetLength(), temp);
		loger += _T("\r\n");
		socket_service.Send("tcp Server 001", strlen("tcp Server 001"));
		UpdateData(FALSE);
	}

	else
	{
		socket_service.GetSockName(client_strIP, send_port);
		timeStamp ts;
		loger.Insert(loger.GetLength(), ts.getNow());
		CString temp = _T("��ip ") + client_strIP + _T("����ʧ�� ");
		loger.Insert(loger.GetLength(), temp);
		loger += _T("\r\n");
		UpdateData(FALSE);
	}
}

void tcpServerDlg::OnClose()
{
	UINT port;
	UpdateData(TRUE);
	timeStamp ts;
	loger.Insert(loger.GetLength(), ts.getNow());
	CString temp = _T("��ip ") + client_strIP + _T("�����ж� ");
	loger.Insert(loger.GetLength(), temp);
	loger += _T("\r\n");
	UpdateData(FALSE);
	OnBnClickedButton2();
}

void tcpServerDlg::OnReceive() {
	UpdateData(TRUE);
	char *pBuf = new char[1025];
	CString strData;
	int iLen;
	iLen = socket_service.Receive(pBuf, 1024);
	if (iLen == SOCKET_ERROR)
	{
		timeStamp ts;
		loger.Insert(loger.GetLength(), ts.getNow());
		CString temp = _T("���տͻ�����Ϣʧ�� ");
		loger.Insert(loger.GetLength(), temp);
		loger += _T("\r\n");
	}
	else
	{
		pBuf[iLen] = NULL;
		strData = pBuf;
		CString reducedCommand = strData;
		reducedCommand.MakeUpper();
		if (strData.Compare(protocal_table[0]) == 0)
		{ //���ְ��յ�
		}else if (reducedCommand.Compare(protocal_table[2]) == 0)
		{ //dateָ��
			timeStamp ts;
			loger.Insert(loger.GetLength(), ts.getNow());
			CString response = ts.getDate();
			CString temp = _T("�յ����� ") + strData + _T("��ӦΪ  ") + response;
			loger.Insert(loger.GetLength(), temp);
			loger += _T("\r\n");
			socket_service.Send(response, strlen(response));
		}else if (reducedCommand.Compare(protocal_table[3]) == 0)
		{ //timeָ��
			timeStamp ts;
			loger.Insert(loger.GetLength(), ts.getNow());
			CString response = ts.getTime();
			CString temp = _T("�յ����� ") + strData + _T("��ӦΪ  ") + response;
			loger.Insert(loger.GetLength(), temp);
			loger += _T("\r\n");
			socket_service.Send(response, strlen(response));
		}
		else {//δʶ��ָ��
			timeStamp ts;
			loger.Insert(loger.GetLength(), ts.getNow());
			CString temp = _T("�յ����� ") + strData + _T("��������δʶ��ָ��");
			loger.Insert(loger.GetLength(), temp);
			loger += _T("\r\n");
			socket_service.Send("fatal:undetifier command", strlen("fatal:undetifier command"));
		}
		UpdateData(FALSE);
		delete pBuf;
	}
}