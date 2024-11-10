//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
// SetDialog.cpp: файл реализации
//



//TRANSLATED


#include "stdafx.h"
#include "Semantics.h"
#include "SetDialog.h"
#include "afxdialogex.h"
//#include <cmath>




IMPLEMENT_DYNAMIC(SetDialog, CDialogEx)


//
// конструктор
//
SetDialog::SetDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(SetDialog::IDD, pParent)
{
	m_fIndexes = nullptr;
	m_fSymbol = nullptr;
}


//
// деструктор
//
SetDialog::~SetDialog()
{
	// если шрифты установлены (указатели на них не равны nullptr), освободить обьекты
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


// обработчики сообщений SetDialog

//
// обработчик нажатия на кнопку "OK"
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



	int nIndex3 = m_comboSet.GetCurSel();    // получаю индекс выбранного элемента для обозначения переменной
	int nCount3 = m_comboSet.GetCount();    // получаю количество элементов всписке обозначений переменной
	if ((nIndex3 != CB_ERR) && (nCount3 > 1))    // если выбран
	{
		int len3 = m_comboSet.GetLBTextLen(nIndex3);    // длина текста элемента
		tbuf2 = new TCHAR[len3 + 2];    // создаю буфер для хранения текста переменной
		m_comboSet.GetLBText(nIndex3, (LPTSTR)tbuf2);    // сохраняю текст переменной в созданный буфер
		len3 = m_indexSet.GetWindowTextLengthW();    // длина текста индекса переменной
		if(len3)
		{
			tbuf_index2 = new TCHAR[len3 + 2];    // создаю буфер для хранения текста индекса переменной
			m_indexSet.GetWindowTextT(tbuf_index2, len3 + 1);    // сохраняю текст индекса переменной в созданный буфер
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
						AfxMessageBox(_T("Введите другое обозначение множества, это уже используется в схеме."));
					else
						AfxMessageBox(_T("Enter another notation for the set, this is already used in the scheme."));
					setnaming_success = false;
				}
			}
			else
			{
				if (CURRENT_LANG_OF == "rus")
					AfxMessageBox(_T("В индексе множества указано не число"));
				else
					AfxMessageBox(_T("The index of the set does not specify a number"));
				m_indexSet.SetFocus();
				setnaming_success = false;
			}
		}
		else
		{
			if (CURRENT_LANG_OF == "rus")
				AfxMessageBox(_T("Не выбран индекс для построения множества"));
			else
				AfxMessageBox(_T("The index for building the set is not selected"));
			setnaming_success = false;
		}
	}
	else
	{
		if (CURRENT_LANG_OF == "rus")
			AfxMessageBox(_T("Не выбран индекс для построения подмножества"));
		else
			AfxMessageBox(_T("An index has not been selected to build a subset"));
		setnaming_success = false;
	}
	if (setnaming_success)
	{
		int selected1 = m_list.GetCurSel();    // номер выбранной формулы
		if (selected1 != LB_ERR)     // если номер выбранного элемента, возвращённый методом GetCurSel, действителен
		{
			SemanticString* dsi1 = (SemanticString*)m_list.DCU.at(selected1);    // получаем указатель на SemanticString, связанную с выбранным элементом
			Formula* formula = (Formula*)dsi1->formula;    // берём указатель на обьект Formula для текущего объекта SemanticString
			if (formula != nullptr)    // проверка на то, что указатель не нулевой (избыточная проверка)
			{
				// Get the indexes of all the selected items.
				int nCount = m_listVariables.GetSelCount();    // проверяем, сколько свободных переменных выбрано
				if (nCount > 0)    // если выбрана хотя бы одна
				{
					vector <EntityVariable*>* variables = new vector <EntityVariable*>;


					CArray<int, int> aryListBoxSel;    // контейнер для выбранных элементов списка свободных переменных
					aryListBoxSel.SetSize(nCount);    // устанавливаем размер контейнера, равным числу выбранных свободных переменных
					m_listVariables.GetSelItems(nCount, aryListBoxSel.GetData());     // заполняем контейнер
					int pt;
					// перебор по выбранным свободным переменным
					for (int i = 0; i <= aryListBoxSel.GetUpperBound(); i++)
					{
						pt = aryListBoxSel.GetAt(i);    // получаю номер очередного элемента, соответствующего очередной выбранной свободной переменной
						vector <EntityVariable*>* fv = formula->getFreeVariables();
						variables->push_back(fv->at(pt)); // добавляем в вектор переменных, по которым строим множество истинности
					}
					// проверка, построено ли раньше такое множство истинности, на основе той же формулы и тех же наборов переменных
					bool isExist = false;
					for (size_t i = 0; i < entities->size(); i++) // перебор всех созданных сущностей
					{
						bool toProccess = false;
						EntityBase* base = entities->at(i);     // указатель на очередную сущность
						if (base->isFormula()) // если очередная сущность формула, то переходим к следующей сущности
							continue;
						FormulaSet* baseFS = (FormulaSet*)base;    // указатель на множество истинности
						if (formula == baseFS->getParentFormula()) // если родительская формула для очередной сущности совпадает с выбранной формулой, 
							// по которой построим множество истинности
						{
							// проверка, что совпадают наборы свободных переменных для этих двух формул ( возможно, избыточная проверка)
							vector <EntityVariable*>* fv_base = base->getFreeVariables();
							vector <EntityVariable*>* fv_formula = formula->getFreeVariables();
							if (fv_base->size() == fv_formula->size()) // только если размеры наборов свободных переменных совпадают
							{
								bool isFoundFVAll = true;
								for (size_t i1 = 0; i1 < fv_base->size(); i1++)    // перебор по всем свободным переменным очередной сущности
								{
									EntityVariable* pev = fv_base->at(i1);
									bool isFoundFV = false;
									for (size_t i2 = 0; i2 < fv_formula->size(); i2++)    // вложенный цикл по свободным переменным формулы
									{
										if (pev->compare(*fv_formula->at(i2)))     // если сопадают
										{
											isFoundFV = true;
											break;
										}
									}
									if (!isFoundFV)
									{
										isFoundFVAll = false;    // по всей видимости, сработает даже только при одной совпадающей переменной, но и вся проверка,
										// возможно, является избыточной
										break;
									}
								}
								if (isFoundFVAll)
									toProccess = true;
							}
							// проверка, что совпадают наборы базовых переменных будущей сущности и очередной сущности, по которым строятся множества истинности
							vector <EntityVariable*>* bv_base = baseFS->getBaseVariables();
							if (toProccess && (bv_base->size() == variables->size())) // только если размеры наборов свободных переменных совпадают
							{
								toProccess = false;
								bool isFoundFVAll = true; // начальное условие, что наборы совпадают
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
					if (!isExist)     // если не найдено подобного множества истинности
					{
						// блок проверки на выбор имени и индекса для подмножества, если выставлен соответстующий чекокс
						int checked = m_CheckSubSet.GetCheck();
						//					if(m_CheckBelonging.GetCheck() && checked)
						if (checked)
						{
							if (variables->size() > 0)
							{
								int nIndex = m_ComboSubSet.GetCurSel();    // получаю индекс выбранного элемента для обозначения переменной
								int nCount = m_ComboSubSet.GetCount();    // получаю количество элементов всписке обозначений переменной
								if ((nIndex != CB_ERR) && (nCount > 1))    // если выбран
								{
									int len = m_ComboSubSet.GetLBTextLen(nIndex);    // длина текста элемента
									tbuf1 = new TCHAR[len + 2];    // создаю буфер для хранения текста переменной
									m_ComboSubSet.GetLBText(nIndex, (LPTSTR)tbuf1);    // сохраняю текст переменной в созданный буфер
									len = m_IndexSubSet.GetWindowTextLengthW();    // длина текста индекса переменной
									if (len)
									{
										tbuf_index1 = new TCHAR[len + 2];    // создаю буфер для хранения текста индекса переменной
										m_IndexSubSet.GetWindowTextT(tbuf_index1, len + 1);    // сохраняю текст индекса переменной в созданный буфер
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
														AfxMessageBox(_T("Введите другое обозначение подмножества, это уже используется для строящегося множества истинности."));
													else
														AfxMessageBox(_T("Enter another subset notation, this is already used for the truth set under construction."));
													subset_success = false;
												}
											}
											else
											{
												if (CURRENT_LANG_OF == "rus")
													AfxMessageBox(_T("Введите другое обозначение подмножества, это уже используется в схеме."));
												else
													AfxMessageBox(_T("Enter a different subset designation, this is already used in the schema."));
												subset_success = false;
											}
										}
										else
										{
											if (CURRENT_LANG_OF == "rus")
												AfxMessageBox(_T("В индексе подмножества указано не число"));
											else
												AfxMessageBox(_T("The subset index does not specify a number"));
											m_IndexSubSet.SetFocus();
											subset_success = false;
										}
									}
									else
									{
										if (CURRENT_LANG_OF == "rus")
											AfxMessageBox(_T("Не выбран индекс для построения подмножества"));
										else
											AfxMessageBox(_T("An index has not been selected to build a subset"));
										subset_success = false;
									}
								}
								else
								{
									if (CURRENT_LANG_OF == "rus")
										AfxMessageBox(_T("Не выбрано обозначение для построения подмножества"));
									else
										AfxMessageBox(_T("The notation for the construction of a subset is not selected"));
									subset_success = false;
								}
							}
							else
							{
								if (CURRENT_LANG_OF == "rus")
									AfxMessageBox(_T("Подмножество не будетпостроено,потому что не выбрано ни одной переменной. "));
								else
									AfxMessageBox(_T("The subset will not be built because no variables are selected."));
								subset_success = false;
							}

						}
						if (subset_success) // если создание подмножества не задано или задано и обозначение введено и такое подмножество возможно
						{
							//							FormulaSet * pfs = new FormulaSet(formula, variables);    // создаём множество истинности
							tstring tlevel = _T("<");
							for (size_t i = 0; i < variables->size(); i++)
							{
								if (i > 0)
									tlevel += _T(",");
								tlevel += ((Level*)variables->at(i))->GetLevel();
							}
							tlevel += _T(">");
							((Level*)pset)->SetLevel(tlevel);
							FormulaSet* pfs = new FormulaSet(formula, variables, pset);    // создаём множество истинности
							tstring tvars;
							tstring tlevel1;
							if (pfs->isExclusion(formula))
							{
								pfs->proccessExclusion(formula, variables, tvars, tlevel1);
							}
							pfs->SetLabel(entities);    // формируем обозначение
							entities->push_back(pfs);   // добавляю созданное множество истинности в схему
							if (m_CheckBelonging.GetCheck())
							{
								// дополнительно создаю предикат принадлежности
								Formula* predicate = new Formula();
								if (tvars.length() > 0)
									predicate->predicateBelonging(entities, formula, pfs, &tvars);
								else
									predicate->predicateBelonging(entities, formula, pfs);
								entities->push_back(predicate);   // добавляю созданный предикат принадлежности в схему
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
										temp_tuple->SetTupleText(&depending, &tvars); // строю текст кортежа
									else
										temp_tuple->SetTupleText(&depending); // строю текст кортежа										
									temp_tuple->SetLabel(entities); // строю обозначение кортежа
									entities->push_back(temp_tuple);   // добавляю созданное подмножество в схему
									//строю подмножество для кортежа, задающего принадлежность к подмножеству
									variables->push_back(psubset);
									Formula* pfsubset = new Formula();
									pfsubset->subset(entities, pfs, variables);    // создаём подмножество
									pfsubset->putTextOfFormula(entities);
									pfsubset->SetLabel(entities);    // формируем обозначение
									entities->push_back(pfsubset);   // добавляю созданное подмножество в схему
								}
							}
						}

					}
					else {
						if (CURRENT_LANG_OF == "rus")
							AfxMessageBox(_T("Выберите другой набор переменных, по этому множество истинности уже построено"));
						else
							AfxMessageBox(_T("Choose a different set of variables, so the truth set has already been built"));
					}
					// пишем обозначение
					delete variables;     // освобождаю память
					if (!isExist && subset_success)       // если было создано множество истинности
						CDialogEx::OnOK();    // закрываю диалоговое окно
				}
				else {
					if (CURRENT_LANG_OF == "rus")
						AfxMessageBox(_T("Не выбрано ни одной переменной"));
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
								// пишем обозначение
								delete variables;
							}
				*/
			}
		}
		else {
			if (CURRENT_LANG_OF == "rus")
				AfxMessageBox(_T("Не выбрана формула для построения множества истинности"));
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
	// TODO: добавьте свой код обработчика уведомлений
}


