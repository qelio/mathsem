//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once
#include "afxcmn.h"
#include "Formula.h"
#include "afxwin.h"
#include "MathListCtrlEx.h"
#include "MyEdit.h"





// диалоговое окно SummaryDialog

class SummaryDialog : public CDialog
{
	DECLARE_DYNAMIC(SummaryDialog)
	BOOL OnInitDialog();

	vector <EntityBase *> * entities;
	// функция проверяет строку замены на обозначения, которые могут быть обозначениями переменных (вида симол и обозначение индекса) и если они найдены, 
	// проверяет, все ли эти обозначения совпадают со свободными переменными у данного обьекта
	bool IfCorrectRedefinition(EntityBase * pbase, tstring & new_text);
public:
	// конструктор
	SummaryDialog(CWnd* pParent = NULL);   
	// деструктор
	virtual ~SummaryDialog();

// Данные диалогового окна
	enum { IDD = IDD_SUMMARYDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	// таблица просмотра/редактирования, отображающая строки SemanticString
	CMathListCtrlEx m_list;
	// окно редактирования
//	CEdit m_edit;
	CMyEdit m_edit;

public:
	// метод сопоставляет элементу просмотра контейнер сущностей (формул и множеств истинности)
	void  setFormulas(vector <EntityBase *> * all_entities = NULL);
	//  раньше использовался для отлавливания событий от клавиатуры, сейчас пока ничего
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//  обработчик нажатия на кнопку "Отмена"
	virtual void OnCancel();
	//  обработчик нажатия на кнопку "ОК"
//	virtual void OnOK();
	// метод выставляет высоту столбцов
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	// перебор строк таблицы и сохранение значений редактируемых ячеек в соответствующих сущностях схемы
	void SaveAndExit();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedPereopisanie();
	afx_msg void OnLvnOdstatechangedSummarylist(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_RedefineBtn;
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};


void ReverseDefinition(vector <EntityBase *> * temp_entities, vector <EntityBase *> * entities, int first, int last, SummaryDialog *psd = nullptr);
