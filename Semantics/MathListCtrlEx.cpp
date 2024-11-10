//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
// ListCtrlEx.cpp : implementation file
//



//TRANSLATED


#include "stdafx.h"
#include "MathListCtrlEx.h"
#include "common_functions.h"



CMathListCtrlEx::EditorInfo::EditorInfo()
:m_pfnInitEditor(NULL)
,m_pfnEndEditor(NULL)
,m_pWnd(NULL)
,m_bReadOnly(false)
{
}
CMathListCtrlEx::EditorInfo::EditorInfo(PFNEDITORCALLBACK pfnInitEditor, PFNEDITORCALLBACK pfnEndEditor, CWnd *pWnd)
:m_pfnInitEditor(pfnInitEditor)
,m_pfnEndEditor(pfnEndEditor)
,m_pWnd(pWnd)
,m_bReadOnly(false)
{
}

CMathListCtrlEx::CellInfo::CellInfo(int nColumn)
:m_clrBack(-1)
,m_clrText(-1)
,m_dwUserData(NULL)
,m_nColumn(nColumn)
{
	
}
CMathListCtrlEx::CellInfo::CellInfo(int nColumn, COLORREF clrBack, COLORREF clrText, DWORD_PTR dwUserData)
:m_clrBack(clrBack)
,m_clrText(clrText)
,m_dwUserData(dwUserData)
,m_nColumn(nColumn)
{
}
CMathListCtrlEx::CellInfo::CellInfo(int nColumn, EditorInfo eiEditor, COLORREF clrBack, COLORREF clrText, DWORD_PTR dwUserData)
:m_clrBack(clrBack)
,m_clrText(clrText)
,m_dwUserData(dwUserData)
,m_eiEditor(eiEditor)
,m_nColumn(nColumn)
{
}
CMathListCtrlEx::CellInfo::CellInfo(int nColumn, EditorInfo eiEditor, DWORD_PTR dwUserData)
:m_clrBack(-1)
,m_clrText(-1)
,m_dwUserData(dwUserData)
,m_eiEditor(eiEditor)
,m_nColumn(nColumn)
{
}

CMathListCtrlEx::ColumnInfo::ColumnInfo(int nColumn)
:m_eiEditor()
,m_clrBack(-1)
,m_clrText(-1)
,m_nColumn(nColumn)
,m_eSort(None)
,m_eCompare(NotSet)
,m_fnCompare(NULL)
{
}
CMathListCtrlEx::ColumnInfo::ColumnInfo(int nColumn, PFNEDITORCALLBACK pfnInitEditor, PFNEDITORCALLBACK pfnEndEditor, CWnd *pWnd)
:m_eiEditor(pfnInitEditor, pfnEndEditor, pWnd)
,m_nColumn(nColumn)
,m_clrBack(-1)
,m_clrText(-1)
,m_eSort(None)
,m_eCompare(NotSet)
,m_fnCompare(NULL)
{
}
CMathListCtrlEx::ItemData::ItemData(DWORD_PTR dwUserData)
:m_clrBack(0xFFFFFFFF)
,m_clrText(0xFFFFFFFF)
,m_dwUserData(dwUserData)
{
}
CMathListCtrlEx::ItemData::ItemData(COLORREF clrBack, COLORREF clrText, DWORD_PTR dwUserData)
:m_clrBack(clrBack)
,m_clrText(clrText)
,m_dwUserData(dwUserData)
{
}
CMathListCtrlEx::ItemData::~ItemData()
{
	while(m_aCellInfo.GetCount()>0)
	{
		CellInfo *pInfo = (CellInfo*)m_aCellInfo.GetAt(0);
		m_aCellInfo.RemoveAt(0);
		delete pInfo;
	}
}
// CMathListCtrlEx

IMPLEMENT_DYNAMIC(CMathListCtrlEx, CListCtrl)

CMathListCtrlEx::CMathListCtrlEx()
:m_pEditor(NULL)
,m_nEditingRow(-1)
,m_nEditingColumn(-1)
,m_msgHook()
,m_nRow(-1)
,m_nColumn(-1)
,m_bHandleDelete(FALSE)
,m_nSortColumn(-1)
,m_fnCompare(NULL)
,m_hAccel(NULL)
,m_dwSortData(NULL)
, m_bInvokeAddNew(FALSE)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif
	m_fSymbol = new CFont;
//	m_fSymbol->CreatePointFont(140, L"Symbol");
	m_fSymbol->CreatePointFont(140, L"Arial Unicode MS");
	m_fIndexes = 0;

}
#define ID_EDITOR_CTRL		5000
CMathListCtrlEx::~CMathListCtrlEx()
{
	DeleteAllItemsData();
	DeleteAllColumnInfo();
	if(m_fSymbol)
		delete m_fSymbol;
	if(m_fIndexes)
		delete m_fIndexes;
	for ( size_t i = 0; i < DCU.size(); i++)
		delete []DCU.at(i);
}


BEGIN_MESSAGE_MAP(CMathListCtrlEx, CListCtrl)
	ON_NOTIFY_REFLECT_EX(NM_DBLCLK, &CMathListCtrlEx::OnNMDblclk)
	ON_NOTIFY_REFLECT_EX(NM_CUSTOMDRAW, &CMathListCtrlEx::OnNMCustomdraw)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &CMathListCtrlEx::OnHdnItemclick)
//	ON_WM_MEASUREITEM()
END_MESSAGE_MAP()



// CMathListCtrlEx message handlers


// Retrieves the data (lParam) associated with a particular item.
DWORD_PTR CMathListCtrlEx::GetItemData(int nItem) const
{

	ItemData* pData = (ItemData*)GetItemDataInternal(nItem);
	if(!pData) return NULL;
	return pData->m_dwUserData;
}
// Retrieves the data (lParam) associated with a particular item.
DWORD_PTR CMathListCtrlEx::GetItemDataInternal(int nItem) const
{
	return CListCtrl::GetItemData(nItem);
}
int CMathListCtrlEx::InsertItem(int nItem, LPCTSTR lpszItem)
{
	int ret = CListCtrl::InsertItem(nItem, lpszItem);
	SetItemData(ret, 0);
	return ret;
}
int CMathListCtrlEx::InsertItem(int nItem, LPCTSTR lpszItem, int nImage)
{
	int ret = CListCtrl::InsertItem(nItem, lpszItem, nImage);
	SetItemData(ret, 0);
	return ret;
}
int CMathListCtrlEx::InsertItem(const LVITEM* pItem)
{
	int ret = 0;
	LVITEM pI = *pItem;
	if(pItem && (pItem->mask & LVIF_PARAM))
	{
		pI.mask &= (~LVIF_PARAM);
	}
	ret = CListCtrl::InsertItem(&pI);
	SetItemData(ret, pItem->lParam);
	return ret;
}
// Sets the data (lParam) associated with a particular item.
BOOL CMathListCtrlEx::SetItemData(int nItem, DWORD_PTR dwData)
{
	ItemData* pData = (ItemData*)GetItemDataInternal(nItem);
	if(!pData)
	{
		pData = new ItemData(dwData);
		m_aItemData.Add(pData);
	}
	else
		pData->m_dwUserData = dwData;
	return CListCtrl::SetItemData(nItem, (DWORD_PTR)pData);
}

