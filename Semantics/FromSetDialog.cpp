// FromSetDialog.cpp: ���� ����������
//

#include "stdafx.h"
#include "Semantics.h"
#include "FromSetDialog.h"
#include "afxdialogex.h"


//TRANSLATED



// ���������� ���� FromSetDialog

IMPLEMENT_DYNAMIC(FromSetDialog, CDialogEx)

FromSetDialog::FromSetDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(FromSetDialog::IDD, pParent)
{
	sets = new vector <FormulaSet *>;
	allEntities = nullptr;
}

FromSetDialog::~FromSetDialog()
{
	if (sets != nullptr)
	{
		delete sets;
	}
}

void FromSetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SETLIST1, m_ListBoxSource);
	DDX_Control(pDX, IDOK, m_ButtonOK);
}


BEGIN_MESSAGE_MAP(FromSetDialog, CDialogEx)
	ON_LBN_SELCHANGE(IDC_SETLIST1, &FromSetDialog::OnLbnSelchangeSetlist1)
	ON_BN_CLICKED(IDOK, &FromSetDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// ����������� ��������� FromSetDialog


void FromSetDialog::OnLbnSelchangeSetlist1()
{
	int selected = m_ListBoxSource.GetCurSel();     // ������� ����� ���������� ������� (���������� � �������� ��������)
	if( selected >= 0 )     //���� �������� 
	{
		m_ButtonOK.EnableWindow(true);    // ����� ��������� ������ "OK"
	}
	else
	{
		m_ButtonOK.EnableWindow(false);    // ����� ��������� ������ "OK"
	}
	// TODO: �������� ���� ��� ����������� �����������
}


BOOL FromSetDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString str;
	int count = 0;
	for (size_t i = 0; i < allEntities->size(); i++)
	{
		bool toProccess = true;
		EntityBase * base = allEntities->at(i);
		if ( base->getType() != FORMULA_SET )
			continue;
		FormulaSet * icurr = (FormulaSet *)base;
		sets->push_back(icurr);
		// ��������� � �������� ������ � ���������� �������
		str.Format(_T("%d"), count);
		m_ListBoxSource.AddString(str);
		m_ListBoxSource.SetItemHeight(count, 30);
		SemanticString * dsi = new SemanticString;
		m_ListBoxSource.DCU.push_back(dsi);
		dsi->PrepareSubItemData(icurr->getText());
//		dsi->formula = base;
		m_ListBoxSource.SetItemData(count, (DWORD_PTR)dsi);
		if(count == 0)
		{
			m_ButtonOK.EnableWindow(true);
			m_ListBoxSource.EnableWindow(true);
		}

		count++;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}

void FromSetDialog::OnBnClickedOk()
{
/*
		SemanticString * dsi1 = (SemanticString *) m_list.DCU.at(selected1);    // �������� ��������� �� SemanticString, ��������� � ��������� ���������
		Formula * formula = dsi1->formula;    // ���� ��������� �� ������ Formula ��� �������� ������� SemnticString
		if ( formula != nullptr)    // �������� �� ��, ��� ��������� �� ������� (���������� ��������)
		{
			// Get the indexes of all the selected items.
			int nCount = m_listVariables.GetSelCount();    // ���������, ������� ��������� ���������� �������
			if(nCount > 0)    // ���� ������� ���� �� ����
			{
				vector <EntityVariable *> * variables = new vector <EntityVariable *>;


				CArray<int,int> aryListBoxSel;    // ��������� ��� ��������� ��������� ������ ��������� ����������
				aryListBoxSel.SetSize(nCount);    // ������������� ������ ����������, ������ ����� ��������� ��������� ����������
				m_listVariables.GetSelItems(nCount, aryListBoxSel.GetData());     // ��������� ���������
				int pt;
				// ������� �� ��������� ��������� ����������
				for (int i = 0; i <= aryListBoxSel.GetUpperBound(); i++)
				{
					pt = aryListBoxSel.GetAt(i);    // ������� ����� ���������� ��������, ���������������� ��������� ��������� ��������� ����������
					vector <EntityVariable *> * fv = formula->getFreeVariables(); 
					variables->push_back(fv->at(pt)); // ��������� � ������ ����������, �� ������� ������ ��������� ����������
				}
				// ��������, ��������� �� ������ ����� �������� ����������, �� ������ ��� �� ������� � ��� �� ������� ����������
				bool isExist = false;
				for (size_t i = 0; i < entities->size(); i++) // ������� ���� ��������� ���������
				{
					bool toProccess = false;
					EntityBase * base = entities->at(i);     // ��������� �� ��������� ��������
					if ( base->isFormula() ) // ���� ��������� �������� �������, �� ��������� � ��������� ��������
						continue;
					FormulaSet * baseFS = (FormulaSet *)base;    // ��������� �� ��������� ����������
					if (formula == baseFS->getParentFormula()) // ���� ������������ ������� ��� ��������� �������� ��������� � ��������� ��������, 
					// �� ������� �������� ��������� ����������
					{
						// ��������, ��� ��������� ������ ��������� ���������� ��� ���� ���� ������ ( ��������, ���������� ��������)
						vector <EntityVariable *> * fv_base = base->getFreeVariables();
						vector <EntityVariable *> * fv_formula = formula->getFreeVariables();
						if ( fv_base->size() == fv_formula->size() ) // ������ ���� ������� ������� ��������� ���������� ���������
						{
							bool isFoundFVAll = false;
							for (size_t i1 = 0; i1 < fv_base->size(); i1++)    // ������� �� ���� ��������� ���������� ��������� ��������
							{
								EntityVariable * pev = fv_base->at(i1);    
								bool isFoundFV = false;
								for (size_t i2 = 0; i2 < fv_formula->size(); i2++)    // ��������� ���� �� ��������� ���������� �������
								{
									if ( pev->compare(*fv_formula->at(i2)))     // ���� ��������
									{
										isFoundFV = true;
										break;
									}
								}
								if ( isFoundFV )
								{
									isFoundFVAll = true;    // �� ���� ���������, ��������� ���� ������ ��� ����� ����������� ����������, �� � ��� ��������,
									// ��������, �������� ����������
									break;
								}
							}
							if ( isFoundFVAll )
								toProccess = true;
						}
						// ��������, ��� ��������� ������ ������� ���������� ������� �������� � ��������� ��������, �� ������� �������� ��������� ����������
						vector <EntityVariable *> * bv_base = baseFS->getBaseVariables();
						if ( toProccess && ( bv_base->size() == variables->size() ) ) // ������ ���� ������� ������� ��������� ���������� ���������
						{
							toProccess = false;
							bool isFoundFVAll = false;
							for (size_t i1 = 0; i1 < bv_base->size(); i1++)
							{
								EntityVariable * pev = bv_base->at(i1);
								bool isFoundFV = false;
								for (size_t i2 = 0; i2 < variables->size(); i2++)
								{
									if ( pev->compare(*variables->at(i2)))
									{
										isFoundFV = true;
										break;
									}
								}
								if ( isFoundFV )
								{
									isFoundFVAll = true;
									break;
								}
							}
							if ( isFoundFVAll )
								toProccess = true;
						}
						else
							toProccess = false;
					}
					if(toProccess)
					{
						isExist = toProccess;
						break;
					}
				}
				if ( !isExist )     // ���� �� ������� ��������� ��������� ����������
				{
					FormulaSet * pfs = new FormulaSet(formula, variables);    // ������ ��������� ����������
					pfs->SetLabel(entities);    // ��������� �����������
					entities->push_back(pfs);   // �������� ��������� ��������� ���������� � �����
				}
				else
					AfxMessageBox(_T("�������� ������ ����� ����������, �� ����� ��������� ���������� ��� ���������"));
				// ����� �����������
				delete variables;     // ���������� ������
				if ( !isExist )       // ���� ���� ������� ��������� ����������
					CDialogEx::OnOK();    // �������� ���������� ����
			}
			else
				AfxMessageBox(_T("�� ������� �� ����� ����������"));

		}
	}
	else
		AfxMessageBox(_T("�� ������� ������� ��� ���������� ��������� ����������"));
*/
}
