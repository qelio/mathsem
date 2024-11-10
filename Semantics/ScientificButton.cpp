//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
// ScientificButton.cpp: ���� ����������
//

#include "stdafx.h"
#include "Semantics.h"
#include "ScientificButton.h"



//TRANSLATED


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ����� CScientificButton, ������ �� ����� ���������� ���� ��� ����������� �������������� ��������.
//  ������ � ��� ��� �� ��������� � ����� ���� (deprecated)
//  ������������� ��� ��������� �� ������� ��������� � ��������

IMPLEMENT_DYNAMIC(CScientificButton, CMFCButton)

//
//  �����������
//
CScientificButton::CScientificButton()
{
	m_fSymbol.CreatePointFont(160, L"Symbol");    // ������ ����� Symbol
}

//
// ����������
//
CScientificButton::~CScientificButton()
{
}


BEGIN_MESSAGE_MAP(CScientificButton, CMFCButton)
END_MESSAGE_MAP()



// ����������� ��������� CScientificButton



//
// ������� ��������� ������ �� ������
//
void CScientificButton::OnDrawText(CDC* pDC, const CRect& rect, const CString& strText, UINT uiDTFlags, UINT uiState)
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
//#define MAP_STYLE(src, dest) if(dwStyle & (src)) dwText |= (dest)
	DWORD dwStyle = GetStyle(), dwText = 0;

	// ����� ����� ������������� �� ������ � ������, ������� ���������� �������������� ��� ��������� ������
	CRect curr_rect = rect;    // ������� ����������, �������� �������������, � ������� ����� ������������� �����
	CSize csize;
	csize = pDC->GetTextExtent(strText);    // ������� �������, ����������� ��� ����������� ������ � �������������� ������
	curr_rect.left = (curr_rect.right + curr_rect.left - csize.cx)/2;   // ������ ����� ���������� �� �������� ������� ������ ������� ��������������� 
	// �������������� � ������� ������ ������
	curr_rect.top = (curr_rect.top + curr_rect.bottom - csize.cy)/2;   // ������ ������� ���������� �� �������� ������� ������ ������� ��������������� 
	// �������������� � ������� ������ ������
	curr_rect.bottom = (curr_rect.top + curr_rect.bottom + csize.cy)/2;   // ������ ������ ���������� �� �������� ������� ������ ������� ��������������� 
	// �������������� � ������� ������ ������, �� �� ����, � �����
	int prev_pos = 0;
	for( SciCharMapIterator i = m_SciChars.begin(); i != m_SciChars.end(); ++i)    // ������� �� ���� �������������� ��������
	{
		int pos = (*i).first;    // ������� ���������� ����� ������� � ������
		if ( pos >= strText.GetLength())    // ���� ����� ������ ��� ����� ����� ������
			break;    // ������� ����
		if( pos > prev_pos)     // ���� ����� ������� ������ ����������� ��� ���� (� ������ ������ ��������)
		{
			CString szText1 = strText.Left(pos).Right(pos - prev_pos);    // ������� ��������� �������� �� ��������
			csize = pDC->GetTextExtent(szText1);     // ������ ��������� ��� ���������
			pDC->DrawText(szText1, &curr_rect, dwText);    // ����� ����� � �������������� ��� ���������
			curr_rect.left += csize.cx;     // ������ ������ �������������� ��� ���������
		}
//		CString szText1 = strText.Left(pos + 1).Right(1);
//	pFont = GetFont();
		switch( (*i).second)    // ������� ��� ��������������� �������
		{
			case LowerIndex:    // ������ ������
			{
				CString szQuantor = strText.Left(pos + 1).Right(1);    // ������, ������� ������ ���� �������� ��� ������ ������
				csize = pDC->GetTextExtent(szQuantor);    // ������� ������� ��� ���������
				// ������ ������� ��������� ����
				CRect cr = curr_rect;    
				cr.top += csize.cy/2;
				cr.bottom += csize.cy/2;
				pDC->DrawText(szQuantor, &cr, dwText);    // ����� ������
				curr_rect.left += csize.cx;    // ������ ������������� ��������� �����

				break;
			}
			case FirstQuantor:    // ������ �������
			{
				CString szQuantor;
				szQuantor.AppendChar(TCHAR(0x22));    // ������ ������� �� ������� ��������    
				CFont *pOldFont;
				pOldFont = pDC->SelectObject(&m_fSymbol);    // ����� ��� ��������� �������������� ��������
				csize = pDC->GetTextExtent(szQuantor);    // ������� ������� ��� ���������
				// ������� ������� ���������, ��� ��� ������ �������� ����� ���� ����������� ��� ���������
				CRect cr = curr_rect;
				cr.top = ((cr.bottom + cr.top )/2) - (csize.cy *2/3);
				pDC->DrawText(szQuantor, &cr, dwText);    // ����� ������
				curr_rect.left += csize.cx;    // ������ ������������� ��������� �����
				pDC->SelectObject(pOldFont);    // �������������� �������������� �����
				break;
			}
			case SecondQuantor:    // ������ �������
			{
				CString szQuantor;
				szQuantor.AppendChar(TCHAR(0x24));    // ������ ������� �� ������� ��������
				CFont *pOldFont;
				pOldFont = pDC->SelectObject(&m_fSymbol);    // ����� ��� ��������� �������������� ��������
				csize = pDC->GetTextExtent(szQuantor);    // ������� ������� ��� ���������
				// ������� ������� ���������, ��� ��� ������ �������� ����� ���� ����������� ��� ���������
				CRect cr = curr_rect;
				cr.top = ((cr.bottom + cr.top )/2) - (csize.cy *2/3);
				pDC->DrawText(szQuantor, &cr, dwText);    // ����� ������
				curr_rect.left += csize.cx;    // ������ ������������� ��������� �����
				pDC->SelectObject(pOldFont);    // �������������� �������������� �����
				break;
			}
		}
		

		prev_pos = pos;    // �������� �������, �� ������� ��������� ��� ��������
		prev_pos++;    // ��������� �������, � ������� ������� ��������� ��������
	}
	if(strText.GetLength() > prev_pos)    // ���� �������� ������ ����� ����� �� ���� ��������������
	{
		CString strFinal = strText.Right(strText.GetLength() - prev_pos);    // ��������� ����������� ������
		pDC->DrawText(strFinal, &curr_rect, dwText);     // ������ ����������� �����
	}

//	return CMFCButton::OnDrawText(pDC, rect, strText, uiDTFlags, uiState);
}
