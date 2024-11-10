//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
// AksiomaDialog.cpp: ���� ����������
//

#include "stdafx.h"
#include "Semantics.h"
#include "AtomFormulaDialog.h"
#include "afxdialogex.h"
#include "common_functions.h"


//TRANSLATED

// ���������� ���� CAtomFormulaDialog

IMPLEMENT_DYNAMIC(CAtomFormulaDialog, CDialog)

//
// �����������
//
CAtomFormulaDialog::CAtomFormulaDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAtomFormulaDialog::IDD, pParent)
{
	tbuf1 = NULL;
	tbuf2 = NULL;
	tbuf_index1 = NULL;
	tbuf_index2 = NULL;
	m_fSymbol = NULL;
	m_fIndexes = NULL;
}

//
// ����������
//
CAtomFormulaDialog::~CAtomFormulaDialog()
{
	// ��������� ��������� �������
	if(tbuf1)
		delete tbuf1;
	if(tbuf2)
		delete tbuf2;
	if(tbuf_index1)
		delete tbuf_index1;
	if(tbuf_index2)
		delete tbuf_index2;
	if(m_fSymbol)
		delete m_fSymbol;
	if(m_fIndexes)
		delete m_fIndexes;
}

void CAtomFormulaDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DESCRIPTION, m_lblDescription);
	DDX_Control(pDX, IDC_EDIT3, m_index1);
	DDX_Control(pDX, IDC_EDIT4, m_index2);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
}


BEGIN_MESSAGE_MAP(CAtomFormulaDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CAtomFormulaDialog::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL CAtomFormulaDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_index1.SetWindowText(_T("0"));  // ����� �� ��������� ������ ��� ����������
	m_index2.SetWindowText(_T("0"));  // ����� �� ��������� ������ ��� ���������
	LPCTSTR lpszSelect1 = _T("x");    // ����� �� ��������� ����������� ����������
	LPCTSTR lpszSelect2 = _T("A");    // ����� �� ��������� ����������� ���������

	// ����� �������� �����, ������� ������������ �������������
	int nSel = m_combo1.SelectString(0, lpszSelect1);
	int nSel1 = m_combo2.SelectString(0, lpszSelect2);
	
	// ������ ����� �� ���������
	m_fIndexes = new CFont;
	m_fIndexes->CreatePointFont(70, L"Arial Unicode MS");
//	m_fIndexes->CreatePointFont(70, L"Microsoft San Serif");
	m_lblDescription.m_fIndexes = m_fIndexes;
	// ������ ����� ��� �������������� ��������
	m_fSymbol = new CFont;
//	m_fSymbol->CreatePointFont(140, L"Symbol");
	m_fSymbol->CreatePointFont(140, L"Arial Unicode MS");
	m_lblDescription.m_fSymbol = m_fSymbol;
	CString cs;
	m_lblDescription.GetWindowTextT(cs);
	tstring tstr = cs;
	m_lblDescription.dsi->PrepareSubItemData(tstr);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}


// ����������� ��������� CAtomFormulaDialog

