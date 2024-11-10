//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
// SummaryDialog.cpp: файл реализации
//

//TRANSLATED

#include "stdafx.h"
#include "Semantics.h"
#include "SummaryDialog.h"
#include "afxdialogex.h"
#include "common_functions.h"


// диалоговое окно SummaryDialog

IMPLEMENT_DYNAMIC(SummaryDialog, CDialog)

//
//  конструктор
//
SummaryDialog::SummaryDialog(CWnd* pParent /*=NULL*/)
	: CDialog(SummaryDialog::IDD, pParent)
{
//	m_list.m_bColor = TRUE;
//	m_list.m_bModifyFont = TRUE;
}

//
//  деструктор
//
SummaryDialog::~SummaryDialog()
{
}

void SummaryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SUMMARYLIST, m_list);
	DDX_Control(pDX, IDREDEFINE, m_RedefineBtn);
}


BEGIN_MESSAGE_MAP(SummaryDialog, CDialog)
	ON_WM_MEASUREITEM()
	ON_BN_CLICKED(IDOK, &SummaryDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDREDEFINE, &SummaryDialog::OnBnClickedPereopisanie)
	ON_NOTIFY(LVN_ODSTATECHANGED, IDC_SUMMARYLIST, &SummaryDialog::OnLvnOdstatechangedSummarylist)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


//
// метод сопоставляет элементу просмотра контейнер сущностей (формул и множеств истинности)
//
void  SummaryDialog::setFormulas(vector <EntityBase *> * all_entities)
{
	entities = all_entities;
}


// обработчики сообщений SummaryDialog

//
// устанавливает значения и свойства диалога и его элементов при инициализации
//
BOOL SummaryDialog::OnInitDialog()
{
	CDialog::OnInitDialog();    // стандартная инициализация базового диалогового класса
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);    // устанавливает возможность выбора целой строки таблицы просмотра и отрисовку 
	// разграничительных линий
	
	// добавление колонок в таблицу просмотра, установка их заголовков и ширины
	if (CURRENT_LANG_OF == "rus") {
		m_list.InsertColumn(0, _T("Номер"), LVCFMT_LEFT, 100);
		m_list.InsertColumn(1, _T("Формула"), LVCFMT_LEFT, 200);
		m_list.InsertColumn(2, _T("Тип"), LVCFMT_LEFT, 100);
		m_list.InsertColumn(3, _T("Свободные переменные"), LVCFMT_LEFT, 120);
		m_list.InsertColumn(4, _T("Описание"), LVCFMT_LEFT, 100);
		m_list.InsertColumn(5, _T("Addons"), LVCFMT_LEFT, 200);
		m_list.InsertColumn(6, _T("Обозначение"), LVCFMT_LEFT, 200);
		m_list.InsertColumn(7, _T("Нач. текст"), LVCFMT_LEFT, 200);
	}
	else {
		m_list.InsertColumn(0, _T("Number"), LVCFMT_LEFT, 100);
		m_list.InsertColumn(1, _T("Formula"), LVCFMT_LEFT, 200);
		m_list.InsertColumn(2, _T("Type"), LVCFMT_LEFT, 100);
		m_list.InsertColumn(3, _T("Free variables"), LVCFMT_LEFT, 120);
		m_list.InsertColumn(4, _T("Description"), LVCFMT_LEFT, 100);
		m_list.InsertColumn(5, _T("Addons"), LVCFMT_LEFT, 200);
		m_list.InsertColumn(6, _T("Designation"), LVCFMT_LEFT, 200);
		m_list.InsertColumn(7, _T("the initial text"), LVCFMT_LEFT, 200);
	}

	int nColumns = 7;    // число колонок в таблице просмотра
	// установка колонок "только для чтения"
	m_list.SetColumnReadOnly(0);
	m_list.SetColumnReadOnly(1);
	m_list.SetColumnReadOnly(2);
	m_list.SetColumnReadOnly(3);
	m_list.SetColumnReadOnly(6);
	m_list.SetColumnReadOnly(7);

	// предварительная инициализация элемента редактирования, которое будет использоваться в дальнейшем для редактируемых ячеек (колонок)
	CRect rect(0,0,20,20);
	m_edit.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | WS_BORDER, rect, this, IDC_LIST_EDIT); 
	m_edit.ShowWindow(SW_HIDE);
    m_list.SetDefaultEditor(NULL, NULL, &m_edit);	// установка этого элемента редактируемым элементом по умолчанию
	m_edit.SetFont(m_list.GetFont());    // установка шрифта для элемента редактирования
	tstring str_number;
	tstring res, res_formula;
	m_list.SetItemCount(entities->size());     // установка числа строк в таблице просмотра
	// перебор сущностей схемы и заполнение ячеек таблицы
	for (size_t i = 0; i < entities->size(); i++)
	{
		SemanticString * dsi = new SemanticString[nColumns + 1];    // для (nColumns + 1) ячеек в строке создаём массив SemanticString
		m_list.DCU.push_back(dsi);    //  добавляем массив в член класса-контейнер элементов SemanticString
		str_number = to_tstring((long long)(i + 1));    // строка с номером строки таблицы, начинается с 1
		dsi[0].PrepareSubItemData(str_number);   //  преобразую номер строки в SemanticString
		EntityBase * base = entities->at(i);     // указатель на очередную сущность 
		tstring text = base->getText();
		dsi[1].PrepareSubItemData(text);    // преобразую текст сущности в SemanticString

//		tstring description = *base->getDescription();
//		dsi[4].PrepareSubItemData(description); 
		m_list.SetItemText(i, 4, base->getDescription()->data());    // устанавливаю в соответствие описание сущности четвёртой ячейке строки таблицы (редактируемой)
		m_list.SetItemText(i, 5, base->getAddOns()->data());    // устанавливаю в соответствие дополнительное описание сущности пятой ячейке строки таблицы (редактируемой)


		dsi[6].PrepareSubItemData(*(base->getLabel()));    // преобразую в SemanticString обозначение формулы
		if(base->isRedefined())
		{
			tstring redefined_text = *base->getRedefinedText(); 
			tstring initial_text = *base->getInitialText();
			trimWhitespaces(&redefined_text);
			trimWhitespaces(&initial_text);
			if((redefined_text.length() > 0) && (redefined_text.compare(initial_text))) 
				dsi[7].PrepareSubItemData(initial_text);    // преобразую в SemanticString начальное обозначение формулы
		}
		else
		{
			res.clear();
			dsi[7].PrepareSubItemData(res);
		}
		res = makeVarPartOfLabel(entities, base);

		if(!res.empty())    // если строка непустая (есть свободные переменные)
		{
			dsi[3].PrepareSubItemData(res);    // преобразую в SemanticString строку свободных переменных
		}
		res.clear();
		if ( base->getType() == FORMULA_SET )    // eсли сущность - множество истинности
		{
		}
		else    // если сущность - формула
		{
			Formula * icurr = (Formula *)base;    // привожу к указателю на формулу
			// формирую строку типа
			if (CURRENT_LANG_OF == "rus") {
				if (icurr->getFeature() == PERFORMED_FEATURE)
					res = _T("выполнимая");
				else if (icurr->getFeature() == TRUTH_FEATURE)
					res = _T("истинная");
				else if (icurr->getFeature() == FALSE_FEATURE)
					res = _T("ложная");
				else if (icurr->getFeature() == ATOMARN_FEATURE)
					res = _T("атомарная");
			}
			else {
				if (icurr->getFeature() == PERFORMED_FEATURE)
					res = _T("doable");
				else if (icurr->getFeature() == TRUTH_FEATURE)
					res = _T("true");
				else if (icurr->getFeature() == FALSE_FEATURE)
					res = _T("false");
				else if (icurr->getFeature() == ATOMARN_FEATURE)
					res = _T("atomic");
			}
		}
		if(!res.empty())    // если строка типа формулы (если это формула) непустая
		{ 
			dsi[2].PrepareSubItemData(res);    // преобразую строку типа к SemanticString
		}

	}
	// устанавливаю шрифт для таблицы просмотра/редактирования
	CFont * m_curr = new CFont;    