// Removes a single item from the control.
BOOL CMathListCtrlEx::DeleteItem(int nItem)
{
	DeleteItemData(nItem);
	return CListCtrl::DeleteItem(nItem);
}
// Removes all items from the control.
BOOL CMathListCtrlEx::DeleteAllItems()
{
	int nCount = this->GetItemCount();
	DeleteAllItemsData();
	return CListCtrl::DeleteAllItems();
}
BOOL CMathListCtrlEx::DeleteAllItemsData( )
{
	while(m_aItemData.GetCount()>0)
	{
		ItemData* pData = (ItemData*)m_aItemData.GetAt(0);
		if(pData) delete pData;
		m_aItemData.RemoveAt(0);
	}

	return TRUE;
}
BOOL CMathListCtrlEx::DeleteItemData(int nItem)
{
	if(nItem < 0 || nItem > GetItemCount()) return FALSE;
	ItemData* pData = (ItemData*)CListCtrl::GetItemData(nItem);
	
	INT_PTR nCount = m_aItemData.GetCount();
	for(INT_PTR i = 0; i < nCount && pData; i++)
	{
		if(m_aItemData.GetAt(i) == pData)
		{
			m_aItemData.RemoveAt(i);
			break;
		}
	}

	if(pData) delete pData;

	return TRUE;
}	
BOOL CMathListCtrlEx::DeleteAllColumnInfo( )
{
	while(m_aColumnInfo.GetCount()>0)
	{
		ColumnInfo* pData = (ColumnInfo*)m_aColumnInfo.GetAt(0);
		if(pData) delete pData;
		m_aColumnInfo.RemoveAt(0);
	}

	return TRUE;
}
BOOL CMathListCtrlEx::DeleteColumnInfo(int nColumn)
{
	if(nColumn < 0 || nColumn > GetColumnCount()) return FALSE;
	ColumnInfo* pData = (ColumnInfo*)GetColumnInfo(nColumn);
	
	INT_PTR nCount = m_aColumnInfo.GetCount();
	for(INT_PTR i = 0; i < nCount && pData; i++)
	{
		if(m_aColumnInfo.GetAt(i) == pData)
		{
			m_aColumnInfo.RemoveAt(i);
			break;
		}
	}

	if(pData) delete pData;

	return TRUE;
}

void CMathListCtrlEx::SetColumnEditor(int nColumn, PFNEDITORCALLBACK pfnInitEditor, PFNEDITORCALLBACK pfnEndEditor, CWnd* pWnd)
{
	ColumnInfo* pColInfo = GetColumnInfo(nColumn);
	if(!pColInfo)
	{ 
		pColInfo = new ColumnInfo(nColumn);  
		m_aColumnInfo.Add(pColInfo);
	}
	pColInfo->m_eiEditor.m_pfnInitEditor = pfnInitEditor;
	pColInfo->m_eiEditor.m_pfnEndEditor = pfnEndEditor;
	pColInfo->m_eiEditor.m_pWnd = pWnd;
	
}

void CMathListCtrlEx::SetColumnEditor(int nColumn, CWnd* pWnd)
{
	SetColumnEditor(nColumn, NULL, NULL, pWnd);
}
void CMathListCtrlEx::SetRowEditor(int nRow, CWnd* pWnd)
{
	SetRowEditor(nRow, NULL, NULL, pWnd);
}
void CMathListCtrlEx::SetRowEditor(int nRow, PFNEDITORCALLBACK pfnInitEditor, PFNEDITORCALLBACK pfnEndEditor, CWnd* pWnd)
{
	ItemData* pData = (ItemData*)GetItemDataInternal(nRow);
	if(!pData)
	{ 
		SetItemData(nRow, 0);
		pData = (ItemData*)GetItemDataInternal(nRow);
	}
	pData->m_eiEditor.m_pfnInitEditor = pfnInitEditor;
	pData->m_eiEditor.m_pfnEndEditor = pfnEndEditor;
	pData->m_eiEditor.m_pWnd = pWnd;
	
}

