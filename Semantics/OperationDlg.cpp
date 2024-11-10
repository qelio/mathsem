//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
// OperationDlg.cpp: файл реализации
//

//TRANSLATED

#include "stdafx.h"
#include "Semantics.h"
#include "OperationDlg.h"
#include "afxdialogex.h"


// диалоговое окно OperationDlg

IMPLEMENT_DYNAMIC(OperationDlg, CDialogEx)

OperationDlg::OperationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(OperationDlg::IDD, pParent)
{
	operation = NONE_FORMULA;
	m_fSymbol = NULL;
	m_fIndexes = NULL;
	m_fVariables = NULL;
	m_fIndexesVariables = NULL;
	m_fSymbolVariables = NULL;
	if(m_fSymbol)
		delete m_fSymbol;
	if(m_fIndexes)
		delete m_fIndexes;
	formulas = new vector <Formula *>;
	allEntities = nullptr;
}

OperationDlg::~OperationDlg()
{
	if (formulas != nullptr)
	{
/*
		for ( size_t i = 0; i < formulas->size(); i++)
			delete formulas->at(i);
*/
		delete formulas;
	}
}

void OperationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTSOURCE, m_ListBoxSource);
	DDX_Control(pDX, IDC_LISTDEST1, m_ListBoxDestination1);
	DDX_Control(pDX, IDC_LISTDEST2, m_ListBoxDestination2);
	DDX_Control(pDX, IDC_MFCBUTTON1, m_ButtonAdd1);
	DDX_Control(pDX, IDC_MFCBUTTON2, m_ButtonRemove1);
	DDX_Control(pDX, IDC_STATIC1, m_StaticDescription);
	DDX_Control(pDX, IDC_CHECK1, m_CheckApplyForAll);
	DDX_Control(pDX, IDC_CHECK2, m_CheckBinary);
	DDX_Control(pDX, IDC_MFCBUTTON5, m_ButtonAddAll1);
	DDX_Control(pDX, IDC_MFCBUTTON6, m_ButtonRemoveAll1);
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDC_CHECKALL1, m_checkAll1);
	DDX_Control(pDX, IDC_CHECKALL2, m_checkAll2);
}


BEGIN_MESSAGE_MAP(OperationDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK2, &OperationDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDOK, &OperationDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_MFCBUTTON1, &OperationDlg::OnBnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_MFCBUTTON5, &OperationDlg::OnBnClickedMfcbutton5)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &OperationDlg::OnBnClickedMfcbutton2)
	ON_BN_CLICKED(IDC_MFCBUTTON6, &OperationDlg::OnBnClickedMfcbutton6)
	ON_LBN_SELCHANGE(IDC_LISTDEST1, &OperationDlg::OnSelchangeListdest1)
	ON_STN_CLICKED(IDC_STATIC1, &OperationDlg::OnStnClickedStatic1)
	ON_BN_CLICKED(IDC_CHECKALL1, &OperationDlg::OnBnClickedCheckall1)
END_MESSAGE_MAP()


// обработчики сообщений OperationDlg


void OperationDlg::OnBnClickedCheck2()
{
	if(m_CheckBinary.GetCheck() == false)
	{
//		m_CheckBinary.SetCheck(1);
		m_ListBoxDestination2.EnableWindow(true);
	}
	else
	{
//		m_CheckBinary.SetCheck(1);
		m_ListBoxDestination2.EnableWindow(false);

	}
	// TODO: добавьте свой код обработчика уведомлений
}


BOOL OperationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetOperationState();
//	this->m_ListBoxDestination2.SetItemHeight(0, 30);
//	this->m_ListBoxDestination2.set