//	m_curr->CreatePointFont(70, L"Microsoft Sans Serif");
	m_curr->CreatePointFont(70, L"Arial Unicode MS");
	m_list.SetIndexesFont(m_curr);
	m_list.SetFocus();
//	m_list.SetCallbackMask(LVIS_SELECTED|LVIS_FOCUSED);
	return true;
}



//
//  раньше использовался для отлавливания событий от клавиатуры, сейчас пока ничего
//
BOOL SummaryDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: добавьте специализированный код или вызов базового класса
/*
	if( pMsg->message == WM_KEYDOWN )
	{
		if(pMsg->wParam == VK_ESCAPE)
		{
			if((m_edit != NULL) && (m_edit == m_edit->getF
		}
	}
*/
	return CDialog::PreTranslateMessage(pMsg);
}


//
// перебор строк таблицы и сохранение значений редактируемых ячеек в соответствующих сущностях схемы
//
void SummaryDialog::SaveAndExit()
{
	for ( size_t i = 0; i < entities->size(); i++)    // перебор всех сущностей, столько же, сколько и строк в таблице
	{
		EntityBase * base = entities->at(i);    // указатель на очередную сущность
		TCHAR buf[2048];    // буфер для строки
		buf[0]=TCHAR(0x00);
		m_list.GetItemText(i, 4, buf, 2047);    // сохраняю (обычный, не Semanticstring) текст четвёртой ячейки в буфер
		base->SetDescription(buf);    // записываю текст из буфера в описание сущности
		buf[0]=TCHAR(0x00);
		m_list.GetItemText(i, 5, buf, 2047);    // сохраняю (обычный, не Semanticstring) текст пятой ячейки в буфер
		base->SetAddons(buf);    // записываю текст из буфера в дополнителное описание сущности
		buf[0]=TCHAR(0x00);
		m_list.GetItemText(i, 1, buf, 2047);    // сохраняю (обычный, не Semanticstring) текст первой ячейки в буфер
		base->SetText(buf);    // записываю текст из буфера в описание сущности
	}
}

