//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#if !defined(AFX_ITEM_H__9DD28C1C_C5C2_4CDB_9D09_D54FA75B418E__INCLUDED_)
#define AFX_ITEM_H__9DD28C1C_C5C2_4CDB_9D09_D54FA75B418E__INCLUDED_

/**
 * @file Item.h
 * @brief Defines classes for serialization and handling of formula items.
 */


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
// CItem - ����� �������� xml-����� ��� ������������ ����� (.fms)
//
class CItem : public CObject
{
	// ������ ������������ �����������
	CItem(const CItem& src);
	void operator=(const CItem& src);

	DECLARE_XMLSERIAL(CItem)

public:
	/**
     * @brief Default constructor.
     */
// �����������
	CItem();


public:
	/**
     * @brief The creation date of the item.
     */
	CTime		DateOfCreation;    // ���� �������� �����
    /**
     * @brief The version of the file.
     */
	CString		Version;           // ������ ������, ���� ���� "1.0"
// ��������� ��� ������� ������������� ��������� ����������
//	bool		m_boolAtribute;
//	double		m_doubleAttribute;
//	CStringArray m_stringArrayAttribute;

public:
	// ����������
	/**
     * @brief Destructor.
     */
	virtual ~CItem();
	// ������� ������������ (������ � ����/�������� �� �����)
    /**
     * @brief Serialize the item to or from an archive.
     * @param ar The archive to serialize to or from.
     */
	virtual void Serialize(CArchive &ar);

};

/////////////////////////////////////////////////////////////////////////////
// CDerivedItem ����������� ����� �� CItem
//

/**
 * @brief Represents a derived item from CItem.
 */
class CDerivedItem : public CItem
{
	// ������ ������������ �����������
	CDerivedItem(const CDerivedItem& src);
	void operator=(const CDerivedItem& src);

	DECLARE_XMLSERIAL(CDerivedItem)


public:
    /**
     * @brief Default constructor.
     */
	// �����������
	CDerivedItem();

public:
    /**
     * @brief An example enumeration attribute.
     */
	enum { eFIRST, eSECOND } m_enumAttribute;

// Implementation
public:

    /**
     * @brief Destructor.
     */
	// ����������
	virtual ~CDerivedItem();
	/**
     * @brief Serialize the derived item to or from an archive.
     * @param ar The archive to serialize to or from.
     */
	// ������� ������������ (������ � ����/�������� �� �����)
	virtual void Serialize(CArchive &ar);

};


/////////////////////////////////////////////////////////////////////////////
// CVariableItem - ����� ��� ������������ ������ EntityVariable, ������������ ����������
//
/**
 * @brief Represents a variable item used in serialization.
 */
class CVariableItem : public CObject
{
	// ������ ������������ �����������
	CVariableItem(const CVariableItem& src);
	void operator=(const CVariableItem& src);

	DECLARE_XMLSERIAL(CVariableItem)

public:
    /**
     * @brief Default constructor.
     */
	// �����������
	CVariableItem();

public:
	/**
     * @brief The type of the variable.
     */
    VariableType Variable;

    /**
     * @brief The label of the variable.
     */
    CString Label;

    /**
     * @brief The index of the variable.
     */
    CString Index;

    /**
     * @brief The initial text of the variable.
     */
    CString Text;

    /**
     * @brief The level of the variable.
     */
    CString Level;

    /**
     * @brief The redefinition text of the variable.
     */
    CString Redefinition;

public:
    /**
     * @brief Destructor.
     */
	// ����������
	virtual ~CVariableItem();
    /**
     * @brief Serialize the variable item to or from an archive.
     * @param ar The archive to serialize to or from.
     */
	// ������� ������������ (������ � ����/�������� �� �����)
	virtual void Serialize(CArchive &ar);
    /**
     * @brief Constructor that creates a variable item from an EntityVariable.
     * @param ev The EntityVariable to create from.
     */
	// �����������, ����������� � �������� ��������� ������ �� ������ EntityVariable
	CVariableItem(EntityVariable& ev);

};


/////////////////////////////////////////////////////////////////////////////
// CParentLinkItem - ����� ��� ������������ ������������ ������ ParentLink
//
/**
 * @brief Represents a parent link item used in serialization.
 */
class CParentLinkItem : public CObject
{
	// ������ ������������ �����������
	CParentLinkItem(const CParentLinkItem& src);
	void operator=(const CParentLinkItem& src);

	DECLARE_XMLSERIAL(CParentLinkItem)

public:
    /**
     * @brief Default constructor.
     */
	// ����������� �� ���������
	CParentLinkItem();

public:
    /**
     * @brief The number of the parent formula.
     */
	int FormulaNumber;    // ���������� ����� ������������ �������
    /**
     * @brief The number of the variable in the parent formula.
     */
	int VariableNumber;    // ���������� ����� ������������ ����������

// Implementation
public:
    /**
     * @brief Destructor.
     */
	// ����������
	virtual ~CParentLinkItem();
    /**
     * @brief Serialize the parent link item to or from an archive.
     * @param ar The archive to serialize to or from.
     */
	// ������� ������������ (������ � ����/�������� �� �����)
	virtual void Serialize(CArchive &ar);
    /**
     * @brief Constructor that creates a parent link item with specified formula and variable numbers.
     * @param FormulaNumber_ The formula number.
     * @param VariableNumber_ The variable number.
     */
	// �����������, ����������� � �������� ���������� ���������� ����� ������� � ���������� ����� ���������� ��� �������� ������������ �����
	CParentLinkItem(int FormulaNumber_, int VariableNumber_);

};



