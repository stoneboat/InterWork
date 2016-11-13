#pragma once

// udpSocket ÃüÁîÄ¿±ê

class Socket : public CAsyncSocket
{
public:
	void SetParentDlg(CDialog *pDlg, int type);
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	Socket();
	virtual ~Socket();
private:
	CDialog * m_pDlg;
	int DialogType;
	/*
	0 for tcp_client
	1 for tcp_server
	2 for udp_client
	3 for udp_server
	*/
};


