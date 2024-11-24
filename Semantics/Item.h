//  Автор кода: Татаринцев В.В., akizelokro@mail.ru, 2013-2014
#if !defined(AFX_ITEM_H__9DD28C1C_C5C2_4CDB_9D09_D54FA75B418E__INCLUDED_)
#define AFX_ITEM_H__9DD28C1C_C5C2_4CDB_9D09_D54FA75B418E__INCLUDED_

/**
 * @file Item.h
 * @brief Определяет классы для сериализации и обработки элементов формул.
 */

#include <objbase.h>
#include <msxml6.h>
#include "Formula.h"
#include "common_functions.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Item.h : заголовочный файл
//

/////////////////////////////////////////////////////////////////////////////
// CItem - класс для сериализации XML-структур при сохранении формулы (.fms)
//
class CItem : public CObject
{
	// Запрещаем копирование
	CItem(const CItem& src);
	void operator=(const CItem& src);

	DECLARE_XMLSERIAL(CItem)

public:
	/**
     * @brief Конструктор по умолчанию.
     */
	CItem();

public:
	/**
     * @brief Дата создания элемента.
     */
	CTime		DateOfCreation;    // Дата создания элемента
    /**
     * @brief Версия файла.
     */
	CString		Version;           // Версия файла, например "1.0"
// Атрибуты для пользовательской сериализации
//	bool		m_boolAtribute;
//	double		m_doubleAttribute;
//	CStringArray m_stringArrayAttribute;

public:
	/**
     * @brief Деструктор.
     */
	virtual ~CItem();
	/**
     * @brief Сериализация элемента (запись в поток/чтение из потока).
     * @param ar Архив для сериализации.
     */
	virtual void Serialize(CArchive &ar);
};

/////////////////////////////////////////////////////////////////////////////
// CDerivedItem - производный класс от CItem
//

/**
 * @brief Представляет производный элемент от CItem.
 */
class CDerivedItem : public CItem
{
	// Запрещаем копирование
	CDerivedItem(const CDerivedItem& src);
	void operator=(const CDerivedItem& src);

	DECLARE_XMLSERIAL(CDerivedItem)

public:
    /**
     * @brief Конструктор по умолчанию.
     */
	CDerivedItem();

public:
    /**
     * @brief Пример перечислительного атрибута.
     */
	enum { eFIRST, eSECOND } m_enumAttribute;

// Реализация
public:

    /**
     * @brief Деструктор.
     */
	virtual ~CDerivedItem();
	/**
     * @brief Сериализация производного элемента (запись в поток/чтение из потока).
     * @param ar Архив для сериализации.
     */
	virtual void Serialize(CArchive &ar);
};

/////////////////////////////////////////////////////////////////////////////
// CVariableItem - класс для сериализации переменной EntityVariable
//
/**
 * @brief Представляет переменную для сериализации.
 */
class CVariableItem : public CObject
{
	// Запрещаем копирование
	CVariableItem(const CVariableItem& src);
	void operator=(const CVariableItem& src);

	DECLARE_XMLSERIAL(CVariableItem)

public:
    /**
     * @brief Конструктор по умолчанию.
     */
	CVariableItem();

public:
	/**
     * @brief Тип переменной.
     */
    VariableType Variable;

    /**
     * @brief Метка переменной.
     */
    CString Label;

    /**
     * @brief Индекс переменной.
     */
    CString Index;

    /**
     * @brief Исходный текст переменной.
     */
    CString Text;

    /**
     * @brief Уровень переменной.
     */
    CString Level;

    /**
     * @brief Текст переопределения переменной.
     */
    CString Redefinition;

public:
    /**
     * @brief Деструктор.
     */
	virtual ~CVariableItem();
    /**
     * @brief Сериализация переменной (запись в поток/чтение из потока).
     * @param ar Архив для сериализации.
     */
	virtual void Serialize(CArchive &ar);
    /**
     * @brief Конструктор, который создает переменную из EntityVariable.
     * @param ev EntityVariable для создания.
     */
	CVariableItem(EntityVariable& ev);
};


/////////////////////////////////////////////////////////////////////////////
// CParentLinkItem - класс для сериализации родительской связи ParentLink
//
/**
 * @brief Представляет родительскую связь для сериализации.
 */
class CParentLinkItem : public CObject
{
	// Запрещаем копирование
	CParentLinkItem(const CParentLinkItem& src);
	void operator=(const CParentLinkItem& src);

	DECLARE_XMLSERIAL(CParentLinkItem)

public:
    /**
     * @brief Конструктор по умолчанию.
     */
	CParentLinkItem();

public:
    /**
     * @brief Номер родительской формулы.
     */
	int FormulaNumber;    // Номер родительской формулы
    /**
     * @brief Номер переменной в родительской формуле.
     */
	int VariableNumber;    // Номер переменной в родительской формуле

// Реализация
public:
    /**
     * @brief Деструктор.
     */
	virtual ~CParentLinkItem();
    /**
     * @brief Сериализация родительской связи (запись в поток/чтение из потока).
     * @param ar Архив для сериализации.
     */
	virtual void Serialize(CArchive &ar);
    /**
     * @brief Конструктор, который создает родительскую связь с указанными номерами формулы и переменной.
     * @param FormulaNumber_ Номер формулы.
     * @param VariableNumber_ Номер переменной.
     */
	CParentLinkItem(int FormulaNumber_, int VariableNumber_);
};


