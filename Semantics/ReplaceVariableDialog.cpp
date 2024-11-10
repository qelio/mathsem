// ReplaceVariableDialog.cpp: ���� ����������
//

#include "stdafx.h"
#include "Semantics.h"
#include "ReplaceVariableDialog.h"
#include "SummaryDialog.h"
#include "afxdialogex.h"




//



// ���������� ���� ReplaceVariableDialog

IMPLEMENT_DYNAMIC(ReplaceVariableDialog, CDialogEx)

ReplaceVariableDialog::ReplaceVariableDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(ReplaceVariableDialog::IDD, pParent)
{
	m_fIndexes = nullptr;
	m_fSymbol = nullptr;
}

ReplaceVariableDialog::~ReplaceVariableDialog()
{
	pev_new.clear();
	m_fIndexes = nullptr;
	m_fSymbol = nullptr;
}

void ReplaceVariableDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITINDEX, m_editIndex);
	DDX_Control(pDX, IDC_SETLIST1, m_list);
	DDX_Control(pDX, IDC_SETLIST2, m_listFreeVariables);
	DDX_Control(pDX, IDC_SETLIST3, m_listVariables);
	DDX_Control(pDX, IDOK, m_buttonOK);
	DDX_Control(pDX, IDC_COMBONAME, m_comboName);
}


BEGIN_MESSAGE_MAP(ReplaceVariableDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &ReplaceVariableDialog::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_SETLIST1, &ReplaceVariableDialog::OnSelchangeSetlist1)
	ON_LBN_SELCHANGE(IDC_SETLIST2, &ReplaceVariableDialog::OnSelchangeSetlist2)
	ON_BN_CLICKED(IDC_RADIOINPUTTEXT, &ReplaceVariableDialog::OnBnClickedRadioinputtext)
	ON_BN_CLICKED(IDC_RADIOSELECTVARIABLE, &ReplaceVariableDialog::OnBnClickedRadioselectvariable)
END_MESSAGE_MAP()

//
// ����� ���������� ��������� ���������� � �������� m_listFreeVariables ��� ���������� �������� � ������ ������
//
void ReplaceVariableDialog::ShowFreeVariables()
{
	int selected = m_list.GetCurSel();     // ������� ����� ���������� ������� (���������� � �������� ��������)
	if( selected >= 0 )     //���� �������� 
	{
		SemanticString * dsi = m_list.DCU.at(selected);    // ������� ��������� �� SemanticString, ��������� � ��������� ��������
//		Formula * f = dsi->formula;     // �� SemanticString ������� ��������� �� ���� �������
//		vector <EntityVariable *> * freeVariables = f->getFreeVariables();   // ��������� �� ��������� ���������� �������
		EntityBase * peb = dsi->formula;;     // �� SemanticString ������� ��������� �� ���� �������
//		EntityBase * peb = entities->at(selected);     // �� SemanticString ������� ��������� �� ���� �������
		vector <EntityVariable *> * freeVariables = peb->getFreeVariables();   // ��������� �� ��������� ���������� �������
		vector <EntityVariable *> * linkedVariables = peb->getLinkedVariables();   // ��������� �� ��������� ���������� �������
		vector <EntityVariable *> allVariables(*freeVariables);
		allVariables.insert(allVariables.end(), linkedVariables->begin(), linkedVariables->end());
		for (size_t i = 0; i < allVariables.size(); i++)     // ������� �� ����, ��������� � ���������, ����������
		{
			CString str;
			// ��������� � �������� ������ � ���������� �������
			str.Format(_T("%d"), i);
			m_listFreeVariables.InsertString(i,str);
			m_listFreeVariables.SetItemHeight(i, 30);
			// ������� ������ SemanticString ��� ��������� ��������� ���������� �� ������ �������-������
			SemanticString * dsi1 = new SemanticString;
			m_listFreeVariables.DCU.push_back(dsi1);
			dsi1->PrepareSubItemData(*(allVariables.at(i)->GetText()));
			m_listFreeVariables.SetItemData(i, (DWORD_PTR)dsi1);     // �������� 
			if(i == 0)     // ���� ������ (�� ���� ���� �� ���� ��������� �������)
			{
				m_buttonOK.EnableWindow(true);    // ����� ��������� ������ "OK"
				m_listFreeVariables.EnableWindow(true);    // ����� ��������� ����
			}
		}
		m_listFreeVariables.SetCurSel(0);    // ������������ ��������� ������ �������
		int selected = m_listFreeVariables.GetCurSel();     // ������� ����� ���������� ������� (���������� � �������� ��������)
		if( selected >= 0 )     //���� �������� 
		{
			GetDlgItem(IDC_RADIOINPUTTEXT)->EnableWindow(true);
			GetDlgItem(IDC_RADIOSELECTVARIABLE)->EnableWindow(true);
//			EntityVariable * pselVariable = freeVariables->at(0);
			EntityVariable * pselVariable = allVariables.at(0);
			tstring var = *pselVariable->GetText();
			TCHAR symbol = var.at(0);
			ResetComboNames(symbol);
			m_comboName.EnableWindow(true);
			m_editIndex.EnableWindow(true);
		}
	}
}

