#pragma once


// test1 �Ի���

class test1 : public CDialogEx
{
	DECLARE_DYNAMIC(test1)

public:
	test1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~test1();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