//
//  обработчик нажатия на кнопку "Отмена"
//
void SummaryDialog::OnCancel()
{
	CDialog::OnCancel();
}

/*
//
//  обработчик нажатия на кнопку "ОК"
//
void SummaryDialog::OnOK()
{
	CDialog::OnOK();
}
*/


//
//  обработчик нажатия на кнопку "ОК"
//
void SummaryDialog::OnBnClickedOk()
{
	// перебор строк таблицы и сохранение значений редактируемых ячеек в соответствующих сущностях схемы
	SaveAndExit();
	CDialog::OnOK();
}


//
// метод выставляет высоту столбцов
//
void SummaryDialog::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
/*
  HDC hDC = ::GetDC(NULL);
  CFont* pFont = GetFont();
  HFONT hFontOld = (HFONT)SelectObject(hDC, pFont->GetSafeHandle());
  CRect rect;

  DrawText(hDC, _T(" "), 1, rect, DT_SINGLELINE | DT_CALCRECT);
  lpMeasureItemStruct->itemHeight = rect.bottom - rect.top;
  lpMeasureItemStruct->itemHeight = 30;
  SelectObject(hDC, hFontOld);
  ::ReleaseDC(NULL, hDC);
*/
  lpMeasureItemStruct->itemHeight = 30;
//	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}