//
// ����� ������� ��������� ���������� �� �������� m_listFreeVariables
//
void ReplaceVariableDialog::HideFreeVariables()
{
	int item;
	while( (m_listFreeVariables.GetCount( ) ) > 0 )   // ���� � ������ ��������� ���������� ������� ���� �� ���� �������
	{
		item = m_listFreeVariables.GetTopIndex( );    // �������� ������ �������� ��������
		SemanticString * dsi = (SemanticString *) m_listFreeVariables.GetItemData(item);    // �������� ������
		CString cs;
		m_listFreeVariables.GetText(item, cs);	   // �������� ������, ��������������� �������� ��������, �������, ���� �������� ������
		m_listFreeVariables.DeleteString(item);    //  ������� �� ����-������ ������ ��� �������� � �������� item
		DELETEITEMSTRUCT dis;                  // ��������� ��� �������� ������ �������� 
		dis.itemID = item;                     
		m_listFreeVariables.DeleteItem(&dis);      // ������� ���� ������� ���������
	}
	m_listFreeVariables.DCU.clear();               // ������� ��������� ������������ SemanticString
	m_buttonOK.EnableWindow(false);            // ����� ���� ����������
	m_listFreeVariables.EnableWindow(false); 
	m_listFreeVariables.EnableWindow(false);
	GetDlgItem(IDC_RADIOINPUTTEXT)->EnableWindow(false);
	GetDlgItem(IDC_RADIOSELECTVARIABLE)->EnableWindow(false);
	m_comboName.EnableWindow(false);
	m_editIndex.EnableWindow(false);
}


//
// ������������� �������� � �������� ������� � ��� ��������� ��� �������������
//
BOOL ReplaceVariableDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_dataRadio = 1;
	switch(m_dataRadio)
	{
	case 1:
		CheckDlgButton(IDC_RADIOINPUTTEXT,1);
		break;
	case 2:
		CheckDlgButton(IDC_RADIOSELECTVARIABLE,1);
		break;
	}
	CString str;
	int count = 0;
	tstring res;
	tstring res_formula;
	for (size_t i = 0; i < entities->size(); i++)    // ������� �� ���� ��������� �����
	{
		bool toProccess = true;     // ���� 
		EntityBase * base = entities->at(i);    // ��������� �� ��������� ��������
//		if(base->getType() == REPLACE_VARIABLE)
//			continue;
//		if ( !base->isFormula() )       // ���� �������� �� �������
//			continue;     // ��������� � ������
		vector <EntityVariable *> * fv = base->getFreeVariables();    // ��������� �� ��������� ��������� ���������� ��������
		vector <EntityVariable *> * plv = base->getLinkedVariables();    // ��������� �� ��������� ��������� ���������� ��������
		if ( (fv->size() + plv->size()) == 0)     // ���� ��� ��������� ����������
			continue;     // ��������� � ��������� ��������
		Formula * icurr = (Formula *)base;    // ��������� �� ������ ������ Formula
/*
���� ���� ������ �������� �� ��������� � ������ ������-���������� ��� ����������� �������� ����������
�� ��� ���� �� ����, ��� � ������ ����������� ��������� � �� ������ ��������
		if ( icurr->formulasetCandidate(entities) == nullptr )
			continue;
*/
		// ��������� � �������� ������ � ���������� �������
		str.Format(_T("%d"), count);
		m_list.AddString(str);
		m_list.SetItemHeight(count, 30);
		SemanticString * dsi = new SemanticString;
		m_list.DCU.push_back(dsi);
		dsi->PrepareSubItemData(icurr->getText());
		dsi->formula = base;
		m_list.SetItemData(count, (DWORD_PTR)dsi);   // ������������� ���������� SemanticString � �������� 
	}
	// TODO:  �������� �������������� �������������
