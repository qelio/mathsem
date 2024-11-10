#pragma once
#include "afxwin.h"
#include "afxbutton.h"
#include "ScientificListBox.h"
#include "Formula.h"
//#include "ScientificStatic.h"
//#include "afxcmn.h"

// диалоговое окно FromSetDialog

class FromSetDialog : public CDialogEx
{
	DECLARE_DYNAMIC(FromSetDialog)

	vector <FormulaSet *> * sets;
	vector <EntityBase *> * allEntities;

public:
	FromSetDialog(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~FromSetDialog();

// Данные диалогового окна
	enum { IDD = IDD_BELONGING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	void  setEntities(vector <EntityBase *> * all_entities_ = NULL) { allEntities = all_entities_; };
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeSetlist1();
	ScientificListBox m_ListBoxSource;
	CButton m_ButtonOK;
	afx_msg void OnBnClickedOk();
};