/*
BOOL CDemoDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    ...
    //Set image list to increase row height
    m_imgList.Create(1, 20, ILC_COLOR, 0, 1);
    m_lstDemo.SetImageList(&m_imgList, LVSIL_SMALL);
    FillListBox();
    m_lstDemo.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    //set full row select and grid lines

    return TRUE;
    // return TRUE  unless you set the focus to a control
}

void CDemoDlg::AddColumns(void)
{
    m_lstDemo.InsertColumn(0, "Default Editor", LVCFMT_LEFT, 100);
    m_lstDemo.InsertColumn(1, "Date Time Editor", LVCFMT_LEFT, 100);
    m_lstDemo.InsertColumn(2, "Combobox Editor", LVCFMT_LEFT, 100);
    m_lstDemo.InsertColumn(3, "Color Select", LVCFMT_LEFT, 150);
    m_lstDemo.InsertColumn(4, "Read Only Column", LVCFMT_LEFT, 100);
    m_lstDemo.InsertColumn(5, "Just a Column", LVCFMT_LEFT, 100);

    m_lstDemo.SetColumnEditor(1, &CDemoDlg::InitEditor, 
                                 &CDemoDlg::EndEditor, &m_wndDT);
    m_lstDemo.SetColumnEditor(2, &CDemoDlg::InitEditor, 
                                 &CDemoDlg::EndEditor, &m_wndCB);
    m_lstDemo.SetColumnEditor(3, &CDemoDlg::InitEditor, 
                                 &CDemoDlg::EndEditor, &m_dlgColor);
    m_lstDemo.SetColumnReadOnly(4);
    m_lstDemo.SetDefaultEditor(NULL, NULL, &m_wndEdit);
    m_lstDemo.SetColumnColors(4, RGB(200, 200, 200), RGB(128, 128, 128));
    m_lstDemo.SetColumnSorting(0, CListCtrlEx::Auto, CListCtrlEx::StringNoCase);
    m_lstDemo.SetColumnSorting(1, CListCtrlEx::Auto, CListCtrlEx::Date);
    m_lstDemo.SetColumnSorting(2, CListCtrlEx::Auto, CListCtrlEx::String);
    m_lstDemo.SetColumnSorting(3, CListCtrlEx::Auto, CListCtrlEx::StringNoCase);
    m_lstDemo.SetColumnSorting(4, CListCtrlEx::Auto, CListCtrlEx::StringNoCase);
}

void CDemoDlg::FillListBox(void)
{
    m_lstDemo.Reset();
    AddColumns();
    CString strDate = COleDateTime(CTime::GetCurrentTime().GetTime()).Format();
    for(int i = 0; i < 20; i++)
    {
        CString str;
        str.Format("Some %d Text %d", rand(), rand());
        m_lstDemo.InsertItem(i, str);
        m_lstDemo.SetItemText(i, 1, strDate);
        m_lstDemo.SetItemText(i, 2, "text1");
        m_lstDemo.SetItemText(i, 3, "Some Text");
        m_lstDemo.SetItemText(i, 4, "Read Only");
        m_lstDemo.SetItemText(i, 5, "Some Text");
        if(i%9 == 3)
        {
            m_lstDemo.SetRowColors(i, -1, RGB(255, 0, 0));
            m_lstDemo.SetRowEditor(i, NULL, NULL, &m_wndEdit);
        }
        if(i % 7 == 0)
        {
            m_lstDemo.SetCellColors(i, 5, RGB(0, 255, 0), RGB(255, 255, 255));
            m_lstDemo.SetCellEditor(i, 5, &CDemoDlg::InitEditor, 
                                    &CDemoDlg::EndEditor, &m_wndDT);
        }
        if(i % 8 == 0) m_lstDemo.SetCellColors(i, 5, RGB(0, 255, 0), -1);
    }
    
}
//Call back function to initialize the cell editor.
BOOL
CDemoDlg::InitEditor(CWnd** pWnd, int nRow, int nColumn, CString&
strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate)
{
    ASSERT(*pWnd);
    switch(nColumn)
    {
    case 1:
    case 5:
        {
            CDateTimeCtrl *pDTC = dynamic_cast<CDateTimeCtrl *>(*pWnd);
            COleDateTime dt;
            if(dt.ParseDateTime(strSubItemText)) pDTC->SetTime(dt);
        }
        break;
    case 2:
        {
            CComboBox *pCmb = dynamic_cast<CComboBox *>(*pWnd);
            pCmb->SelectString(0, strSubItemText);
        }
        break;
    case 3:
        {
            CDlgColor *pDlg = dynamic_cast<CDlgColor *>(*pWnd);        
            pDlg->m_nColor = strSubItemText.CompareNoCase("green")? 
               (strSubItemText.CompareNoCase("blue")?0:2):1;
            pDlg->Create(CDlgColor::IDD, (CWnd*)pThis);            
            pDlg->UpdateData(FALSE);
        }
        break;
    }
    return TRUE;
}
 
//Call back function to end and destroy the cell editor.
//Spacial feature return -1 to sort list control items 
//based on the current editing item.
BOOL CDemoDlg::EndEditor(CWnd** pWnd, int nRow, int nColumn, 
                         CString& strSubItemText, 
                         DWORD_PTR dwItemData, 
                         void* pThis, BOOL bUpdate)
{
    ASSERT(pWnd);
    switch(nColumn)
    {
    case 1:
    case 5:
        {
            CDateTimeCtrl *pDTC = dynamic_cast<CDateTimeCtrl *>(*pWnd);
            COleDateTime dt;
            pDTC->GetTime(dt);
            strSubItemText = dt.Format();
        }
        break;
    case 2:
        {
            CComboBox *pCmb = dynamic_cast<CComboBox *>(*pWnd);
            int index = pCmb->GetCurSel();
            if(index >= 0) pCmb->GetLBText(index, strSubItemText);
        }
        break;
    case 3:
        {
            CDlgColor *pDlg = dynamic_cast<CDlgColor *>(*pWnd);
            CListCtrlEx *pList = reinterpret_cast<CListCtrlEx *>(pThis);
            pDlg->UpdateData(TRUE);
            switch(pDlg->m_nColor)
            {
            case 1:
                strSubItemText = "Green";
                pList->SetCellColors(nRow, nColumn, RGB(0, 255, 0), -1);
                break;
            case 2:
                strSubItemText = "Blue";
                pList->SetCellColors(nRow, nColumn, RGB(0, 0,255 ), -1);
                break;
            default:
                strSubItemText = "Red";
                pList->SetCellColors(nRow, nColumn, RGB(255, 0, 0), -1);
                break;
            }                
            pDlg->DestroyWindow();
        }
        break;
    }
    return TRUE;
}
*/