/*
	m_fIndexes = new CFont;
	m_fIndexes->CreatePointFont(70, L"Microsoft San Serif");
	m_StaticDescription.m_fIndexes = m_fIndexes;
	m_fSymbol = new CFont;
	m_fSymbol->CreatePointFont(140, L"Symbol");
	m_StaticDescription.m_fSymbol = m_fSymbol;
*/
	m_listFreeVariables.EnableWindow(false);
	GetDlgItem(IDC_RADIOINPUTTEXT)->EnableWindow(false);
	GetDlgItem(IDC_RADIOSELECTVARIABLE)->EnableWindow(false);
	m_comboName.EnableWindow(false);
	m_editIndex.EnableWindow(false);
//	m_listVariables.EnableWindow(false);
//	m_CheckSubSet.SetCheck(0);
//	m_ComboSubSet.EnableWindow(false);
//	m_IndexSubSet.EnableWindow(false);
	// TODO:  �������� �������������� �������������

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����������: �������� ������� OCX ������ ���������� �������� FALSE
}


void addReplacingFormula(vector <EntityBase *> * pentities, EntityBase * peb, EntityVariable * pev_old, EntityVariable * pev_new)
{
	EntityBase * peb_new = nullptr;
	if(peb->isFormula())
	{
		Formula * pf_new = new Formula;
		peb_new = (EntityBase *)pf_new;
	}
	else
	{
		FormulaSet * pfs_new = new FormulaSet();
		peb_new = (EntityBase *)pfs_new;
	}
	if(peb_new != nullptr)
	{
		peb_new->SetReplacing( peb, pev_old, pev_new);
		if(peb_new->isFormula())
			((Formula *)peb_new)->SetLabel(pentities);
		else
			((FormulaSet *)peb_new)->SetLabel(pentities);
		pentities->push_back(peb_new);
	}
}



// ����������� ��������� ReplaceVariableDialog


