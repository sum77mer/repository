
// autodetect.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CautodetectApp: 
// �йش����ʵ�֣������ autodetect.cpp
//

class CautodetectApp : public CWinApp
{
public:
	CautodetectApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CautodetectApp theApp;