
// Semantics.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������
#include <string>

__declspec(selectany) std::string CURRENT_LANG_OF("eng");


// CSemanticsApp:
// � ���������� ������� ������ ��. Semantics.cpp
//

class CSemanticsApp : public CWinApp
{
public:
	CSemanticsApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CSemanticsApp theApp;