void ReplaceVariableDialog::OnBnClickedOk()
{
	bool result = false;
	TCHAR * tbuf = nullptr;
	TCHAR * tbuf1 = nullptr;
	EntityVariable * pev1 = nullptr;
	int selected = m_list.GetCurSel();     // ������� ����� ���������� ������� (���������� � �������� ��������)
	if( selected >= 0 )     //���� �������� 
	{
		SemanticString * dsi = m_list.DCU.at(selected);    // ������� ��������� �� SemanticString, ��������� � ��������� ��������
		EntityBase * peb = dsi->formula;		
//		EntityBase * peb = entities->at(selected);
//		Formula * f = dsi->formula;     // �� SemanticString ������� ��������� �� ���� �������
		vector <EntityVariable *> * freeVariables = peb->getFreeVariables();   // ��������� �� ��������� ���������� �������
		//�������� ���� ��� ����, � ��� ����� � �������� ����������
		vector <EntityVariable *> * linkedVariables = peb->getLinkedVariables();   // ��������� �� ��������� ���������� �������
		vector <EntityVariable *> allVariables(*freeVariables);
		allVariables.insert(allVariables.end(), linkedVariables->begin(), linkedVariables->end());
		// ����� ���� ���� �������������
		int nIndex1 = m_listFreeVariables.GetCurSel();    // ������� ������ ��������� ��������� ����������
		int nCount1 = m_listFreeVariables.GetCount();    // ������� ���������� ��������� ����������
		if ((nIndex1 != CB_ERR) && (nCount1 > 0))    // ���� ��������� ���������� �������
		{
//			EntityVariable * pselVariable = freeVariables->at(nIndex1);
			EntityVariable * pselVariable = allVariables.at(nIndex1);
			{
				if(m_dataRadio == 1) // ����  ������� ������ ������ ����� ����������
				{
					int nIndex = m_comboName.GetCurSel();    // ������� ������ ���������� �������� ��� ����������� ����������
					int nCount = m_comboName.GetCount();    // ������� ���������� ��������� ������� ����������� ����������
					if ((nIndex != CB_ERR) && (nCount > 0))    // ���� ������
					{
						int len = m_comboName.GetLBTextLen(nIndex);    // ����� ������ ��������
						tbuf = new TCHAR[len + 2];    // ������ ����� ��� �������� ������ ����������
						m_comboName.GetLBText(nIndex, (LPTSTR)tbuf);    // �������� ����� ���������� � ��������� �����
						len = m_editIndex.GetWindowTextLengthW();    // ����� ������ ��������
						if(len > 0)
						{
							tbuf1 = new TCHAR[len + 2];    // ������ ����� ��� �������� ������ ����������
							m_editIndex.GetWindowTextT(tbuf1, len + 1);    // �������� ����� ������� ���������� � ��������� �����
							tstring ind1 = tbuf1;
							trimWhitespaces(&ind1);
							if(ind1.length() > 0)
							{
								if(find_if_not(ind1.begin(), ind1.end(), istdigit) == ind1.end())
								{
									result = true;
								}
								else
								{
									if(CURRENT_LANG_OF=="rus")
										AfxMessageBox(_T("������ ��� ������ ���������� �� ����� ������������� �����"));
									else
										AfxMessageBox(_T("The index to replace the variable is not a positive integer"));
									m_editIndex.SetFocus();
								}
							}
							else
							{
								if (CURRENT_LANG_OF == "rus")
									AfxMessageBox(_T("�� ������ ������ ��� ������ ����������"));
								else 
									AfxMessageBox(_T("The index for replacing the variable is not specified"));
								m_editIndex.SetFocus();
							}
						}
						else
						{
							if (CURRENT_LANG_OF == "rus")
								AfxMessageBox(_T("�� ������ ������ ��� ������ ����������"));
							else
								AfxMessageBox(_T("The index for replacing the variable is not specified"));
							m_editIndex.SetFocus();
						}
					}
					else
					{
						if (CURRENT_LANG_OF == "rus")
							AfxMessageBox(_T("�� ������� ����������� ��� ������ ����������"));
						else 
							AfxMessageBox(_T("The designation for replacing the variable is not selected"));
						m_comboName.SetFocus();
					}
				}
				else // ���� ���������� ��� ������ ���������� �� ������
				{
					int nIndex = m_listVariables.GetCurSel();    // ������� ������ ���������� �������� ��� ����������� ����������
					int nCount = m_listVariables.GetCount();    // ������� ���������� ��������� ������� ����������� ����������
					if ((nIndex != CB_ERR) && (nCount > 0))    // ���� ������
					{
						pev1 = new EntityVariable(*pev_new.at(nIndex));
						result = true;
					}
					else
					{
						if (CURRENT_LANG_OF == "rus")
							AfxMessageBox(_T("�� ������� ���������� ��� ������"));
						else
							AfxMessageBox(_T("A replacement variable has not been selected"));
						m_listVariables.SetFocus();
					}
				}
			}
			if(result)
			{				
				EntityVariable * pev = new EntityVariable(*pselVariable);
				if( (tbuf != nullptr) && (tbuf1 != nullptr) ) // �������� ��������
				{
					tstring tstr = tbuf;
					tstring tstr_index = tbuf1;
					trimWhitespaces(&tstr_index);
					pev1 = new EntityVariable(tstr, tstr_index, VARIABLE);
					pev1->SetLevel(pselVariable->GetLevel());
				}
				// �������� �� ��, ����������� �� ��� ����� ���������������
				bool is_exist = false;
				for(size_t i = 0; i < entities->size(); i++)
				{
					EntityBase * peb_i = entities->at(i);
					if(peb_i->getType() == REPLACE_VARIABLE)
					{
						if( (peb == peb_i->getReplacedBase()) && pev->compare(*peb_i->getInitialVariable()) && pev1->compare(*peb_i->getNewVariable()) )
						{
							is_exist = true;
							break;
						}
					}
				}
				if(!is_exist) // ���� ����� �� ��������������� ��� �� ������� � �����
				{
					if(!pev1->compare(*pselVariable))
					{
						SetGroup sg = peb->isPartOfSetGroup(entities);
						EntityBase * peb_first = get<0>(sg);
						int count_objs = get<1>(sg);
						tstring caps = * pselVariable->GetText();
						caps[0] = toupper(caps[0]);
						if((peb_first == nullptr) || (*(pselVariable->GetText()) != caps)) // ���� ��������� ������ �� ������ � ������� ��������� ����������
						{
							addReplacingFormula(entities, peb, pev, pev1);
						}
						else
						{	
							// ���� ��������� �� ��, ����� ���������� ���������� � � ����������� �������� �� 2 �� 4 ��������
							// ���������� ���������� �� ����� ���� ������������ ��������� ����������, ��� ���������� ��� ������, ������ ���� ���������,
							// ��� ���������� ���������� �������� ������������, �������� � ������ ��������, ��������� � ������� �������� ��������� ����������
							if((peb->getType() == SUBSET) && (pselVariable->compare(*freeVariables->at(freeVariables->size() - 1))))
							{
								auto ppf = find(entities->begin(), entities->end(), peb);
								ppf--;
								peb_first = *ppf;
								count_objs = 2;
							}
							else if((peb->getType() == TUPLE) && (pselVariable->compare(*freeVariables->at(freeVariables->size() - 1))))
							{
								peb_first = peb;
								count_objs = 2;
							}
							auto ppf = find(entities->begin(), entities->end(), peb_first);
							EntityBase * p_cur = peb_first;
							for(int i = 0; i < count_objs; i++)
							{
								addReplacingFormula(entities, p_cur, pev, pev1);
								ppf = find(entities->begin(), entities->end(), p_cur);
								ppf++;
								p_cur = *ppf;
							}
						}
					
/*
�������������� ���� ��� ������� ���������������
				vector <EntityBase *> * temp_entities = new vector <EntityBase *>;
				ReverseDefinition(temp_entities, entities, 0, entities->size());
				for(int i = 0; i < entities->size(); i++)
				{
					EntityBase * base = entities->at(i);
					if ( base->isSet() )
					{
						FormulaSet * fs = (FormulaSet *)base;
						delete fs;
					}
					else
					{
						Formula * f = (Formula *)base;
						delete f;
					}
				}
				entities->clear();
				*entities = *temp_entities;
				delete temp_entities;
*/
					}
					else
					{
						result = false;
						if (CURRENT_LANG_OF == "rus")
							AfxMessageBox(_T("����������� ���������� � ���������� ��� ������ ���������"));
						else
							AfxMessageBox(_T("The designations of the replaced and the variable to replace are the same"));
						m_listFreeVariables.SetFocus();						
					}
				}
				else
				{
					result = false;
					if (CURRENT_LANG_OF == "rus")
						AfxMessageBox(_T("����� ��������������� ���������� ��� ����������"));
					else
						AfxMessageBox(_T("Such a reinvention of the variable already exists"));
					m_listFreeVariables.SetFocus();
				}
			}
		}
		else
		{
			if (CURRENT_LANG_OF == "rus")
				AfxMessageBox(_T("�� ������� ��������� ����������"));
			else
				AfxMessageBox(_T("A free variable is not selected"));
			m_listFreeVariables.SetFocus();
		}			
	}
	else
	{
		if (CURRENT_LANG_OF == "rus")
			AfxMessageBox(_T("�� ������� �������"));
		else
			AfxMessageBox(_T("The formula is not selected"));
		m_list.SetFocus();
	}
	if(tbuf != nullptr)
		delete tbuf;
	if(tbuf1 != nullptr)
		delete tbuf1;
//	if(pev1 != nullptr)
//		delete pev1;
	// TODO: �������� ���� ��� ����������� �����������
	if(result)
		CDialogEx::OnOK();
}