//
// устанавливает значения и свойства диалога и его элементов при инициализации
//
BOOL SetDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString str;
	int count = 0;
	tstring res;
	tstring res_formula;
	for (size_t i = 0; i < entities->size(); i++)    // перебор по всем сущностям схемы
	{
		bool toProccess = true;     // флаг 
		EntityBase * base = entities->at(i);    // указатель на очередную сущность
		if ( !base->isFormula() )       // если сущность не формула
			continue;     // переходим к другой
		vector <EntityVariable *> * fv = base->getFreeVariables();    // указатель на контейнер свободных переменных сущности
		if ( fv->size() == 0)     // если нет свободных переменных
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
		dsi->formula = icurr;
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
	m_CheckSubSet.SetCheck(0);
	m_ComboSubSet.EnableWindow(false);
	m_IndexSubSet.EnableWindow(false);
	// TODO:  Добавить дополнительную инициализацию

	// создаю шрифт по умолчанию
	m_fIndexes = new CFont;
	m_fIndexes->CreatePointFont(70, L"Arial Unicode MS");
//	m_fIndexes->CreatePointFont(70, L"Microsoft San Serif");
	m_label.m_fIndexes = m_fIndexes;
	m_level.m_fIndexes = m_fIndexes;
	// создаю шрифт для математических символов
	m_fSymbol = new CFont;
//	m_fSymbol->CreatePointFont(140, L"Symbol");
	m_fSymbol->CreatePointFont(140, L"Arial Unicode MS");
	m_label.m_fSymbol = m_fSymbol;
	m_level.m_fSymbol = m_fSymbol;


	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

//
// метод отображает свободные переменные в элементе m_listVariables для выбранного элемента в списке формул
//
void SetDialog::ShowFreeVariables()
{
	int selected = m_list.GetCurSel();     // получаю номер выделенной формулы (связанного с формулой элемента)
	if( selected >= 0 )     //если выделена 
	{
		SemanticString * dsi = m_list.DCU.at(selected);    // получаю указатель на SemanticString, связанную с указанной формулой
		Formula * f = (Formula *)dsi->formula;     // из SemanticString получаю указатель на саму формулу
		vector <EntityVariable *> * freeVariables = f->getFreeVariables();   // указатель на свободные переменные формулы
		for (size_t i = 0; i < freeVariables->size(); i++)     // перебор по свободным переменным
		{
			CString str;
			// вставляем в листбокс строку с порядковым номером
			str.Format(_T("%d"), i);
			m_listVariables.InsertString(i,str);
			m_listVariables.SetItemHeight(i, 30);
			// готовлю обьект SemanticString для очередной свободной переменной во второй элемент-список
			SemanticString * dsi1 = new SemanticString;
			m_listVariables.DCU.push_back(dsi1);
			dsi1->PrepareSubItemData(*(freeVariables->at(i)->GetText()));
			m_listVariables.SetItemData(i, (DWORD_PTR)dsi1);     // добавляю 
			if(i == 0)     // если первая (то есть хотя бы одна свободная формула)
			{
				m_buttonOK.EnableWindow(true);    // делаю доступным кнопку "OK"
				m_listVariables.EnableWindow(true);    // делаю доступным окно
			}
		}
		m_listVariables.SetCurSel(0);    // устанавливаю выбранным первый элемент
	}
}

//
// метод удаляет свободные переменные из элемента m_listVariables
//
void SetDialog::HideFreeVariables()
{
	int item;
	CString cs;
	m_label.SetWindowTextT(cs);
	m_level.SetWindowTextT(cs);
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
	m_buttonOK.EnableWindow(false);            // делаю окно неактивным
}

//
// обработчик выбора формулы
//
void SetDialog::OnSelchangeSetlist1()
{
	HideFreeVariables();    // удаляет переменные, если есть, из окна-списка свободных переменных
	ShowFreeVariables();    // заполняет окно-список свободных переменных в зависимости от выбранной формулы
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
	// TODO: добавьте свой код обработчика уведомлений
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

	int nIndex3 = m_comboSet.GetCurSel();    // получаю индекс выбранного элемента для обозначения переменной
	int nCount3 = m_comboSet.GetCount();    // получаю количество элементов всписке обозначений переменной
	if ((nIndex3 != CB_ERR) && (nCount3 > 1))    // если выбран
	{
		int len3 = m_comboSet.GetLBTextLen(nIndex3);    // длина текста элемента
		tbuf2 = new TCHAR[len3 + 2];    // создаю буфер для хранения текста переменной
		m_comboSet.GetLBText(nIndex3, (LPTSTR)tbuf2);    // сохраняю текст переменной в созданный буфер
		len3 = m_indexSet.GetWindowTextLengthW();    // длина текста индекса переменной
		if(len3)
		{
			tbuf_index2 = new TCHAR[len3 + 2];    // создаю буфер для хранения текста индекса переменной
			m_indexSet.GetWindowTextT(tbuf_index2, len3 + 1);    // сохраняю текст индекса переменной в созданный буфер
			tset = tstring(tbuf2);
			tset_index = tstring(tbuf_index2);
			if(find_if_not(tset_index.begin(), tset_index.end(), istdigit) == tset_index.end())
			{

				pset = new EntityVariable(tset, tset_index, SET);
				int selected1 = m_list.GetCurSel();    // номер выбранной формулы
				if ( selected1 != LB_ERR )     // если номер выбранного элемента, возвращённый методом GetCurSel, действителен
				{
					SemanticString * dsi1 = (SemanticString *) m_list.DCU.at(selected1);    // получаем указатель на SemanticString, связанную с выбранным элементом
					Formula * formula = (Formula *)dsi1->formula;    // берём указатель на обьект Formula для текущего объекта SemanticString
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
							FormulaSet pfs(formula, variables, pset);    // создаём множество истинности
							pfs.SetLabel(entities);    // формируем обозначение
							cs_label = pfs.getLabel()->data();
							cs_level = ((Level *)pfs.getNaming())->GetLevel().data();
						}
						else
						{
							if(CURRENT_LANG_OF=="rus")
								cs_label = _T("Не выбрана ни одна переменная");
							else 
								cs_label = _T("No variables are selected");

						}
					}		
					else
						cs_label = _T("Ошибка указателя на обьект");
				}
				else
					cs_label = _T("Не выбрана формула");
			}
			else
				cs_label = _T("В индексе множества указано не число");

		}
		else
			cs_label = _T("Не указан индекс");
	}
	else
		cs_label = _T("Не выбрано обозначение или индекс");
	
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
		delete pset;	// TODO: добавьте свой код обработчика уведомлений
}



void SetDialog::OnSelchangeSetcombo()
{
	CheckSelection();
	// TODO: добавьте свой код обработчика уведомлений
}


void SetDialog::OnChangeSetindex()
{
	CheckSelection();
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}