/////////////////////////////////////////////////////////////////////////////
// CFormulaItem - ����� ��� ������������ ������ Formula, ������������ �������
//
/**
 * @brief Represents a formula item used in serialization.
 */
class CFormulaItem : public CObject
{
	// ������ ������������ �����������
	CFormulaItem(const CFormulaItem& src);
	void operator=(const CFormulaItem& src);

	DECLARE_XMLSERIAL(CFormulaItem)


public:
    /**
     * @brief Default constructor.
     */
	// �����������
	CFormulaItem();

// Attributes
public:
	/**
     * @brief The feature of the formula (axiom, theorem, conclusion).
     */
    Formula_Feature Feature;

    /**
     * @brief The unique number of the formula in general numbering.
     */
    int Number;

    /**
     * @brief The number of the parent set for this formula (used in conclusions).
     */
    int ParentSetNumber;

    /**
     * @brief The number of the formula replaced by this one.
     */
    int ReplacedNumber;

    /**
     * @brief The collection of free variables.
     */
    CArrayXML <CVariableItem*, CVariableItem*> FreeVariables;

    /**
     * @brief The collection of linked variables.
     */
    CArrayXML <CVariableItem*, CVariableItem*> LinkedVariables;

    /**
     * @brief The collection of parent links.
     */
    CArrayXML <CParentLinkItem*, CParentLinkItem*> ParentLinks;

    /**
     * @brief The collection of variables replaced in this formula.
     */
    CArrayXML <CVariableItem*, CVariableItem*> ReplaceVariables;

    /**
     * @brief The description of the formula.
     */
    CString Description;

    /**
     * @brief Additional information for the formula.
     */
    CString Addons;

    /**
     * @brief The label of the formula.
     */
    CString Label;

    /**
     * @brief The initial text of the formula.
     */
    CString Text;

    /**
     * @brief The redefined text of the formula.
     */
    CString Redefined;

    /**
     * @brief Flag indicating whether the formula has been redefined.
     */
    bool Redefined_Flag;

    /**
     * @brief The type of the entity from EntityBaseType enumeration.
     */
    EntityBaseType EntityType; // ��� c�������, ���� �� �������� enum EntityBaseType::

// Implementation
public:
    /**
     * @brief Destructor.
     */
	// ����������
	virtual ~CFormulaItem();
    /**
     * @brief Serialize the formula item to or from an archive.
     * @param ar The archive to serialize to or from.
     */
	// ������� ������������ (������ � ����/�������� �� �����)
	virtual void Serialize(CArchive &ar);
    /**
     * @brief Constructor that creates a formula item from a Formula object.
     * @param f The Formula object to create from.
     */
	//  �����������, ����������� � �������� ��������� ������ �� ������ Formula
	CFormulaItem(Formula& ev);
    /**
     * @brief Sets the formula number.
     * @param number The new formula number.
     */
	void SetNumber(int number) { Number = number; };
	void SetParentSetNumber(int number) { ParentSetNumber = number; };
};


/////////////////////////////////////////////////////////////////////////////
// CSetItem - ����� ��� ������������ ������ FormulaSet, ������������ ��������� ����������
//
/**
 * @brief Represents a set item used in serialization.
 */
class CSetItem : public CObject
{
	CSetItem(const CSetItem& src);
	void operator=(const CSetItem& src);

	DECLARE_XMLSERIAL(CSetItem)

public:
    /**
     * @brief Default constructor.
     */
	// �����������
	CSetItem();

public:
	/**
     * @brief The feature of the formula set.
     */
    Formula_Feature Feature;

    /**
     * @brief The unique number of the set in general numbering.
     */
    int Number;

    /**
     * @brief The number of the parent set for this set.
     */
    int ParentSetNumber;

    /**
     * @brief The number of the set replaced by this one.
     */
    int ReplacedNumber;

    /**
     * @brief The collection of formulas in this set.
     */
    CArrayXML <CFormulaItem*, CFormulaItem*> Formulas;

    /**
     * @brief The collection of replace variables.
     */
    CArrayXML <CVariableItem*, CVariableItem*> ReplaceVariables;

    /**
     * @brief The description of the set.
     */
    CString Description;

    /**
     * @brief Additional information for the set.
     */
    CString Addons;

    /**
     * @brief The label of the set.
     */
    CString Label;

    /**
     * @brief The initial text of the set.
     */
    CString Text;

    /**
     * @brief The redefined text of the set.
     */
    CString Redefined;

    /**
     * @brief Flag indicating whether the set has been redefined.
     */
    bool Redefined_Flag;

    /**
     * @brief The type of the entity from EntityBaseType enumeration.
     */
    EntityBaseType EntityType; // ��� c�������, ���� �� �������� enum EntityBaseType::

// Implementation
public:
    /**
     * @brief Destructor.
     */
	// ����������
	virtual ~CSetItem();
    /**
     * @brief Serialize the set item to or from an archive.
     * @param ar The archive to serialize to or from.
     */
	// ������� ������������ (������ � ����/�������� �� �����)
	virtual void Serialize(CArchive &ar);

    /**
     * @brief Constructor that creates a set item from a FormulaSet object.
     * @param f The FormulaSet object to create from.
     */
	//  �����������, ����������� � �������� ��������� ������ �� ������ FormulaSet
	CSetItem(FormulaSet& ev);
	void SetNumber(int number) { Number = number; };
};


/////////////////////////////////////////////////////////////////////////////




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_ITEM_H__9DD28C1C_C5C2_4CDB_9D09_D54FA75B418E__INCLUDED_)