void ReplaceVariableDialog::OnSelchangeSetlist1()
{
	HideVariables();   // ������� ������ ����������, �������� ����� ��������
	HideFreeVariables();    // ������� ����������, ���� ����, �� ����-������ ��������� ����������
	ShowFreeVariables();    // ��������� ����-������ ��������� ���������� � ����������� �� ��������� �������
	ShowVariables();
	// TODO: �������� ���� ��� ����������� �����������
}


void ReplaceVariableDialog::OnSelchangeSetlist2()
{
	int selected1 = m_listFreeVariables.GetCurSel();     // ������� ����� ���������� ������� (���������� � �������� ��������)
	int nCount1 = m_listFreeVariables.GetCount();    // ������� ���������� ��������� ����������
	int selected = m_list.GetCurSel();     // ������� ����� ���������� ������� (���������� � �������� ��������)
	int nCount = m_list.GetCount();    // ������� ���������� ��������� ����������
	if( (selected >= 0) && (nCount >= 1) && (selected1 >= 0) && (nCount1 >= 1))     //���� �������� 
	{
		GetDlgItem(IDC_RADIOINPUTTEXT)->EnableWindow(true);
		GetDlgItem(IDC_RADIOSELECTVARIABLE)->EnableWindow(true);
		SemanticString * dsi = m_list.DCU.at(selected);    // ������� ��������� �� SemanticString, ��������� � ��������� ��������
		EntityBase * peb = dsi->formula;		
//		EntityBase * peb = entities->at(selected);
		vector <EntityVariable *> * freeVariables = peb->getFreeVariables();   // ��������� �� ��������� ���������� �������
		//�������� ���� ��� ����, � ��� ����� � �������� ����������
		vector <EntityVariable *> * linkedVariables = peb->getLinkedVariables();   // ��������� �� ��������� ���������� �������
		vector <EntityVariable *> allVariables(*freeVariables);
		allVariables.insert(allVariables.end(), linkedVariables->begin(), linkedVariables->end());
		EntityVariable * pselVariable = allVariables.at(selected1);
//		EntityVariable * pselVariable = freeVariables->at(selected1);
		// ����� ���� ���� �������������
		tstring var = *pselVariable->GetText();
		TCHAR symbol = var.at(0);
		ResetComboNames(symbol);
		m_comboName.EnableWindow(true);
		m_editIndex.EnableWindow(true);
		m_listVariables.EnableWindow(false);
		HideVariables();
		ShowVariables();

//		m_listVariables.EnableWindow(true);    // ����� ��������� ����
	}
/*
	else
	{
		GetDlgItem(IDC_RADIOINPUTTEXT)->EnableWindow(false);
		GetDlgItem(IDC_RADIOSELECTVARIABLE)->EnableWindow(false);
		m_editReplaceText.EnableWindow(false);
		m_listVariables.EnableWindow(false);
	}
*/
	// TODO: �������� ���� ��� ����������� �����������
}