// функция для реверсного пересоздания набора temp_entities на основе уже существующего entities с first номера до last
//void SummaryDialog::ReverseDefinition(vector <EntityBase *> * temp_entities, vector <EntityBase *> * entities, int first, int last)
void ReverseDefinition(vector <EntityBase *> * temp_entities, vector <EntityBase *> * entities, int first, int last, SummaryDialog *psd)
{
	TCHAR buf[2048];    // буфер для строки			
			for ( size_t i1 = first; i1 < last; i1++)
			{
				if(i1 == entities->size())
					break;
				EntityBase * base = entities->at(i1);
				tstring text;
				text.clear();
				bool redefined = base->isRedefined();
				if(redefined)
				{
					base->setTemporarilyUnredefined();
					if(psd != nullptr)
					{
						SemanticString * dsi1 = &(psd->m_list.DCU.at(i1)[1]);
						psd->m_list.GetItemText(i1, 1, buf, 2047);    // получаю текст переобозначения
						text = buf;
					}
				}
//				if ( base->getType() == FORMULA_SET )
				if ( base->isSet() )
				{
					if(base->getType() == REPLACE_VARIABLE)
					{
						EntityBase * prb = base->getReplacedBase();
						int count_prb = 0;
						for(size_t i = 0; i < entities->size(); i++)
						{
							if((prb != nullptr) && (prb == entities->at(i)))
							{
								count_prb = i + 1;
								break;
							}
						}
						if(count_prb > 0)
						{
							FormulaSet * pfs_new = new FormulaSet;
							EntityBase * peb_new = (EntityBase *)pfs_new;
							EntityVariable * pev_old = new EntityVariable(*base->getInitialVariable());
							EntityVariable * pev_new = new EntityVariable(*base->getNewVariable());
							peb_new->SetReplacing( temp_entities->at(count_prb - 1), pev_old, pev_new);
							pfs_new->SetLabel(temp_entities);
							temp_entities->push_back((EntityBase *)pfs_new);
						}
					}
					else
					{
						FormulaSet * fs = (FormulaSet *)base;
						Formula * parent = fs->getParentFormula();
						Formula * parent_new = nullptr;
						for(int j=0;j < entities->size(); j++)
						{
							if(entities->at(j) == parent)
							{
								parent_new = (Formula *)temp_entities->at(j);
								break;
							}
						}
						FormulaSet * pfs_new = new FormulaSet(parent_new, fs->getBaseVariables(), nullptr);
						temp_entities->push_back((EntityBase *)pfs_new);
					}
				}
				else
				{
					Formula * f = (Formula *)(base);
					Formula * f_new = nullptr;
					if(f->getType() == ATOMIC_FORMULA)
					{
						f_new = new Formula;
						f_new->setAtomFormula(temp_entities, *f->getFreeVariables()->at(0), *f->getFreeVariables()->at(1));
//						continue;
					}
					else if(f->getType() == REPLACE_VARIABLE)
					{
						EntityBase * prb = base->getReplacedBase();
						int count_prb = 0;
						for(size_t i = 0; i < entities->size(); i++)
						{
							if((prb != nullptr) && (prb == entities->at(i)))
							{
								count_prb = i + 1;
								break;
							}
						}
						if(count_prb > 0)
						{
							Formula * pf_new = new Formula;
							EntityBase * peb_new = (EntityBase *)pf_new;
							EntityVariable * pev_old = new EntityVariable(*base->getInitialVariable());
							EntityVariable * pev_new = new EntityVariable(*base->getNewVariable());
							peb_new->SetReplacing( temp_entities->at(count_prb - 1), pev_old, pev_new);
							pf_new->SetLabel(temp_entities);
							temp_entities->push_back((EntityBase *)peb_new);
						}
					}
					else if(f->getType() == TUPLE)
					{
						Tuple * pt = nullptr;
						if(f->getFreeVariables()->size() == 2)
						{
							pt = new Tuple(*f->getFreeVariables()->at(0), *f->getFreeVariables()->at(1));
						}
						else if(f->getFreeVariables()->size() == 3)
						{
							pt = new Tuple(*f->getFreeVariables()->at(0), *f->getFreeVariables()->at(1), *f->getFreeVariables()->at(2));
						}
						if(pt != nullptr)
						{
//							pt->putTextOfFormula(temp_entities);
							size_t count_entities = temp_entities->size();
							vector <EntityVariable *> depending;
							if(count_entities > 2)
							{
								EntityBase * peb = temp_entities->at(count_entities - 1);
								if(peb->isFormula() && (((Formula *)peb)->getType() == BELONGING_PREDICATE) )
								{
//									Formula * ppred = (Formula *)peb;
									depending = *(((Formula *)peb)->getFreeVariables());
									size_t count_dep = depending.size();
									if(count_dep > 0)
									{
										count_dep -= 1;
//										depending.erase(depending.begin() + count_dep);
									}
								}
								else if(peb->isSet())
									depending = *(peb->getFreeVariables());
								vector <EntityVariable *> * fv1 = pt->getFreeVariables();
								for(size_t i = 0 ; i < depending.size(); i++)
								{
									for(size_t i1 = 0; i1 < fv1->size(); i1++)
									{
										if(fv1->at(i1)->compare(*depending.at(i)))
										{
											depending.erase (depending.begin()+i);
											break;
										}
									}
								}
							}
							pt->SetTupleText(&depending);
							pt->SetLabel(temp_entities);
							f_new = (Formula *)pt;
							temp_entities->push_back((EntityBase *)f_new);
						}
					}
					else if ( ( f->getType() == AND_OPERATION ) || ( f->getType() == OR_OPERATION ) )
					{
						ParentLink * curr = f->getParentLink(0);
						EntityBase * parent1 = get<0>(*curr);
						curr = f->getParentLink(1);
						EntityBase * parent2 = get<0>(*curr);
						Formula * parent1_new = nullptr;
						Formula * parent2_new = nullptr;
						for(int j=0;j < entities->size(); j++)
						{
							if(entities->at(j) == parent1)
								parent1_new = (Formula *)temp_entities->at(j);
							if(entities->at(j) == parent2)
								parent2_new = (Formula *)temp_entities->at(j);
							if(parent1_new && parent2_new)
								break;
						}
						f_new = joinFormula(temp_entities, f->getType(), parent1_new, parent2_new);
//						int xxxx = 1;
						temp_entities->push_back((EntityBase *)f_new);
					}
					else if ( ( f->getType() == QUANTIFIER1_OPERATION ) || ( f->getType() == QUANTIFIER2_OPERATION ) )
					{
						ParentLink * curr = f->getParentLink(0);
						EntityBase * parent1 = get<0>(*curr);
						Formula * parent1_new;
						for(int j=0;j < entities->size(); j++)
						{
							if(entities->at(j) == parent1)
							{
								parent1_new = (Formula *)temp_entities->at(j);
								break;
							}
						}
						vector <EntityVariable *> * from_current = f->getFreeVariables();
						vector <EntityVariable *> * from_parent = parent1->getFreeVariables();
						int found = 0;
						for(int j = 0; j < from_parent->size(); j++)
						{
							found = 0;
							for(int j1 = 0; j1 < from_current->size(); j1++)
							{
								if(*from_current->at(j1) == *from_parent->at(j))
								{
									found = 1;
									break;
								}
							}
							if(!found)
							{
								found = j;
								break;
							}
						}
						f_new = parent1_new->quantifierFormula(temp_entities, f->getType(), parent1_new->getFreeVariables()->at(found));
//						continue;
					}
					else if ( f->getType() == NEGATIVE_OPERATION )
					{
						ParentLink * curr = f->getParentLink(0);
						EntityBase * parent1 = get<0>(*curr);
						Formula * parent1_new;
						for(int j=0;j < entities->size(); j++)
						{
							if(entities->at(j) == parent1)
							{
								parent1_new = (Formula *)temp_entities->at(j);
								break;
							}
						}
						f_new = parent1_new->negativeFormula(temp_entities, 1);
//						continue;
					}
					else if ( f->getType() == BELONGING_PREDICATE )
					{
						FormulaSet * parent_set = f->getParentSet();
						if(parent_set != nullptr)
						{
							f_new = new Formula;
							f_new->predicateBelonging(entities, parent_set->getParentFormula(), parent_set);
							temp_entities->push_back((EntityBase *)f_new);
						}
					}
					else if ( f->getType() == SUBSET )
					{
						f_new = new Formula;
						FormulaSet * parent_set = f->getParentSet();
						vector <EntityVariable *> excluding; // вектор свободных переменных, которые надо удалить из вектора свободных переменных включающего 
						// множества, чтобы получить свободные переменные подмножества
						excluding = *(parent_set->getBaseVariables());
						vector <EntityVariable *> free_variables1 = *(f->getFreeVariables());

						if(free_variables1.size() > 0)
							excluding.push_back(free_variables1.at(free_variables1.size() - 1));
						f_new->subset(temp_entities, parent_set, &excluding);    // создаём подмножество истинности
						f_new->putTextOfFormula(temp_entities);
						f_new->SetLabel(temp_entities);    // формируем обозначение
						temp_entities->push_back((EntityBase *)f_new);   // добавляю созданное подмножество в схему
					}
				}
				if(redefined)
				{
					base->setRedefined();
					temp_entities->at(i1)->SetText(text.data());
					temp_entities->at(i1)->setRedefined();
				}
			}
}

