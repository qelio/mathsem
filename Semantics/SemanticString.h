//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once

#include "common_functions.h"
#include "Formula.h"

// перечисление видов математических символов
enum MathStyle { 
	NONE_MATHSTYLE,			// не математический символ, обычный
	LOW_MATHINDEX = 1,		// нижний индекс
	HIGH_MATHINDEX = 2,		// верхний индекс
	SYMBOL_TYPEFACE =3		// математический символ, который отображается шрифтом Symbol
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  класс SemanticString используется для одновременного отображения двух шрифотов, один из которых Symbol для математических символов
//
class SemanticString
{
public:
	// буфер символов " в смеси", отличается от обычных тем, что для индексов может быть '0', является или нет символ индексным, надо смотреть 
	// в соответствующем элемента массива symbolics. также в соответствующем элементе symbolics указывается, простой это символ или математический,
	// который должен отображаться шрифтом Symbol
#ifdef _UNICODE
	WCHAR tchars[256];
#else
	unsigned char tchars[256];
#endif
	// массив значений MathStyle, описывающий соответствующие символы массива tchars (под тем же номером)
	int symbolics[256];
	// количество символов в tchars и symbolics
	int count;
	// указатель на соответствующую формулу, которую описывает объект класса SemanticString
//	Formula * formula;
	EntityBase * formula;
	// соответствующий текст
	tstring * text;
	// рассчитываемые размеры строки для отрисовки (пока блок определения размера не дореализован)
	CSize size;

public:
	// конструктор по умолчанию
	SemanticString();
	// деструктор
	~SemanticString();

	// метод получает строку с математическими тэгами и заполняет из неё члены объекта класса SemanticString. Преобразование в Word несколько отличается от
	// преобразования для отрисовки строки, вызывается с флагом forWordExport, выставленным в true
	bool PrepareSubItemData(tstring & tstr, bool forWordExport = false);
	// метод отрисовывает объект SemanticString, заранее подготовленный методом 'PrepareSubItemData' в прямоугольнике rectSubItem для контекста 
	// устройства dc. Для отрисовки индексов используется шрифт m_fIndexes, для отрисовки математических символов m_fSymbol (как правило, шрифт Symbol)
	void DrawItem(CDC &dc, CRect &rectSubItem, CFont * m_fSymbol, CFont * m_fIndexes);

	SemanticString operator=(SemanticString &str); // присвоение
};