//	m_ListBoxSource.SetSorting(true);
	CString str;
	int count = 0;
	tstring res;
	tstring res_formula;
	EntityBaseType type = this->GetOperation();
	for (size_t i = 0; i < allEntities->size(); i++)
	{
		bool toProccess = true;
		EntityBase * base = allEntities->at(i);
		if ( base->getType() == FORMULA_SET )
			continue;
		Formula * icurr = (Formula *)base;
// здесь пока на время отладки раносильностей комментарим
//#ifdef EQUITYTEST
		icurr = icurr->operationCandidate(allEntities, type);
		if( icurr == nullptr )
			continue;
//#endif
		formulas->push_back(icurr);
		// вставляем в листбокс строку с порядковым номером
		str.Format(_T("%d"), count);
		m_ListBoxSource.AddString(str);
		m_ListBoxSource.SetItemHeight(count, 30);
		SemanticString * dsi = new SemanticString;
		m_ListBoxSource.DCU.push_back(dsi);
		dsi->PrepareSubItemData(icurr->getText());
		dsi->formula = icurr;
		m_ListBoxSource.SetItemData(count, (DWORD_PTR)dsi);
		if(count == 0)
		{
			m_ButtonOK.EnableWindow(true);
			m_ButtonAdd1.EnableWindow(true);
			m_ButtonAddAll1.EnableWindow(true);
			m_CheckApplyForAll.EnableWindow(true);
			m_ListBoxDestination1.EnableWindow(true);
			m_ListBoxSource.EnableWindow(true);
			if ( ( operation == AND_OPERATION) || ( operation == OR_OPERATION ) )
			{
				m_CheckBinary.SetCheck(1);
			}
		}

		count++;
	}
	// TODO:  Добавить дополнительную инициализацию
	m_fIndexes = new CFont;
//	m_fIndexes->CreatePointFont(70, L"Microsoft San Serif");
	m_fIndexes->CreatePointFont(70, L"Arial Unicode MS");
	m_StaticDescription.m_fIndexes = m_fIndexes;
	m_fSymbol = new CFont;
//	m_fSymbol->CreatePointFont(140, L"Symbol");
	m_fSymbol->CreatePointFont(140, L"Arial Unicode MS");
	m_StaticDescription.m_fSymbol = m_fSymbol;

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}



