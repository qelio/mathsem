//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
// EquivalenceDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "Semantics.h"
#include "EquivalenceDlg.h"
#include "afxdialogex.h"


// диалоговое окно EquivalenceDlg

IMPLEMENT_DYNAMIC(EquivalenceDlg, CDialogEx)

EquivalenceDlg::EquivalenceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(EquivalenceDlg::IDD, pParent)
{
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

EquivalenceDlg::~EquivalenceDlg()
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

void EquivalenceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTSOURCE, m_ListBoxSource);
	DDX_Control(pDX, IDC_LISTDEST1, m_ListBoxDestination1);
	DDX_Control(pDX, IDC_LISTDEST2, m_ListBoxDestination2);
	DDX_Control(pDX, IDC_MFCBUTTON1, m_ButtonAdd1);
	DDX_Control(pDX, IDC_MFCBUTTON2, m_ButtonRemove1);
//	DDX_Control(pDX, IDC_STATIC1, m_StaticDescription);
//	DDX_Control(pDX, IDC_CHECK1, m_CheckApplyForAll);
//	DDX_Control(pDX, IDC_CHECK2, m_CheckBinary);
	DDX_Control(pDX, IDC_MFCBUTTON5, m_ButtonAddAll1);
	DDX_Control(pDX, IDC_MFCBUTTON6, m_ButtonRemoveAll1);
	DDX_Control(pDX, IDOK, m_ButtonOK);
//	DDX_Control(pDX, IDC_CHECKALL1, m_checkAll1);
//	DDX_Control(pDX, IDC_CHECKALL2, m_checkAll2);
}


BEGIN_MESSAGE_MAP(EquivalenceDlg, CDialogEx)
//	ON_BN_CLICKED(IDC_CHECK2, &EquivalenceDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDOK, &EquivalenceDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_MFCBUTTON1, &EquivalenceDlg::OnBnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_MFCBUTTON5, &EquivalenceDlg::OnBnClickedMfcbutton5)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &EquivalenceDlg::OnBnClickedMfcbutton2)
	ON_BN_CLICKED(IDC_MFCBUTTON6, &EquivalenceDlg::OnBnClickedMfcbutton6)
	ON_LBN_SELCHANGE(IDC_LISTDEST1, &EquivalenceDlg::OnSelchangeListdest1)
END_MESSAGE_MAP()





BOOL EquivalenceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
//	SetEquivalenceState();
//	this->m_ListBoxDestination2.SetItemHeight(0, 30);
//	this->m_ListBoxDestination2.set

//	m_ListBoxSource.SetSorting(true);
	CString str;
	int count = 0;
	tstring res;
	tstring res_formula;
	for (size_t i = 0; i < allEntities->size(); i++)
	{
		bool toProccess = true;
		EntityBase * base = allEntities->at(i);
		if ( base->getType() == FORMULA_SET )
			continue;
		Formula * icurr = (Formula *)base;
// здесь пока на время отладки раносильностей комментарим
//#ifdef EQUITYTEST
		icurr = equivalenceCandidate(icurr, allEntities, allEquivalences);
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
			m_ListBoxDestination1.EnableWindow(true);
			m_ListBoxSource.EnableWindow(true);
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



void EquivalenceDlg::SetEquivalenceState()
{
	tstring tstr;
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
		m_ButtonAdd1.EnableWindow(false);
		m_ButtonRemove1.EnableWindow(false);
		m_ButtonAddAll1.EnableWindow(false);
		m_ButtonRemoveAll1.EnableWindow(false);


}




//
// обработка нажатия клавиши OK
//
void EquivalenceDlg::OnBnClickedOk()
{
	int selected1 = m_ListBoxDestination1.GetCurSel();
	if ( selected1 >= 0 )
	{
		SemanticString * dsi1 = (SemanticString *) m_ListBoxDestination1.DCU.at(selected1);
		Formula * first = dsi1->formula;
		if ( first != nullptr)
		{
			int selected2 = m_ListBoxDestination2.GetCurSel();
			if(selected2 >= 0)
			{
				SemanticString * dsi2 = (SemanticString *) m_ListBoxDestination2.DCU.at(selected2);
				Formula * second = dsi2->formula;
				if ( second != nullptr )
				{
					Equivalence *pe = new Equivalence(first, second);
					pe->setFormulasNumbers(allEntities);
					allEquivalences->push_back(pe);
				}
			}
		}
	}

	HideCandidates();

	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
}

// перенос выбранной формулы из окна всех формул в список тех, над которыми будут производиться унарные операции
void EquivalenceDlg::OnBnClickedMfcbutton1()
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
			if(bRepaintVars)
			{
				m_ListBoxDestination1.SetCurSel(0);
				ShowCandidates();
			}
	}
	// TODO: добавьте свой код обработчика уведомлений
}

// перенос всех формул из окна всех формул в список тех, над которыми будут производиться унарные операции
void EquivalenceDlg::OnBnClickedMfcbutton5()
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
	if(bRepaintVars)
	{
		m_ListBoxDestination1.SetCurSel(0);
		ShowCandidates();
	}


	// TODO: добавьте свой код обработчика уведомлений
}

// обратный перенос выбранной формулы из списка тех, над которыми будут производиться унарные операции, в окно всех формул
void EquivalenceDlg::OnBnClickedMfcbutton2()
{
	MoveSelected(m_ListBoxDestination1, m_ListBoxSource);
	if(m_ListBoxDestination1.GetCount( ) < 1)
	{
			HideCandidates();
		m_ButtonRemove1.EnableWindow(false);
		m_ButtonRemoveAll1.EnableWindow(false);
	}
	m_ButtonAdd1.EnableWindow(true);
	m_ButtonAddAll1.EnableWindow(true);
	// TODO: добавьте свой код обработчика уведомлений
}

// функция переноса выбранного элемента из одного листбокса в другой
void EquivalenceDlg::MoveSelected(ScientificListBox &Source, ScientificListBox &Destination)
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
void EquivalenceDlg::MoveAll(ScientificListBox &Source, ScientificListBox &Destination)
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
void EquivalenceDlg::OnBnClickedMfcbutton6()
{
	MoveAll(m_ListBoxDestination1 ,m_ListBoxSource);
	m_ButtonAdd1.EnableWindow(true);
	m_ButtonAddAll1.EnableWindow(true);
	m_ButtonRemove1.EnableWindow(false);
	m_ButtonRemoveAll1.EnableWindow(false);
	HideCandidates();
	// TODO: добавьте свой код обработчика уведомлений
}




void EquivalenceDlg::OnSelchangeListdest1()
{
	HideCandidates();
	ShowCandidates();
	// TODO: добавьте свой код обработчика уведомлений
}

//
//  функция заполняет окно для правых функций в бинарных операциях объединения
//
void EquivalenceDlg::ShowCandidates()
{
	int selected = m_ListBoxDestination1.GetCurSel();
	if( selected >= 0 )
	{
		SemanticString * dsi = m_ListBoxDestination1.DCU.at(selected);
		Formula * first = dsi->formula;
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
			}
		}
		m_ListBoxDestination2.SetCurSel(0);
	}
}

//
//  функция очищает окно для правых функций в бинарных операциях объединения
//
void EquivalenceDlg::HideCandidates()
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
}