CMathListCtrlEx::ColumnInfo* CMathListCtrlEx::GetColumnInfo(int nColumn)
{
	INT_PTR nCount = m_aColumnInfo.GetCount();
	for(INT_PTR i = 0; i < nCount; i++)
	{
		ColumnInfo* pColInfo = (ColumnInfo*)m_aColumnInfo.GetAt(i);
		if(pColInfo->m_nColumn == nColumn) return pColInfo;
	}
	return NULL;
}
int CMathListCtrlEx::FindItem(LVFINDINFO* pFindInfo, int nStart ) const
{
	if(pFindInfo->flags & LVIF_PARAM)
	{
		int nCount = GetItemCount();
		for(int i = nStart+1; i < nCount; i++)
		{
			if(pFindInfo->lParam == GetItemData(i)) return i;
		}
		return -1;
	}
	else
	{
		return CListCtrl::FindItem(pFindInfo, nStart);
	}
}
int CMathListCtrlEx::GetItemIndexFromData(DWORD_PTR dwData)
{
	LVFINDINFO find;
	find.flags = LVFI_PARAM;
	find.lParam = dwData;
	return CListCtrl::FindItem(&find);
}
int CALLBACK CMathListCtrlEx::CompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CMathListCtrlEx *This = reinterpret_cast<CMathListCtrlEx*>(lParamSort);
	ColumnInfo *pColInfo;
	int nSort = 0;
	int nCompare = 0;

	if(!This) return 0;
	if(!(This->m_nSortColumn < 0 || This->m_nSortColumn >= This->GetColumnCount()) )
	{
		pColInfo = This->GetColumnInfo(This->m_nSortColumn);
		if(pColInfo && (pColInfo->m_eSort & SortBits)) 
		{
			nSort = pColInfo->m_eSort & Ascending ? 1: -1 ;
			if(!This->m_fnCompare && pColInfo->m_fnCompare) This->m_fnCompare = pColInfo->m_fnCompare;
		}
	}
	if(This->m_fnCompare && This->m_fnCompare != &CMathListCtrlEx::CompareProc) 
	{
		ItemData *pD1 = reinterpret_cast<ItemData*>(lParam1);
		ItemData *pD2 = reinterpret_cast<ItemData*>(lParam2);
		if(pD1) lParam1 = pD1->m_dwUserData;
		if(pD2) lParam2 = pD2->m_dwUserData;
		nCompare = This->m_fnCompare(lParam1, lParam2, This->m_dwSortData?This->m_dwSortData:This->m_nSortColumn);
		if(!This->m_dwSortData && nSort) 
		{
			return nCompare * nSort;
		}
	}
	if(!nSort) return 0;
	
	int nLeft = This->GetItemIndexFromData(lParam1); 
	int nRight = This->GetItemIndexFromData(lParam2);

	if(nLeft < 0) nLeft = lParam1;
	if(nRight < 0) nRight = lParam2;
	int nCount = This->GetItemCount();
	if(nLeft < 0 || nRight < 0 || nLeft >= nCount || nRight >= nCount) return 0;
	nCompare = Compare(nLeft, nRight, lParamSort);
	return (nCompare * nSort);
}
void CMathListCtrlEx::OnHdnItemclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW*  phdr = reinterpret_cast<NM_LISTVIEW*>(pNMHDR);
	SortOnColumn(phdr->iSubItem, TRUE);
	*pResult = 0;
	//return FALSE;
}
BOOL CMathListCtrlEx::SortItems(PFNLVCOMPARE pfnCompare, DWORD_PTR dwData)
{
	int nCount = GetItemCount();
	DWORD_PTR dwEditingItemData = 0;
	if(m_nEditingRow >= 0 && m_nEditingRow < nCount)
	 dwEditingItemData = GetItemDataInternal(m_nEditingRow);
	CString dbg;
	dbg.Format(_T("\nBefore : %d"), m_nEditingRow);
	OutputDebugString(dbg);
	m_fnCompare = pfnCompare;
	m_dwSortData = dwData;
	BOOL ret = CListCtrl::SortItems(CompareProc, (DWORD_PTR)this);
	m_fnCompare = NULL;
	m_dwSortData = NULL;
	if(dwEditingItemData) 
		m_nEditingRow = GetItemIndexFromData(dwEditingItemData);
	
	dbg.Format(_T("\nAfter : %d"), m_nEditingRow);
	OutputDebugString(dbg);
	return ret;
}

BOOL CMathListCtrlEx::SortOnColumn(int nColumn, BOOL bChangeOrder)
{
	ColumnInfo *pColInfo;
	if((pColInfo = GetColumnInfo(nColumn)) && (pColInfo->m_eSort & SortBits ))
	{
		if(pColInfo->m_eSort & Auto)
		{
			pColInfo->m_eSort =(Sort)((pColInfo->m_eSort & (Ascending | Descending)) ? pColInfo->m_eSort : pColInfo->m_eSort | Descending);
			if(bChangeOrder) pColInfo->m_eSort = (Sort)(pColInfo->m_eSort ^ (Ascending | Descending));
		}		
		CHeaderCtrl *pHdr = this->GetHeaderCtrl();
		HDITEM hd;
		hd.mask = HDI_FORMAT;
		if(pHdr)
		{
			pHdr->GetItem(m_nSortColumn, &hd);
			hd.fmt = hd.fmt & ~(HDF_SORTDOWN|HDF_SORTUP);			
			pHdr->SetItem(m_nSortColumn, &hd);
		}
		m_nSortColumn = nColumn;
		CListCtrl::SortItems(CompareProc, (DWORD_PTR)this);
		if(pHdr)
		{
			pHdr->GetItem(nColumn, &hd);
			hd.fmt = hd.fmt & ~(HDF_SORTDOWN|HDF_SORTUP);
			hd.fmt |= pColInfo->m_eSort & Ascending ? HDF_SORTUP : HDF_SORTDOWN;
			pHdr->SetItem(nColumn, &hd);
		}		
		return TRUE;
	}
	return FALSE;
}

BOOL CMathListCtrlEx::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
	if(!pNMListView) return FALSE;
	int nItem = pNMListView->iItem, nSubItem = pNMListView->iSubItem;		

	*pResult = DisplayEditor(nItem, nSubItem);

	return *pResult;
}