void OperationDlg::SetOperationState()
{
	tstring tstr;
	switch (operation)
	{
	case NONE_FORMULA:
		m_ListBoxDestination2.EnableWindow(false);
		m_ListBoxDestination1.EnableWindow(false);
		m_ListBoxSource.EnableWindow(false);
		m_CheckApplyForAll.EnableWindow(false);
		m_CheckBinary.EnableWindow(false);
		m_ButtonAdd1.EnableWindow(false);
		m_ButtonRemove1.EnableWindow(false);
		m_ButtonAddAll1.EnableWindow(false);
		m_ButtonRemoveAll1.EnableWindow(false);
		m_checkAll1.EnableWindow(false);
		m_checkAll2.EnableWindow(false);
		m_checkAll1.ShowWindow(SW_HIDE);
		m_checkAll2.EnableWindow(SW_HIDE);
		break;
	case NEGATIVE_OPERATION:
		if( formulas->size() > 0 )
		{
			m_ListBoxDestination1.EnableWindow(true);
			m_ListBoxSource.EnableWindow(true);
			m_CheckApplyForAll.EnableWindow(true);
			m_ButtonAdd1.EnableWindow(true);
			m_ButtonAddAll1.EnableWindow(true);
			m_ButtonOK.EnableWindow(true);
		}
		else
		{
			m_ButtonOK.EnableWindow(false);
			m_ListBoxDestination1.EnableWindow(false);
			m_ListBoxSource.EnableWindow(false);
			m_CheckApplyForAll.EnableWindow(false);
			m_ButtonAdd1.EnableWindow(false);
			m_ButtonAddAll1.EnableWindow(false);
		}
		m_ListBoxDestination2.EnableWindow(false);
		m_CheckBinary.EnableWindow(false);
		m_ButtonRemove1.EnableWindow(false);
		m_ButtonRemoveAll1.EnableWindow(false);
		m_checkAll1.ShowWindow(SW_SHOW);
		m_checkAll1.EnableWindow(false);
		if(CURRENT_LANG_OF=="rus")
			tstr = _T("Операция отрицания \"not\"");
		else 
			tstr = _T("The negation operation \"not\"");

		m_StaticDescription.dsi->PrepareSubItemData(tstr);
//		this->m_StaticDescription.SetWindowTextT(tstr.data());
		break;
	case QUANTIFIER1_OPERATION:
	case QUANTIFIER2_OPERATION:
		if( formulas->size() > 0 )
		{
			m_ButtonOK.EnableWindow(true);
			m_ListBoxDestination1.EnableWindow(true);
			m_ListBoxSource.EnableWindow(true);
		}
		else
		{
			m_ButtonOK.EnableWindow(false);
			m_ListBoxDestination1.EnableWindow(false);
			m_ListBoxSource.EnableWindow(false);
		}
		m_ListBoxDestination2.EnableWindow(false);
		m_CheckApplyForAll.EnableWindow(false);
		m_CheckBinary.EnableWindow(false);
		m_ButtonAdd1.EnableWindow(false);
		m_ButtonAddAll1.EnableWindow(false);
		m_ButtonRemove1.EnableWindow(false);
		m_ButtonRemoveAll1.EnableWindow(false);
		if (CURRENT_LANG_OF == "rus") {
			if (operation == QUANTIFIER1_OPERATION)
				tstr = _T("Операция навешивания квантора <Symbol=/34>");
			else
				tstr = _T("Операция навешивания квантора <Symbol=/36>");
		}
		else {
			if (operation == QUANTIFIER1_OPERATION)
				tstr = _T("The operation of attaching a quantifier <Symbol=/34>");
			else
				tstr = _T("The operation of attaching a quantifier <Symbol=/36>");
		}
		m_StaticDescription.dsi->PrepareSubItemData(tstr);
		m_checkAll2.ShowWindow(SW_SHOW);
		m_checkAll2.EnableWindow(false);
		break;
	case AND_OPERATION:
	case OR_OPERATION:
		if( formulas->size() > 0 )
		{
			m_ButtonOK.EnableWindow(true);
			m_ListBoxDestination1.EnableWindow(true);
			m_ListBoxSource.EnableWindow(true);
			m_ListBoxDestination2.EnableWindow(true);
		}
		else
		{
			m_ButtonOK.EnableWindow(false);
			m_ListBoxDestination1.EnableWindow(false);
			m_ListBoxSource.EnableWindow(false);
			m_ListBoxDestination2.EnableWindow(false);
		}
		m_ListBoxDestination2.EnableWindow(false);
		m_CheckApplyForAll.EnableWindow(false);
		m_CheckBinary.EnableWindow(false);
		m_CheckBinary.SetCheck(1);
		m_ButtonAdd1.EnableWindow(false);
		m_ButtonRemove1.EnableWindow(false);
		m_ButtonAddAll1.EnableWindow(false);
		m_ButtonRemoveAll1.EnableWindow(false);
		if (CURRENT_LANG_OF == "rus") {
			if (operation == AND_OPERATION)
				tstr = _T("Операция объединения <Symbol=/and>");
			else
				tstr = _T("Операция объединения <Symbol=/or>");
		}
		else {
			if (operation == AND_OPERATION)
				tstr = _T("The merge operation <Symbol=/and>");
			else
				tstr = _T("The merge operation <Symbol=/or>");
		}
		
		m_StaticDescription.dsi->PrepareSubItemData(tstr);
		m_checkAll2.ShowWindow(SW_SHOW);
		m_checkAll2.EnableWindow(false);
		break;
	default:
		break;
	}
}




