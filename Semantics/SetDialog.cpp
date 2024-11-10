//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
// SetDialog.cpp: ���� ����������
//



//TRANSLATED


#include "stdafx.h"
#include "Semantics.h"
#include "SetDialog.h"
#include "afxdialogex.h"
//#include <cmath>




IMPLEMENT_DYNAMIC(SetDialog, CDialogEx)


//
// �����������
//
SetDialog::SetDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(SetDialog::IDD, pParent)
{
	m_fIndexes = nullptr;
	m_fSymbol = nullptr;
}


//
// ����������
//
SetDialog::~SetDialog()
{
	// ���� ������ ����������� (��������� �� ��� �� ����� nullptr), ���������� �������
	if ( m_fIndexes != nullptr )
		delete m_fIndexes;
	if ( m_fSymbol != nullptr )
		delete m_fSymbol;
}

void SetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SETLIST1, m_list);
	DDX_Control(pDX, IDC_SETLIST2, m_listVariables);
	DDX_Control(pDX, IDOK, m_buttonOK);
	DDX_Control(pDX, IDC_BELONGING, m_CheckBelonging);
	DDX_Control(pDX, IDC_BUILDSUBSET, m_CheckSubSet);
	DDX_Control(pDX, IDC_SUBSETCOMBO, m_ComboSubSet);
	DDX_Control(pDX, IDC_SUBSETINDEX, m_IndexSubSet);
	DDX_Control(pDX, IDC_SETCOMBO, m_comboSet);
	DDX_Control(pDX, IDC_SETINDEX, m_indexSet);
	DDX_Control(pDX, IDC_STATICLABEL, m_label);
	DDX_Control(pDX, IDC_STATICLEVEL, m_level);
}


BEGIN_MESSAGE_MAP(SetDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &SetDialog::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_SETLIST1, &SetDialog::OnSelchangeSetlist1)
	ON_BN_CLICKED(IDC_BUILDSUBSET, &SetDialog::OnClickedBuildsubset)
	ON_LBN_SELCHANGE(IDC_SETLIST2, &SetDialog::OnSelchangeSetlist2)
	ON_CBN_SELCHANGE(IDC_SETCOMBO, &SetDialog::OnSelchangeSetcombo)
	ON_EN_CHANGE(IDC_SETINDEX, &SetDialog::OnChangeSetindex)
END_MESSAGE_MAP()


// ����������� ��������� SetDialog

