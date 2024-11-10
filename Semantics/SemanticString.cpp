//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014

#include "stdafx.h"
#include "SemanticString.h"

//TRANSLATED




// конструктор по умолчанию
//
SemanticString::SemanticString()
{
	text = new tstring;
	formula = NULL;
}

//
// деструктор
//
SemanticString::~SemanticString()
{
	if(text)
	{
		delete text;
		text = NULL;
	}
}


SemanticString SemanticString::operator=(SemanticString &str) {
	for(int i = 0; i < 256; i++)
	{
		tchars[i] = str.tchars[i];
		symbolics[i] = str.symbolics[i];
	}
	count = str.count;
//	if(text)
//		delete text;
//	text = new tstring;
	if(str.text && str.text->length() > 0)
		*text = *str.text;
	size = str.size;
	return *this;
}


//
// метод получает строку с математическими тэгами и заполняет из неё члены объекта класса SemanticString. Преобразование в Word несколько отличается от
// преобразования для отрисовки строки, вызывается с флагом forWordExport, выставленным в true
//
bool SemanticString::PrepareSubItemData(tstring & tstr, bool forWordExport)
{
	bool result = true;
		if(!forWordExport)
			*text = tstr;
		count = 0;    // переменная для количества символов
		size.cx = 0;
		size.cy = 0;
		// начали разбор на математические симовлы в виде <symbol=..>
		bool isFound = false;
		int worked = 0;   // сётчик обработанных символов
		int pos = 0;    // положение в строке, с которого начинаем поиск левого тэга '<'
		while ( (pos = tstr.find(_T("<"), pos)) != -1)    // если левый тэг найден, начиная с положения pos
		{
			isFound = false;
			// все символы до позиции pos заносим в структуру dataSubItes как обычные (не математические символы)
			int diff = pos - worked;    // число символов, которые надо занести
			for ( int k = 0; k < diff; k++)
			{
				tchars[count] = tstr.at(worked);     // заносим очередной символ
				symbolics[count] = 0;                // указываем, что это обычный символ ( не индекс и не математический)
				worked ++;			// инкремент числа обработанных символов
				count ++;			// инкремент числа содержащихся в tchar и symbolics элементов
			}
			int pos1 = tstr.find(_T(">"), pos + 1);    // поиск правого тэга '>' вправо,начиная с символа следующего за найденным левым тэгом
			if ( pos1 > 0 )     // если правый тэг найден
			{
				tstring part_tstr = tstr.substr(pos + 1, pos1 - pos - 1);    // получаю подстроку внутри левого и правого тэгов
				trimWhitespaces(&part_tstr);    // убираю начальные и завершающие символы
				// проверяю полученную подстроку на соответствие виду <symbol=..> или <s=..>
				int pos_of_equal = part_tstr.find(_T("="));    // нахожу позицию вхождения знака равенства
				if ( (pos_of_equal > 0) && (pos_of_equal < ((int)part_tstr.size() - 1)) )   // если он находится внутри полученной подстроки
				{
					tstring beforeDelim = part_tstr.substr(0, pos_of_equal);    // подстрока до знака равенства
					tstring afterDelim = part_tstr.substr(pos_of_equal + 1, part_tstr.size() - pos_of_equal);    // подстрока после знака равенства
					// удаляю начальные и завершающие пробельные символы для обеих полученных подстрок
					trimWhitespaces(&beforeDelim);     
					trimWhitespaces(&afterDelim);
					transform(beforeDelim.begin(), beforeDelim.end(), beforeDelim.begin(), ::tolower); // перевожу первую из двух подстрок в lower case
					if (!beforeDelim.compare(_T("s")) || !beforeDelim.compare(_T("symbol")) )    // сравниваю на совпадение с 'symbol' или 's'
					{
						// сравниваю вторую подстроку с совпадением с любых из разрешённых обозначений, если найдено, то заношу в tchar и symbolics и
						// взвожу флаг, что всястрока имеет корректный вид
						if(!afterDelim.compare(_T("/low")) )  //low index
						{
							tchars[count] = TCHAR(0x20);
							symbolics[count] = LOW_MATHINDEX;
							isFound = true;
						}
						else if(!afterDelim.compare(_T("/high")) ) //high index
						{
							tchars[count] = TCHAR(0x20);
							symbolics[count] = HIGH_MATHINDEX;
							isFound = true;
						}
						else if(!afterDelim.compare(_T("/left_tag")) ) //left tag
						{
//							tchars[count] = TCHAR('<');
//							symbolics[count] = SYMBOL_TYPEFACE;
//							isFound = true;
							if(forWordExport)
								tchars[count] = TCHAR(0xe1);
							else
								tchars[count] = TCHAR(0x2329);
//								tchars[count] = TCHAR(0x2229);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if(!afterDelim.compare(_T("/right_tag")) ) //right tag
						{
//							tchars[count] = TCHAR('>');
//							symbolics[count] = SYMBOL_TYPEFACE;
//							isFound = true;
							if(forWordExport)
								tchars[count] = TCHAR(0xf1);
							else
								tchars[count] = TCHAR(0x232a);
//								tchars[count] = TCHAR(0x2229);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if(!afterDelim.compare(_T("/34")) )  // first quantor
						{
							if(forWordExport)
								tchars[count] = TCHAR(0x22);
							else
								tchars[count] = TCHAR(0x2200);
//								tchars[count] = TCHAR(0x22); для шрифта Symbol
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if(!afterDelim.compare(_T("/36")) )  //second quantor
						{
							if(forWordExport)
								tchars[count] = TCHAR(0x24);
							else
								tchars[count] = TCHAR(0x2203);
//								tchars[count] = TCHAR(0x24); для шрифта Symbol
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if ( (!afterDelim.compare(_T("/38")) )  || (!afterDelim.compare(_T("/and")) ) )//and
						{
							if(forWordExport)
								tchars[count] = TCHAR(0x26);
							else
								tchars[count] = TCHAR(0x0026);
//								tchars[count] = TCHAR(0x26); для шрифта Symbol
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if(!afterDelim.compare(_T("/123")) )  //левая фигурная скобка
						{
							tchars[count] = TCHAR(123);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if(!afterDelim.compare(_T("/125")) )  //парвая фигурная скобка
						{
							tchars[count] = TCHAR(125);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if ( (!afterDelim.compare(_T("/216")) )  || (!afterDelim.compare(_T("/not")) ) ) //not
						{
							if(forWordExport)
								tchars[count] = TCHAR(216);
							else
								tchars[count] = TCHAR(0x00AC);
//								tchars[count] = TCHAR(0x0428);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if ( (!afterDelim.compare(_T("/218")) ) || (!afterDelim.compare(_T("/or")) ) )//или
						{
							if(forWordExport)
								tchars[count] = TCHAR(0xda); //tchars[count] = TCHAR(0xc7);
							else
								tchars[count] = TCHAR(0x2228);
//								tchars[count] = TCHAR(0x042A);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if ( (!afterDelim.compare(_T("/199")) ) || (!afterDelim.compare(_T("/crossing")) ) )//пересечение
						{
							if(forWordExport)
								tchars[count] = TCHAR(0xc7);
							else
								tchars[count] = TCHAR(0x2229);
//								tchars[count] = TCHAR(0x417);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if ( (!afterDelim.compare(_T("/200")) ) || (!afterDelim.compare(_T("/union")) ) )//объединение
						{
							if(forWordExport)
								tchars[count] = TCHAR(0xc8);
							else
								tchars[count] = TCHAR(0x222A);
//								tchars[count] = TCHAR(0x418);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if ( (!afterDelim.compare(_T("/204")) ) || (!afterDelim.compare(_T("/similar")) ) )//подобие
						{
							if(forWordExport)
								tchars[count] = TCHAR(0xcc);
							else
								tchars[count] = TCHAR(0x2282);
//								tchars[count] = TCHAR(0x041c);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if (!afterDelim.compare(_T("/empty")) ) //empty_set
						{
							if(forWordExport)
								tchars[count] = TCHAR(0xc6);
							else
								tchars[count] = TCHAR(0x2205);
//								tchars[count] = TCHAR(0x041c);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if (!afterDelim.compare(_T("/fuzzy")) ) //fuzzy inclusion
						{
							if(forWordExport)
								tchars[count] = TCHAR(0xcc);
							else
								tchars[count] = TCHAR(0x2286);
//								tchars[count] = TCHAR(0x041c);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
						else if ( (!afterDelim.compare(_T("/0xCE")) ) || (!afterDelim.compare(_T("/206")) ) || (!afterDelim.compare(_T("/in")) ) )//принадлежноть
						{
							// для этого символа есть тонкость при ковертировании в Word'овский документ
							if(forWordExport)
								tchars[count] = TCHAR(206);
							else
								tchars[count] = TCHAR(0x2208);
//								tchars[count] = TCHAR(0x041E);
							symbolics[count] = SYMBOL_TYPEFACE;
							isFound = true;
						}
					}
				}
				if(isFound)	// если найденный(е) тэг(и) относятся к математическим символам, а не просто тэги
				{
					count++;    // увеличиваем счётчик
					isFound = false;     // занесли, и убираем флаг
					worked += (pos1 + 1 - pos);	// увеличиваем счётчик числа обработанных символов
				}
				pos = pos1 + 1; // выставляем pos для новой итерации поиска
			}
			else     // не найден правый тэг
				break;    // прервываю цикл
			if( pos >= ((int)tstr.size() - 2) )    // если для разбора остаётся только два или меньше символов
				break;    // прерываю цикл, так как искать смысла больше нет

		}
		// и после окончания всех проверок довносим в dataSubItme те данные, которые не занесли ввиду завершения цикла не достигнув конца строки либо 
		// ввиду того, что цикл так и не отработал. По всей видимости, корректных математических тэгов не найдено, заносим оставшиеся символы по одному
		// как обычные
		if(worked < (int)tstr.size())
		{
			for ( size_t j = worked; j < tstr.size(); j++)
			{
				tchars[count] = tstr.at(j);
				symbolics[count] = 0;
				count++;
			}
		}
		// данные разобрали, теперь последний раз проходимся по данным и определяем размер вывода на экран (пока не отработано)
		for ( int j = 0; j < count; j++)
		{
			CSize sizeSymbol;
			sizeSymbol.cx = 0;
			sizeSymbol.cy = 0;
			switch(tchars[j])
			{
			case LOW_MATHINDEX:
				// надо будет уменьшать размер следующего символа, сейчас пропускаем
				break;
			case HIGH_MATHINDEX:
				// надо будет уменьшать размер следующего символа, сейчас пропускаем
				break;
			case SYMBOL_TYPEFACE:
				break;
				
			case NONE_MATHSTYLE:
			default:
				CString cstest(tchars[j]);
//				sizeSymbol = dc.GetTextExtent(cstest);
				break;
			}
			size.cx += sizeSymbol.cx;
		}
		tchars[count] = TCHAR(0x00);
	return result;
}

//
// метод отрисовывает объект SemanticString, заранее подготовленный методом 'PrepareSubItemData' в прямоугольнике rectSubItem для контекста 
// устройства dc. Для отрисовки индексов используется шрифт m_fIndexes, для отрисовки математических символов m_fSymbol (как правило, шрифт Symbol)
//
void SemanticString::DrawItem(CDC &dc, CRect &rectSubItem, CFont * m_fSymbol, CFont * m_fIndexes)
{
	CFont * pOldFont = NULL;
	CRect rectReal = rectSubItem;
	rectReal.left += 2;    // сдвигаем левую границу на 2 единицы
	int indexing = 0;    // переменная для вида индексирования, одновременно используется как флаг, чтобы показать, что символ будет изображаться как индекс
	// цикл по числу символов, содержащихся в объекте SemanticString
	for (int j = 0; j < count; j++)    
	{
		TCHAR tch[4];    // массив для временного хранения очередного символа
		tch[0] = tchars[j];
		tch[1] = TCHAR(0x00);    // выставляем в 0, чтобы использовать как С-строку
		if( ( symbolics[j] == LOW_MATHINDEX ) || ( symbolics[j] == HIGH_MATHINDEX ) )     // если индекс
		{
			indexing = symbolics[j];    // указываем вид индексирования
			continue;    // переход к последующему символу из tchars
		}
		CSize sizeSymbol;    // переменная для размера символа
		CRect rectIndex ;    // прямоугольник для отображения символа как индекса
		if ( indexing == LOW_MATHINDEX ) // пока что реализуем для нижних индексов
		{
			pOldFont = dc.SelectObject(m_fIndexes);    // выставляю шрифт для изображения индексов
		}
		else
		{
			if ( symbolics[j] == SYMBOL_TYPEFACE )
			{
				pOldFont = dc.SelectObject(m_fSymbol);
				// выставляем шрифт Symbol
			}
//				sizeSymbol = dc.GetTextExtent(tch);
		}
		sizeSymbol = dc.GetTextExtent(tch);    // получили размер
		if ( tch[0] == TCHAR(0x26) ) //  если амперсандом
		{
			tch[1] = tch[0];    // задублируем в случае амперсанда, формы своеобразно отображают (не обображают амперсанды), нужно удваивать
			tch[2] = TCHAR(0x00);
		}
		rectReal.right = rectReal.left + sizeSymbol.cx;    // устанавливаю ширину прямоугольника отображения символа
		if( rectReal.right >= rectSubItem.right ) // если отображение выходит за границы, восстанавливаем фонт и прерываем цикл 
		{
			if(pOldFont != NULL)
			{
				dc.SelectObject(pOldFont);
				pOldFont = NULL;
			}
			break;
		}
		if(indexing)    // если отображается индекс, определяем прямоугольник отображения для него
		{
			rectIndex = rectReal;
			rectIndex.top += (sizeSymbol.cy / 2);    // смещение вниз верхней границы
			rectIndex.bottom += (sizeSymbol.cy / 2);    // смещение вниз нижней границы
		}
		if(( symbolics[j] == SYMBOL_TYPEFACE ) && (tchars[j] == TCHAR(0x2208)))  // если символ принадлежности, то немного поднимаю его
		{
			rectIndex = rectReal;
			rectIndex.top -= (sizeSymbol.cy / 10);    // смещение вниз верхней границы
			rectIndex.bottom -= (sizeSymbol.cy / 10);    // смещение вниз нижней границы
			dc.DrawText(    // отрисовка очередного символа
				tch,
				1,    
				rectIndex,     
				DT_CENTER|DT_SINGLELINE|DT_VCENTER);
		} 
		else
		dc.DrawText(    // отрисовка очередного символа
			tch,
			( tch[0] == TCHAR(0x26) )? 2 : 1,    // если амперсан, то отображение двух символов (первый амперсанд в формах не отображается
			indexing ? rectIndex : rectReal,     // выбираем прямоугольник отрисовки в зависимости от того, отображается как индекс или нет
			DT_CENTER|DT_SINGLELINE|DT_VCENTER);
		rectReal.left += sizeSymbol.cx;	// переносим левую координату для отображения следующего фонта
	
		if ( pOldFont != NULL )    // восстанавливаем первоначальный фонт, основной для элемента
		{
			dc.SelectObject(pOldFont);
			pOldFont = NULL;
		}
		if(indexing)    // если был отрисован символ
			indexing = 0;    // убираю флаг индексировния
		
	}
}