BOOL CMathListCtrlEx::EnsureSubItemVisible(int nItem, int nSubItem, CRect *pRect)
{
	BOOL ret = EnsureVisible(nItem, FALSE);
	CRect rect;
	GetSubItemRect(nItem, nSubItem, LVIR_LABEL, rect);
	CRect rtList;
	GetClientRect(&rtList);
	if(rect.right > rtList.Width()) Scroll(CSize( rect.Width() > rtList.Width()?rect.left : rect.right - rtList.Width(), 0));
	if(rect.left < 0) Scroll(CSize(rect.left));
	if(pRect)
	{
		GetSubItemRect(nItem, nSubItem, LVIR_LABEL, rect);
		rect.right = min(rect.right, rtList.Width()-4);
		*pRect = rect;
	}
	return ret;
}
BOOL CMathListCtrlEx::DisplayEditor(int nItem, int nSubItem)
{
	int nCount = GetItemCount();
	DWORD_PTR dwEditingItemData = 0;
	if(nItem >= 0 && nItem < nCount)
	 dwEditingItemData = GetItemDataInternal(nItem);
	HideEditor();
	if(dwEditingItemData) 
		nItem = GetItemIndexFromData(dwEditingItemData);
	if(nItem < 0 || nItem > nCount || nSubItem < 0 || nSubItem > this->GetColumnCount() 
		|| IsColumnReadOnly(nSubItem) || IsRowReadOnly(nItem) || IsCellReadOnly(nItem, nSubItem)) return FALSE;
	CRect rectSubItem;
	//GetSubItemRect(nItem, nSubItem, LVIR_LABEL, rectSubItem);
	EnsureSubItemVisible(nItem, nSubItem, &rectSubItem);

	CellInfo *pCellInfo = GetCellInfo(nItem, nSubItem);
	ColumnInfo *pColInfo = GetColumnInfo(nSubItem);
	ItemData *pRowInfo = (ItemData *)GetItemDataInternal(nItem);

	m_pEditor = &m_eiDefEditor;
	BOOL bReadOnly = FALSE;
	if(pColInfo && !(bReadOnly|= pColInfo->m_eiEditor.m_bReadOnly) && pColInfo->m_eiEditor.IsSet())
	{				
		m_pEditor = &pColInfo->m_eiEditor;
	}
	if(pRowInfo && !(bReadOnly|= pRowInfo->m_eiEditor.m_bReadOnly) && pRowInfo->m_eiEditor.IsSet())
	{				
		m_pEditor = &pRowInfo->m_eiEditor;
	}
	if(pCellInfo && !(bReadOnly|= pCellInfo->m_eiEditor.m_bReadOnly) && pCellInfo->m_eiEditor.IsSet())
	{
		m_pEditor = &pCellInfo->m_eiEditor;
	}
	if(bReadOnly || !m_pEditor || !m_pEditor->IsSet() || m_pEditor->m_bReadOnly){m_pEditor = NULL; return  FALSE;}
	
	m_nEditingRow = nItem;
	m_nEditingColumn = nSubItem;
	m_nRow = nItem;
	m_nColumn = nSubItem;
	CString text =  GetItemText(nItem, nSubItem);
	if(m_pEditor->m_pfnInitEditor) 
		m_pEditor->m_pfnInitEditor(&m_pEditor->m_pWnd, nItem, nSubItem, text, GetItemData(nItem), this, TRUE);

	if(!m_pEditor->m_pWnd) return  FALSE;
	SelectItem(-1, FALSE);
	if(!m_pEditor->m_pfnInitEditor) m_pEditor->m_pWnd->SetWindowText(text);

	m_pEditor->m_pWnd->SetParent(this);
	m_pEditor->m_pWnd->SetOwner(this);

	ASSERT(m_pEditor->m_pWnd->GetParent() == this);	
	m_pEditor->m_pWnd->SetWindowPos(NULL, rectSubItem.left, rectSubItem.top, rectSubItem.Width(), rectSubItem.Height(), SWP_SHOWWINDOW);	
	m_pEditor->m_pWnd->ShowWindow(SW_SHOW);
	m_pEditor->m_pWnd->SetFocus();

	m_msgHook.Attach(m_pEditor->m_pWnd->m_hWnd, this->m_hWnd);

	return TRUE;
}

CMathListCtrlEx::CellInfo* CMathListCtrlEx::GetCellInfo(int nItem, int nSubItem)
{
	ItemData* pData = (ItemData*)GetItemDataInternal(nItem);
	if(pData == NULL) return NULL;
	INT_PTR nCount = pData->m_aCellInfo.GetCount();
	for(INT_PTR i = 0; i < nCount; i++)
	{
		CellInfo *pInfo = (CellInfo*)pData->m_aCellInfo.GetAt(i);
		if(pInfo && pInfo->m_nColumn == nSubItem) return pInfo;
	}
	return NULL;
}

void CMathListCtrlEx::HideEditor(BOOL bUpdate)
{
	CSingleLock lock(&m_oLock, TRUE);
	if(lock.IsLocked() && m_msgHook.Detach())
	{	
		if(m_pEditor && m_pEditor->m_pWnd)
		{
			m_pEditor->m_pWnd->ShowWindow(SW_HIDE);
			CString text;
			DWORD_PTR dwData = 0;
			if(GetItemCount() > m_nEditingRow)
			{
				text =  GetItemText(m_nEditingRow, m_nEditingColumn);
				dwData = GetItemData(m_nEditingRow);
			}
			else
			{
				bUpdate = FALSE;
			}
			if(m_pEditor->m_pfnEndEditor)
			{
				bUpdate = m_pEditor->m_pfnEndEditor(&m_pEditor->m_pWnd, m_nEditingRow, m_nEditingColumn, text, dwData, this, bUpdate);
			}
			else
			{
				m_pEditor->m_pWnd->GetWindowText(text);
			}
			if(bUpdate)
			{
				SetItemText(m_nEditingRow, m_nEditingColumn, text);
			}
			if(GetItemCount() > m_nEditingRow) Update(m_nEditingRow);
			if(bUpdate == -1) SortOnColumn(m_nEditingColumn);
			m_pEditor = NULL;
		}
	}
	lock.Unlock();
}

int CMathListCtrlEx::GetColumnCount(void)
{
	CHeaderCtrl *pHdr = GetHeaderCtrl();
	if(pHdr) return pHdr->GetItemCount();
	int i = 0;
	LVCOLUMN col;
	col.mask = LVCF_WIDTH;
	while(GetColumn(i++, &col));
	return i;
}