//
// ���������� ������� �� ������ "OK"
//
void SetDialog::OnBnClickedOk()
{
	TCHAR * tbuf1 = nullptr;
	TCHAR * tbuf_index1 = nullptr;
	TCHAR * tbuf2 = nullptr;
	TCHAR * tbuf_index2 = nullptr;
	tstring tsubset;
	tstring tsubset_index;
	tstring tset;
	tstring tset_index;
	EntityVariable * psubset = nullptr;
	EntityVariable * pset = nullptr;
	bool subset_success = true;
	bool setnaming_success = true;



	int nIndex3 = m_comboSet.GetCurSel();    // ������� ������ ���������� �������� ��� ����������� ����������
	int nCount3 = m_comboSet.GetCount();    // ������� ���������� ��������� ������� ����������� ����������
	if ((nIndex3 != CB_ERR) && (nCount3 > 1))    // ���� ������
	{
		int len3 = m_comboSet.GetLBTextLen(nIndex3);    // ����� ������ ��������
		tbuf2 = new TCHAR[len3 + 2];    // ������ ����� ��� �������� ������ ����������
		m_comboSet.GetLBText(nIndex3, (LPTSTR)tbuf2);    // �������� ����� ���������� � ��������� �����
		len3 = m_indexSet.GetWindowTextLengthW();    // ����� ������ ������� ����������
		if(len3)
		{
			tbuf_index2 = new TCHAR[len3 + 2];    // ������ ����� ��� �������� ������ ������� ����������
			m_indexSet.GetWindowTextT(tbuf_index2, len3 + 1);    // �������� ����� ������� ���������� � ��������� �����
			tset = tstring(tbuf2);
			tset_index = tstring(tbuf_index2);
			if(find_if_not(tset_index.begin(), tset_index.end(), istdigit) == tset_index.end())
			{
				bool foundEV = isExistVariable(tset, tset_index, entities);
				if(!foundEV)
					pset = new EntityVariable(tset, tset_index, SET);
				else
				{
					if(CURRENT_LANG_OF=="rus")
						AfxMessageBox(_T("������� ������ ����������� ���������, ��� ��� ������������ � �����."));
					else
						AfxMessageBox(_T("Enter another notation for the set, this is already used in the scheme."));
					setnaming_success = false;
				}
			}
			else
			{
				if (CURRENT_LANG_OF == "rus")
					AfxMessageBox(_T("� ������� ��������� ������� �� �����"));
				else
					AfxMessageBox(_T("The index of the set does not specify a number"));
				m_indexSet.SetFocus();
				setnaming_success = false;
			}
		}
		else
		{
			if (CURRENT_LANG_OF == "rus")
				AfxMessageBox(_T("�� ������ ������ ��� ���������� ���������"));
			else
				AfxMessageBox(_T("The index for building the set is not selected"));
			setnaming_success = false;
		}
	}
	else
	{
		if (CURRENT_LANG_OF == "rus")
			AfxMessageBox(_T("�� ������ ������ ��� ���������� ������������"));
		else
			AfxMessageBox(_T("An index has not been selected to build a subset"));
		setnaming_success = false;
	}
	if (setnaming_success)
	{
		int selected1 = m_list.GetCurSel();    // ����� ��������� �������
		if (selected1 != LB_ERR)     // ���� ����� ���������� ��������, ������������ ������� GetCurSel, ������������
		{
			SemanticString* dsi1 = (SemanticString*)m_list.DCU.at(selected1);    // �������� ��������� �� SemanticString, ��������� � ��������� ���������
			Formula* formula = (Formula*)dsi1->formula;    // ���� ��������� �� ������ Formula ��� �������� ������� SemanticString
			if (formula != nullptr)    // �������� �� ��, ��� ��������� �� ������� (���������� ��������)
			{
				// Get the indexes of all the selected items.
				int nCount = m_listVariables.GetSelCount();    // ���������, ������� ��������� ���������� �������
				if (nCount > 0)    // ���� ������� ���� �� ����
				{
					vector <EntityVariable*>* variables = new vector <EntityVariable*>;


					CArray<int, int> aryListBoxSel;    // ��������� ��� ��������� ��������� ������ ��������� ����������
					aryListBoxSel.SetSize(nCount);    // ������������� ������ ����������, ������ ����� ��������� ��������� ����������
					m_listVariables.GetSelItems(nCount, aryListBoxSel.GetData());     // ��������� ���������
					int pt;
					// ������� �� ��������� ��������� ����������
					for (int i = 0; i <= aryListBoxSel.GetUpperBound(); i++)
					{
						pt = aryListBoxSel.GetAt(i);    // ������� ����� ���������� ��������, ���������������� ��������� ��������� ��������� ����������
						vector <EntityVariable*>* fv = formula->getFreeVariables();
						variables->push_back(fv->at(pt)); // ��������� � ������ ����������, �� ������� ������ ��������� ����������
					}
					// ��������, ��������� �� ������ ����� �������� ����������, �� ������ ��� �� ������� � ��� �� ������� ����������
					bool isExist = false;
					for (size_t i = 0; i < entities->size(); i++) // ������� ���� ��������� ���������
					{
						bool toProccess = false;
						EntityBase* base = entities->at(i);     // ��������� �� ��������� ��������
						if (base->isFormula()) // ���� ��������� �������� �������, �� ��������� � ��������� ��������
							continue;
						FormulaSet* baseFS = (FormulaSet*)base;    // ��������� �� ��������� ����������
						if (formula == baseFS->getParentFormula()) // ���� ������������ ������� ��� ��������� �������� ��������� � ��������� ��������, 
							// �� ������� �������� ��������� ����������
						{
							// ��������, ��� ��������� ������ ��������� ���������� ��� ���� ���� ������ ( ��������, ���������� ��������)
							vector <EntityVariable*>* fv_base = base->getFreeVariables();
							vector <EntityVariable*>* fv_formula = formula->getFreeVariables();
							if (fv_base->size() == fv_formula->size()) // ������ ���� ������� ������� ��������� ���������� ���������
							{
								bool isFoundFVAll = true;
								for (size_t i1 = 0; i1 < fv_base->size(); i1++)    // ������� �� ���� ��������� ���������� ��������� ��������
								{
									EntityVariable* pev = fv_base->at(i1);
									bool isFoundFV = false;
									for (size_t i2 = 0; i2 < fv_formula->size(); i2++)    // ��������� ���� �� ��������� ���������� �������
									{
										if (pev->compare(*fv_formula->at(i2)))     // ���� ��������
										{
											isFoundFV = true;
											break;
										}
									}
									if (!isFoundFV)
									{
										isFoundFVAll = false;    // �� ���� ���������, ��������� ���� ������ ��� ����� ����������� ����������, �� � ��� ��������,
										// ��������, �������� ����������
										break;
									}
								}
								if (isFoundFVAll)
									toProccess = true;
							}
							// ��������, ��� ��������� ������ ������� ���������� ������� �������� � ��������� ��������, �� ������� �������� ��������� ����������
							vector <EntityVariable*>* bv_base = baseFS->getBaseVariables();
							if (toProccess && (bv_base->size() == variables->size())) // ������ ���� ������� ������� ��������� ���������� ���������
							{
								toProccess = false;
								bool isFoundFVAll = true; // ��������� �������, ��� ������ ���������
								for (size_t i1 = 0; i1 < bv_base->size(); i1++)
								{
									EntityVariable* pev = bv_base->at(i1);
									bool isFoundFV = false;
									for (size_t i2 = 0; i2 < variables->size(); i2++)
									{
										if (pev->compare(*variables->at(i2)))
										{
											isFoundFV = true;
											break;
										}
									}
									if (!isFoundFV)
									{
										isFoundFVAll = false;
										break;
									}
								}
								if (isFoundFVAll)
									toProccess = true;
							}
							else
								toProccess = false;
						}
						if (toProccess)
						{
							isExist = toProccess;
							break;
						}
					}
					if (!isExist)     // ���� �� ������� ��������� ��������� ����������
					{
						// ���� �������� �� ����� ����� � ������� ��� ������������, ���� ��������� �������������� ������
						int checked = m_CheckSubSet.GetCheck();
						//					if(m_CheckBelonging.GetCheck() && checked)
						if (checked)
						{
							if (variables->size() > 0)
							{
								int nIndex = m_ComboSubSet.GetCurSel();    // ������� ������ ���������� �������� ��� ����������� ����������
								int nCount = m_ComboSubSet.GetCount();    // ������� ���������� ��������� ������� ����������� ����������
								if ((nIndex != CB_ERR) && (nCount > 1))    // ���� ������
								{
									int len = m_ComboSubSet.GetLBTextLen(nIndex);    // ����� ������ ��������
									tbuf1 = new TCHAR[len + 2];    // ������ ����� ��� �������� ������ ����������
									m_ComboSubSet.GetLBText(nIndex, (LPTSTR)tbuf1);    // �������� ����� ���������� � ��������� �����
									len = m_IndexSubSet.GetWindowTextLengthW();    // ����� ������ ������� ����������
									if (len)
									{
										tbuf_index1 = new TCHAR[len + 2];    // ������ ����� ��� �������� ������ ������� ����������
										m_IndexSubSet.GetWindowTextT(tbuf_index1, len + 1);    // �������� ����� ������� ���������� � ��������� �����
										tsubset = tstring(tbuf1);
										tsubset_index = tstring(tbuf_index1);
										if (find_if_not(tsubset_index.begin(), tsubset_index.end(), istdigit) == tsubset_index.end())
										{

											bool foundEV = isExistVariable(tsubset, tsubset_index, entities);
											if (!foundEV)
											{
												psubset = new EntityVariable(tsubset, tsubset_index, SET);
												if (psubset->compare(*pset))
												{
													if (CURRENT_LANG_OF == "rus")
														AfxMessageBox(_T("������� ������ ����������� ������������, ��� ��� ������������ ��� ����������� ��������� ����������."));
													else
														AfxMessageBox(_T("Enter another subset notation, this is already used for the truth set under construction."));
													subset_success = false;
												}
											}
											else
											{
												if (CURRENT_LANG_OF == "rus")
													AfxMessageBox(_T("������� ������ ����������� ������������, ��� ��� ������������ � �����."));
												else
													AfxMessageBox(_T("Enter a different subset designation, this is already used in the schema."));
												subset_success = false;
											}
										}
										else
										{
											if (CURRENT_LANG_OF == "rus")
												AfxMessageBox(_T("� ������� ������������ ������� �� �����"));
											else
												AfxMessageBox(_T("The subset index does not specify a number"));
											m_IndexSubSet.SetFocus();
											subset_success = false;
										}
									}
									else
									{
										if (CURRENT_LANG_OF == "rus")
											AfxMessageBox(_T("�� ������ ������ ��� ���������� ������������"));
										else
											AfxMessageBox(_T("An index has not been selected to build a subset"));
										subset_success = false;
									}
								}
								else
								{
									if (CURRENT_LANG_OF == "rus")
										AfxMessageBox(_T("�� ������� ����������� ��� ���������� ������������"));
									else
										AfxMessageBox(_T("The notation for the construction of a subset is not selected"));
									subset_success = false;
								}
							}
							else
							{
								if (CURRENT_LANG_OF == "rus")
									AfxMessageBox(_T("������������ �� ��������������,������ ��� �� ������� �� ����� ����������. "));
								else
									AfxMessageBox(_T("The subset will not be built because no variables are selected."));
								subset_success = false;
							}

						}
						if (subset_success) // ���� �������� ������������ �� ������ ��� ������ � ����������� ������� � ����� ������������ ��������
						{
							//							FormulaSet * pfs = new FormulaSet(formula, variables);    // ������ ��������� ����������
							tstring tlevel = _T("<");
							for (size_t i = 0; i < variables->size(); i++)
							{
								if (i > 0)
									tlevel += _T(",");
								tlevel += ((Level*)variables->at(i))->GetLevel();
							}
							tlevel += _T(">");
							((Level*)pset)->SetLevel(tlevel);
							FormulaSet* pfs = new FormulaSet(formula, variables, pset);    // ������ ��������� ����������
							tstring tvars;
							tstring tlevel1;
							if (pfs->isExclusion(formula))
							{
								pfs->proccessExclusion(formula, variables, tvars, tlevel1);
							}
							pfs->SetLabel(entities);    // ��������� �����������
							entities->push_back(pfs);   // �������� ��������� ��������� ���������� � �����
							if (m_CheckBelonging.GetCheck())
							{
								// ������������� ������ �������� ��������������
								Formula* predicate = new Formula();
								if (tvars.length() > 0)
									predicate->predicateBelonging(entities, formula, pfs, &tvars);
								else
									predicate->predicateBelonging(entities, formula, pfs);
								entities->push_back(predicate);   // �������� ��������� �������� �������������� � �����
							}
							if (checked)
							{
								Tuple* temp_tuple = nullptr;
								size_t fv_count = variables->size();
								/*
																if(fv_count == 1)
																{
																	tstring new_level = variables->at(0)->GetLevel();
																	new_level = _T("<") + new_level + _T(">");
																	psubset->SetLevel(new_level);
																	temp_tuple = new Tuple(*variables->at(0), *psubset);
																}
																else if(fv_count == 2)
																{
																	tstring new_level = variables->at(0)->GetLevel() + _T(",") + variables->at(1)->GetLevel();
																	new_level = _T("<") + new_level + _T(">");
																	psubset->SetLevel(new_level);
																	temp_tuple = new Tuple(*variables->at(0), *variables->at(1), *psubset);
																}
								*/
								if (fv_count > 0)
								{
									tstring new_level;
									if (tlevel1.length() > 0)
									{
										new_level = tlevel1;
									}
									else
									{
										for (size_t i = 0; i < variables->size(); i++)
										{
											if (i > 0)
												new_level += _T(",");
											new_level += variables->at(i)->GetLevel();
										}
										new_level = _T("<") + new_level + _T(">");
									}

									psubset->SetLevel(new_level);
									temp_tuple = new Tuple(variables, *psubset);
								}
								if (temp_tuple != nullptr)
								{
									vector <EntityVariable*> depending(*(formula->getFreeVariables()));
									vector <EntityVariable*>* fv1 = temp_tuple->getFreeVariables();
									for (size_t i = 0; i < depending.size(); i++)
									{
										for (size_t i1 = 0; i1 < fv1->size(); i1++)
										{
											if (fv1->at(i1)->compare(*depending.at(i)))
											{
												depending.erase(depending.begin() + i);
												break;
											}
										}
									}
									if (tvars.length() > 0)
										temp_tuple->SetTupleText(&depending, &tvars); // ����� ����� �������
									else
										temp_tuple->SetTupleText(&depending); // ����� ����� �������										
									temp_tuple->SetLabel(entities); // ����� ����������� �������
									entities->push_back(temp_tuple);   // �������� ��������� ������������ � �����
									//����� ������������ ��� �������, ��������� �������������� � ������������
									variables->push_back(psubset);
									Formula* pfsubset = new Formula();
									pfsubset->subset(entities, pfs, variables);    // ������ ������������
									pfsubset->putTextOfFormula(entities);
									pfsubset->SetLabel(entities);    // ��������� �����������
									entities->push_back(pfsubset);   // �������� ��������� ������������ � �����
								}
							}
						}

					}
					else {
						if (CURRENT_LANG_OF == "rus")
							AfxMessageBox(_T("�������� ������ ����� ����������, �� ����� ��������� ���������� ��� ���������"));
						else
							AfxMessageBox(_T("Choose a different set of variables, so the truth set has already been built"));
					}
					// ����� �����������
					delete variables;     // ���������� ������
					if (!isExist && subset_success)       // ���� ���� ������� ��������� ����������
						CDialogEx::OnOK();    // �������� ���������� ����
				}
				else {
					if (CURRENT_LANG_OF == "rus")
						AfxMessageBox(_T("�� ������� �� ����� ����������"));
					else
						AfxMessageBox(_T("No variables are selected"));
				}
				/*
							int selected2 = m_listVariables.GetCurSel();
							if(selected2 != LB_ERR)
							{
				//				SemanticString * dsi2 = (SemanticString *) m_listVariables.DCU.at(selected2);
								vector <EntityVariable *> * fv = formula->getFreeVariables();
								vector <EntityVariable *> * variables = new vector <EntityVariable *>;
								variables->push_back(fv->at(selected2));
								FormulaSet * pfs = new FormulaSet(formula, variables);
								pfs->SetLabel(entities);
								entities->push_back(pfs);
								// ����� �����������
								delete variables;
							}
				*/
			}
		}
		else {
			if (CURRENT_LANG_OF == "rus")
				AfxMessageBox(_T("�� ������� ������� ��� ���������� ��������� ����������"));
			else
				AfxMessageBox(_T("The formula for constructing the truth set has not been chosen"));
		}
	}
	if(tbuf1 != nullptr)
		delete tbuf1;
	if(tbuf_index1 != nullptr)
		delete tbuf_index1;
	if(psubset != nullptr)
		delete psubset;
	if(tbuf2 != nullptr)
		delete tbuf2;
	if(tbuf_index2 != nullptr)
		delete tbuf_index2;
	if(pset != nullptr)
		delete pset;
	// TODO: �������� ���� ��� ����������� �����������
}


