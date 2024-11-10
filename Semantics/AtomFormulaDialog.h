//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once

#include "ScientificStatic.h"
#include "afxwin.h"

// диалоговое окно CAtomFormulaDialog

class CAtomFormulaDialog : public CDialog
{
	DECLARE_DYNAMIC(CAtomFormulaDialog)
	BOOL OnInitDialog();
public:
	CAtomFormulaDialog(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CAtomFormulaDialog();

// Данные диалогового окна
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	// указатель на буфер текста переменной
	TCHAR * tbuf1;   
	// указатель на буфер текста множества
	TCHAR * tbuf2; 
	// указатель на буфер текста индекса переменной
	TCHAR * tbuf_index1;  
	// указатель на буфер текста индекса множества
	TCHAR * tbuf_index2;  
	// элемент описания 
	CScientificStatic m_lblDescription;
	// обработчик нажатия кнопки "Добавить"
	afx_msg void OnBnClickedOk();
	// основной шрифт для элемента описания m_lblDescription
	CFont * m_fIndexes;    
	// шрифт для математических символов
	CFont * m_fSymbol;
	// элемент для ввода индекса переменной
	CEdit m_index1;    
	// элемент для ввода индекса множества
	CEdit m_index2;  
	// выпадающий список текста переменной
	CComboBox m_combo1;
	// выпадающий список текста множества
	CComboBox m_combo2;
};
