//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#if !defined(AFX_ITEM_H__9DD28C1C_C5C2_4CDB_9D09_D54FA75B418E__INCLUDED_)
#define AFX_ITEM_H__9DD28C1C_C5C2_4CDB_9D09_D54FA75B418E__INCLUDED_


#include <objbase.h>
#include <msxml6.h>
#include "Formula.h"
#include "common_functions.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Item.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CItem - класс описания xml-файла для сериализации схемы (.fms)
//
class CItem : public CObject
{
	// запрет конструктора копирования
	CItem(const CItem& src);            
	void operator=(const CItem& src);   

	DECLARE_XMLSERIAL(CItem)

public:
// конструктор
	CItem();


public:

	CTime		DateOfCreation;    // дата создания файла
	CString		Version;           // строка версии, пока пишу "1.0"
// оставлены как примеры использования различных переменных
//	bool		m_boolAtribute;
//	double		m_doubleAttribute;
//	CStringArray m_stringArrayAttribute;

public:
	// деструктор
	virtual ~CItem();
	// функция сериализации (записи в файл/загрузки из файла)
	virtual void Serialize(CArchive &ar);

};

/////////////////////////////////////////////////////////////////////////////
// CDerivedItem производный класс от CItem
//
class CDerivedItem : public CItem
{
	// запрет конструктора копирования
	CDerivedItem(const CDerivedItem& src);            
	void operator=(const CDerivedItem& src);   

	DECLARE_XMLSERIAL(CDerivedItem)


public:
	// конструктор
	CDerivedItem();

public:
	enum { eFIRST, eSECOND } m_enumAttribute;
	
// Implementation
public:
	// деструктор
	virtual ~CDerivedItem();
	// функция сериализации (записи в файл/загрузки из файла)
	virtual void Serialize(CArchive &ar);

};


/////////////////////////////////////////////////////////////////////////////
// CVariableItem - класс для сериализации класса EntityVariable, описывающего переменные
//
class CVariableItem : public CObject
{
	// запрет конструктора копирования
	CVariableItem(const CVariableItem& src);
	void operator=(const CVariableItem& src);   

	DECLARE_XMLSERIAL(CVariableItem)

public:
	// конструктор
	CVariableItem();

public:
	VariableType Variable;    // тип переменной (простая переменная или множество)
	CString Label;    // символ переменной
	CString Index;    // символ индекса
	CString Text;    // текст переменной, текст в формате с тэгами
	CString Level;   // уровень переменной
	CString Redefinition; // переопределение текста переменной
	
public:
	// деструктор
	virtual ~CVariableItem();
	// функция сериализации (записи в файл/загрузки из файла)
	virtual void Serialize(CArchive &ar);
	// конструктор, принимающий в качестве параметра ссылку на объект EntityVariable
	CVariableItem(EntityVariable& ev);

};


/////////////////////////////////////////////////////////////////////////////
// CParentLinkItem - класс для сериализации родительских связей ParentLink
//
class CParentLinkItem : public CObject
{
	// запрет конструктора копирования
	CParentLinkItem(const CParentLinkItem& src);
	void operator=(const CParentLinkItem& src);   

	DECLARE_XMLSERIAL(CParentLinkItem)

public:
	// конструктор по умолчанию
	CParentLinkItem();

public:
	int FormulaNumber;    // порядковый номер используемой формулы
	int VariableNumber;    // порядковый номер используемой переменной
	
// Implementation
public:
	// деструктор
	virtual ~CParentLinkItem();
	// функция сериализации (записи в файл/загрузки из файла)
	virtual void Serialize(CArchive &ar);
	// конструктор, принимающий в качестве параметров порядковый номер формулы и порядковый номер переменной для указания родительской связи
	CParentLinkItem(int FormulaNumber_, int VariableNumber_);

};



