//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
// SummaryDialog.cpp: ���� ����������
//

//TRANSLATED

#include "stdafx.h"
#include "Semantics.h"
#include "SummaryDialog.h"
#include "afxdialogex.h"
#include "common_functions.h"


// ���������� ���� SummaryDialog

IMPLEMENT_DYNAMIC(SummaryDialog, CDialog)

//
//  �����������
//
SummaryDialog::SummaryDialog(CWnd* pParent /*=NULL*/)
	: CDialog(SummaryDialog::IDD, pParent)
{
//	m_list.m_bColor = TRUE;
//	m_list.m_bModifyFont = TRUE;
}

//
//  ����������
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
// ����� ������������ �������� ��������� ��������� ��������� (������ � �������� ����������)
//
void  SummaryDialog::setFormulas(vector <EntityBase *> * all_entities)
{
	entities = all_entities;
}


// ����������� ��������� SummaryDialog

//
// ������������� �������� � �������� ������� � ��� ��������� ��� �������������
//
BOOL SummaryDialog::OnInitDialog()
{
	CDialog::OnInitDialog();    // ����������� ������������� �������� ����������� ������
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);    // ������������� ����������� ������ ����� ������ ������� ��������� � ��������� 
	// ����������������� �����
	
	// ���������� ������� � ������� ���������, ��������� �� ���������� � ������
	if (CURRENT_LANG_OF == "rus") {
		m_list.InsertColumn(0, _T("�����"), LVCFMT_LEFT, 100);
		m_list.InsertColumn(1, _T("�������"), LVCFMT_LEFT, 200);
		m_list.InsertColumn(2, _T("���"), LVCFMT_LEFT, 100);
		m_list.InsertColumn(3, _T("��������� ����������"), LVCFMT_LEFT, 120);
		m_list.InsertColumn(4, _T("��������"), LVCFMT_LEFT, 100);
		m_list.InsertColumn(5, _T("Addons"), LVCFMT_LEFT, 200);
		m_list.InsertColumn(6, _T("�����������"), LVCFMT_LEFT, 200);
		m_list.InsertColumn(7, _T("���. �����"), LVCFMT_LEFT, 200);
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

	int nColumns = 7;    // ����� ������� � ������� ���������
	// ��������� ������� "������ ��� ������"
	m_list.SetColumnReadOnly(0);
	m_list.SetColumnReadOnly(1);
	m_list.SetColumnReadOnly(2);
	m_list.SetColumnReadOnly(3);
	m_list.SetColumnReadOnly(6);
	m_list.SetColumnReadOnly(7);

	// ��������������� ������������� �������� ��������������, ������� ����� �������������� � ���������� ��� ������������� ����� (�������)
	CRect rect(0,0,20,20);
	m_edit.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | WS_BORDER, rect, this, IDC_LIST_EDIT); 
	m_edit.ShowWindow(SW_HIDE);
    m_list.SetDefaultEditor(NULL, NULL, &m_edit);	// ��������� ����� �������� ������������� ��������� �� ���������
	m_edit.SetFont(m_list.GetFont());    // ��������� ������ ��� �������� ��������������
	tstring str_number;
	tstring res, res_formula;
	m_list.SetItemCount(entities->size());     // ��������� ����� ����� � ������� ���������
	// ������� ��������� ����� � ���������� ����� �������
	for (size_t i = 0; i < entities->size(); i++)
	{
		SemanticString * dsi = new SemanticString[nColumns + 1];    // ��� (nColumns + 1) ����� � ������ ������ ������ SemanticString
		m_list.DCU.push_back(dsi);    //  ��������� ������ � ���� ������-��������� ��������� SemanticString
		str_number = to_tstring((long long)(i + 1));    // ������ � ������� ������ �������, ���������� � 1
		dsi[0].PrepareSubItemData(str_number);   //  ���������� ����� ������ � SemanticString
		EntityBase * base = entities->at(i);     // ��������� �� ��������� �������� 
		tstring text = base->getText();
		dsi[1].PrepareSubItemData(text);    // ���������� ����� �������� � SemanticString

//		tstring description = *base->getDescription();
//		dsi[4].PrepareSubItemData(description); 
		m_list.SetItemText(i, 4, base->getDescription()->data());    // ������������ � ������������ �������� �������� �������� ������ ������ ������� (�������������)
		m_list.SetItemText(i, 5, base->getAddOns()->data());    // ������������ � ������������ �������������� �������� �������� ����� ������ ������ ������� (�������������)


		dsi[6].PrepareSubItemData(*(base->getLabel()));    // ���������� � SemanticString ����������� �������
		if(base->isRedefined())
		{
			tstring redefined_text = *base->getRedefinedText(); 
			tstring initial_text = *base->getInitialText();
			trimWhitespaces(&redefined_text);
			trimWhitespaces(&initial_text);
			if((redefined_text.length() > 0) && (redefined_text.compare(initial_text))) 
				dsi[7].PrepareSubItemData(initial_text);    // ���������� � SemanticString ��������� ����������� �������
		}
		else
		{
			res.clear();
			dsi[7].PrepareSubItemData(res);
		}
		res = makeVarPartOfLabel(entities, base);

		if(!res.empty())    // ���� ������ �������� (���� ��������� ����������)
		{
			dsi[3].PrepareSubItemData(res);    // ���������� � SemanticString ������ ��������� ����������
		}
		res.clear();
		if ( base->getType() == FORMULA_SET )    // e��� �������� - ��������� ����������
		{
		}
		else    // ���� �������� - �������
		{
			Formula * icurr = (Formula *)base;    // ������� � ��������� �� �������
			// �������� ������ ����
			if (CURRENT_LANG_OF == "rus") {
				if (icurr->getFeature() == PERFORMED_FEATURE)
					res = _T("����������");
				else if (icurr->getFeature() == TRUTH_FEATURE)
					res = _T("��������");
				else if (icurr->getFeature() == FALSE_FEATURE)
					res = _T("������");
				else if (icurr->getFeature() == ATOMARN_FEATURE)
					res = _T("���������");
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
		if(!res.empty())    // ���� ������ ���� ������� (���� ��� �������) ��������
		{ 
			dsi[2].PrepareSubItemData(res);    // ���������� ������ ���� � SemanticString
		}

	}
	// ������������ ����� ��� ������� ���������/��������������
	CFont * m_curr = new CFont;    
//	m_curr->CreatePointFont(70, L"Microsoft Sans Serif");
	m_curr->CreatePointFont(70, L"Arial Unicode MS");
	m_list.SetIndexesFont(m_curr);
	m_list.SetFocus();
//	m_list.SetCallbackMask(LVIS_SELECTED|LVIS_FOCUSED);
	return true;
}



//
//  ������ ������������� ��� ������������ ������� �� ����������, ������ ���� ������
//
BOOL SummaryDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
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
// ������� ����� ������� � ���������� �������� ������������� ����� � ��������������� ��������� �����
//
void SummaryDialog::SaveAndExit()
{
	for ( size_t i = 0; i < entities->size(); i++)    // ������� ���� ���������, ������� ��, ������� � ����� � �������
	{
		EntityBase * base = entities->at(i);    // ��������� �� ��������� ��������
		TCHAR buf[2048];    // ����� ��� ������
		buf[0]=TCHAR(0x00);
		m_list.GetItemText(i, 4, buf, 2047);    // �������� (�������, �� Semanticstring) ����� �������� ������ � �����
		base->SetDescription(buf);    // ��������� ����� �� ������ � �������� ��������
		buf[0]=TCHAR(0x00);
		m_list.GetItemText(i, 5, buf, 2047);    // �������� (�������, �� Semanticstring) ����� ����� ������ � �����
		base->SetAddons(buf);    // ��������� ����� �� ������ � ������������� �������� ��������
		buf[0]=TCHAR(0x00);
		m_list.GetItemText(i, 1, buf, 2047);    // �������� (�������, �� Semanticstring) ����� ������ ������ � �����
		base->SetText(buf);    // ��������� ����� �� ������ � �������� ��������
	}
}

//
//  ���������� ������� �� ������ "������"
//
void SummaryDialog::OnCancel()
{
	CDialog::OnCancel();
}

/*
//
//  ���������� ������� �� ������ "��"
//
void SummaryDialog::OnOK()
{
	CDialog::OnOK();
}
*/


//
//  ���������� ������� �� ������ "��"
//
void SummaryDialog::OnBnClickedOk()
{
	// ������� ����� ������� � ���������� �������� ������������� ����� � ��������������� ��������� �����
	SaveAndExit();
	CDialog::OnOK();
}


//
// ����� ���������� ������ ��������
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


// ������� ��� ���������� ������������ ������ temp_entities �� ������ ��� ������������� entities � first ������ �� last
//void SummaryDialog::ReverseDefinition(vector <EntityBase *> * temp_entities, vector <EntityBase *> * entities, int first, int last)
void ReverseDefinition(vector <EntityBase *> * temp_entities, vector <EntityBase *> * entities, int first, int last, SummaryDialog *psd)
{
	TCHAR buf[2048];    // ����� ��� ������			
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
						psd->m_list.GetItemText(i1, 1, buf, 2047);    // ������� ����� ���������������
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
						vector <EntityVariable *> excluding; // ������ ��������� ����������, ������� ���� ������� �� ������� ��������� ���������� ����������� 
						// ���������, ����� �������� ��������� ���������� ������������
						excluding = *(parent_set->getBaseVariables());
						vector <EntityVariable *> free_variables1 = *(f->getFreeVariables());

						if(free_variables1.size() > 0)
							excluding.push_back(free_variables1.at(free_variables1.size() - 1));
						f_new->subset(temp_entities, parent_set, &excluding);    // ������ ������������ ����������
						f_new->putTextOfFormula(temp_entities);
						f_new->SetLabel(temp_entities);    // ��������� �����������
						temp_entities->push_back((EntityBase *)f_new);   // �������� ��������� ������������ � �����
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

// ������� ��������� ������ ������ �� �����������, ������� ����� ���� ������������� ���������� (���� ����� � ����������� �������) � ���� ��� �������, 
// ���������, ��� �� ��� ����������� ��������� �� ���������� ����������� � ������� �������
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
	// TODO: �������� ���� ��� ����������� �����������
	tstring mess, caption;
	if (CURRENT_LANG_OF == "rus") {
		mess = tstring(_T("�� ����������� �������������� �������. ���� �� ����������� � ����� ����������� ��������� �������, ��������� �� �� ���������� � �������������. ��� ���������� �� ��������������� ����� �������. ����������?"));
		caption = tstring(_T("��������!"));
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
			TCHAR buf[2048];    // ����� ��� ������
			m_list.GetItemText(nItem11, 4, buf, 2047);    // ������� ����� ���������������
			tstring set_text = buf;
			EntityBase * base = entities->at(nItem11);
			if (CURRENT_LANG_OF == "rus") {

				if (!IfCorrectRedefinition(entities->at(nItem11), set_text))
				{

					tstring mess(_T("� ��������������� "));
					mess += to_tstring((long long)(nItem11 + 1));
					mess += _T(" ������� �� ������� ��� ��������� ���������� ��� ����� �������");
					tstring caption(_T("��������!"));
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
		TCHAR buf[2048];    // ����� ��� ������
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
			m_list.GetItemText(nItem, 4, buf, 2047);    // ������� ����� ���������������
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
					MessageBox(_T("������������ �����"), _T("������"));
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
			if(base->getType() == FORMULA_SET)		// ���� �������������� ��������� ����������
			{
				EntityBase * peb = entities->at(nItem);			// �������� ��������� �� ����� EntityBase, ��������������� ��������� ����������
				EntityVariable * pnaming = ((FormulaSet *)peb)->getNaming(); // �������� ��������� �� ����������-�����������
				pnaming->SetRedefinition(set_text);						// ��������� ����� ���������������
				SetGroup sg = peb->isPartOfSetGroup(entities);	// ������ �������� �� ����� ��������� � ������ ��������� ����������
				EntityBase * peb_first = get<0>(sg);
				int count_objs = get<1>(sg);					// ����� �������� � ������ ��������� ����������
				if(count_objs > 1)								// ���� � ������ ���� ��� ������� ������ ��������� ����������
				{
					nLast += count_objs;						// ����������� �������, �� �������� �������� �������� ���������������, �� ����� ��������� � ������
					ReverseDefinition(temp_entities, entities, nFirst, nLast, this);
					if( (count_objs == 2) || (count_objs == 4) ) // ���� �������� � �������� �������������� 
					{
						EntityBase * peb_predicate = entities->at(nItem + 1);
						EntityBase * peb_predicate_temp = temp_entities->at(nItem + 1);
						if(!peb_predicate->isRedefined())		// ���� �������� �������������� �� �������������
						{
/*
							SemanticString * dsi1 = &(m_list.DCU.at(nItem + 1)[1]);
							SemanticString * dsi4 = &(m_list.DCU.at(nItem + 1)[4]);
							SemanticString * dsi7 = &(m_list.DCU.at(nItem + 1)[7]);
							m_list.GetItemText(nItem + 1, 1, buf, 2047);    // ������� �������������� ����� ��������� ��������������
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
					if( (count_objs == 3) || (count_objs == 4) ) // ���� �������� � ������������ 
					{
						EntityBase * peb_subset = entities->at(nItem + count_objs - 1);
						EntityBase * peb_subset_temp = temp_entities->at(nItem + count_objs - 1);
						if(!peb_subset->isRedefined())
						{

							SemanticString * dsi1 = &(m_list.DCU.at(nItem + 1)[1]);
							SemanticString * dsi4 = &(m_list.DCU.at(nItem + 1)[4]);
							SemanticString * dsi7 = &(m_list.DCU.at(nItem + 1)[7]);
							m_list.GetItemText(nItem + 1, 1, buf, 2047);    // ������� �������������� ����� ��������� ��������������
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
	// �������� ����� �� ���������� �� ����������� xml-����� �������� Formulas � Sets
	// ����� ������������� ������� �� Formulas � Sets, ������ �������������� ���������� ������, ��������������� �������� ������ � �����
//		m_list.UpdateWindow();
	}
	}
}

	void SummaryDialog::OnLvnOdstatechangedSummarylist(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMLVODSTATECHANGE pStateChanged = reinterpret_cast<LPNMLVODSTATECHANGE>(pNMHDR);
		// TODO: �������� ���� ��� ����������� �����������
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
		// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
		 CMenu menu;
 
     // ������� ����������� ����.
 
    menu.LoadMenu(IDR_MENU_SYMBOLS);
 
     // �������� ����������.
 
     ClientToScreen(&point);
 
 
     // ���������� ����������� ����.
 
     menu.TrackPopupMenu(TPM_RIGHTALIGN, point.x, point.y, this); 

 		CDialog::OnRButtonDown(nFlags, point);
	}