/////////////////////////////////////////////////////////////////////////////
// CFormulaItem - класс для сериализации формулы Formula
//
/**
 * @brief Представляет формулу для сериализации.
 */
class CFormulaItem : public CObject
{
	// Запрещаем копирование
	CFormulaItem(const CFormulaItem& src);
	void operator=(const CFormulaItem& src);

	DECLARE_XMLSERIAL(CFormulaItem)

public:
    /**
     * @brief Конструктор по умолчанию.
     */
	CFormulaItem();

// Атрибуты
public:
	/**
     * @brief Характеристика формулы (аксиома, теорема, заключение).
     */
    Formula_Feature Feature;

    /**
     * @brief Уникальный номер формулы в общей нумерации.
     */
    int Number;

    /**
     * @brief Номер родительского набора для этой формулы (используется в заключениях).
     */
    int ParentSetNumber;

    /**
     * @brief Номер формулы, заменённой этой.
     */
    int ReplacedNumber;

    /**
     * @brief Коллекция свободных переменных.
     */
    CArrayXML <CVariableItem*, CVariableItem*> FreeVariables;

    /**
     * @brief Коллекция связанных переменных.
     */
    CArrayXML <CVariableItem*, CVariableItem*> LinkedVariables;

    /**
     * @brief Коллекция родительских связей.
     */
    CArrayXML <CParentLinkItem*, CParentLinkItem*> ParentLinks;

    /**
     * @brief Коллекция переменных, заменённых в этой формуле.
     */
    CArrayXML <CVariableItem*, CVariableItem*> ReplaceVariables;

    /**
     * @brief Описание формулы.
     */
    CString Description;

    /**
     * @brief Дополнительная информация для формулы.
     */
    CString Addons;

    /**
     * @brief Метка формулы.
     */
    CString Label;

    /**
     * @brief Исходный текст формулы.
     */
    CString Text;

    /**
     * @brief Переопределённый текст формулы.
     */
    CString Redefined;

    /**
     * @brief Флаг, указывающий, была ли формула переопределена.
     */
    bool Redefined_Flag;

    /**
     * @brief Тип сущности из перечисления EntityBaseType.
     */
    EntityBaseType EntityType; // Тип сущности, из перечисления enum EntityBaseType::

// Реализация
public:
    /**
     * @brief Деструктор.
     */
	virtual ~CFormulaItem();
    /**
     * @brief Сериализация формулы (запись в поток/чтение из потока).
     * @param ar Архив для сериализации.
     */
	virtual void Serialize(CArchive &ar);
    /**
     * @brief Конструктор, который создаёт формулу из объекта Formula.
     * @param f Formula для создания.
     */
	CFormulaItem(Formula& ev);
    /**
     * @brief Устанавливает номер формулы.
     * @param number Новый номер формулы.
     */
	void SetNumber(int number) { Number = number; };
	void SetParentSetNumber(int number) { ParentSetNumber = number; };
};


/////////////////////////////////////////////////////////////////////////////
// CSetItem - класс для сериализации набора формул FormulaSet
//
/**
 * @brief Представляет набор для сериализации.
 */
class CSetItem : public CObject
{
	CSetItem(const CSetItem& src);
	void operator=(const CSetItem& src);

	DECLARE_XMLSERIAL(CSetItem)

public:
    /**
     * @brief Конструктор по умолчанию.
     */
	CSetItem();

public:
	/**
     * @brief Характеристика набора формул.
     */
    Formula_Feature Feature;

    /**
     * @brief Уникальный номер набора в общей нумерации.
     */
    int Number;

    /**
     * @brief Номер родительского набора для этого набора.
     */
    int ParentSetNumber;

    /**
     * @brief Номер набора, заменённого этим.
     */
    int ReplacedNumber;

    /**
     * @brief Коллекция формул в этом наборе.
     */
    CArrayXML <CFormulaItem*, CFormulaItem*> Formulas;

    /**
     * @brief Коллекция заменённых переменных.
     */
    CArrayXML <CVariableItem*, CVariableItem*> ReplaceVariables;

    /**
     * @brief Описание набора.
     */
    CString Description;

    /**
     * @brief Дополнительная информация для набора.
     */
    CString Addons;

    /**
     * @brief Метка набора.
     */
    CString Label;

    /**
     * @brief Исходный текст набора.
     */
    CString Text;

    /**
     * @brief Переопределённый текст набора.
     */
    CString Redefined;

    /**
     * @brief Флаг, указывающий, был ли набор переопределён.
     */
    bool Redefined_Flag;

    /**
     * @brief Тип сущности из перечисления EntityBaseType.
     */
    EntityBaseType EntityType; // Тип сущности, из перечисления enum EntityBaseType::

// Реализация
public:
    /**
     * @brief Деструктор.
     */
	virtual ~CSetItem();
    /**
     * @brief Сериализация набора (запись в поток/чтение из потока).
     * @param ar Архив для сериализации.
     */
	virtual void Serialize(CArchive &ar);

    /**
     * @brief Конструктор, который создаёт набор из объекта FormulaSet.
     * @param f FormulaSet для создания.
     */
	CSetItem(FormulaSet& ev);
	void SetNumber(int number) { Number = number; };
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ITEM_H__9DD28C1C_C5C2_4CDB_9D09_D54FA75B418E__INCLUDED_)