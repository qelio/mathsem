// Написано Виталием Татаринцевым, akizelokro@mail.ru, vtatarintsev.ru, 3 августа 2013
// Написано Виталием Татаринцевым, akizelokro@mail.ru, vtatarintsev.ru, 3 августа 2013
//
// В следующий код содержит вспомогательные функции для работы со строками,
// включая удаление пробелов и поиск строк.

#pragma once

#include "tchar.h"
#include <vector>
#include <functional>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <tuple>
#include <random>
#include <map>

#include <sys/timeb.h>
#include <time.h>
using namespace std;

// Определяет типы строк широких символов для поддержки Unicode или многобайтных символов
#ifdef _UNICODE
typedef wstring tstring;
#define tcin wcin
#define tcout wcout
#define tcerr wcerr
typedef wostringstream tostringstream;
typedef wistringstream tistringstream;
typedef wifstream tifstream;
typedef wofstream tofstream;
typedef wostream tostream;
#define istspace iswspace
#define to_tstring to_wstring
#define SetWindowTextT SetWindowTextW
#define GetWindowTextT GetWindowTextW
#define GetWindowTextLengthT GetWindowTextLengthW
#define HtmlHelpT HtmlHelpW
#define istdigit iswdigit
#else
typedef std::string tstring;
#define tcin cin
#define tcout cout
#define tcerr cerr
typedef ostringstream tostringstream;
typedef istringstream tistringstream;
typedef ifstream tifstream;
typedef ofstream tofstream;
typedef ostream tostream;
#define istspace isspace
#define to_tstring to_string
#define SetWindowTextT SetWindowText
#define GetWindowTextT GetWindowText
#define GetWindowTextLengthT GetWindowTextLength
#define HtmlHelpT HtmlHelp
#define istdigit isdigit
#endif

const long bufferLength = 500;

/**
 * @brief Удаляет начальные пробелы из строки.
 *
 * Эта функция удаляет все начальные пробельные символы (пробелы, табуляции и т.д.)
 * из начала заданной строки.
 *
 * @param str Указатель на строку для изменения.
 */
void removeLeadingWhitespaces(tstring * str);

/**
 * @brief Удаляет конечные пробелы из строки.
 *
 * Эта функция удаляет все конечные пробельные символы (пробелы, табуляции и т.д.)
 * из конца заданной строки.
 *
 * @param str Указатель на строку для изменения.
 */
void removeTrailingWhitespaces(tstring * str);

/**
 * @brief Обрезает пробелы с обоих концов строки.
 *
 * Эта функция удаляет все начальные и конечные пробельные символы
 * (пробелы, табуляции и т.д.) из заданной строки.
 *
 * @param str Указатель на строку для изменения.
 */
void trimWhitespaces(tstring * str);

/**
 * @brief Удаляет дублированные пробелы из строки.
 *
 * Эта функция удаляет любые дублирующиеся идущие подряд пробельные символы
 * внутри строки, оставляя только один пробел там, где были дубли.
 *
 * @param ptstr Указатель на строку для изменения.
 */
void removeDoubledWhitespaces(tstring * ptstr);

/**
 * @brief Удаляет все пробельные символы из строки.
 *
 * Эта функция удаляет все пробельные символы (пробелы, табуляции и т.д.)
 * по всей длине строки.
 *
 * @param ptstr Указатель на строку для изменения.
 */
void removeAllWhitespaces(tstring * ptstr);

/**
 * @brief Осуществляет поиск строки внутри списка строк.
 *
 * Эта функция осуществляет поиск заданной строки внутри вектора строк.
 * Она возвращает true, если строка найдена, в противном случае false.
 *
 * @param search Указатель на строку для поиска.
 * @param where Указатель на вектор строк, где осуществляется поиск.
 * @return true если строка найдена, false в противном случае.
 */
bool search_in(tstring *search, vector<tstring> *where);

/**
 * @brief Парсинг целого числа типа long из строки.
 *
 * Эта функция пытается распарсить целое число типа long из строки. Она возвращает
 * false, если строку нельзя распарсить в правильное значение типа long.
 *
 * @param str Указатель на строку для парсинга.
 * @param value Указатель на переменную, в которую будет сохранено распарсенное значение.
 * @return true если парсинг успешен, false в противном случае.
 */
bool parseLongFromString(tstring * str, long * value);

/**
 * @brief Удаляет протокол и конечный слэш из URL.
 *
 * Эта функция удаляет протокол (например, http:// или https://) и
 * любые конечные слэши из URL, оставляя только основной адрес.
 *
 * @param url Указатель на строку, представляющую URL.
 * @return Измененная строка без протокола и конечных слэшей.
 */
tstring * removeProtocolAndSlash(tstring * url);