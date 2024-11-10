//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once

#include "afxwin.h"
#include "Formula.h"
#include "ScientificListBox.h"
#include "ScientificStatic.h"
// ���������� ���� SetDialog

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����� SetDialog, ������������ ��� ����������� ���� IDD_SETDIALOG, ������������� ��� ���������� �������� ����������


class SetDialog : public CDialogEx
{
	DECLARE_DYNAMIC(SetDialog)

	vector <EntityBase *> * entities;    // ��������� �� ������ ���������, �� ������� ����� �������������� ����� ��� ���������� ��������� ����������
public:
	// �����������
	SetDialog(CWnd* pParent = NULL);   
	// �����������
	virtual ~SetDialog();

// ������ ����������� ����
	enum { IDD = IDD_SETDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	ScientificListBox m_list;    // ���� ������ ������
	CFont * m_fIndexes;          // 
	CFont * m_fSymbol;           // ��������� �� �����, ������������ ��� ����������� �������������� �������� (��� �������, Symbol)
	ScientificListBox m_listVariables;    // ���� ������ ��������� ����������
	CButton m_buttonOK;          // ������ "OK"


	// ���������� ������� �� ������ "OK"
	afx_msg void OnBnClickedOk();
	// ������������� �������� � �������� ������� � ��� ��������� ��� �������������
	virtual BOOL OnInitDialog();
	// ������������ ��������� �� ��������� ���������, �� ������� ����� ������� ������� � ��������� ����������, ��� ������� ��� �� ���������
	// ��������� ���������� (���� ��������� � ����������
	void  setEntities(vector <EntityBase *> * all_entities = NULL) {entities = all_entities; };
	// ����� ���������� ��������� ���������� � �������� m_listVariables ��� ���������� �������� � ������ ������
	void ShowFreeVariables();
	// ����� ������� ��������� ���������� �� �������� m_listVariables 
	void HideFreeVariables();
	// ���������� ������ �������
	afx_msg void OnSelchangeSetlist1();
	CButton m_CheckBelonging;
	CButton m_CheckSubSet;
	afx_msg void OnClickedBuildsubset();
	CComboBox m_ComboSubSet;
	CEdit m_IndexSubSet;
	CComboBox m_comboSet;
	CEdit m_indexSet;
	CScientificStatic m_label;
	CScientificStatic m_level;
	afx_msg void OnSelchangeSetlist2();

	// ����� ����������� ��������� ���������� � ������, ���� ��������� �� ������ ������ � �������������� ����������� ��������� ����� �����
	void CheckSelection();
	afx_msg void OnSelchangeSetcombo();
	afx_msg void OnChangeSetindex();
};