//
// ���������� ������� ������ "��������"
//
void CAtomFormulaDialog::OnBnClickedOk()
{
	// ������ ��������� ����� ���� ������ ������
	if(tbuf1)
		delete tbuf1;
	if(tbuf2)
		delete tbuf2;
	if(tbuf_index1)
		delete tbuf_index1;
	if(tbuf_index2)
		delete tbuf_index2;
	tbuf1 = NULL;
	tbuf2 = NULL;
	tbuf_index1 = NULL;
	tbuf_index2 = NULL;

	int nIndex = m_combo1.GetCurSel();    // ������� ������ ���������� �������� ��� ����������� ����������
	int nCount = m_combo1.GetCount();    // ������� ���������� ��������� ������� ����������� ����������
	if ((nIndex != CB_ERR) && (nCount > 1))    // ���� ������
	{
		int len = m_combo1.GetLBTextLen(nIndex);    // ����� ������ ��������
		tbuf1 = new TCHAR[len + 2];    // ������ ����� ��� �������� ������ ����������
		m_combo1.GetLBText(nIndex, (LPTSTR)tbuf1);    // �������� ����� ���������� � ��������� �����
		nIndex = m_combo2.GetCurSel();    // ������� ������ ���������� �������� ��� ����������� ���������
		nCount = m_combo2.GetCount();    // ������� ���������� ��������� � ������ ����������� ���������
		if ((nIndex != CB_ERR) && (nCount > 1))   // ���� ������
		{
			int len = m_combo1.GetLBTextLen(nIndex);    // ����� ������ ��������
			tbuf2 = new TCHAR[len + 2];    // ������ ����� ��� �������� ������ ���������
			m_combo2.GetLBText(nIndex, (LPTSTR)tbuf2);    // �������� ����� ��������� � ��������� �����
			len = m_index1.GetWindowTextLengthW();    // ����� ������ ������� ����������
			tbuf_index1 = new TCHAR[len + 2];    // ������ ����� ��� �������� ������ ������� ����������
			m_index1.GetWindowTextT(tbuf_index1, len + 1);    // �������� ����� ������� ���������� � ��������� �����
			tstring ind1 = tbuf_index1;
			trimWhitespaces(&ind1);
			if(ind1.length() > 0)
			{
				if(find_if_not(ind1.begin(), ind1.end(), istdigit) == ind1.end())
				{
					len = m_index2.GetWindowTextLengthW();    // ����� ������ ������� ���������
					tbuf_index2 = new TCHAR[len + 2];    // ������ ����� ��� �������� ������ ������� ���������
					m_index2.GetWindowTextT(tbuf_index2, len + 1);    // �������� ����� ������� ��������� � ��������� �����
					tstring ind2 = tbuf_index2;
					trimWhitespaces(&ind2);
					if(ind2.length() > 0)
					{
						if(find_if_not(ind2.begin(), ind2.end(), istdigit) == ind2.end())
						{
							// TODO: �������� ���� ��� ����������� �����������
							CDialog::OnOK();
						}
						else

						{

							if (CURRENT_LANG_OF == "rus") 
								AfxMessageBox(_T("� ������� ��� ������ ���������� ������� �� �����"));
							else 
								AfxMessageBox(_T("The index for the second variable does not specify a number"));
							m_index2.SetFocus();
						}
					}
					else
					{
						if (CURRENT_LANG_OF == "rus")
							AfxMessageBox(_T("������ ��� ������ ���������� �� ������"));
						else
							AfxMessageBox(_T("The index for the second variable has not been entered"));
						m_index1.SetFocus();
					}
				}
				else
				{
					if (CURRENT_LANG_OF == "rus")
						AfxMessageBox(_T("� ������� ��� ������ ���������� ������� �� �����"));
					else
						AfxMessageBox(_T("The index for the first variable does not specify a number"));
					m_index1.SetFocus();
				}
			}
			else
			{
				if (CURRENT_LANG_OF == "rus")
					AfxMessageBox(_T("������ ��� ������ ���������� �� ������"));
				else
					AfxMessageBox(_T("The index for the first variable is not entered"));
				m_index1.SetFocus();
			}
		}
		else
		{
			if (CURRENT_LANG_OF == "rus")
				AfxMessageBox(_T("�� ������� ����������� ��� ������ ����������"));
			else
				AfxMessageBox(_T("The designation for the second variable is not selected"));
			m_combo2.SetFocus();
		}
	}
	else
	{
		if (CURRENT_LANG_OF == "rus")
			AfxMessageBox(_T("�� ������� ����������� ��� ������ ����������"));
		else
			AfxMessageBox(_T("The designation for the first variable is not selected"));
		m_combo1.SetFocus();
	}
}