BOOL CMathListCtrlEx::PreTranslateMessage(MSG* pMsg)
{
	if((m_hAccel && GetParent() && GetFocus() == this && ::TranslateAccelerator(GetParent()->m_hWnd, m_hAccel, pMsg))) return TRUE;
	
	if(pMsg->message == WM_KEYDOWN )
	{
		if( pMsg->wParam == VK_TAB && (GetKeyState(VK_CONTROL)>>8 != -1))
		{
			int nCount = GetItemCount();
			int nColCount = GetColumnCount();
			if(m_pEditor && m_pEditor->m_pWnd && m_pEditor->m_pWnd->m_hWnd == pMsg->hwnd)
			{
				PostMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
				return TRUE;
			}
			bool bShiftPressed = (GetKeyState(VK_SHIFT)>>8 == -1);
			if(!bShiftPressed && nCount == 0 && OnAddNew())
			{
				nCount = GetItemCount();
				m_nColumn = 0;
			}
			if(nCount > 0 && nColCount > 0)
			{
				BOOL bContinue;
				do
				{
					bContinue = FALSE;
					if(m_nRow < 0 || m_nColumn < 0)
					{ 
						m_nRow = bShiftPressed ? nCount - 1: 0; 
						m_nColumn = bShiftPressed ? nColCount - 1: 0;
					}
					else if(m_nRow >= nCount || m_nColumn >= nColCount)
					{
						m_nRow = bShiftPressed ? nCount - 1: 0 ; 
						m_nColumn = bShiftPressed ? nColCount - 1: 0;
					}
					else
					{
						m_nColumn += (bShiftPressed ? -1 : 1);
						if(m_nColumn <0 || m_nColumn >= nColCount)
						{
							m_nRow += (bShiftPressed ? -1 : 1);
							m_nColumn = (bShiftPressed ? nColCount-1 : 0);
						}
					}
					
					if(m_bInvokeAddNew && ((m_nRow == nCount -1 && m_nColumn >= nColCount)||m_nRow >= nCount))
					{
						HideEditor();
						if(OnAddNew())
						{
							nCount = GetItemCount();
							m_nColumn = 0;
						}
						else return TRUE;
					}
					if(m_nRow >= 0 && m_nRow < nCount && m_nColumn >= 0 && m_nColumn < nColCount )
					{					
						if(DisplayEditor(m_nRow, m_nColumn))
							return TRUE;
						bContinue = TRUE;
					}
				}while(bContinue);
			}
		}
		else if( pMsg->wParam == VK_DELETE  && m_bHandleDelete)
		{
			DeleteSelectedItems();
			return TRUE;
		}
	}
	else if( ( pMsg->message == WM_LBUTTONDOWN) && (GetKeyState(VK_CONTROL)>>8 != -1)) // ( pMsg->message == WM_LBUTTONUP) ||
	{
//		return TRUE;
		UINT i, uSelectedCount = GetSelectedCount();
		if(uSelectedCount > 0)
		{
			int  nItem = -1;
			for (i=0; i < uSelectedCount; i++)
			{
				nItem = GetNextItem(nItem, LVNI_SELECTED);
				SetItemState(nItem, 0, LVIS_SELECTED);
//				m_list.RedrawItems(nFirst, nLast);
			}		
		}
	}
	return CListCtrl::PreTranslateMessage(pMsg);
	
}



void CMathListCtrlEx::SetRowColors(int nItem, COLORREF clrBk, COLORREF clrText)
{
	
	ItemData* pData = (ItemData*)GetItemDataInternal(nItem);
	if(!pData) SetItemData(nItem, 0);
	pData = (ItemData*)GetItemDataInternal(nItem);
	if(!pData) return;

	pData->m_clrText = clrText;
	pData->m_clrBack = clrBk;
	Update(nItem);
}
BOOL CMathListCtrlEx::AddItem(int ItemIndex, int SubItemIndex, LPCTSTR ItemText, int ImageIndex)
{
	LV_ITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = ItemIndex;
	lvItem.iSubItem = SubItemIndex;
	lvItem.pszText = (LPTSTR) ItemText;
	if(ImageIndex != -1){
		lvItem.mask |= LVIF_IMAGE;
		lvItem.iImage |= LVIF_IMAGE;
	}
	if(SubItemIndex == 0)
		return InsertItem(&lvItem);
	return SetItem(&lvItem);
}
LRESULT CMathListCtrlEx::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(message == UM_HIDEEDITOR)
	{
		HideEditor((BOOL)wParam);
	}
	return CListCtrl::WindowProc(message, wParam, lParam);
}

void CMathListCtrlEx::SetColumnColors(int nColumn, COLORREF clrBack, COLORREF clrText)
{
	if(nColumn < 0 || nColumn >= GetColumnCount()) return;

	ColumnInfo* pColInfo = GetColumnInfo(nColumn);
	if(!pColInfo)
	{ 
		pColInfo = new ColumnInfo(nColumn);  
		m_aColumnInfo.Add(pColInfo);
	}

	pColInfo->m_clrBack = clrBack;
	pColInfo->m_clrText = clrText;
	
}
void CMathListCtrlEx::SetCellColors(int nRow, int nColumn, COLORREF clrBack, COLORREF clrText)
{
	if(nRow < 0 || nRow >= GetItemCount() || nColumn < 0 || nColumn >= GetColumnCount()) return;
	CellInfo* pCellInfo = GetCellInfo(nRow, nColumn);
	if(!pCellInfo)
	{ 
		SetCellData(nRow, nColumn, 0);
	}
	pCellInfo = GetCellInfo(nRow, nColumn);
	ASSERT(pCellInfo);
	pCellInfo->m_clrBack = clrBack;
	pCellInfo->m_clrText = clrText;
	
}
void CMathListCtrlEx::PreSubclassWindow()
{
	m_clrDefBack = GetTextBkColor();
	m_clrDefText = GetTextColor();
	CListCtrl::PreSubclassWindow();
	SetExtendedStyle(LVS_EX_FULLROWSELECT);
	SetExtendedStyle(GetExtendedStyle()|LVS_EX_GRIDLINES);
	SetExtendedStyle(GetExtendedStyle()|LVS_REPORT);
//	ModifyStyle(0, LVS_REPORT );
}

BOOL CMathListCtrlEx::SetCellData(int nItem, int nSubItem, DWORD_PTR dwData)
{
	if(nItem < 0 || nItem >= GetItemCount() || nSubItem < 0 || nSubItem >= GetColumnCount()) return FALSE;
	CellInfo* pCellInfo = GetCellInfo(nItem, nSubItem);
	if(!pCellInfo)
	{ 
		pCellInfo = new CellInfo(nSubItem);
		ItemData *pData = (ItemData*)GetItemDataInternal(nItem);
		if(!pData)
		{
			SetItemData(nItem, 0);
			pData = (ItemData*)GetItemDataInternal(nItem);
		}
		pData->m_aCellInfo.Add(pCellInfo);
	}
	pCellInfo->m_dwUserData = dwData;

	return TRUE;
}

DWORD_PTR CMathListCtrlEx::GetCellData(int nItem, int nSubItem)
{
	CellInfo* pCellInfo = GetCellInfo(nItem, nSubItem);
	if(pCellInfo) return pCellInfo->m_dwUserData;
	else return 0;
}

void CMathListCtrlEx::SetCellEditor(int nRow, int nColumn, PFNEDITORCALLBACK pfnInitEditor, PFNEDITORCALLBACK pfnEndEditor, CWnd* pWnd)
{
	if(nRow < 0 || nRow >= GetItemCount() || nColumn < 0 || nColumn >= GetColumnCount()) return;
	CellInfo* pCellInfo = GetCellInfo(nRow, nColumn);
	if(!pCellInfo)
	{ 
		SetCellData(nRow, nColumn, 0);
		pCellInfo = (CellInfo*)GetCellInfo(nRow, nColumn);
		ASSERT(pCellInfo);
	}
	
	pCellInfo->m_eiEditor.m_pfnInitEditor = pfnInitEditor;
	pCellInfo->m_eiEditor.m_pfnEndEditor = pfnEndEditor;
	pCellInfo->m_eiEditor.m_pWnd = pWnd;
	
}

