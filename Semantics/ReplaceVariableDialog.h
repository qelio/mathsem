//  јвтор кода: “атаринцев ¬.¬., tatarintsev_vv@mail.ru , 2013-2017
//  Author: Tatarintsev V.V., tatarintsev_vv@mail.ru, 2013-2017
#pragma once

#include "afxwin.h"
#include "Formula.h"
#include "ScientificListBox.h"
// диалоговое окно ReplaceVariableDialog

class ReplaceVariableDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ReplaceVariableDialog)

	vector <EntityBase *> * entities;    // указатель на список сущностей схемы, по которым будет заполн€тьс€ список формул и множеств, уже из которых 
	// будут выбиратьс€ свободные переменные дл€ замены

public:
	ReplaceVariableDialog(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~ReplaceVariableDialog();

// ƒанные диалогового окна
	enum { IDD = IDD_REPLACEVARIABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CFont * m_fIndexes;          // 
	CFont * m_fSymbol;           // указатель на шрифт, используемый дл€ отображени€ математических символов (как правило, Symbol)
	CEdit m_editIndex;
	ScientificListBox m_list;
	ScientificListBox m_listFreeVariables;
	ScientificListBox m_listVariables;
	// выпадающий список текста переменной
	CComboBox m_comboName;

	// устанавливает значени€ и свойства диалога и его элементов при инициализации
	virtual BOOL OnInitDialog();
	// устанавливаю указатель на контейнер сущностей, из которых нужно выбрать формулы и свободные переменные, уже дл€ которых будут осуществл€тьс€ замена
	void setEntities(vector <EntityBase *> * all_entities = NULL) {entities = all_entities; };
	// метод отображает свободные переменные в элементе m_listFreeVariables дл€ выбранного элемента в списке формул
	void ShowFreeVariables();
	// метод удал€ет свободные переменные из элемента m_listFreeVariables 
	void HideFreeVariables();
	// метод отображает свободные переменные в элементе m_listeVariables дл€ выбранного элемента в списке свободных (замен€емых) переменных
	void ShowVariables();
	// метод удал€ет свободные переменные из элемента m_listVariables 
	void HideVariables();
	// замен€ю список обозначений в комбобоксе на заглавные или прописные, в зависимости от того, заглавный или прописной символ, передаваемый параметром функции
	void ResetComboNames(TCHAR symbol);
	int m_dataRadio;
	vector <EntityVariable *> pev_new;	// вектор переменных дл€ замены

	CButton m_buttonOK;
	afx_msg void OnSelchangeSetlist1();
	afx_msg void OnSelchangeSetlist2();
	afx_msg void OnBnClickedRadioinputtext();
	afx_msg void OnBnClickedRadioselectvariable();
};