//
// обработка нажатия клавиши OK
//
void OperationDlg::OnBnClickedOk()
{
	switch (operation)
	{
	case NEGATIVE_OPERATION:
		if(m_CheckApplyForAll.GetCheck())
		{
			if(formulas->size() > 0)
				negativeAllFormulas(allEntities);
		}
		else
		{
			if(m_checkAll1.GetCheck())
			{
				int item;
				while( (m_ListBoxDestination1.GetCount( ) ) > 0 )
				{
					item = m_ListBoxDestination1.GetTopIndex( );
					if(item >= 0)
					{
						SemanticString * dsi = (SemanticString *) m_ListBoxDestination1.GetItemData(item);
						Formula * f = (Formula *)dsi->formula;
						if(f)
							f->negativeFormula(allEntities);
						m_ListBoxDestination1.DeleteString(item);
						DELETEITEMSTRUCT dis;
						dis.itemID = item;
						m_ListBoxDestination1.DeleteItem(&dis);
					}
				}
			}
			else
			{
				int selected = m_ListBoxDestination1.GetCurSel();
				if(selected >= 0)
				{
					SemanticString * dsi = (SemanticString *) m_ListBoxDestination1.DCU.at(selected);
					Formula * f = (Formula *)dsi->formula;
					if(f)
					{
						Formula * formula = f->negativeFormula(allEntities);
						if (!formula) {
							if (CURRENT_LANG_OF == "rus") {
								MessageBox(_T("Формула с такими же переменными уже существует и не может быть создана"), _T("Предупреждение"), MB_OK);
							}
							else {
								MessageBox(_T("A formula with the same variables already exists and cannot be created"), _T("Warning"), MB_OK);

							}
						}
					}
				}
			}
		}
		break;
	case QUANTIFIER1_OPERATION:
	case QUANTIFIER2_OPERATION:
		if(m_CheckApplyForAll.GetCheck())
		{
			if(formulas->size() > 0)
				quantifierAllFormulas(allEntities, operation);
		}
		else
		{
			int selected = m_ListBoxDestination1.GetCurSel();
			if(selected >= 0)
			{
				SemanticString * dsi = (SemanticString *) m_ListBoxDestination1.DCU.at(selected);
				Formula * f = (Formula *)dsi->formula;
				if(f)
				{
					if ( m_checkAll2.GetCheck() )
					{
						for ( size_t i = 0; i < f->possibleVariables.size(); i++)
						{
							EntityVariable * pev = f->possibleVariables.at(i);
							f->quantifierFormula(allEntities, operation, pev);
						}
					}
					else
					{
						int selected1 = m_ListBoxDestination2.GetCurSel();
						if(selected1 >= 0)
						{
							EntityVariable * pev = f->possibleVariables.at(selected1);
							f->quantifierFormula(allEntities, operation, pev);
						}
					}
				}
			}
		}
		HideFreeVariables();
	break;

	case AND_OPERATION:
	case OR_OPERATION:
		if(m_CheckApplyForAll.GetCheck())
		{
			if(formulas->size() > 0)
				joinAllFormulas(allEntities, operation);
		}
		else
		{
			int selected1 = m_ListBoxDestination1.GetCurSel();
			if ( selected1 >= 0 )
			{
				SemanticString * dsi1 = (SemanticString *) m_ListBoxDestination1.DCU.at(selected1);
				Formula * first = (Formula *)dsi1->formula;
				if ( first != nullptr)
				{
					if ( m_checkAll2.GetCheck() )
					{
						for ( size_t i = 0; i < first->possibleFormulas.size(); i++)
						{
							Formula * second = first->possibleFormulas.at(i);
							if ( second != nullptr )
							{
								Formula * formula = joinFormula(allEntities, operation, first, second);
								if ( formula != nullptr )
									allEntities->push_back(formula);
							}
						}
					}
					else
					{
						int selected2 = m_ListBoxDestination2.GetCurSel();
						if(selected2 >= 0)
						{
							SemanticString * dsi2 = (SemanticString *) m_ListBoxDestination2.DCU.at(selected2);
							Formula * second = (Formula *)dsi2->formula;
							if ( second != nullptr )
							{
								Formula * formula = joinFormula(allEntities, operation, first, second);
								if ( formula != nullptr )
									allEntities->push_back(formula);
							}
						}
					}
				}
			}
		}
		HideCandidates();
		break;
	default:
		break;
	}
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
}