// ������� ������ ����������� � ���������� �� ��������� ��� ���������, � ����������� �� ����, ��������� ��� ��������� ������, ������������ ���������� �������
void ReplaceVariableDialog::ResetComboNames(TCHAR symbol)
{
	TCHAR highValues[] = { TCHAR('A'), TCHAR('B'), TCHAR('C'), TCHAR('D'), TCHAR('E'), TCHAR('F'), TCHAR('G'), TCHAR('H'), TCHAR('I'), TCHAR('J'), TCHAR('K'), 
		TCHAR('L'), TCHAR('N'), TCHAR('O'), TCHAR('Q'), TCHAR('S'), TCHAR('T'), TCHAR('U'), TCHAR('V'), TCHAR('W'), TCHAR('X'), TCHAR('Y'), TCHAR('Z') };
	TCHAR lowValues[] = { TCHAR('a'), TCHAR('b'), TCHAR('c'), TCHAR('d'), TCHAR('e'), TCHAR('f'), TCHAR('g'), TCHAR('h'), TCHAR('i'), TCHAR('j'), TCHAR('k'), 
		TCHAR('l'), TCHAR('m'), TCHAR('n'), TCHAR('o'), TCHAR('p'), TCHAR('q'), TCHAR('r'), TCHAR('s'), TCHAR('t'), TCHAR('u'), TCHAR('v'), TCHAR('w'), 
		TCHAR('x'), TCHAR('y'), TCHAR('z') };
		bool found = false;
		for (int i = 0; i < 26; i++)
		{
			if(symbol == lowValues[i])
			{
				found = true;
				break;
			}
		}
		m_comboName.ResetContent();
		int count = 23;
		if(found)
			count = 26;

		CString str;
		for (int i = 0; i < count; i++)
		{
//		str.Format(_T("item string %d"), i);
			if(found)
				str = lowValues[i];
			else
				str = highValues[i];
			m_comboName.AddString(str);
		}
}