void CMathListCtrlEx::SetCellEditor(int nRow, int nColumn, CWnd* pWnd)
{
	SetCellEditor(nRow, nColumn, NULL, NULL, pWnd);
}


void CMathListCtrlEx::SetDefaultEditor(PFNEDITORCALLBACK pfnInitEditor, PFNEDITORCALLBACK pfnEndEditor, CWnd* pWnd)
{
	m_eiDefEditor.m_pfnInitEditor = pfnInitEditor;
	m_eiDefEditor.m_pfnEndEditor = pfnEndEditor;
	m_eiDefEditor.m_pWnd = pWnd;	
}

void CMathListCtrlEx::SetDefaultEditor(CWnd* pWnd)
{
	SetDefaultEditor(NULL, NULL, pWnd);
}

void CMathListCtrlEx::SetColumnReadOnly(int nColumn, bool bReadOnly)
{
	if(nColumn < 0 || nColumn >= GetColumnCount()) return;
	ColumnInfo *pInfo = (ColumnInfo*)GetColumnInfo(nColumn);
	if(!pInfo) SetColumnEditor(nColumn, (CWnd*)NULL);
	pInfo = (ColumnInfo*)GetColumnInfo(nColumn);
	ASSERT(pInfo);
	pInfo->m_eiEditor.m_bReadOnly = bReadOnly;
}

void CMathListCtrlEx::SetColumnSorting(int nColumn, Sort eSort, Comparer eComparer)
{
	if(nColumn < 0 || nColumn >= GetColumnCount() || !(eSort & SortBits)) return;
	ColumnInfo *pInfo = (ColumnInfo*)GetColumnInfo(nColumn);
	if(!pInfo) SetColumnEditor(nColumn, (CWnd*)NULL);
	pInfo = (ColumnInfo*)GetColumnInfo(nColumn);
	ASSERT(pInfo);
	pInfo->m_eSort = eSort;
	pInfo->m_eCompare = eComparer;
	pInfo->m_fnCompare = NULL;
}
void CMathListCtrlEx::SetColumnSorting(int nColumn, Sort eSort, PFNLVCOMPARE fnCallBack)
{
	if(nColumn < 0 || nColumn >= GetColumnCount() || !(eSort & SortBits)) return;
	ColumnInfo *pInfo = (ColumnInfo*)GetColumnInfo(nColumn);
	if(!pInfo) SetColumnEditor(nColumn, (CWnd*)NULL);
	pInfo = (ColumnInfo*)GetColumnInfo(nColumn);
	ASSERT(pInfo);
	pInfo->m_eSort = eSort;
	pInfo->m_eCompare = NotSet;
	pInfo->m_fnCompare = fnCallBack;
}
void CMathListCtrlEx::SetCellReadOnly(int nRow, int nColumn, bool bReadOnly )
{
	if(nRow < 0 || nRow >= GetItemCount() || nColumn < 0 || nColumn >= GetColumnCount()) return;

	CellInfo *pInfo = (CellInfo*)GetCellInfo(nRow, nColumn);
	if(!pInfo) SetCellEditor(nRow, nColumn, (CWnd*)NULL);
	pInfo = (CellInfo*)GetCellInfo(nRow, nColumn);
	ASSERT(pInfo);
	pInfo->m_eiEditor.m_bReadOnly = bReadOnly;
}
void CMathListCtrlEx::SetRowReadOnly(int nRow, bool bReadOnly)
{
	if(nRow < 0 || nRow >= GetItemCount() ) return;

	ItemData *pInfo = (ItemData*)GetItemDataInternal(nRow);
	if(!pInfo) SetItemData(nRow, 0);
	pInfo = (ItemData*)GetItemDataInternal(nRow);
	ASSERT(pInfo);
	pInfo->m_eiEditor.m_bReadOnly = bReadOnly;
}

BOOL CMathListCtrlEx::IsColumnReadOnly(int nColumn)
{
	if(nColumn < 0 || nColumn >= GetColumnCount()) return FALSE;
	ColumnInfo *pInfo = (ColumnInfo*)GetColumnInfo(nColumn);
	if( pInfo )
	{
		 return pInfo->m_eiEditor.m_bReadOnly;
	}
	return FALSE;
}

BOOL CMathListCtrlEx::IsRowReadOnly(int nRow)
{
	if(nRow < 0 || nRow >= GetItemCount() ) return FALSE;
	ItemData *pInfo = (ItemData*)GetItemDataInternal(nRow);
	if( pInfo )
	{
		 return pInfo->m_eiEditor.m_bReadOnly;
	}
	return FALSE;
}

BOOL CMathListCtrlEx::IsCellReadOnly(int nRow, int nColumn)
{
	if(nRow < 0 || nRow >= GetItemCount() || nColumn < 0 || nColumn >= GetColumnCount()) return FALSE;

	CellInfo *pInfo = (CellInfo*)GetCellInfo(nRow, nColumn);
	if( pInfo )
	{
		 return pInfo->m_eiEditor.m_bReadOnly;
	}
	else
		return (IsRowReadOnly(nRow) || IsColumnReadOnly(nColumn));
}

void CMathListCtrlEx::DeleteSelectedItems(void)
{
	int nItem = -1;
	while((nItem = GetNextItem(-1, LVNI_SELECTED)) >= 0)
	{
		DeleteItem(nItem);
	}	
}
void CMathListCtrlEx::HandleDeleteKey(BOOL bHandle)
{
	m_bHandleDelete = bHandle;
}
void CMathListCtrlEx::SelectItem(int nItem, BOOL bSelect)
{
	if(nItem < 0)
	{
		int nIndex = -1;
		while((nIndex = this->GetNextItem(nIndex, bSelect ? LVNI_ALL : LVNI_SELECTED)) >= 0)
		{
			this->SetItemState(nIndex, (bSelect ? LVIS_SELECTED: 0 ), LVIS_SELECTED);
		}
	}
	else
	{
		this->SetItemState(nItem, (bSelect ? LVIS_SELECTED: 0 ), LVIS_SELECTED);
	}
}