// перенос выбранной формулы из окна всех формул в список тех, над которыми будут производиться унарные операции
void OperationDlg::OnBnClickedMfcbutton1()
{
	bool bRepaintVars = false;
	if(m_ListBoxDestination1.GetCount( ) < 1)
	{
		bRepaintVars = true;
	}
	MoveSelected(m_ListBoxSource, m_ListBoxDestination1);
	if(m_ListBoxSource.GetCount( ) < 1)
	{
		m_ButtonAdd1.EnableWindow(false);
		m_ButtonAddAll1.EnableWindow(false);
	}
	if(m_ListBoxDestination1.GetCount( ) > 0)
	{
		m_ButtonRemove1.EnableWindow(true);
		m_ButtonRemoveAll1.EnableWindow(true);
		m_ButtonOK.EnableWindow(true);
		if ( ( operation == QUANTIFIER1_OPERATION) || ( operation == QUANTIFIER2_OPERATION ) )
		{
			if(bRepaintVars)
			{
				m_ListBoxDestination1.SetCurSel(0);
				ShowFreeVariables();
			}
		}
		else if ( ( operation == AND_OPERATION) || ( operation == OR_OPERATION ) )
		{
			if(bRepaintVars)
			{
				m_ListBoxDestination1.SetCurSel(0);
				ShowCandidates();
			}
		}
		else if ( operation == NEGATIVE_OPERATION )
		{
			if(bRepaintVars)
			{
				m_ListBoxDestination1.SetCurSel(0);
				m_checkAll1.EnableWindow(true);
			}
		}
	}
	// TODO: добавьте свой код обработчика уведомлений
}

// перенос всех формул из окна всех формул в список тех, над которыми будут производиться унарные операции
void OperationDlg::OnBnClickedMfcbutton5()
{
	bool bRepaintVars = false;
	if(m_ListBoxDestination1.GetCount( ) < 1)
	{
		bRepaintVars = true;
	}
	MoveAll(m_ListBoxSource, m_ListBoxDestination1);
	m_ButtonAdd1.EnableWindow(false);
	m_ButtonAddAll1.EnableWindow(false);
	m_ButtonRemove1.EnableWindow(true);
	m_ButtonRemoveAll1.EnableWindow(true);
	m_ButtonOK.EnableWindow(true);
	if ( ( operation == QUANTIFIER1_OPERATION) || ( operation == QUANTIFIER2_OPERATION ) )
	{
		if(bRepaintVars)
		{
			m_ListBoxDestination1.SetCurSel(0);
			ShowFreeVariables();
		}
	}
	else if ( ( operation == AND_OPERATION) || ( operation == OR_OPERATION ) )
	{
		if(bRepaintVars)
		{
			m_ListBoxDestination1.SetCurSel(0);
			ShowCandidates();
		}

	}
	else if ( operation == NEGATIVE_OPERATION )
	{
		if(bRepaintVars)
		{
			m_ButtonOK.EnableWindow(true);
			m_ListBoxDestination1.SetCurSel(0);
			m_checkAll1.EnableWindow(true);
			m_checkAll1.SetCheck(0);		
		}
	}


	// TODO: добавьте свой код обработчика уведомлений
}

// обратный перенос выбранной формулы из списка тех, над которыми будут производиться унарные операции, в окно всех формул
void OperationDlg::OnBnClickedMfcbutton2()
{
	MoveSelected(m_ListBoxDestination1, m_ListBoxSource);
	if(m_ListBoxDestination1.GetCount( ) < 1)
	{
		if ( ( operation == QUANTIFIER1_OPERATION) || ( operation == QUANTIFIER2_OPERATION ) )
		{
			HideFreeVariables();
		}
		else if ( ( operation == AND_OPERATION) || ( operation == OR_OPERATION ) )
		{
			HideCandidates();
		}
		else if ( operation == NEGATIVE_OPERATION )
		{
			m_ButtonOK.EnableWindow(true);
			m_checkAll1.EnableWindow(false);
			m_checkAll1.SetCheck(0);		
		}
		m_ButtonRemove1.EnableWindow(false);
		m_ButtonRemoveAll1.EnableWindow(false);
	}
	m_ButtonAdd1.EnableWindow(true);
	m_ButtonAddAll1.EnableWindow(true);
	// TODO: добавьте свой код обработчика уведомлений
}

