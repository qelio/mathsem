//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once
#include "afxcmn.h"
#include "Formula.h"
#include "afxwin.h"
#include "MathListCtrlEx.h"
#include "MyEdit.h"





// ���������� ���� SummaryDialog

class SummaryDialog : public CDialog
{
	DECLARE_DYNAMIC(SummaryDialog)
	BOOL OnInitDialog();

	vector <EntityBase *> * entities;
	// ������� ��������� ������ ������ �� �����������, ������� ����� ���� ������������� ���������� (���� ����� � ����������� �������) � ���� ��� �������, 
	// ���������, ��� �� ��� ����������� ��������� �� ���������� ����������� � ������� �������
	bool IfCorrectRedefinition(EntityBase * pbase, tstring & new_text);
public:
	// �����������
	SummaryDialog(CWnd* pParent = NULL);   
	// ����������
	virtual ~SummaryDialog();

// ������ ����������� ����
	enum { IDD = IDD_SUMMARYDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	// ������� ���������/��������������, ������������ ������ SemanticString
	CMathListCtrlEx m_list;
	// ���� ��������������
//	CEdit m_edit;
	CMyEdit m_edit;

public:
	// ����� ������������ �������� ��������� ��������� ��������� (������ � �������� ����������)
	void  setFormulas(vector <EntityBase *> * all_entities = NULL);
	//  ������ ������������� ��� ������������ ������� �� ����������, ������ ���� ������
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//  ���������� ������� �� ������ "������"
	virtual void OnCancel();
	//  ���������� ������� �� ������ "��"
//	virtual void OnOK();
	// ����� ���������� ������ ��������
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	// ������� ����� ������� � ���������� �������� ������������� ����� � ��������������� ��������� �����
	void SaveAndExit();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedPereopisanie();
	afx_msg void OnLvnOdstatechangedSummarylist(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_RedefineBtn;
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};


void ReverseDefinition(vector <EntityBase *> * temp_entities, vector <EntityBase *> * entities, int first, int last, SummaryDialog *psd = nullptr);
