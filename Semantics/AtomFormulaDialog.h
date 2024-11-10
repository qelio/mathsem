//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once

#include "ScientificStatic.h"
#include "afxwin.h"

// ���������� ���� CAtomFormulaDialog

class CAtomFormulaDialog : public CDialog
{
	DECLARE_DYNAMIC(CAtomFormulaDialog)
	BOOL OnInitDialog();
public:
	CAtomFormulaDialog(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CAtomFormulaDialog();

// ������ ����������� ����
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	// ��������� �� ����� ������ ����������
	TCHAR * tbuf1;   
	// ��������� �� ����� ������ ���������
	TCHAR * tbuf2; 
	// ��������� �� ����� ������ ������� ����������
	TCHAR * tbuf_index1;  
	// ��������� �� ����� ������ ������� ���������
	TCHAR * tbuf_index2;  
	// ������� �������� 
	CScientificStatic m_lblDescription;
	// ���������� ������� ������ "��������"
	afx_msg void OnBnClickedOk();
	// �������� ����� ��� �������� �������� m_lblDescription
	CFont * m_fIndexes;    
	// ����� ��� �������������� ��������
	CFont * m_fSymbol;
	// ������� ��� ����� ������� ����������
	CEdit m_index1;    
	// ������� ��� ����� ������� ���������
	CEdit m_index2;  
	// ���������� ������ ������ ����������
	CComboBox m_combo1;
	// ���������� ������ ������ ���������
	CComboBox m_combo2;
};