// функция переноса выбранного элемента из одного листбокса в другой
void OperationDlg::MoveSelected(ScientificListBox &Source, ScientificListBox &Destination)
{
	int item = Source.GetCurSel();
	if(item != LB_ERR)
	{
		SemanticString * dsi = (SemanticString *) Source.GetItemData(item);
		CString cs;
		Source.GetText(item, cs);
		Source.DeleteString(item);
		DELETEITEMSTRUCT dis;
		dis.itemID = item;
		Source.DeleteItem(&dis);
		for( auto it = Source.DCU.begin(); it != Source.DCU.end(); ++it)
		{
			if(*it == dsi)
			{
				Source.DCU.erase(it);
				break;
			}
		}
		item = Destination.DCU.size();
		Destination.InsertString(item,cs);
		Destination.SetItemData(item, (DWORD_PTR) dsi);
		Destination.SetItemHeight(item, 30);
		Destination.DCU.push_back(dsi);
	}
}

// функции переноса всего списка из одного листбокса в другой
void OperationDlg::MoveAll(ScientificListBox &Source, ScientificListBox &Destination)
{
	int item;
	while( (Source.GetCount( ) ) > 0 )
	{
		item = Source.GetTopIndex( );
		SemanticString * dsi = (SemanticString *) Source.GetItemData(item);
		CString cs;
		Source.GetText(item, cs);	
		Source.DeleteString(item);
		DELETEITEMSTRUCT dis;
		dis.itemID = item;
		Source.DeleteItem(&dis);
		int new_item = Destination.DCU.size(); 
		Destination.DCU.push_back(dsi);
		Destination.InsertString(new_item,cs);
		Destination.SetItemData(new_item, (DWORD_PTR) dsi);
		Destination.SetItemHeight(new_item, 30);
	}
	Source.DCU.clear();
}


// обратный перенос всех формул из списка тех, над которыми будут производиться унарные операции, в окно всех формул 
void OperationDlg::OnBnClickedMfcbutton6()
{
	MoveAll(m_ListBoxDestination1 ,m_ListBoxSource);
	m_ButtonAdd1.EnableWindow(true);
	m_ButtonAddAll1.EnableWindow(true);
	m_ButtonRemove1.EnableWindow(false);
	m_ButtonRemoveAll1.EnableWindow(false);
	if ( ( operation == QUANTIFIER1_OPERATION) || ( operation == QUANTIFIER2_OPERATION ) )
	{
		HideFreeVariables();
	}
	else if ( ( operation == AND_OPERATION) || ( operation == OR_OPERATION ) )
	{
		HideCandidates();
	}
	else if ( operation == NEGATIVE_OPERATION )
	{
		m_checkAll1.EnableWindow(false);
	}
	// TODO: добавьте свой код обработчика уведомлений
}

void OperationDlg::ShowFreeVariables()
{
	int selected = m_ListBoxDestination1.GetCurSel();
	if( selected >= 0 )
	{
		SemanticString * dsi = m_ListBoxDestination1.DCU.at(selected);
		Formula * f = (Formula *)dsi->formula;
		for (size_t i = 0; i < f->possibleVariables.size(); i++)
		{
			CString str;
			// вставляем в листбокс строку с порядковым номером
			str.Format(_T("%d"), i);
			m_ListBoxDestination2.InsertString(i,str);
			m_ListBoxDestination2.SetItemHeight(i, 30);
			SemanticString * dsi1 = new SemanticString;
			m_ListBoxDestination2.DCU.push_back(dsi1);
			dsi1->PrepareSubItemData(*(f->possibleVariables.at(i)->GetText()));
			m_ListBoxDestination2.SetItemData(i, (DWORD_PTR)dsi1);
			if(i == 0)
			{
				m_ButtonOK.EnableWindow(true);
				m_ListBoxDestination2.EnableWindow(true);
				m_checkAll2.EnableWindow(true);
			}
		}
		m_ListBoxDestination2.SetCurSel(0);
	}
}

