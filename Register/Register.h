
// Register.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "Sys.h"
// CRegisterApp:
// �йش����ʵ�֣������ Register.cpp
//

class CRegisterApp : public CWinApp
{
public:
	CRegisterApp();
	~CRegisterApp();
// ��д
public:
	virtual BOOL InitInstance();
// ʵ��
protected:
	
public:
	
	DECLARE_MESSAGE_MAP()
};

extern CRegisterApp theApp;