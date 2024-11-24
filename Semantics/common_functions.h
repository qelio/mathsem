// Written by Vitaly Tatarintsev, akizelokro@mail.ru, vtatarintsev.ru, 3 August 2013
// Written by Vitaly Tatarintsev, akizelokro@mail.ru, vtatarintsev.ru, 3 August 2013
//
// The following code contains utility functions for string manipulation,
// including removing whitespaces and searching strings.

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

// Defines wide character string types for Unicode or multibyte support
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
 * @brief Removes leading whitespace characters from a string.
 *
 * This function removes all leading whitespace characters (spaces, tabs, etc.)
 * from the beginning of the given string.
 *
 * @param str A pointer to the string to modify.
 */
void removeLeadingWhitespaces(tstring * str);

/**
 * @brief Removes trailing whitespace characters from a string.
 *
 * This function removes all trailing whitespace characters (spaces, tabs, etc.)
 * from the end of the given string.
 *
 * @param str A pointer to the string to modify.
 */
void removeTrailingWhitespaces(tstring * str);

/**
 * @brief Trims whitespace characters from both ends of a string.
 *
 * This function removes all leading and trailing whitespace characters
 * (spaces, tabs, etc.) from the given string.
 *
 * @param str A pointer to the string to modify.
 */
void trimWhitespaces(tstring * str);

/**
 * @brief Removes doubled whitespace characters from a string.
 *
 * This function removes any consecutive duplicate whitespace characters
 * within the string, leaving only single spaces where there were duplicates.
 *
 * @param ptstr A pointer to the string to modify.
 */
void removeDoubledWhitespaces(tstring * ptstr);

/**
 * @brief Removes all whitespace characters from a string.
 *
 * This function removes all whitespace characters (spaces, tabs, etc.)
 * throughout the entire string.
 *
 * @param ptstr A pointer to the string to modify.
 */
void removeAllWhitespaces(tstring * ptstr);

/**
 * @brief Searches for a string within a list of strings.
 *
 * This function searches for a given string within a vector of strings.
 * It returns true if the string is found, otherwise false.
 *
 * @param search A pointer to the string to search for.
 * @param where A pointer to the vector of strings where to search.
 * @return true if the string is found, false otherwise.
 */
bool search_in(tstring *search, vector<tstring> *where);

/**
 * @brief Parses a long integer from a string.
 *
 * This function attempts to parse a long integer from a string. It returns
 * false if the string cannot be parsed into a valid long integer.
 *
 * @param str A pointer to the string to parse.
 * @param value A pointer to the variable where the parsed value will be stored.
 * @return true if the parsing is successful, false otherwise.
 */
bool parseLongFromString(tstring * str, long * value);

/**
 * @brief Removes protocol and trailing slash from a URL.
 *
 * This function removes the protocol (e.g., http:// or https://) and
 * any trailing slashes from a URL, leaving just the main address.
 *
 * @param url A pointer to the string representing the URL.
 * @return A modified string with the protocol and trailing slashes removed.
 */
tstring * removeProtocolAndSlash(tstring * url);
