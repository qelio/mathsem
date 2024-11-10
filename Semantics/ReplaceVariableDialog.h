//  ����� ����: ���������� �.�., tatarintsev_vv@mail.ru , 2013-2017
//  Author: Tatarintsev V.V., tatarintsev_vv@mail.ru, 2013-2017
#pragma once

#include "afxwin.h"
#include "Formula.h"
#include "ScientificListBox.h"
// ���������� ���� ReplaceVariableDialog

class ReplaceVariableDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ReplaceVariableDialog)

	vector <EntityBase *> * entities;    // ��������� �� ������ ��������� �����, �� ������� ����� ����������� ������ ������ � ��������, ��� �� ������� 
	// ����� ���������� ��������� ���������� ��� ������

public:
	ReplaceVariableDialog(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~ReplaceVariableDialog();

// ������ ����������� ����
	enum { IDD = IDD_REPLACEVARIABLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CFont * m_fIndexes;          // 
	CFont * m_fSymbol;           // ��������� �� �����, ������������ ��� ����������� �������������� �������� (��� �������, Symbol)
	CEdit m_editIndex;
	ScientificListBox m_list;
	ScientificListBox m_listFreeVariables;
	ScientificListBox m_listVariables;
	// ���������� ������ ������ ����������
	CComboBox m_comboName;

	// ������������� �������� � �������� ������� � ��� ��������� ��� �������������
	virtual BOOL OnInitDialog();
	// ������������ ��������� �� ��������� ���������, �� ������� ����� ������� ������� � ��������� ����������, ��� ��� ������� ����� �������������� ������
	void setEntities(vector <EntityBase *> * all_entities = NULL) {entities = all_entities; };
	// ����� ���������� ��������� ���������� � �������� m_listFreeVariables ��� ���������� �������� � ������ ������
	void ShowFreeVariables();
	// ����� ������� ��������� ���������� �� �������� m_listFreeVariables 
	void HideFreeVariables();
	// ����� ���������� ��������� ���������� � �������� m_listeVariables ��� ���������� �������� � ������ ��������� (����������) ����������
	void ShowVariables();
	// ����� ������� ��������� ���������� �� �������� m_listVariables 
	void HideVariables();
	// ������� ������ ����������� � ���������� �� ��������� ��� ���������, � ����������� �� ����, ��������� ��� ��������� ������, ������������ ���������� �������
	void ResetComboNames(TCHAR symbol);
	int m_dataRadio;
	vector <EntityVariable *> pev_new;	// ������ ���������� ��� ������

	CButton m_buttonOK;
	afx_msg void OnSelchangeSetlist1();
	afx_msg void OnSelchangeSetlist2();
	afx_msg void OnBnClickedRadioinputtext();
	afx_msg void OnBnClickedRadioselectvariable();
};