//
// ������������� �������� � �������� ������� � ��� ��������� ��� �������������
//
BOOL SetDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString str;
	int count = 0;
	tstring res;
	tstring res_formula;
	for (size_t i = 0; i < entities->size(); i++)    // ������� �� ���� ��������� �����
	{
		bool toProccess = true;     // ���� 
		EntityBase * base = entities->at(i);    // ��������� �� ��������� ��������
		if ( !base->isFormula() )       // ���� �������� �� �������
			continue;     // ��������� � ������
		vector <EntityVariable *> * fv = base->getFreeVariables();    // ��������� �� ��������� ��������� ���������� ��������
		if ( fv->size() == 0)     // ���� ��� ��������� ����������
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
		dsi->formula = icurr;
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
	m_CheckSubSet.SetCheck(0);
	m_ComboSubSet.EnableWindow(false);
	m_IndexSubSet.EnableWindow(false);
	// TODO:  �������� �������������� �������������

	// ������ ����� �� ���������
	m_fIndexes = new CFont;
	m_fIndexes->CreatePointFont(70, L"Arial Unicode MS");
//	m_fIndexes->CreatePointFont(70, L"Microsoft San Serif");
	m_label.m_fIndexes = m_fIndexes;
	m_level.m_fIndexes = m_fIndexes;
	// ������ ����� ��� �������������� ��������
	m_fSymbol = new CFont;
//	m_fSymbol->CreatePointFont(140, L"Symbol");
	m_fSymbol->CreatePointFont(140, L"Arial Unicode MS");
	m_label.m_fSymbol = m_fSymbol;
	m_level.m_fSymbol = m_fSymbol;


	return TRUE;  // return TRUE unless you set the focus to a control
	// ����������: �������� ������� OCX ������ ���������� �������� FALSE
}