void OperationDlg::HideFreeVariables()
{
	int item;
	while( (m_ListBoxDestination2.GetCount( ) ) > 0 )
	{
		item = m_ListBoxDestination2.GetTopIndex( );
		SemanticString * dsi = (SemanticString *) m_ListBoxDestination2.GetItemData(item);
		CString cs;
		m_ListBoxDestination2.GetText(item, cs);	
		m_ListBoxDestination2.DeleteString(item);
		DELETEITEMSTRUCT dis;
		dis.itemID = item;
		m_ListBoxDestination2.DeleteItem(&dis);
	}
	m_ListBoxDestination2.DCU.clear();
	m_checkAll2.EnableWindow(false);
	m_checkAll2.SetCheck(0);
}


void OperationDlg::OnSelchangeListdest1()
{
	if ( ( operation == QUANTIFIER1_OPERATION) || ( operation == QUANTIFIER2_OPERATION ) )
	{
		HideFreeVariables();
		ShowFreeVariables();
	}
	else if ( ( operation == AND_OPERATION) || ( operation == OR_OPERATION ) )
	{
		HideCandidates();
		ShowCandidates();
	}
	// TODO: добавьте свой код обработчика уведомлений
}

//
//  функция заполняет окно для правых функций в бинарных операциях объединения
//
void OperationDlg::ShowCandidates()
{
	int selected = m_ListBoxDestination1.GetCurSel();
	if( selected >= 0 )
	{
		SemanticString * dsi = m_ListBoxDestination1.DCU.at(selected);
		Formula * first = (Formula *)dsi->formula;
		for (size_t i = 0; i < first->possibleFormulas.size(); i++)
		{
			CString str;
			Formula * icurr = first->possibleFormulas.at(i);
			// вставляем в листбокс строку с порядковым номером
			str.Format(_T("%d"), i);
			m_ListBoxDestination2.InsertString(i,str);
//			m_ListBoxDestination2.AddString(str);
			m_ListBoxDestination2.SetItemHeight(i, 30);
			SemanticString * dsi1 = new SemanticString;
			m_ListBoxDestination2.DCU.push_back(dsi1);
			dsi1->PrepareSubItemData(icurr->getText());
			dsi1->formula = icurr;
			m_ListBoxDestination2.SetItemData(i, (DWORD_PTR)dsi);
			if(i == 0)
			{
				m_ButtonOK.EnableWindow(true);
				m_ListBoxDestination2.EnableWindow(true);
				m_checkAll2.EnableWindow(true);
			}
		}
		m_ListBoxDestination2.SetCurSel(0);
	}
}

//
//  функция очищает окно для правых функций в бинарных операциях объединения
//
void OperationDlg::HideCandidates()
{
	int item;
	while( (m_ListBoxDestination2.GetCount( ) ) > 0 )
	{
		item = m_ListBoxDestination2.GetTopIndex( );
		SemanticString * dsi = (SemanticString *) m_ListBoxDestination2.GetItemData(item);
		CString cs;
		m_ListBoxDestination2.GetText(item, cs);	
		m_ListBoxDestination2.DeleteString(item);
		DELETEITEMSTRUCT dis;
		dis.itemID = item;
		m_ListBoxDestination2.DeleteItem(&dis);
	}
	m_ListBoxDestination2.DCU.clear();
	m_checkAll2.EnableWindow(false);
	m_checkAll2.SetCheck(0);
}

void OperationDlg::OnStnClickedStatic1()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void OperationDlg::OnBnClickedCheckall1()
{
	// TODO: добавьте свой код обработчика уведомлений
}
