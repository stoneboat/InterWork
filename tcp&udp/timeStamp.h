#pragma once
#include "afxwin.h"
class timeStamp {
public:
	timeStamp();
	virtual~timeStamp();
	CString getNow();
	CString getTime();
	CString getDate();
};