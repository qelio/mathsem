// TupleDlg.cpp: ���� ����������
//

#include "stdafx.h"
#include "Semantics.h"
#include "TupleDlg.h"
#include "afxdialogex.h"
//#include "common_functions.h"
//#include "Formula.h"
#include "Operation.h"


//TRANSLATED

// ���������� ���� TupleDlg

IMPLEMENT_DYNAMIC(CTupleDlg, CDialog)

CTupleDlg::CTupleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTupleDlg::IDD, pParent)
{

}

CTupleDlg::~CTupleDlg()
{
}

void CTupleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, combo1);
	DDX_Control(pDX, IDC_COMBO2, combo2);
	DDX_Control(pDX, IDC_COMBO3, combo3);
	DDX_Control(pDX, IDC_LOWINDEX1, m_lowindex1);
	DDX_Control(pDX, IDC_LOWINDEX2, m_lowindex2);
	DDX_Control(pDX, IDC_LOWINDEX3, m_lowindex3);
}

BOOL CTupleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CTupleDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CTupleDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ����������� ��������� TupleDlg


void CTupleDlg::OnBnClickedOk()
{
	Tuple * tuple_temp = nullptr;
	TCHAR * tbuf1 = nullptr;
	TCHAR * tbuf2 = nullptr;
	TCHAR * tbuf3 = nullptr;
	TCHAR * tbuf_index1 = nullptr;
	TCHAR * tbuf_index2 = nullptr;
	TCHAR * tbuf_index3 = nullptr;
	bool success = false;
	int nIndex = combo1.GetCurSel();    // ������� ������ ���������� �������� ��� ����������� ����������
	int nCount = combo1.GetCount();    // ������� ���������� ��������� ������� ����������� ����������
	if ((nIndex != CB_ERR) && (nCount > 1))    // ���� ������
	{
		int len = combo1.GetLBTextLen(nIndex);    // ����� ������ ��������
		tbuf1 = new TCHAR[len + 2];    // ������ ����� ��� �������� ������ ����������
		combo1.GetLBText(nIndex, (LPTSTR)tbuf1);    // �������� ����� ���������� � ��������� �����
		len = m_lowindex1.GetWindowTextLengthW();    // ����� ������ ������� ����������
		tbuf_index1 = new TCHAR[len + 2];    // ������ ����� ��� �������� ������ ������� ����������
		m_lowindex1.GetWindowTextT(tbuf_index1, len + 1);    // �������� ����� ������� ���������� � ��������� �����
		success = true;
	}
	else
	{	
		if (CURRENT_LANG_OF == "rus")
			MessageBox(_T("�� ������� ������ ���������� ��� ���������� �������"), _T("��������������"), MB_OK );
		else
			MessageBox(_T("The first variable for building the tuple is not selected"), _T("Warning"), MB_OK );
		combo1.SetFocus();
	}
	if(success)
	{
		nIndex = combo2.GetCurSel();    // ������� ������ ���������� �������� ��� ����������� ���������
		nCount = combo2.GetCount();    // ������� ���������� ��������� � ������ ����������� ���������
		if ((nIndex != CB_ERR) && (nCount > 1))   // ���� ������
		{
			int len = combo2.GetLBTextLen(nIndex);    // ����� ������ ��������
			tbuf2 = new TCHAR[len + 2];    // ������ ����� ��� �������� ������ ���������
			combo2.GetLBText(nIndex, (LPTSTR)tbuf2);    // �������� ����� ��������� � ��������� �����
			len = m_lowindex2.GetWindowTextLengthW();    // ����� ������ ������� ����������
			tbuf_index2 = new TCHAR[len + 2];    // ������ ����� ��� �������� ������ ������� ����������
			m_lowindex2.GetWindowTextT(tbuf_index2, len + 1);    // �������� ����� ������� ���������� � ��������� �����
		}
	}
	nIndex = combo3.GetCurSel();    // ������� ������ ���������� �������� ��� ����������� ���������
	nCount = combo3.GetCount();    // ������� ���������� ��������� � ������ ����������� ���������
	if ((nIndex != CB_ERR) && (nCount > 1))   // ���� ������
	{
		if(success)
		{
			int len = combo3.GetLBTextLen(nIndex);    // ����� ������ ��������
			tbuf3 = new TCHAR[len + 2];    // ������ ����� ��� �������� ������ ���������
			combo3.GetLBText(nIndex, (LPTSTR)tbuf3);    // �������� ����� ��������� � ��������� �����
			len = m_lowindex3.GetWindowTextLengthW();    // ����� ������ ������� ����������
			tbuf_index3 = new TCHAR[len + 2];    // ������ ����� ��� �������� ������ ������� ����������
			m_lowindex3.GetWindowTextT(tbuf_index3, len + 1);    // �������� ����� ������� ���������� � ��������� �����
		}
	}
	else
	{
		if(success)
		{
			success = false;
			if (CURRENT_LANG_OF == "rus")
				MessageBox(_T("�� ������� ��������� ��� ���������� �������"), _T("��������������"), MB_OK );
			else	
				MessageBox(_T("The set for building the tuple is not selected"), _T("Warning"), MB_OK );
			combo3.SetFocus();
		}
	}
	// �� ���� �� ���������� ������� �� ������ ��������� � ����������, ������� ��������
	tstring tstr1, tstr2, tstr3;
	tstring tstr_index1, tstr_index2, tstr_index3;
	if(success)
	{
		tstr1 = tstring(tbuf1);
		tstr3 = tstring(tbuf3);
		tstr_index1 = tstring(tbuf_index1);
		tstr_index3 = tstring(tbuf_index3);
		if((tstr1.compare(tstr3) == 0) && (tstr_index1.compare(tstr_index3) == 0))
		{
			if (CURRENT_LANG_OF == "rus")
				MessageBox(_T("������ ���������� ������� ��������� � ����������"), _T("��������������"), MB_OK );
			else	
				MessageBox(_T("The first variable of the tuple coincides with the set"), _T("Warning"), MB_OK );
			success = false;
		}
	}
	if(success && (tbuf2 != nullptr) &&  (tbuf_index2 != nullptr))
	{
		tstr2 = tstring(tbuf2);
		tstr_index2 = tstring(tbuf_index2);
		if((tstr2.compare(tstr3) == 0) && (tstr_index2.compare(tstr_index3) == 0))
		{
			if (CURRENT_LANG_OF == "rus")
				MessageBox(_T("������ ���������� ������� ��������� � ����������"), _T("��������������"), MB_OK );
			else
				MessageBox(_T("The second variable of the tuple coincides with the set"), _T("Warning"), MB_OK );
			success = false;
		}
	}
	if(success)
	{
		EntityVariable ev1(tstr1, tstr_index1, VARIABLE);
		EntityVariable set(tstr3, tstr_index3, SET);
		if((tbuf2 != nullptr) &&  (tbuf_index2 != nullptr))
		{
			EntityVariable ev2(tstr2, tstr_index2, VARIABLE);
			tuple_temp = new Tuple(ev1, ev2, set);
		}
		else
		{
			tuple_temp = new Tuple(ev1, set);
		}
		if(tuple_temp != nullptr)
		{
			tuple_temp->SetLabel(all_entities); // ����� ����������� �������
//			tuple_temp->putTextOfFormula(all_entities); // ����� ����� �������
			bool found = false;
			for(int i = 0; i < all_entities->size(); i++)
			{
				if(all_entities->at(i)->isFormula())
				{
					Formula * f = (Formula *)all_entities->at(i);
					if(*f == *tuple_temp)
					{
						found = true;
						break;
					}
				}
			}
			if(!found)
				all_entities->push_back(tuple_temp);    // ��������� ������� ������� � ��������� ��������� ����� entities
			else
			{
				delete tuple_temp;
				if (CURRENT_LANG_OF == "rus")
					MessageBox(_T("����� �� ������ ��� ������ � �����."), _T("��������������"), MB_OK );
				else
					MessageBox(_T("The same tuple has already been created in the schema."), _T("Warning"), MB_OK );
			}
		}
	}
	if(tbuf1 != nullptr)
		delete tbuf1;
	if(tbuf2 != nullptr)
		delete tbuf2;
	if(tbuf3 != nullptr)
		delete tbuf3;
	if(tbuf_index1 != nullptr)
		delete tbuf_index1;
	if(tbuf_index2 != nullptr)
		delete tbuf_index2;
	if(tbuf_index3 != nullptr)
		delete tbuf_index3;
	// TODO: �������� ���� ��� ����������� �����������
	if(success)
		CDialog::OnOK();
}
