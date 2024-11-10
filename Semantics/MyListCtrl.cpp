#include "stdafx.h"
#include "MyListCtrl.h"
//#include "Semantics.h"
//#include "SummaryDialog.h"
//#include "afxdialogex.h"
#include "common_functions.h"
#include "resource.h"

IMPLEMENT_DYNAMIC(CMyListCtrl, CMFCListCtrl)

CMyListCtrl::CMyListCtrl()
{
	subItemEdit = -1;
	itemEdit = -1;
	m_edit = NULL;
	m_bIsModified = false;
	formulas = NULL;
}

CMyListCtrl::~CMyListCtrl()
{
	if(m_edit != NULL)
		delete m_edit;
}


COLORREF CMyListCtrl::OnGetCellTextColor(int nRow, int nColum)
{
	if (!m_bColor)
	{
		return CMFCListCtrl::OnGetCellTextColor(nRow, nColum);
	}

	return(nRow % 2) == 0 ? RGB(128, 37, 0) : RGB(0, 0, 0);
}

COLORREF CMyListCtrl::OnGetCellBkColor(int nRow, int nColum)
{
	if (!m_bColor)
	{
		return CMFCListCtrl::OnGetCellBkColor(nRow, nColum);
	}

	if (m_bMarkSortedColumn && nColum == m_iSortedColumn)
	{
		return(nRow % 2) == 0 ? RGB(233, 221, 229) : RGB(176, 218, 234);
	}

	return(nRow % 2) == 0 ? RGB(253, 241, 249) : RGB(196, 238, 254);
}

HFONT CMyListCtrl::OnGetCellFont(int nRow, int nColum, DWORD /*dwData* = 0*/)
{
	if (!m_bModifyFont)
	{
		return NULL;
	}

	if (nColum == 2 &&(nRow >= 4 && nRow <= 8))
	{
		return afxGlobalData.fontDefaultGUIBold;
	}

	return NULL;
}


int CMyListCtrl::OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn)
{
	CString strItem1 = GetItemText((int)(lParam1 < lParam2 ? lParam1 : lParam2), iColumn);
	CString strItem2 = GetItemText((int)(lParam1 < lParam2 ? lParam2 : lParam1), iColumn);

	if (iColumn == 0)
	{
		int nItem1 = _ttoi(strItem1);
		int nItem2 = _ttoi(strItem2);
		return(nItem1 < nItem2 ? -1 : 1);
	}
	else
	{
		int iSort = _tcsicmp(strItem1, strItem2);
		return(iSort);
	}
}
BEGIN_MESSAGE_MAP(CMyListCtrl, CMFCListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CMyListCtrl::OnNMClick)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


void CMyListCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: добавьте свой код обработчика уведомлений
	int subItem = pNMItemActivate->iSubItem;
	int item = pNMItemActivate->iItem;
	if((subItem > 3) && (item >= 0) )
	{
		if( (itemEdit != item) || (subItemEdit != subItem) )
		{
			if( (m_edit != NULL) && (m_edit == m_edit->GetFocus()) )
			{
				m_edit->ShowWindow(SW_HIDE);
			}
			else
			{
				if(m_edit !=NULL)
				{
					subItemEdit = -1;
					itemEdit = -1;
					delete m_edit;
				}
				CFont editFont;
//				editFont = this->getfo
//				editFont.CreatePointFont(60, L"Segoe UI");
				CRect crect;
				this->GetSubItemRect(item, subItem, 0, crect);
				crect.bottom -= 1;
				crect.top += 1;
				crect.left += 1;
				crect.right -= 1;
				m_edit = new CEdit();
				m_edit->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | WS_BORDER, crect, this, IDC_LIST_EDIT); 
				m_edit->SetWindowTextT(GetItemText(item, subItem));
				m_edit->SetFont(GetFont(), 1);
				m_edit->ShowWindow(SW_SHOW);

				itemEdit = item;
				subItemEdit = subItem;
				m_edit->ShowCaret();
				m_edit->SetParent(this);
			}
		}
		else
		{
			m_edit->SetFocus();
			m_edit->ShowCaret();
		}
	}
	else
	{
		if(m_edit != NULL)
		{
			m_edit->ShowWindow(SW_HIDE);
		}
	}
	*pResult = 0;
//	MessageBox(_T("Clicked"), _T("OK"), MB_OK);
}


BOOL CMyListCtrl::PreTranslateMessage(MSG* pMsg)
{
	// TODO: добавьте специализированный код или вызов базового класса
	if( pMsg->message == WM_KEYDOWN )
	{
		if(pMsg->wParam == VK_ESCAPE)
		{
			if((m_edit != NULL) && (m_edit == m_edit->GetFocus()) )
			{
				m_edit->ShowWindow(SW_HIDE);

			}
			return true;
		}
		else if(pMsg->wParam == VK_RETURN)
		{
			if((m_edit != NULL) && (m_edit == m_edit->GetFocus()) )
			{
				m_edit->ShowWindow(SW_HIDE);
				CString cs;
				m_edit->GetWindowTextW(cs); 
				this->SetItemText(itemEdit, subItemEdit, cs);
				m_bIsModified = true;
			}
			return true;
		}
	}

	return CMFCListCtrl::PreTranslateMessage(pMsg);
}


void CMyListCtrl::SaveFormulas()
{
	for ( size_t i = 0; i < formulas->size(); i++)
	{
		Formula * icurr = formulas->at(i);
		TCHAR buf[2048];
		GetItemText(i, 4, buf, 2047);
		icurr->SetDescription(buf);
		GetItemText(i, 5, buf, 2047);
		icurr->SetAddons(buf);
	}
}

