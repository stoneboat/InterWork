#pragma once
#include "afxwin.h"


// consoleWin 对话框

class consoleWin : public CDialogEx
{
	DECLARE_DYNAMIC(consoleWin)

public:
	consoleWin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~consoleWin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CButton server_factory;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