void ReplaceVariableDialog::OnBnClickedRadioinputtext()
{
	m_dataRadio = 1;
	m_comboName.EnableWindow(true);
	m_editIndex.EnableWindow(true);
	m_listVariables.EnableWindow(false);
//	GetDlgItem(IDC_RADIOINPUTTEXT)->EnableWindow(true);
//	GetDlgItem(IDC_RADIOSELECTVARIABLE)->EnableWindow(false);
	// TODO: �������� ���� ��� ����������� �����������
}




void ReplaceVariableDialog::OnBnClickedRadioselectvariable()
{
	m_dataRadio = 2;
	m_comboName.EnableWindow(false);
	m_editIndex.EnableWindow(false);
	m_listVariables.EnableWindow(true);
	HideVariables();
	ShowVariables();

//	GetDlgItem(IDC_RADIOINPUTTEXT)->EnableWindow(false);
//	GetDlgItem(IDC_RADIOSELECTVARIABLE)->EnableWindow(true);
	// TODO: �������� ���� ��� ����������� �����������
}

// ����� ������� ��������� ���������� �� �������� m_listVariables 
void ReplaceVariableDialog::HideVariables()
{
		// ���� ������� ��������� ���������� �� ������
	CString str;
	int item;
	pev_new.clear();
	while( (m_listVariables.GetCount( ) ) > 0 )   // ���� � ������ ��������� ���������� ������� ���� �� ���� �������
	{
		item = m_listVariables.GetTopIndex( );    // �������� ������ �������� ��������
		SemanticString * dsi = (SemanticString *) m_listVariables.GetItemData(item);    // �������� ������
		CString cs;
		m_listVariables.GetText(item, cs);	   // �������� ������, ��������������� �������� ��������, �������, ���� �������� ������
		m_listVariables.DeleteString(item);    //  ������� �� ����-������ ������ ��� �������� � �������� item
		DELETEITEMSTRUCT dis;                  // ��������� ��� �������� ������ �������� 
		dis.itemID = item;                     
		m_listVariables.DeleteItem(&dis);      // ������� ���� ������� ���������
	}
	m_listVariables.DCU.clear();               // ������� ��������� ������������ SemanticString
	// ��������� ������� ������ ���������� �� ������
}