//
// ����� ���������� ��������� ���������� � �������� m_listVariables ��� ���������� �������� � ������ ������
//
void SetDialog::ShowFreeVariables()
{
	int selected = m_list.GetCurSel();     // ������� ����� ���������� ������� (���������� � �������� ��������)
	if( selected >= 0 )     //���� �������� 
	{
		SemanticString * dsi = m_list.DCU.at(selected);    // ������� ��������� �� SemanticString, ��������� � ��������� ��������
		Formula * f = (Formula *)dsi->formula;     // �� SemanticString ������� ��������� �� ���� �������
		vector <EntityVariable *> * freeVariables = f->getFreeVariables();   // ��������� �� ��������� ���������� �������
		for (size_t i = 0; i < freeVariables->size(); i++)     // ������� �� ��������� ����������
		{
			CString str;
			// ��������� � �������� ������ � ���������� �������
			str.Format(_T("%d"), i);
			m_listVariables.InsertString(i,str);
			m_listVariables.SetItemHeight(i, 30);
			// ������� ������ SemanticString ��� ��������� ��������� ���������� �� ������ �������-������
			SemanticString * dsi1 = new SemanticString;
			m_listVariables.DCU.push_back(dsi1);
			dsi1->PrepareSubItemData(*(freeVariables->at(i)->GetText()));
			m_listVariables.SetItemData(i, (DWORD_PTR)dsi1);     // �������� 
			if(i == 0)     // ���� ������ (�� ���� ���� �� ���� ��������� �������)
			{
				m_buttonOK.EnableWindow(true);    // ����� ��������� ������ "OK"
				m_listVariables.EnableWindow(true);    // ����� ��������� ����
			}
		}
		m_listVariables.SetCurSel(0);    // ������������ ��������� ������ �������
	}
}