BOOL CMathListCtrlEx::DeleteAllColumns(void)
{
	while(DeleteColumn(0));
	return (GetColumnCount() == 0);
}

BOOL CMathListCtrlEx::Reset(void)
{
	return (DeleteAllItems() &&
	DeleteAllColumns());
}
int CMathListCtrlEx::Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CMathListCtrlEx *This = (CMathListCtrlEx *)lParamSort;
	if(!This || This->m_nSortColumn < 0 || This->m_nSortColumn >= This->GetColumnCount()) return 0;
	int nSubItem = This->m_nSortColumn;
	ColumnInfo *pInfo = This->GetColumnInfo(nSubItem);
	if(!pInfo) return 0;

	CString strLeft = This->GetItemText(lParam1, nSubItem);
	CString strRight = This->GetItemText(lParam2, nSubItem);
	
	switch(pInfo->m_eCompare)
	{
	case Int:
		return CompareInt(strLeft, strRight);
	case Double:
		return CompareDouble(strLeft, strRight);
	case StringNoCase:
		return CompareStringNoCase(strLeft, strRight);
	case StringNumber:
		return CompareNumberString(strLeft, strRight);
	case StringNumberNoCase:
		return CompareNumberStringNoCase(strLeft, strRight);
	case String:
		return CompareString(strLeft, strRight);
	case Date:
		return CompareDate(strLeft, strRight);
	case NotSet:
		return 0;
	default:
		return CompareString(strLeft, strRight);
	}
	return CompareString(strLeft, strRight);
}
int CMathListCtrlEx::CompareInt(LPCTSTR pLeftText, LPCTSTR pRightText)
{
	tstring::size_type sz;   // alias of size_t
	return (int)(stoi(pLeftText,&sz) - stoi(pRightText,&sz));
}
int CMathListCtrlEx::CompareDouble(LPCTSTR pLeftText, LPCTSTR pRightText)
{
	tstring::size_type sz;   // alias of size_t
	return (int)(stof(pLeftText,&sz) - stof(pRightText,&sz));
}
int CMathListCtrlEx::CompareString(LPCTSTR pLeftText, LPCTSTR pRightText)
{
	return CString(pLeftText).Compare(pRightText);
}
int CMathListCtrlEx::CompareNumberString(LPCTSTR pLeftText, LPCTSTR pRightText)
{
//	LONGLONG l1 = atol(pLeftText);
//	LONGLONG l2 = atol(pRightText);
	tstring::size_type sz;   // alias of size_t

	LONGLONG l1 = stol (pLeftText,&sz);
//	LONGLONG l1 = strtol(pLeftText);
	LONGLONG l2 = std::stol (pRightText,&sz);
//	LONGLONG l2 = atol(pRightText);
	if(l1 && l2 && (l1 - l2))
	{
		CString str1, str2;
		str1.Format(_T("%ld"), l1);
		str2.Format(_T("%ld"), l2);
		CString left(pLeftText);
		CString right(pRightText);
		if(str1.GetLength() == left.GetLength() && str2.GetLength() == right.GetLength()) return (int) (l1 - l2);		
	}
	return CString(pLeftText).Compare(pRightText);
}
int CMathListCtrlEx::CompareNumberStringNoCase(LPCTSTR pLeftText, LPCTSTR pRightText)
{
//	LONGLONG l1 = atol(pLeftText);
//	LONGLONG l2 = atol(pRightText);
	tstring::size_type sz;   // alias of size_t
	LONGLONG l1 = stol(pLeftText, &sz);
	LONGLONG l2 = stol(pRightText, &sz);
	if(l1 && l2 && (l1 - l2))
	{
		CString str1, str2;
		str1.Format(_T("%ld"), l1);
		str2.Format(_T("%ld"), l2);
		CString left(pLeftText);
		CString right(pRightText);
		if(str1.GetLength() == left.GetLength() && str2.GetLength() == right.GetLength()) return (int) (l1 - l2);		
	}
	return CString(pLeftText).CompareNoCase(pRightText);
}
int CMathListCtrlEx::CompareStringNoCase(LPCTSTR pLeftText, LPCTSTR pRightText)
{
	return CString(pLeftText).CompareNoCase(pRightText);
}
int CMathListCtrlEx::CompareDate(LPCTSTR pLeftText, LPCTSTR pRightText)
{
	COleDateTime dL, dR;
	dL.ParseDateTime(pLeftText);
	dR.ParseDateTime(pRightText);
	return (dL == dR ? 0 :(dL < dR ? -1 : 1));
}


BOOL CMathListCtrlEx::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.dwExStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;

	return CListCtrl::PreCreateWindow(cs);
}



BOOL CMathListCtrlEx::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW lplvcd = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);

	int iRow = lplvcd->nmcd.dwItemSpec;
	int iCol = lplvcd->iSubItem;
	*pResult = 0;
	switch(lplvcd->nmcd.dwDrawStage)
	{
		case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYSUBITEMDRAW;          // ask for subitem notifications.
//		*pResult = CDRF_DODEFAULT;
//		return FALSE;
		break;

		case CDDS_ITEMPREPAINT:
//			*pResult = CDRF_NOTIFYSUBITEMDRAW;
			break;
		case CDDS_ITEMPREPAINT|CDDS_SUBITEM:
			{
				COLORREF clrBack = 0xFFFFFFFF;
				COLORREF clrText = 0xFFFFFFFF;
				
				*pResult = CDRF_DODEFAULT;
				CellInfo *pCell = GetCellInfo(iRow, iCol);
				if(pCell)
				{
					clrBack = pCell->m_clrBack;
					clrText = pCell->m_clrText;
				}
				if(clrBack == 0xFFFFFFFF && clrText == 0xFFFFFFFF)
				{
					ItemData* pData = (ItemData*)GetItemDataInternal(iRow);
					if(pData)
					{
						clrBack = pData->m_clrBack;
						clrText = pData->m_clrText;
					}
				}
				if(clrBack == 0xFFFFFFFF && clrText == 0xFFFFFFFF)
				{
					ColumnInfo *pInfo = GetColumnInfo(iCol);
					if(pInfo)
					{						
						clrBack = pInfo->m_clrBack;
						clrText = pInfo->m_clrText;
					}
				}
				if(clrBack != 0xFFFFFFFF)
				{
					lplvcd->clrTextBk = clrBack;					
					*pResult  = CDRF_NEWFONT;
				}
				else
				{
					if(clrBack != m_clrDefBack)
					{
						lplvcd->clrTextBk = m_clrDefBack;				
						*pResult  = CDRF_NEWFONT;
					}
				}
				if(clrText != 0xFFFFFFFF)
				{					
					lplvcd->clrText = clrText;					
					*pResult  = CDRF_NEWFONT;
				}				
				else
				{
					if(clrText != m_clrDefText)
					{
						lplvcd->clrText = m_clrDefText;		
						*pResult  = CDRF_NEWFONT;
					}
				}
			}
			if(iCol == 4)
			{
//				DrawItem(lplvcd->);
				*pResult = 0;
			}
		break;

		default:
		*pResult = CDRF_DODEFAULT;
	}
