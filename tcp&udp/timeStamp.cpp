// timeStamp.cpp : 实现文件
//

#include "stdafx.h"
#include "timeStamp.h"
#include <windows.h> 
#include <stdio.h> 
#include <sstream>

// timeStamp

timeStamp::timeStamp()
{
}

timeStamp::~timeStamp()
{
}
CString timeStamp::getNow()
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	short time[7] = { sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds };
	std::string colon = ":";
	std::string slash = "/";
	std::string space = " ";
	CString result = _T("");
	std::string temp;
	std::stringstream ss;
	ss << sys.wYear;
	ss >> temp;
	result.Insert(result.GetAllocLength(), CString(temp.c_str()));
	for (int i = 1; i <= 2; i++) {
		std::stringstream ss;
		result.Insert(result.GetAllocLength(), CString(slash.c_str()));
		ss << time[i];
		ss >> temp;
		result.Insert(result.GetAllocLength(), CString(temp.c_str()));
	}
	result.Insert(result.GetAllocLength(), CString(space.c_str()));
	for (int i = 3; i <= 6; i++) {
		std::stringstream ss;
		ss << time[i];
		ss >> temp;
		result.Insert(result.GetAllocLength(), CString(temp.c_str()));
		result.Insert(result.GetAllocLength(), CString(colon.c_str()));
	}
	return result;
}
CString timeStamp::getTime() {
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	short time[7] = { sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds };
	std::string colon = ":";
	CString result = _T("");
	std::string temp;
	std::stringstream ss;
	for (int i = 3; i <= 6; i++) {
		std::stringstream ss;
		ss << time[i];
		ss >> temp;
		result.Insert(result.GetAllocLength(), CString(temp.c_str()));
		result.Insert(result.GetAllocLength(), CString(colon.c_str()));
	}
	return result;
}
CString timeStamp::getDate() {
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	short time[7] = { sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds };
	std::string slash = "/";
	CString result = _T("");
	std::string temp;
	std::stringstream ss;
	ss << sys.wYear;
	ss >> temp;
	result.Insert(result.GetAllocLength(), CString(temp.c_str()));
	for (int i = 1; i <= 2; i++) {
		std::stringstream ss;
		result.Insert(result.GetAllocLength(), CString(slash.c_str()));
		ss << time[i];
		ss >> temp;
		result.Insert(result.GetAllocLength(), CString(temp.c_str()));
	}
	return result;
}