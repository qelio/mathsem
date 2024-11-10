//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
// ScientificStatic.cpp: файл реализации
//

#include "stdafx.h"
#include "Semantics.h"
#include "ScientificStatic.h"


// CScientificStatic

IMPLEMENT_DYNAMIC(CScientificStatic, CStatic)

CScientificStatic::CScientificStatic()
{
	dsi = new SemanticString;
}

CScientificStatic::~CScientificStatic()
{
	delete dsi;
}


BEGIN_MESSAGE_MAP(CScientificStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// обработчики сообщений CScientificStatic




void CScientificStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
		// Where to draw text
	CRect client_rect;
	GetClientRect(client_rect);


	// Get the caption
	CString szText;
	GetWindowText(szText);

		// Get the font
	CFont *pFont, *pOldFont;
	pFont = GetFont();
	pOldFont = dc.SelectObject(pFont);

	// Map "Static Styles" to "Text Styles"
#define MAP_STYLE(src, dest) if(dwStyle & (src)) dwText |= (dest)
#define NMAP_STYLE(src, dest) if(!(dwStyle & (src))) dwText |= (dest)

	DWORD dwStyle = GetStyle(), dwText = 0;

	MAP_STYLE(	SS_RIGHT,			DT_RIGHT					);
	MAP_STYLE(	SS_CENTER,			DT_CENTER					);
	MAP_STYLE(	SS_CENTERIMAGE,		DT_VCENTER | DT_SINGLELINE	);
	MAP_STYLE(	SS_NOPREFIX,		DT_NOPREFIX					);
	MAP_STYLE(	SS_WORDELLIPSIS,	DT_WORD_ELLIPSIS			);
	MAP_STYLE(	SS_ENDELLIPSIS,		DT_END_ELLIPSIS				);
	MAP_STYLE(	SS_PATHELLIPSIS,	DT_PATH_ELLIPSIS			);

	NMAP_STYLE(	SS_LEFTNOWORDWRAP |
				SS_CENTERIMAGE |
				SS_WORDELLIPSIS |
				SS_ENDELLIPSIS |
				SS_PATHELLIPSIS,	DT_WORDBREAK				);

	// Set transparent background
	dc.SetBkMode(TRANSPARENT);
//	dc.FillSolidRect(&client_rect, GetSysColor(COLOR_WINDOW));
	if(dsi->count > 0)
	{
		dsi->DrawItem(dc, client_rect, m_fSymbol, m_fIndexes);

	}
	else
	{
		if(szText.GetLength() > 2)
		{
			CString szText1 = szText.Left(1);
			dc.DrawText(szText1, client_rect, dwText);
			CSize csize = dc.GetTextExtent(szText1);
			client_rect.left += csize.cx;
			szText1 = szText.Left(2).Right(1);
			CRect next_rect = client_rect;
			next_rect.top += csize.cy/2;
			next_rect.bottom += csize.cy/2;
			dc.DrawText(szText1, next_rect, dwText);
			csize = dc.GetTextExtent(szText1);
			client_rect.left += csize.cx;
			szText1 = szText.Right(szText.GetLength() - 2);
			dc.DrawText(szText1, client_rect, dwText);
		}
		else
			dc.DrawText(szText, client_rect, dwText);
	}
	// TODO: добавьте свой код обработчика сообщений
	// Не вызывать CStatic::OnPaint() для сообщений рисования
}
