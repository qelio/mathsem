//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
// ScientificButton.cpp: файл реализации
//

#include "stdafx.h"
#include "Semantics.h"
#include "ScientificButton.h"



//TRANSLATED


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Класс CScientificButton, первый из числа написанных мной для отображения математических символов.
//  Сейчас я его уже не использую в новом коде (deprecated)
//  Использовался для отрисовки на кнопках кванторов и индексов

IMPLEMENT_DYNAMIC(CScientificButton, CMFCButton)

//
//  конструктор
//
CScientificButton::CScientificButton()
{
	m_fSymbol.CreatePointFont(160, L"Symbol");    // создаю шрифт Symbol
}

//
// деструктор
//
CScientificButton::~CScientificButton()
{
}


BEGIN_MESSAGE_MAP(CScientificButton, CMFCButton)
END_MESSAGE_MAP()



// обработчики сообщений CScientificButton



//
// функция отрисовки текста на кнопке
//
void CScientificButton::OnDrawText(CDC* pDC, const CRect& rect, const CString& strText, UINT uiDTFlags, UINT uiState)
{
	// TODO: добавьте специализированный код или вызов базового класса
//#define MAP_STYLE(src, dest) if(dwStyle & (src)) dwText |= (dest)
	DWORD dwStyle = GetStyle(), dwText = 0;

	// текст будет отцентрирован по ширине и высоте, получаю координаты прямоугольника для отрисовки текста
	CRect curr_rect = rect;    // копирую координаты, задающие прямоугольник, в котором будет располагаться текст
	CSize csize;
	csize = pDC->GetTextExtent(strText);    // копирую размеры, необходимые для отображения текста в первоначальном шрифте
	curr_rect.left = (curr_rect.right + curr_rect.left - csize.cx)/2;   // смещаю левую координату на половину разницы междну шириной первоначального 
	// прямоугольника и шириной самого текста
	curr_rect.top = (curr_rect.top + curr_rect.bottom - csize.cy)/2;   // смещаю верхнюю координату на половину разницы междну высотой первоначального 
	// прямоугольника и высотой самого текста
	curr_rect.bottom = (curr_rect.top + curr_rect.bottom + csize.cy)/2;   // смещаю нижнюю координату на половину разницы междну высотой первоначального 
	// прямоугольника и высотой самого текста, но не вниз, а вверх
	int prev_pos = 0;
	for( SciCharMapIterator i = m_SciChars.begin(); i != m_SciChars.end(); ++i)    // перебор по всем математическим символам
	{
		int pos = (*i).first;    // получаю порядковый номер символа в строке
		if ( pos >= strText.GetLength())    // если номер больше или равен длине строки
			break;    // завераю цикл
		if( pos > prev_pos)     // если номер позиции больше предыдущего или нуля (в случае первой итерации)
		{
			CString szText1 = strText.Left(pos).Right(pos - prev_pos);    // выделяю подстроку символов до текущего
			csize = pDC->GetTextExtent(szText1);     // размер подстроки при рисовании
			pDC->DrawText(szText1, &curr_rect, dwText);    // рисую текст в прямоугольнике для рисования
			curr_rect.left += csize.cx;     // смещаю начало прямоугольника для отрисовки
		}
//		CString szText1 = strText.Left(pos + 1).Right(1);
//	pFont = GetFont();
		switch( (*i).second)    // получаю вид математического символа
		{
			case LowerIndex:    // нижний индекс
			{
				CString szQuantor = strText.Left(pos + 1).Right(1);    // символ, который должен быть отображён как нижний индекс
				csize = pDC->GetTextExtent(szQuantor);    // размеры символа при рисовании
				// смещаю область рисования вниз
				CRect cr = curr_rect;    
				cr.top += csize.cy/2;
				cr.bottom += csize.cy/2;
				pDC->DrawText(szQuantor, &cr, dwText);    // рисую символ
				curr_rect.left += csize.cx;    // смещаю прямоугольник отрисовки влево

				break;
			}
			case FirstQuantor:    // первый квантор
			{
				CString szQuantor;
				szQuantor.AppendChar(TCHAR(0x22));    // строка состоит из первого квантора    
				CFont *pOldFont;
				pOldFont = pDC->SelectObject(&m_fSymbol);    // шрифт для отрисовки математических символов
				csize = pDC->GetTextExtent(szQuantor);    // размеры символа при рисовании
				// изменяю область рисования, так как символ квантора имеет свои особенности при отрисовке
				CRect cr = curr_rect;
				cr.top = ((cr.bottom + cr.top )/2) - (csize.cy *2/3);
				pDC->DrawText(szQuantor, &cr, dwText);    // рисую символ
				curr_rect.left += csize.cx;    // смещаю прямоугольник отрисовки влево
				pDC->SelectObject(pOldFont);    // восстанавливаю первоначальный шрифт
				break;
			}
			case SecondQuantor:    // второй квантор
			{
				CString szQuantor;
				szQuantor.AppendChar(TCHAR(0x24));    // строка состоит из второго квантора
				CFont *pOldFont;
				pOldFont = pDC->SelectObject(&m_fSymbol);    // шрифт для отрисовки математических символов
				csize = pDC->GetTextExtent(szQuantor);    // размеры символа при рисовании
				// изменяю область рисования, так как символ квантора имеет свои особенности при отрисовке
				CRect cr = curr_rect;
				cr.top = ((cr.bottom + cr.top )/2) - (csize.cy *2/3);
				pDC->DrawText(szQuantor, &cr, dwText);    // рисую символ
				curr_rect.left += csize.cx;    // смещаю прямоугольник отрисовки влево
				pDC->SelectObject(pOldFont);    // восстанавливаю первоначальный шрифт
				break;
			}
		}
		

		prev_pos = pos;    // указываю позицию, на которой завершили эту итерацию
		prev_pos++;    // инкремент позиции, с которой начнётся следующая итерация
	}
	if(strText.GetLength() > prev_pos)    // если остались симолы после цикла по всем математическим
	{
		CString strFinal = strText.Right(strText.GetLength() - prev_pos);    // подстрока оставшегося текста
		pDC->DrawText(strFinal, &curr_rect, dwText);     // вывожу отставшийся текст
	}

//	return CMFCButton::OnDrawText(pDC, rect, strText, uiDTFlags, uiState);
}
