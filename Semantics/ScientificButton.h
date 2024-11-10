//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once

#include "common_functions.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Класс CScientificButton, первый из числа написанных мной для отображения математических символов.
//  Сейчас я его уже не использую в новом коде (deprecated)
//  Использовался для отрисовки на кнопках кванторов и индексов


// перечисление вида отрисовки
enum ScientificCharacterAction
{
	NONE = 0,            // обычный символ
	FirstQuantor = 1,    // первый квантор (принадлежности)
	SecondQuantor = 2,   // второй квантор (всеобжности)
	LowerIndex = 3,      // нижний индекс
	UpperIndex = 4       // верхний индекс (не реализовано, но по аналогии с нижним индексом можно сделать быстро)
} ;



// CScientificButton

class CScientificButton : public CMFCButton
{
	DECLARE_DYNAMIC(CScientificButton)

	typedef map<int, ScientificCharacterAction, less<int>> SciCharMap;     // задаю упорядоченный контейнер математических символов по возрастанию 
	// первого параметра (номера символа в строке), второй параметр - указывает вид отрисовки символа, третий параметр - условие сортировки

	typedef SciCharMap::iterator SciCharMapIterator;
	SciCharMap m_SciChars;

	// шрифт,используемый для рисования математических символов (почти всегда Symbol)
	CFont m_fSymbol;
public:
	// конструктор
	CScientificButton();
	// деструктор
	virtual ~CScientificButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	// метод указывает, где нужна эта специальная математическая отрисовка (на каком символе по порядку)
	void addSciCharAction(int pos, ScientificCharacterAction scichar) { m_SciChars[pos] = scichar; };
	// метод устанавливает шрифт для математических символов
	void setSciFont(LOGFONT * lf) { m_fSymbol.CreateFontIndirectW(lf); };
	// функция отрисовки текста на кнопке
	virtual void OnDrawText(CDC* pDC, const CRect& rect, const CString& strText, UINT uiDTFlags, UINT uiState);
};