// ����� ���������� ����������, �������� ����� ��������, � �������� m_listVariables ��� ���������� �������� � ������ ��������� (����������) ����������
void ReplaceVariableDialog::ShowVariables()
{
	CString str;
	// ���� ������� ���������� ��� ������
	pev_new.clear();
	int selected = m_list.GetCurSel();     // ������� ����� ���������� ������� (���������� � �������� ��������)
	if( selected >= 0 )     //���� �������� 
	{
		SemanticString * dsi = m_list.DCU.at(selected);    // ������� ��������� �� SemanticString, ��������� � ��������� ��������
		EntityBase * peb = dsi->formula;		
//		EntityBase * peb = entities->at(selected);
//		Formula * f = dsi->formula;     // �� SemanticString ������� ��������� �� ���� �������
		vector <EntityVariable *> * freeVariables = peb->getFreeVariables();   // ��������� �� ���������� ���������� �������
		//�������� ���� ��� ����, � ��� ����� � �������� ����������
		vector <EntityVariable *> * linkedVariables = peb->getLinkedVariables();   // ��������� �� ��������� ���������� �������
		vector <EntityVariable *> allVariables(*freeVariables);
		allVariables.insert(allVariables.end(), linkedVariables->begin(), linkedVariables->end());
		vector <EntityVariable *> allVariables1;
		int nIndex1 = m_listFreeVariables.GetCurSel();    // ������� ������ ��������� ���������� ����������
		int nCount1 = m_listFreeVariables.GetCount();    // ������� ���������� ���������� ����������
		if ((nIndex1 != CB_ERR) && (nCount1 > 0))    // ���� ��������� ���������� �������
		{
//			EntityVariable * pselVariable = freeVariables->at(nIndex1);
			EntityVariable * pselVariable = allVariables.at(nIndex1);
			Level * pl = (Level *)pselVariable;
			for(size_t i = 0; i < entities->size(); i++)
			{
				vector <EntityVariable *> * pevs = entities->at(i)->getFreeVariables();
				//�������� ���� ��� ����, � ��� ����� � �������� ����������
				vector <EntityVariable *> * linkedVariables1 = entities->at(i)->getLinkedVariables();   // ��������� �� ��������� ���������� �������
//				vector <EntityVariable *> allVariables1(*freeVariables);
				allVariables1.insert(allVariables1.end(), pevs->begin(), pevs->end());
				allVariables1.insert(allVariables1.end(), linkedVariables1->begin(), linkedVariables1->end());
				if(entities->at(i)->isSet())
				{
					FormulaSet * pset = (FormulaSet *)entities->at(i);
					EntityVariable * pevn = pset->getNaming();
					if(pevn != nullptr)
						allVariables1.push_back(pevn);
				}
			}
			for(size_t i1 = 0; i1 < allVariables1.size(); i1++)
			{
				EntityVariable * pev = allVariables1.at(i1);
				Level * plev = (Level *)pev;
				if(!pselVariable->compare(*pev) && (pl->compare(*plev)))
				{
					auto p1 = pev_new.begin();
					auto p2 = pev_new.end();
					bool found_pev = false;
					for(auto p1 = pev_new.begin(); p1 != pev_new.end(); ++p1)
					{
						EntityVariable * pev_left = *p1;
						if((pev_left->compare(*pev)) && !pev->GetText()->compare(*pev_left->GetText()) )
						{
							found_pev = true;
							break;
						}
					}
					if(!found_pev)
						pev_new.push_back(pev);
/*
�� �� �������� binary_search �� �������� ���������� � ������, ���� ������. � ������!
					if(binary_search(p1, p2, pev, myentity_compare))
					{
					}
					else
					{
						pev_new.push_back(pev);
					}
*/
				}
			}
		}
	}
	// ����� ����� ������� ���������� ��� ������

	// ��������� ������������ ����������� ��������
	for(size_t i = 0; i < pev_new.size(); i++)
	{
			// ��������� � �������� ������ � ���������� �������
			str.Format(_T("%d"), i);
			m_listVariables.InsertString(i,str);
			m_listVariables.SetItemHeight(i, 30);
			// ������� ������ SemanticString ��� ��������� ��������� ���������� �� ������ �������-������
			SemanticString * dsi1 = new SemanticString;
			m_listVariables.DCU.push_back(dsi1);
			// ����� �������� ��� ���������������� ����������, ������������ ��� ���������������� �������� ����������
			tstring redefinition = pev_new.at(i)->GetRedefinition();
			if(redefinition.length() >  0)
				dsi1->PrepareSubItemData(pev_new.at(i)->GetRedefinition());
			else
				dsi1->PrepareSubItemData(*(pev_new.at(i)->GetText()));
			m_listVariables.SetItemData(i, (DWORD_PTR)dsi1);     // �������� 
			if(i == 0)     // ���� ������ (�� ���� ���� �� ���� ��������� �������)
			{
				m_buttonOK.EnableWindow(true);    // ����� ��������� ������ "OK"
				m_listVariables.EnableWindow(true);    // ����� ��������� ����
			}

		m_listVariables.SetCurSel(0);    // ������������ ��������� ������ �������
	}
}
