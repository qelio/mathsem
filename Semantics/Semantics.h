
// Semantics.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы
#include <string>

__declspec(selectany) std::string CURRENT_LANG_OF("eng");


// CSemanticsApp:
// О реализации данного класса см. Semantics.cpp
//

class CSemanticsApp : public CWinApp
{
public:
	CSemanticsApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CSemanticsApp theApp;