/////////////////////////////////////////////////////////////////////////////
// CFormulaItem - класс для сериализации класса Formula, описывающего формулы
//
class CFormulaItem : public CObject
{
	// запрет конструктора копирования
	CFormulaItem(const CFormulaItem& src);
	void operator=(const CFormulaItem& src);   

	DECLARE_XMLSERIAL(CFormulaItem)


public:
	// конструктор
	CFormulaItem();

// Attributes
public:
	Formula_Feature Feature;    // тип формулы (выполнимость, ложность, истинность
	int Number;                 // порядковый номер в файле сериализации текущей формулы
	int ParentSetNumber;          // номер родительского множества истинности (для предикатов)
	int ReplacedNumber;          // номер множества, в котором была заменена переменная
	CArrayXML <CVariableItem *, CVariableItem *> FreeVariables;  // свободные переменные
	CArrayXML <CVariableItem *, CVariableItem *> LinkedVariables;  // связаные переменные
	CArrayXML <CParentLinkItem *, CParentLinkItem *> ParentLinks;  // родительские связи
	CArrayXML <CVariableItem *, CVariableItem *> ReplaceVariables;  // свободные переменные, начальная и для замены, в случае REPLACE_VARIABLE
	CString Description;  // описание формулы
	CString Addons;  // дополнительное описание
	CString Label; // условное обозначение
	CString Text; // текст , записывается при создании, выделен в отдельную переменную, чтобы не формировать каждый раз 
	CString Redefined;
	bool Redefined_Flag;

	EntityBaseType EntityType; // тип cущности, одно из значений enum EntityBaseType::
	
// Implementation
public:
	// деструктор
	virtual ~CFormulaItem();
	// функция сериализации (записи в файл/загрузки из файла)
	virtual void Serialize(CArchive &ar);
	//  конструктор, принимающий в качестве аргумента ссылку на объект Formula
	CFormulaItem(Formula& ev);
	void SetNumber(int number) { Number = number; };
	void SetParentSetNumber(int number) { ParentSetNumber = number; };
};


/////////////////////////////////////////////////////////////////////////////
// CSetItem - класс для сериализации класса FormulaSet, описывающего множества истинности
//
class CSetItem : public CObject
{
	// запрет конструктора копирования
	CSetItem(const CSetItem& src);
	void operator=(const CSetItem& src);   

	DECLARE_XMLSERIAL(CSetItem)

public:
	// конструктор
	CSetItem();

public:
	int Number;                 // порядковый номер в файле сериализации текущего множества истинности
	int FormulaNumber;          // номер родительской формулы
	int ReplacedNumber;          // номер множества, в котором была заменена переменная
	CArrayXML <CVariableItem *, CVariableItem *> FreeVariables;  // свободные переменные
	CArrayXML <CVariableItem *, CVariableItem *> LinkedVariables;  // связаные переменные
	CArrayXML <CVariableItem *, CVariableItem *> BaseVariables;  // базовые переменные
	CArrayXML <CVariableItem *, CVariableItem *> ReplaceVariables;  // свободные переменные, начальная и для замены, в случае REPLACE_VARIABLE
	CVariableItem Naming; // наименование множества истинности
	CString Description;  // описание формулы
	CString Addons;  // дополнительное описание
	CString Label; // условное обозначение
	CString Text; // тест , записывается при создании, выделен в отдельную переменную, чтобы не формировать каждый раз 
	CString Redefined;
	bool Redefined_Flag;
	EntityBaseType EntityType; // тип cущности, одно из значений enum EntityBaseType::
	
// Implementation
public:
	// деструктор
	virtual ~CSetItem();
	// функция сериализации (записи в файл/загрузки из файла)
	virtual void Serialize(CArchive &ar);
	//  конструктор, принимающий в качестве аргумента ссылку на объект FormulaSet
	CSetItem(FormulaSet& ev);
	void SetNumber(int number) { Number = number; };
};


/////////////////////////////////////////////////////////////////////////////




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_ITEM_H__9DD28C1C_C5C2_4CDB_9D09_D54FA75B418E__INCLUDED_)
