// FromSetDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "Semantics.h"
#include "FromSetDialog.h"
#include "afxdialogex.h"


//TRANSLATED



// диалоговое окно FromSetDialog

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


// обработчики сообщений FromSetDialog


void FromSetDialog::OnLbnSelchangeSetlist1()
{
	int selected = m_ListBoxSource.GetCurSel();     // получаю номер выделенной формулы (связанного с формулой элемента)
	if( selected >= 0 )     //если выделена 
	{
		m_ButtonOK.EnableWindow(true);    // делаю доступным кнопку "OK"
	}
	else
	{
		m_ButtonOK.EnableWindow(false);    // делаю доступным кнопку "OK"
	}
	// TODO: добавьте свой код обработчика уведомлений
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
		// вставляем в листбокс строку с порядковым номером
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
		SemanticString * dsi1 = (SemanticString *) m_list.DCU.at(selected1);    // получаем указатель на SemanticString, связанную с выбранным элементом
		Formula * formula = dsi1->formula;    // берём указатель на обьект Formula для текущего объекта SemnticString
		if ( formula != nullptr)    // проверка на то, что указатель не нулевой (избыточная проверка)
		{
			// Get the indexes of all the selected items.
			int nCount = m_listVariables.GetSelCount();    // проверяем, сколько свободных переменных выбрано
			if(nCount > 0)    // если выбрана хотя бы одна
			{
				vector <EntityVariable *> * variables = new vector <EntityVariable *>;


				CArray<int,int> aryListBoxSel;    // контейнер для выбранных элементов списка свободных переменных
				aryListBoxSel.SetSize(nCount);    // устанавливаем размер контейнера, равным числу выбранных свободных переменных
				m_listVariables.GetSelItems(nCount, aryListBoxSel.GetData());     // заполняем контейнер
				int pt;
				// перебор по выбранным свободным переменным
				for (int i = 0; i <= aryListBoxSel.GetUpperBound(); i++)
				{
					pt = aryListBoxSel.GetAt(i);    // получаю номер очередного элемента, соответствующего очередной выбранной свободной переменной
					vector <EntityVariable *> * fv = formula->getFreeVariables(); 
					variables->push_back(fv->at(pt)); // добавляем в вектор переменных, по которым строим множество истинности
				}
				// проверка, построено ли раньше такое множство истинности, на основе той же формулы и тех же наборов переменных
				bool isExist = false;
				for (size_t i = 0; i < entities->size(); i++) // перебор всех созданных сущностей
				{
					bool toProccess = false;
					EntityBase * base = entities->at(i);     // указатель на очередную сущность
					if ( base->isFormula() ) // если очередная сущность формула, то переходим к следующей сущности
						continue;
					FormulaSet * baseFS = (FormulaSet *)base;    // указатель на множество истинности
					if (formula == baseFS->getParentFormula()) // если родительская формула для очередной сущности совпадает с выбранной формулой, 
					// по которой построим множество истинности
					{
						// проверка, что совпадают наборы свободных переменных для этих двух формул ( возможно, избыточная проверка)
						vector <EntityVariable *> * fv_base = base->getFreeVariables();
						vector <EntityVariable *> * fv_formula = formula->getFreeVariables();
						if ( fv_base->size() == fv_formula->size() ) // только если размеры наборов свободных переменных совпадают
						{
							bool isFoundFVAll = false;
							for (size_t i1 = 0; i1 < fv_base->size(); i1++)    // перебор по всем свободным переменным очередной сущности
							{
								EntityVariable * pev = fv_base->at(i1);    
								bool isFoundFV = false;
								for (size_t i2 = 0; i2 < fv_formula->size(); i2++)    // вложенный цикл по свободным переменным формулы
								{
									if ( pev->compare(*fv_formula->at(i2)))     // если сопадают
									{
										isFoundFV = true;
										break;
									}
								}
								if ( isFoundFV )
								{
									isFoundFVAll = true;    // по всей видимости, сработает даже только при одной совпадающей переменной, но и вся проверка,
									// возможно, является избыточной
									break;
								}
							}
							if ( isFoundFVAll )
								toProccess = true;
						}
						// проверка, что совпадают наборы базовых переменных будущей сущности и очередной сущности, по которым строятся множества истинности
						vector <EntityVariable *> * bv_base = baseFS->getBaseVariables();
						if ( toProccess && ( bv_base->size() == variables->size() ) ) // только если размеры наборов свободных переменных совпадают
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
				if ( !isExist )     // если не найдено подобного множества истинности
				{
					FormulaSet * pfs = new FormulaSet(formula, variables);    // создаём множество истинности
					pfs->SetLabel(entities);    // формуруем обозначение
					entities->push_back(pfs);   // добавляю созданное множество истинности в схему
				}
				else
					AfxMessageBox(_T("Выберите другой набор переменных, по этому множество истинности уже построено"));
				// пишем обозначение
				delete variables;     // освобождаю память
				if ( !isExist )       // если было создано множество истинности
					CDialogEx::OnOK();    // закрываю диалоговое окно
			}
			else
				AfxMessageBox(_T("Не выбрано ни одной переменной"));

		}
	}
	else
		AfxMessageBox(_T("Не выбрана формула для построения множества истинности"));
*/
}