// функция проверяет строку замены на обозначения, которые могут быть обозначениями переменных (вида симол и обозначение индекса) и если они найдены, 
// проверяет, все ли эти обозначения совпадают со свободными переменными у данного обьекта
bool SummaryDialog::IfCorrectRedefinition(EntityBase * pbase, tstring & new_text)
{
	bool result = true;
	tstring f = _T("<Symbol=/low>");
	vector <EntityVariable *> * pevv = pbase->getFreeVariables();
	vector <EntityVariable *> evv(*pevv);
	size_t pos = new_text.find(f);
	while( (pos != tstring::npos) && (pos > 0) )
	{
		size_t pos_variable = pos - 1;
		tstring name;
		name += new_text.at(pos_variable);
		size_t pos_for_index_search = pos;
		size_t pos_index_part = new_text.find(f, pos_for_index_search);
		tstring index;
		while(pos_index_part != tstring::npos)
		{
			pos = pos_for_index_search;
			if(new_text.length() > (pos_index_part + 13) )
			{
				index += new_text.at(pos_index_part + 13);
			}
			if(new_text.length() > (pos_for_index_search + f.length() + 1) )
			{
				pos_for_index_search += f.length() + 1;
				pos_index_part = new_text.find(f, pos_for_index_search);
				if( pos_for_index_search != pos_index_part)
					break;
			}
			else
			{
				pos_index_part = tstring::npos;
			}
		}
		if(new_text.length() > (pos + f.length() + 2) )
		{
			pos += f.length() + 2;
			pos = new_text.find(f, pos);
		}
		else
			pos = tstring::npos;
		EntityVariable ev(name,index, VARIABLE);
		bool found = false;
		for(auto p = evv.begin(); p != evv.end(); p++)
		{
			if((*p)->compare(ev))
			{
				evv.erase(p);
//				found = true;
				break;
			}
		}
//		if(!found)
//		{
//			result = false;
//			break;
//		}
	}
	if(evv.size() > 0)
		result = false;
	return result;
}



