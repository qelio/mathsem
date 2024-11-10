//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
// ScientificListBox.cpp: ���� ����������
//

#include "stdafx.h"
#include "Semantics.h"
#include "ScientificListBox.h"


// ScientificListBox

IMPLEMENT_DYNAMIC(ScientificListBox, CListBox)

ScientificListBox::ScientificListBox()
{
	m_fSymbol = new CFont;
//	m_fSymbol->CreatePointFont(140, L"Symbol");
	m_fSymbol->CreatePointFont(140, L"Arial Unicode MS");
	m_fIndexes = 0;
	isSorted = false;
}

ScientificListBox::~ScientificListBox()
{
	if(m_fSymbol)
		delete m_fSymbol;
	if(m_fIndexes)
		delete m_fIndexes;
	for ( size_t i = 0; i < DCU.size(); i++)
		delete DCU.at(i);
}


BEGIN_MESSAGE_MAP(ScientificListBox, CListBox)
END_MESSAGE_MAP()



// ����������� ��������� ScientificListBox




void ScientificListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
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

	// Draw the text.
	CRect rectItem = lpDrawItemStruct->rcItem;
//	int widthFirstColumn = rectFirst.right - rectFirst.left;
//	GetItemRect(lpDrawItemStruct->itemID, rectSubItem);
// --------------------------------------
// ������������� 
	if( (DCU.size() > 0) && (DCU.size() >= lpDrawItemStruct->itemID) )
	{
		SemanticString * dsi = DCU.at(lpDrawItemStruct->itemID);

		// ������ ���������� ������ �����, ���������� ����� ������� ������ �����������
		// ���� ������ ������, ��������� � ����� ������ ���������� ������� ������, ���� ��� ������� � �������������, ��� ����� ������
		// c ������������� �� ����� ������� ������
		dsi->DrawItem(dc, rectItem, m_fSymbol, m_fIndexes);
	}
	// Reset the background color and the text color back to their
	// original values.
	dc.SetTextColor(crOldTextColor);
	dc.SetBkColor(crOldBkColor);

	dc.Detach();
	// TODO:  �������� �������� ��� ��� ����������� ���������� ��������
}



int ScientificListBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{

	// TODO:  �������� ��� ��� ����������� ������� ���������� ��������� ���������
	//  ������� -1, ����� �������1 ���� �� ��������2 ��� ����������
	// ������� 0, ���� �������1 � �������2 ����� ���������� ������� ����������
	//  ������� 1, ����� �������1 ����� ����� ��������2 ��� ����������
	if(isSorted)
	{
		TCHAR buf[20];
		GetText(lpCompareItemStruct->itemID1, buf);
		int item1 = stoi(tstring(buf));
		GetText(lpCompareItemStruct->itemID2, buf);
		int item2 = stoi(tstring(buf));
		if( item1 < item2)
			return (-1);
		else if ( item1 == item2)
			return 0;
		else 
			return 1;
	}
	else
	{
		if( lpCompareItemStruct->itemID1 < lpCompareItemStruct->itemID2)
			return (-1);
		else if ( lpCompareItemStruct->itemID1 == lpCompareItemStruct->itemID2)
			return 0;
		else 
			return 1;
	}
}
