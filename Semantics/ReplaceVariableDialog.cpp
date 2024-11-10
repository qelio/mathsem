// ReplaceVariableDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "Semantics.h"
#include "ReplaceVariableDialog.h"
#include "SummaryDialog.h"
#include "afxdialogex.h"




//



// диалоговое окно ReplaceVariableDialog

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
// метод отображает свободные переменные в элементе m_listFreeVariables для выбранного элемента в списке формул
//
void ReplaceVariableDialog::ShowFreeVariables()
{
	int selected = m_list.GetCurSel();     // получаю номер выделенной формулы (связанного с формулой элемента)
	if( selected >= 0 )     //если выделена 
	{
		SemanticString * dsi = m_list.DCU.at(selected);    // получаю указатель на SemanticString, связанную с указанной формулой
//		Formula * f = dsi->formula;     // из SemanticString получаю указатель на саму формулу
//		vector <EntityVariable *> * freeVariables = f->getFreeVariables();   // указатель на свободные переменные формулы
		EntityBase * peb = dsi->formula;;     // из SemanticString получаю указатель на саму формулу
//		EntityBase * peb = entities->at(selected);     // из SemanticString получаю указатель на саму формулу
		vector <EntityVariable *> * freeVariables = peb->getFreeVariables();   // указатель на свободные переменные формулы
		vector <EntityVariable *> * linkedVariables = peb->getLinkedVariables();   // указатель на связанные переменные формулы
		vector <EntityVariable *> allVariables(*freeVariables);
		allVariables.insert(allVariables.end(), linkedVariables->begin(), linkedVariables->end());
		for (size_t i = 0; i < allVariables.size(); i++)     // перебор по всем, свободным и связанным, переменным
		{
			CString str;
			// вставляем в листбокс строку с порядковым номером
			str.Format(_T("%d"), i);
			m_listFreeVariables.InsertString(i,str);
			m_listFreeVariables.SetItemHeight(i, 30);
			// готовлю обьект SemanticString для очередной свободной переменной во второй элемент-список
			SemanticString * dsi1 = new SemanticString;
			m_listFreeVariables.DCU.push_back(dsi1);
			dsi1->PrepareSubItemData(*(allVariables.at(i)->GetText()));
			m_listFreeVariables.SetItemData(i, (DWORD_PTR)dsi1);     // добавляю 
			if(i == 0)     // если первая (то есть хотя бы одна свободная формула)
			{
				m_buttonOK.EnableWindow(true);    // делаю доступным кнопку "OK"
				m_listFreeVariables.EnableWindow(true);    // делаю доступным окно
			}
		}
		m_listFreeVariables.SetCurSel(0);    // устанавливаю выбранным первый элемент
		int selected = m_listFreeVariables.GetCurSel();     // получаю номер выделенной формулы (связанного с формулой элемента)
		if( selected >= 0 )     //если выделена 
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
// метод удаляет свободные переменные из элемента m_listFreeVariables
//
void ReplaceVariableDialog::HideFreeVariables()
{
	int item;
	while( (m_listFreeVariables.GetCount( ) ) > 0 )   // пока в списке свободных переменных остаётся хотя бы один элемент
	{
		item = m_listFreeVariables.GetTopIndex( );    // получаем индекс верхнего элемента
		SemanticString * dsi = (SemanticString *) m_listFreeVariables.GetItemData(item);    // излишняя строка
		CString cs;
		m_listFreeVariables.GetText(item, cs);	   // получаем строку, соответствующюю верхнему элементу, кажется, тоже излишняя строка
		m_listFreeVariables.DeleteString(item);    //  удаляем из окна-списка строку для элемента с индексом item
		DELETEITEMSTRUCT dis;                  // структура для удаления самого элемента 
		dis.itemID = item;                     
		m_listFreeVariables.DeleteItem(&dis);      // удаляем весь элемент полностью
	}
	m_listFreeVariables.DCU.clear();               // очищаем контейнер отображаемых SemanticString
	m_buttonOK.EnableWindow(false);            // делаю окно неактивным
	m_listFreeVariables.EnableWindow(false); 
	m_listFreeVariables.EnableWindow(false);
	GetDlgItem(IDC_RADIOINPUTTEXT)->EnableWindow(false);
	GetDlgItem(IDC_RADIOSELECTVARIABLE)->EnableWindow(false);
	m_comboName.EnableWindow(false);
	m_editIndex.EnableWindow(false);
}


//
// устанавливает значения и свойства диалога и его элементов при инициализации
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
	for (size_t i = 0; i < entities->size(); i++)    // перебор по всем сущностям схемы
	{
		bool toProccess = true;     // флаг 
		EntityBase * base = entities->at(i);    // указатель на очередную сущность
//		if(base->getType() == REPLACE_VARIABLE)
//			continue;
//		if ( !base->isFormula() )       // если сущность не формула
//			continue;     // переходим к другой
		vector <EntityVariable *> * fv = base->getFreeVariables();    // указатель на контейнер свободных переменных сущности
		vector <EntityVariable *> * plv = base->getLinkedVariables();    // указатель на контейнер свободных переменных сущности
		if ( (fv->size() + plv->size()) == 0)     // если нет свободных переменных
			continue;     // переходим к следующей сущности
		Formula * icurr = (Formula *)base;    // указатель на объект класса Formula
/*
этот блок раньше исключал из попадания в список формул-кандидатов для составления множеств истинности
но это было до того, как я начала фомрировать множества и на основе кортежей
		if ( icurr->formulasetCandidate(entities) == nullptr )
			continue;
*/
		// вставляем в листбокс строку с порядковым номером
		str.Format(_T("%d"), count);
		m_list.AddString(str);
		m_list.SetItemHeight(count, 30);
		SemanticString * dsi = new SemanticString;
		m_list.DCU.push_back(dsi);
		dsi->PrepareSubItemData(icurr->getText());
		dsi->formula = base;
		m_list.SetItemData(count, (DWORD_PTR)dsi);   // устанавливаем полученную SemanticString в качестве 
	}
	// TODO:  Добавить дополнительную инициализацию
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
	// TODO:  Добавить дополнительную инициализацию

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
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



// обработчики сообщений ReplaceVariableDialog


void ReplaceVariableDialog::OnBnClickedOk()
{
	bool result = false;
	TCHAR * tbuf = nullptr;
	TCHAR * tbuf1 = nullptr;
	EntityVariable * pev1 = nullptr;
	int selected = m_list.GetCurSel();     // получаю номер выделенной формулы (связанного с формулой элемента)
	if( selected >= 0 )     //если выделена 
	{
		SemanticString * dsi = m_list.DCU.at(selected);    // получаю указатель на SemanticString, связанную с указанной формулой
		EntityBase * peb = dsi->formula;		
//		EntityBase * peb = entities->at(selected);
//		Formula * f = dsi->formula;     // из SemanticString получаю указатель на саму формулу
		vector <EntityVariable *> * freeVariables = peb->getFreeVariables();   // указатель на свободные переменные формулы
		//добавлен блок для всех, в том числе и связаннх переменных
		vector <EntityVariable *> * linkedVariables = peb->getLinkedVariables();   // указатель на связанные переменные формулы
		vector <EntityVariable *> allVariables(*freeVariables);
		allVariables.insert(allVariables.end(), linkedVariables->begin(), linkedVariables->end());
		// здесь этот блок заканчивается
		int nIndex1 = m_listFreeVariables.GetCurSel();    // получаю индекс выбранной свободной переменной
		int nCount1 = m_listFreeVariables.GetCount();    // получаю количество свободных переменных
		if ((nIndex1 != CB_ERR) && (nCount1 > 0))    // если свободная переменная выбрана
		{
//			EntityVariable * pselVariable = freeVariables->at(nIndex1);
			EntityVariable * pselVariable = allVariables.at(nIndex1);
			{
				if(m_dataRadio == 1) // если  выбрана замена вводом новой переменной
				{
					int nIndex = m_comboName.GetCurSel();    // получаю индекс выбранного элемента для обозначения переменной
					int nCount = m_comboName.GetCount();    // получаю количество элементов всписке обозначений переменной
					if ((nIndex != CB_ERR) && (nCount > 0))    // если выбран
					{
						int len = m_comboName.GetLBTextLen(nIndex);    // длина текста элемента
						tbuf = new TCHAR[len + 2];    // создаю буфер для хранения текста переменной
						m_comboName.GetLBText(nIndex, (LPTSTR)tbuf);    // сохраняю текст переменной в созданный буфер
						len = m_editIndex.GetWindowTextLengthW();    // длина текста элемента
						if(len > 0)
						{
							tbuf1 = new TCHAR[len + 2];    // создаю буфер для хранения текста переменной
							m_editIndex.GetWindowTextT(tbuf1, len + 1);    // сохраняю текст индекса переменной в созданный буфер
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
										AfxMessageBox(_T("Индекс для замены переменной не целое положительное число"));
									else
										AfxMessageBox(_T("The index to replace the variable is not a positive integer"));
									m_editIndex.SetFocus();
								}
							}
							else
							{
								if (CURRENT_LANG_OF == "rus")
									AfxMessageBox(_T("Не указан индекс для замены переменной"));
								else 
									AfxMessageBox(_T("The index for replacing the variable is not specified"));
								m_editIndex.SetFocus();
							}
						}
						else
						{
							if (CURRENT_LANG_OF == "rus")
								AfxMessageBox(_T("Не указан индекс для замены переменной"));
							else
								AfxMessageBox(_T("The index for replacing the variable is not specified"));
							m_editIndex.SetFocus();
						}
					}
					else
					{
						if (CURRENT_LANG_OF == "rus")
							AfxMessageBox(_T("Не выбрано обозначение для замены переменной"));
						else 
							AfxMessageBox(_T("The designation for replacing the variable is not selected"));
						m_comboName.SetFocus();
					}
				}
				else // если переменная для замены выбирается из списка
				{
					int nIndex = m_listVariables.GetCurSel();    // получаю индекс выбранного элемента для обозначения переменной
					int nCount = m_listVariables.GetCount();    // получаю количество элементов всписке обозначений переменной
					if ((nIndex != CB_ERR) && (nCount > 0))    // если выбран
					{
						pev1 = new EntityVariable(*pev_new.at(nIndex));
						result = true;
					}
					else
					{
						if (CURRENT_LANG_OF == "rus")
							AfxMessageBox(_T("Не выбрана переменная для замены"));
						else
							AfxMessageBox(_T("A replacement variable has not been selected"));
						m_listVariables.SetFocus();
					}
				}
			}
			if(result)
			{				
				EntityVariable * pev = new EntityVariable(*pselVariable);
				if( (tbuf != nullptr) && (tbuf1 != nullptr) ) // излишняя проверка
				{
					tstring tstr = tbuf;
					tstring tstr_index = tbuf1;
					trimWhitespaces(&tstr_index);
					pev1 = new EntityVariable(tstr, tstr_index, VARIABLE);
					pev1->SetLevel(pselVariable->GetLevel());
				}
				// проверка на то, вчтречается ли уже такое переобозначение
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
				if(!is_exist) // если такое же переобозначение еще не создано в схеме
				{
					if(!pev1->compare(*pselVariable))
					{
						SetGroup sg = peb->isPartOfSetGroup(entities);
						EntityBase * peb_first = get<0>(sg);
						int count_objs = get<1>(sg);
						tstring caps = * pselVariable->GetText();
						caps[0] = toupper(caps[0]);
						if((peb_first == nullptr) || (*(pselVariable->GetText()) != caps)) // если заменемый обьект не создан с группой множества истинности
						{
							addReplacingFormula(entities, peb, pev, pev1);
						}
						else
						{	
							// надо проверить на то, какая переменная заменяется и в зависимости добавить от 2 до 4 обьектов
							// заменяемая переменная не может быть обозначением множества истинности, это ограничили уже раньше, теперь надо проверить,
							// что заменяемая переменная является подмножество, созданнм в группе обьектов, созданным в диалоге создания множества истинности
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
первоначальный блок для полного переопределения
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
							AfxMessageBox(_T("Обозначения заменяемой и переменной для замены совпадают"));
						else
							AfxMessageBox(_T("The designations of the replaced and the variable to replace are the same"));
						m_listFreeVariables.SetFocus();						
					}
				}
				else
				{
					result = false;
					if (CURRENT_LANG_OF == "rus")
						AfxMessageBox(_T("Такое переобозначение переменной уже существует"));
					else
						AfxMessageBox(_T("Such a reinvention of the variable already exists"));
					m_listFreeVariables.SetFocus();
				}
			}
		}
		else
		{
			if (CURRENT_LANG_OF == "rus")
				AfxMessageBox(_T("Не выбрана свободная переменная"));
			else
				AfxMessageBox(_T("A free variable is not selected"));
			m_listFreeVariables.SetFocus();
		}			
	}
	else
	{
		if (CURRENT_LANG_OF == "rus")
			AfxMessageBox(_T("Не выбрана формула"));
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
	// TODO: добавьте свой код обработчика уведомлений
	if(result)
		CDialogEx::OnOK();
}


void ReplaceVariableDialog::OnSelchangeSetlist1()
{
	HideVariables();   // очищает список переменных, которыми можно заменить
	HideFreeVariables();    // удаляет переменные, если есть, из окна-списка свободных переменных
	ShowFreeVariables();    // заполняет окно-список свободных переменных в зависимости от выбранной формулы
	ShowVariables();
	// TODO: добавьте свой код обработчика уведомлений
}


void ReplaceVariableDialog::OnSelchangeSetlist2()
{
	int selected1 = m_listFreeVariables.GetCurSel();     // получаю номер выделенной формулы (связанного с формулой элемента)
	int nCount1 = m_listFreeVariables.GetCount();    // получаю количество свободных переменных
	int selected = m_list.GetCurSel();     // получаю номер выделенной формулы (связанного с формулой элемента)
	int nCount = m_list.GetCount();    // получаю количество свободных переменных
	if( (selected >= 0) && (nCount >= 1) && (selected1 >= 0) && (nCount1 >= 1))     //если выделена 
	{
		GetDlgItem(IDC_RADIOINPUTTEXT)->EnableWindow(true);
		GetDlgItem(IDC_RADIOSELECTVARIABLE)->EnableWindow(true);
		SemanticString * dsi = m_list.DCU.at(selected);    // получаю указатель на SemanticString, связанную с указанной формулой
		EntityBase * peb = dsi->formula;		
//		EntityBase * peb = entities->at(selected);
		vector <EntityVariable *> * freeVariables = peb->getFreeVariables();   // указатель на свободные переменные формулы
		//добавлен блок для всех, в том числе и связаннх переменных
		vector <EntityVariable *> * linkedVariables = peb->getLinkedVariables();   // указатель на связанные переменные формулы
		vector <EntityVariable *> allVariables(*freeVariables);
		allVariables.insert(allVariables.end(), linkedVariables->begin(), linkedVariables->end());
		EntityVariable * pselVariable = allVariables.at(selected1);
//		EntityVariable * pselVariable = freeVariables->at(selected1);
		// здесь этот блок заканчивается
		tstring var = *pselVariable->GetText();
		TCHAR symbol = var.at(0);
		ResetComboNames(symbol);
		m_comboName.EnableWindow(true);
		m_editIndex.EnableWindow(true);
		m_listVariables.EnableWindow(false);
		HideVariables();
		ShowVariables();

//		m_listVariables.EnableWindow(true);    // делаю доступным окно
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
	// TODO: добавьте свой код обработчика уведомлений
}

// заменяю список обозначений в комбобоксе на заглавные или прописные, в зависимости от того, заглавный или прописной символ, передаваемый параметром функции
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
	// TODO: добавьте свой код обработчика уведомлений
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
	// TODO: добавьте свой код обработчика уведомлений
}

// метод удаляет свободные переменные из элемента m_listVariables 
void ReplaceVariableDialog::HideVariables()
{
		// блок очистки листбокса переменных на замену
	CString str;
	int item;
	pev_new.clear();
	while( (m_listVariables.GetCount( ) ) > 0 )   // пока в списке свободных переменных остаётся хотя бы один элемент
	{
		item = m_listVariables.GetTopIndex( );    // получаем индекс верхнего элемента
		SemanticString * dsi = (SemanticString *) m_listVariables.GetItemData(item);    // излишняя строка
		CString cs;
		m_listVariables.GetText(item, cs);	   // получаем строку, соответствующюю верхнему элементу, кажется, тоже излишняя строка
		m_listVariables.DeleteString(item);    //  удаляем из окна-списка строку для элемента с индексом item
		DELETEITEMSTRUCT dis;                  // структура для удаления самого элемента 
		dis.itemID = item;                     
		m_listVariables.DeleteItem(&dis);      // удаляем весь элемент полностью
	}
	m_listVariables.DCU.clear();               // очищаем контейнер отображаемых SemanticString
	// завершили очистку списка переменных на замену
}

// метод отображает переменные, которыми можно заменить, в элементе m_listVariables для выбранного элемента в списке свободных (заменяемых) переменных
void ReplaceVariableDialog::ShowVariables()
{
	CString str;
	// блок подбора переменных для замены
	pev_new.clear();
	int selected = m_list.GetCurSel();     // получаю номер выделенной формулы (связанного с формулой элемента)
	if( selected >= 0 )     //если выделена 
	{
		SemanticString * dsi = m_list.DCU.at(selected);    // получаю указатель на SemanticString, связанную с указанной формулой
		EntityBase * peb = dsi->formula;		
//		EntityBase * peb = entities->at(selected);
//		Formula * f = dsi->formula;     // из SemanticString получаю указатель на саму формулу
		vector <EntityVariable *> * freeVariables = peb->getFreeVariables();   // указатель на заменяемые переменные формулы
		//добавлен блок для всех, в том числе и связаннх переменных
		vector <EntityVariable *> * linkedVariables = peb->getLinkedVariables();   // указатель на связанные переменные формулы
		vector <EntityVariable *> allVariables(*freeVariables);
		allVariables.insert(allVariables.end(), linkedVariables->begin(), linkedVariables->end());
		vector <EntityVariable *> allVariables1;
		int nIndex1 = m_listFreeVariables.GetCurSel();    // получаю индекс выбранной заменяемой переменной
		int nCount1 = m_listFreeVariables.GetCount();    // получаю количество заменяемых переменных
		if ((nIndex1 != CB_ERR) && (nCount1 > 0))    // если свободная переменная выбрана
		{
//			EntityVariable * pselVariable = freeVariables->at(nIndex1);
			EntityVariable * pselVariable = allVariables.at(nIndex1);
			Level * pl = (Level *)pselVariable;
			for(size_t i = 0; i < entities->size(); i++)
			{
				vector <EntityVariable *> * pevs = entities->at(i)->getFreeVariables();
				//добавлен блок для всех, в том числе и связаннх переменных
				vector <EntityVariable *> * linkedVariables1 = entities->at(i)->getLinkedVariables();   // указатель на связанные переменные формулы
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
ну не работает binary_search по перебору указателей с начала, хоть тресни. а должен!
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
	// конец блока подбора переменных для замены

	// заполняем подобранными переменными листбокс
	for(size_t i = 0; i < pev_new.size(); i++)
	{
			// вставляем в листбокс строку с порядковым номером
			str.Format(_T("%d"), i);
			m_listVariables.InsertString(i,str);
			m_listVariables.SetItemHeight(i, 30);
			// готовлю обьект SemanticString для очередной свободной переменной во второй элемент-список
			SemanticString * dsi1 = new SemanticString;
			m_listVariables.DCU.push_back(dsi1);
			// здесь проверка для переобозначенных переменных, используется для переобозначенных множеств истинности
			tstring redefinition = pev_new.at(i)->GetRedefinition();
			if(redefinition.length() >  0)
				dsi1->PrepareSubItemData(pev_new.at(i)->GetRedefinition());
			else
				dsi1->PrepareSubItemData(*(pev_new.at(i)->GetText()));
			m_listVariables.SetItemData(i, (DWORD_PTR)dsi1);     // добавляю 
			if(i == 0)     // если первая (то есть хотя бы одна свободная формула)
			{
				m_buttonOK.EnableWindow(true);    // делаю доступным кнопку "OK"
				m_listVariables.EnableWindow(true);    // делаю доступным окно
			}

		m_listVariables.SetCurSel(0);    // устанавливаю выбранным первый элемент
	}
}