void SummaryDialog::OnBnClickedPereopisanie()
{
	// TODO: добавьте свой код обработчика уведомлений
	tstring mess, caption;
	if (CURRENT_LANG_OF == "rus") {
		mess = tstring(_T("Вы собираетесь переобозначить формулу. Если вы используете в новом обозначении свободные формулы, проверьте их на совпадение с существующими. Или скопируйте из соответствующей графы таблицы. Продолжить?"));
		caption = tstring(_T("Внимание!"));
	}
	else {
		mess = tstring(_T("You are going to reinterpret the formula. If you use free formulas in the new notation, check them to match the existing ones. Or copy it from the corresponding column of the table. Continue?"));
		caption = tstring(_T("Attention!"));
	}
	if(MessageBox( mess.data(), caption.data(), MB_YESNO) == IDYES)
	{
		int  nItem11 = -1;
		UINT ii, uSelectedCount1 = m_list.GetSelectedCount();
		if(uSelectedCount1 > 0)
		{
			nItem11 = m_list.GetNextItem(nItem11, LVNI_SELECTED);
			TCHAR buf[2048];    // буфер для строки
			m_list.GetItemText(nItem11, 4, buf, 2047);    // получаю текст переобозначения
			tstring set_text = buf;
			EntityBase * base = entities->at(nItem11);
			if (CURRENT_LANG_OF == "rus") {

				if (!IfCorrectRedefinition(entities->at(nItem11), set_text))
				{

					tstring mess(_T("В переобозначении "));
					mess += to_tstring((long long)(nItem11 + 1));
					mess += _T(" объекта не указаны все свободные переменные для этого объекта");
					tstring caption(_T("Внимание!"));
					MessageBox(mess.data(), caption.data(), MB_OK);
					return;
				}
			}
			else {
				if (!IfCorrectRedefinition(entities->at(nItem11), set_text))
				{

					tstring mess(_T("In the re-designation "));
					mess += to_tstring((long long)(nItem11 + 1));
					mess += _T(" all free variables for this object are not specified");
					tstring caption(_T("Attention!"));
					MessageBox(mess.data(), caption.data(), MB_OK);
					return;
				}
			}
		}
	UINT i, uSelectedCount = m_list.GetSelectedCount();
	if(uSelectedCount > 0)
	{
		vector <EntityBase *> * temp_entities = new vector <EntityBase *>;
		int  nItem = -1;
		int nFirst = 0, nLast = 0;
		bool success = true;
		TCHAR buf[2048];    // буфер для строки
		for (i=0; i < uSelectedCount; i++)
		{
			nItem = m_list.GetNextItem(nItem, LVNI_SELECTED);
			ReverseDefinition(temp_entities, entities, nFirst, (nItem + 1), this);
			nFirst = nItem + 1;
			nLast = nItem;
			ASSERT(nItem != -1);
			SemanticString * dsi1 = &(m_list.DCU.at(nItem)[1]);
			SemanticString * dsi4 = &(m_list.DCU.at(nItem)[4]);
			SemanticString * dsi7 = &(m_list.DCU.at(nItem)[7]);
			m_list.GetItemText(nItem, 4, buf, 2047);    // получаю текст переобозначения
			tstring set_text = buf;
			tstring tstr = buf;
			if(nItem < temp_entities->size())
			{
				tstr = _T(" ( ")+ tstr + _T(" ) ");
				temp_entities->at(nItem)->SetText(tstr.data());
			}
			else
			{
				success = false;
				if (CURRENT_LANG_OF == "rus") {
					MessageBox(_T("Некорректная схема"), _T("Ошибка"));
				}
				else {
					MessageBox(_T("Incorrect scheme"), _T("Mistake"));

				}
				break;
			}

			dsi1->PrepareSubItemData(tstr);	
			tstr.clear();
			dsi4->PrepareSubItemData(tstr);	
			EntityBase * base = entities->at(nItem); 
			base->setRedefined();
			dsi7->PrepareSubItemData(base->getText());
			m_list.SetItemState(nItem, 0, LVIS_SELECTED);
			m_list.RedrawItems(nFirst, nLast);
			if(base->getType() == FORMULA_SET)		// если переобозначаем множество истинности
			{
				EntityBase * peb = entities->at(nItem);			// получаем указатель на класс EntityBase, соответствующий множеству истинности
				EntityVariable * pnaming = ((FormulaSet *)peb)->getNaming(); // получаем указатель на переменную-обозначение
				pnaming->SetRedefinition(set_text);						// указываем текст переобозначения
				SetGroup sg = peb->isPartOfSetGroup(entities);	// делаем проверку на число элементов в группе множества истинности
				EntityBase * peb_first = get<0>(sg);
				int count_objs = get<1>(sg);					// число обхектов в группе множества истинности
				if(count_objs > 1)								// если в группе есть еще обьекты помимо множества истинности
				{
					nLast += count_objs;						// увеличиваем счетчик, по которому проводит обратное переопределение, на число элементов в группе
					ReverseDefinition(temp_entities, entities, nFirst, nLast, this);
					if( (count_objs == 2) || (count_objs == 4) ) // если строится и предикат принадлежности 
					{
						EntityBase * peb_predicate = entities->at(nItem + 1);
						EntityBase * peb_predicate_temp = temp_entities->at(nItem + 1);
						if(!peb_predicate->isRedefined())		// если предикат принадлежности не переопределен
						{
/*
							SemanticString * dsi1 = &(m_list.DCU.at(nItem + 1)[1]);
							SemanticString * dsi4 = &(m_list.DCU.at(nItem + 1)[4]);
							SemanticString * dsi7 = &(m_list.DCU.at(nItem + 1)[7]);
							m_list.GetItemText(nItem + 1, 1, buf, 2047);    // получаю первоначальный текст предиката принадлежности
							tstring initial_predicate = buf;
							tstring new_text = peb_predicate->getText();
							tstring f = _T(" <Symbol=/in> ");
							size_t pos = new_text.find(f);
							if(pos != tstring::npos)
							{
								new_text = new_text.substr(0, pos + f.length());
								new_text += _T("{ ") + set_text + _T(" }");
							}
//							peb_predicate->SetText(new_text.data());
//							peb_predicate->setRedefined();
							((Formula *)peb_predicate)->SetPredicateText(set_text);
//							peb_predicate_temp->SetText(new_text.data());
//							peb_predicate_temp->setRedefined();
							((Formula *)peb_predicate_temp)->SetPredicateText(set_text);
							dsi1->PrepareSubItemData(new_text);	
//							dsi7->PrepareSubItemData(initial_predicate);	
*/
						}
					}
					if( (count_objs == 3) || (count_objs == 4) ) // если строится и подмножество 
					{
						EntityBase * peb_subset = entities->at(nItem + count_objs - 1);
						EntityBase * peb_subset_temp = temp_entities->at(nItem + count_objs - 1);
						if(!peb_subset->isRedefined())
						{

							SemanticString * dsi1 = &(m_list.DCU.at(nItem + 1)[1]);
							SemanticString * dsi4 = &(m_list.DCU.at(nItem + 1)[4]);
							SemanticString * dsi7 = &(m_list.DCU.at(nItem + 1)[7]);
							m_list.GetItemText(nItem + 1, 1, buf, 2047);    // получаю первоначальный текст предиката принадлежности
							((Formula *)peb_subset)->SetSubsetText(set_text);
							((Formula *)peb_subset_temp)->SetSubsetText(set_text);
							tstring new_text = peb_subset->getText();
							tstring f = _T(" <Symbol=/in> ");
							size_t pos = new_text.find(f);
							if(pos != tstring::npos)
							{
								new_text = new_text.substr(0, pos + f.length());
								new_text += _T("( ") + set_text + _T(" )");
							}
							dsi1->PrepareSubItemData(new_text);	

						}
					}
					m_list.RedrawItems(nFirst, nLast);
					nFirst += (count_objs - 1);
				}
			}

		}
		if(success)
			ReverseDefinition(temp_entities, entities, nFirst, entities->size(), this);
		m_list.RedrawItems(nFirst, entities->size());

		for(int i = temp_entities->size(); i > 0 ;i--)
		{
			SemanticString * dsi1 = &(m_list.DCU.at(i-1)[1]);
			EntityBase * base = temp_entities->at(i-1);
			tstring tstr = base->getText();
			dsi1->PrepareSubItemData(tstr);	
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
		temp_entities->clear();
		delete temp_entities;
	// заполняю схему из полученных из сохранённого xml-файла массивов Formulas и Sets
	// делаю одновременный перебор по Formulas и Sets, находя соотвествующие порядковые номера, соответствующие элементы заношу в схему
//		m_list.UpdateWindow();
	}
	}
}

	void SummaryDialog::OnLvnOdstatechangedSummarylist(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMLVODSTATECHANGE pStateChanged = reinterpret_cast<LPNMLVODSTATECHANGE>(pNMHDR);
		// TODO: добавьте свой код обработчика уведомлений
		if(m_list.GetSelectedCount() > 0)
		{
			m_RedefineBtn.ShowWindow(SW_SHOW);
		}
		else
			m_RedefineBtn.ShowWindow(SW_HIDE);
		*pResult = 0;
	}


	void SummaryDialog::OnRButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: добавьте свой код обработчика сообщений или вызов стандартного
		 CMenu menu;
 
     // Создаем контекстное меню.
 
    menu.LoadMenu(IDR_MENU_SYMBOLS);
 
     // Приводим координаты.
 
     ClientToScreen(&point);
 
 
     // Показываем контекстное меню.
 
     menu.TrackPopupMenu(TPM_RIGHTALIGN, point.x, point.y, this); 

 		CDialog::OnRButtonDown(nFlags, point);
	}
