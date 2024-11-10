//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014

// SemanticsDlg.h : файл заголовка
//

#pragma once

#include "Formula.h"
#include "ScientificStatic.h"
#include "ScientificButton.h"
#include "afxeditbrowsectrl.h"
#include "VUENode.h"
#include "VUELink.h"
#include "afxwin.h"
#include "resource.h"

// здесь кусок для попыток работы с библиотекой libxml2, но для Windows я отказался ввиду сложностей с дополнительными библиоеками и установкой dll
// для библиотеки libxml2 и libiconv, а также принимая во внимание необходимость упрощения для заказчика
//#include <libxml\parser.h>
//#include <libxml\tree.h>


//#define LIBXML_TREE_ENABLED
//#define LIBXML_OUTPUT_ENABLED
// конец блока

// диалоговое окно CSemanticsDlg
class CSemanticsDlg : public CDialogEx
{
// Создание
public:
	CSemanticsDlg(CWnd* pParent = NULL);	// стандартный конструктор
	~CSemanticsDlg();
// Данные диалогового окна
	enum { IDD = IDD_SEMANTICS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedShowallformulas3();
	afx_msg void OnBnClickedAddatomformula();


	vector <EntityBase *> all_entities;

	afx_msg void OnBnClickedBuildformula1();
	afx_msg void OnBnClickedBuildformula2();
	afx_msg void OnBnClickedBuildformula3();
	afx_msg void OnBnClickedBuildformula4();
	afx_msg void OnBnClickedBuildformula5();
	afx_msg void OnBnClickedShowallformulas();
	afx_msg void OnBnClickedChangeNewVariable();
	afx_msg void OnBnClickedHelp();
//	CMFCButton m_button5;
	CScientificButton m_button5;
	CScientificButton m_button4;
	CScientificButton m_button3;
	CScientificButton m_button2;
	CScientificButton m_button1;
	CScientificButton m_button6;
	CScientificButton m_button;
	CMFCEditBrowseCtrl m_fileFinder;
	afx_msg void OnBnClickedBuildformula6();
	CScientificButton m_buttonSet;
	afx_msg void OnBnClickedExport();
	CMFCEditBrowseCtrl m_fileWordExport;
	afx_msg void OnBnClickedSavescheme();
	afx_msg void OnBnClickedLoadscheme();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeMfceditbrowse2();
	afx_msg void OnBnClickedBuildformula7();
	CScientificButton m_button7;
	afx_msg void OnBnClickedBuildtuple();
	CScientificButton m_KortegeButton;
	afx_msg void OnBnClickedChangevariable();
	CScientificButton m_ChangeVariable;
	int m_rbLang;
	afx_msg void OnBnClickedRus();
	afx_msg void OnBnClickedEng();
};