//			if(iCol == 4)
//			{
//				DrawItem(lplvcd->);
//				*pResult = 0;

	*pResult = 0;
//	*pResult |= CDRF_NOTIFYPOSTPAINT;
//  *pResult |= CDRF_NOTIFYITEMDRAW;
  *pResult |= CDRF_NOTIFYSUBITEMDRAW;
				return FALSE;
//			}

	if((*pResult == 0) || (*pResult == CDRF_DODEFAULT))
		return FALSE;
	else
		return TRUE;
}



CString CMathListCtrlEx::GetItemText(int nItem, int nSubItem)
{
	if(nSubItem > 0)
	{
		SemanticString * dsi = &(DCU.at(nItem)[nSubItem]);
		CString cs = dsi->text->data();
		return cs;
	}
	else
		return CListCtrl::GetItemText(nItem, nSubItem);
}


BOOL CMathListCtrlEx::SetItemText( int nItem, int nSubItem, LPCTSTR lpszText)
{
//	if(nItem > 0)
//	{
		SemanticString * dsi = &(DCU.at(nItem)[nSubItem]);
		dsi->text->assign(lpszText);
		tstring tstr = lpszText;
		dsi->PrepareSubItemData(tstr);
		return true;
//	}
//	else
//		return CListCtrl::SetItemText( nItem, nSubItem, lpszText);
}


int  CMathListCtrlEx::GetItemText(int nItem, int nSubItem, LPTSTR lpszText, int nLen)
{
	SemanticString * dsi = &(DCU.at(nItem)[nSubItem]);
	return wcscpy_s(lpszText, nLen, dsi->text->data());
}

//void CMathListCtrlEx::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
//{
//	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
//
//	lpMeasureItemStruct->itemHeight = 40;
//	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
//}





void CMathListCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
//	ASSERT(lpDrawItemStruct->CtlType == ODT_LISTBOX);
//	LPCTSTR lpszText = (LPCTSTR) lpDrawItemStruct->itemData;
//	ASSERT(lpszText != NULL);
	CDC dc;

	dc.Attach(lpDrawItemStruct->hDC);

	// Save these value to restore them when done drawing.
	COLORREF crOldTextColor = dc.GetTextColor();
	COLORREF crOldBkColor = dc.GetBkColor();

   // If this item is selected, set the background color 
   // and the text color to appropriate values. Also, erase
   // rect by filling it with the background color.
	if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&
		(lpDrawItemStruct->itemState & ODS_SELECTED))
	{
		dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, 
			::GetSysColor(COLOR_HIGHLIGHT));
	}
	else
	{
		dc.FillSolidRect(&lpDrawItemStruct->rcItem, crOldBkColor);
	}

	// If this item has the focus, draw a red frame around the
	// item's rect.
	if ((lpDrawItemStruct->itemAction | ODA_FOCUS) &&
		(lpDrawItemStruct->itemState & ODS_FOCUS))
	{
		CBrush br(RGB(255, 0, 0));
		dc.FrameRect(&lpDrawItemStruct->rcItem, &br);
	}
//	CFont * m_fSymbol = GetFont();
//	.CreatePointFont(160, L"Symbol");
//	LOGFONT logf;
//	m_fSymbol->GetLogFont(&logf);
//	logf.lfWeight = FW_BOLD;
//	wcscpy(logf.lfFaceName, L"Symbol");
//	m_fSymbol->CreateFontIndirectW(&logf);

	// Draw the text.
	int countColumn = GetColumnCount();
	CRect rectFirst = lpDrawItemStruct->rcItem;
	int widthFirstColumn = rectFirst.right - rectFirst.left;
	for( int i = 1; i < countColumn; i++)
	{
		CRect rectSubItem;
		GetSubItemRect(lpDrawItemStruct->itemID, i, LVIR_BOUNDS, rectSubItem);
		if ( i == 1 )
			widthFirstColumn = rectSubItem.left;
//		CString cs = (LPCTSTR) GetItemText(lpDrawItemStruct->itemID, i);
//		LPCTSTR dataSubItem = (LPCTSTR)GetCellInfo(lpDrawItemStruct->itemID, i);

//		tstring tstr = cs;
//		SemanticString * dsi = (SemanticString *)GetCellInfo(lpDrawItemStruct->itemID, i)->m_dwUserData;

		// --------------------------------------
		// инициализация 
		SemanticString * dsi = &(DCU.at(lpDrawItemStruct->itemID)[i]);

//		PrepareSubItemData(tstr, DCU.at(idsi);
		// размер выводимого текста готов, занимаемся самим выводом текста посимвольно
		// берём раницы ячейки, применяем к стилю вывода полученные размеры текста, пока что выводим с предположения, что стиль вывода
		// c выравниванием по левой границе ячейки
		dsi->DrawItem(dc, rectSubItem, m_fSymbol, m_fIndexes);

	}
	rectFirst.right = rectFirst.left + widthFirstColumn;
	rectFirst.left += 5;
	SemanticString * dsi = &(DCU.at(lpDrawItemStruct->itemID)[0]);
	CString csFirst = dsi->tchars;
//	CString csFirst = GetItemText(lpDrawItemStruct->itemID, 0);
	dc.DrawText(
		csFirst,
//		(int)_tcslen(lpszText),
		rectFirst,
		DT_LEFT|DT_SINGLELINE|DT_VCENTER);


	// Reset the background color and the text color back to their
	// original values.
	dc.SetTextColor(crOldTextColor);
	dc.SetBkColor(crOldBkColor);

	dc.Detach();
}