//
// ����� ������� ��������� ���������� �� �������� m_listVariables
//
void SetDialog::HideFreeVariables()
{
	int item;
	CString cs;
	m_label.SetWindowTextT(cs);
	m_level.SetWindowTextT(cs);
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
	m_buttonOK.EnableWindow(false);            // ����� ���� ����������
}

//
// ���������� ������ �������
//
void SetDialog::OnSelchangeSetlist1()
{
	HideFreeVariables();    // ������� ����������, ���� ����, �� ����-������ ��������� ����������
	ShowFreeVariables();    // ��������� ����-������ ��������� ���������� � ����������� �� ��������� �������
	CheckSelection();
}


void SetDialog::OnClickedBuildsubset()
{
	if(m_CheckSubSet.GetCheck())
	{
		m_ComboSubSet.EnableWindow(true);
		m_IndexSubSet.EnableWindow(true);
	}
	else
	{
		m_ComboSubSet.EnableWindow(false);
		m_IndexSubSet.EnableWindow(false);
	}
	// TODO: �������� ���� ��� ����������� �����������
}

void SetDialog::OnSelchangeSetlist2()
{
	CheckSelection();
}

void SetDialog::CheckSelection()
{
	TCHAR * tbuf2 = nullptr;
	TCHAR * tbuf_index2 = nullptr;
	tstring tset;
	tstring tset_index;
	EntityVariable * pset = nullptr;
	CString cs_label;
	CString cs_level;

//	m_label.SetWindowTextT(cs_label);
//	m_label.OnPaint();
//	m_level.SetWindowTextT(cs_level);
//	m_level.RedrawWindow();

	int nIndex3 = m_comboSet.GetCurSel();    // ������� ������ ���������� �������� ��� ����������� ����������
	int nCount3 = m_comboSet.GetCount();    // ������� ���������� ��������� ������� ����������� ����������
	if ((nIndex3 != CB_ERR) && (nCount3 > 1))    // ���� ������
	{
		int len3 = m_comboSet.GetLBTextLen(nIndex3);    // ����� ������ ��������
		tbuf2 = new TCHAR[len3 + 2];    // ������ ����� ��� �������� ������ ����������
		m_comboSet.GetLBText(nIndex3, (LPTSTR)tbuf2);    // �������� ����� ���������� � ��������� �����
		len3 = m_indexSet.GetWindowTextLengthW();    // ����� ������ ������� ����������
		if(len3)
		{
			tbuf_index2 = new TCHAR[len3 + 2];    // ������ ����� ��� �������� ������ ������� ����������
			m_indexSet.GetWindowTextT(tbuf_index2, len3 + 1);    // �������� ����� ������� ���������� � ��������� �����
			tset = tstring(tbuf2);
			tset_index = tstring(tbuf_index2);
			if(find_if_not(tset_index.begin(), tset_index.end(), istdigit) == tset_index.end())
			{

				pset = new EntityVariable(tset, tset_index, SET);
				int selected1 = m_list.GetCurSel();    // ����� ��������� �������
				if ( selected1 != LB_ERR )     // ���� ����� ���������� ��������, ������������ ������� GetCurSel, ������������
				{
					SemanticString * dsi1 = (SemanticString *) m_list.DCU.at(selected1);    // �������� ��������� �� SemanticString, ��������� � ��������� ���������
					Formula * formula = (Formula *)dsi1->formula;    // ���� ��������� �� ������ Formula ��� �������� ������� SemanticString
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
//							((Level *)pset)->SetLevel(tstring(_T("<0>")));
							tstring tlevel = _T("<");
							for(size_t i = 0; i < variables->size(); i++)
							{
								if(i > 0)
									tlevel += _T(",");
								tlevel += ((Level *)variables->at(i))->GetLevel();
							}
							tlevel += _T(">");
							((Level *)pset)->SetLevel(tlevel);
							FormulaSet pfs(formula, variables, pset);    // ������ ��������� ����������
							pfs.SetLabel(entities);    // ��������� �����������
							cs_label = pfs.getLabel()->data();
							cs_level = ((Level *)pfs.getNaming())->GetLevel().data();
						}
						else
						{
							if(CURRENT_LANG_OF=="rus")
								cs_label = _T("�� ������� �� ���� ����������");
							else 
								cs_label = _T("No variables are selected");

						}
					}		
					else
						cs_label = _T("������ ��������� �� ������");
				}
				else
					cs_label = _T("�� ������� �������");
			}
			else
				cs_label = _T("� ������� ��������� ������� �� �����");

		}
		else
			cs_label = _T("�� ������ ������");
	}
	else
		cs_label = _T("�� ������� ����������� ��� ������");
	
	CString cs;
	m_label.SetWindowTextT(cs);
	tstring tstr_label = cs_label;
	m_label.dsi->PrepareSubItemData(tstr_label);
	m_label.Invalidate(true);
	m_label.OnPaint();


	m_level.SetWindowTextT(cs);
	tstring tstr_level = cs_level;
	m_level.dsi->PrepareSubItemData(tstr_level);
	m_level.Invalidate(true);
	m_level.OnPaint();

//	m_label.SetWindowTextT(cs_label);
//	m_level.SetWindowTextT(cs_level);
	if(tbuf2 != nullptr)
		delete tbuf2;
	if(tbuf_index2 != nullptr)
		delete tbuf_index2;
	if(pset != nullptr)
		delete pset;	// TODO: �������� ���� ��� ����������� �����������
}



void SetDialog::OnSelchangeSetcombo()
{
	CheckSelection();
	// TODO: �������� ���� ��� ����������� �����������
}


void SetDialog::OnChangeSetindex()
{
	CheckSelection();
	// TODO:  ���� ��� ������� ���������� RICHEDIT, �� ������� ���������� �� �����
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  �������� ��� �������� ����������
}
