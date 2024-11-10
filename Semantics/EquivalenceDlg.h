//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once
#include "afxwin.h"
#include "afxbutton.h"
#include "ScientificListBox.h"
#include "Formula.h"
#include "ScientificStatic.h"
#include "afxcmn.h"

// диалоговое окно EquvalenceDlg

class EquivalenceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EquivalenceDlg)

	void MoveSelected(ScientificListBox &Source, ScientificListBox &Destination);
	void MoveAll(ScientificListBox &Source, ScientificListBox &Destination);


	vector <Formula *> * formulas;
	vector <EntityBase *> * allEntities;
	vector <Equivalence *> * allEquivalences;
public:
	EquivalenceDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~EquivalenceDlg();

// Данные диалогового окна
	enum { IDD = IDD_EQUIVALENCEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	ScientificListBox m_ListBoxSource;
	ScientificListBox m_ListBoxDestination1;
	ScientificListBox m_ListBoxDestination2;
	CMFCButton m_ButtonAdd1;
	CMFCButton m_ButtonRemove1;
	CScientificStatic m_StaticDescription;
	CMFCButton m_ButtonAddAll1;
	CMFCButton m_ButtonRemoveAll1;
	CButton m_ButtonOK;
	CFont * m_fIndexes;
	CFont * m_fSymbol;
	CFont * m_fVariables;
	CFont * m_fIndexesVariables;
	CFont * m_fSymbolVariables;


	afx_msg void OnBnClickedCheck2();
	void  setFormulas(vector <EntityBase *> * all_entities_ = NULL) { allEntities = all_entities_; };
	void  setEquivalences(vector <Equivalence *> * all_equivalences_ = NULL) { allEquivalences = all_equivalences_; };
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedMfcbutton1();
	afx_msg void OnBnClickedMfcbutton5();
	afx_msg void OnBnClickedMfcbutton2();
	afx_msg void OnBnClickedMfcbutton6();
	afx_msg void OnSelchangeListdest1();
	void ShowCandidates();
	void HideCandidates();
	void SetEquivalenceState();
};
