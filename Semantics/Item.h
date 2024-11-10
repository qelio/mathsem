//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
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
// CItem - ����� �������� xml-����� ��� ������������ ����� (.fms)
//
class CItem : public CObject
{
	// ������ ������������ �����������
	CItem(const CItem& src);            
	void operator=(const CItem& src);   

	DECLARE_XMLSERIAL(CItem)

public:
// �����������
	CItem();


public:

	CTime		DateOfCreation;    // ���� �������� �����
	CString		Version;           // ������ ������, ���� ���� "1.0"
// ��������� ��� ������� ������������� ��������� ����������
//	bool		m_boolAtribute;
//	double		m_doubleAttribute;
//	CStringArray m_stringArrayAttribute;

public:
	// ����������
	virtual ~CItem();
	// ������� ������������ (������ � ����/�������� �� �����)
	virtual void Serialize(CArchive &ar);

};

/////////////////////////////////////////////////////////////////////////////
// CDerivedItem ����������� ����� �� CItem
//
class CDerivedItem : public CItem
{
	// ������ ������������ �����������
	CDerivedItem(const CDerivedItem& src);            
	void operator=(const CDerivedItem& src);   

	DECLARE_XMLSERIAL(CDerivedItem)


public:
	// �����������
	CDerivedItem();

public:
	enum { eFIRST, eSECOND } m_enumAttribute;
	
// Implementation
public:
	// ����������
	virtual ~CDerivedItem();
	// ������� ������������ (������ � ����/�������� �� �����)
	virtual void Serialize(CArchive &ar);

};


/////////////////////////////////////////////////////////////////////////////
// CVariableItem - ����� ��� ������������ ������ EntityVariable, ������������ ����������
//
class CVariableItem : public CObject
{
	// ������ ������������ �����������
	CVariableItem(const CVariableItem& src);
	void operator=(const CVariableItem& src);   

	DECLARE_XMLSERIAL(CVariableItem)

public:
	// �����������
	CVariableItem();

public:
	VariableType Variable;    // ��� ���������� (������� ���������� ��� ���������)
	CString Label;    // ������ ����������
	CString Index;    // ������ �������
	CString Text;    // ����� ����������, ����� � ������� � ������
	CString Level;   // ������� ����������
	CString Redefinition; // ��������������� ������ ����������
	
public:
	// ����������
	virtual ~CVariableItem();
	// ������� ������������ (������ � ����/�������� �� �����)
	virtual void Serialize(CArchive &ar);
	// �����������, ����������� � �������� ��������� ������ �� ������ EntityVariable
	CVariableItem(EntityVariable& ev);

};


/////////////////////////////////////////////////////////////////////////////
// CParentLinkItem - ����� ��� ������������ ������������ ������ ParentLink
//
class CParentLinkItem : public CObject
{
	// ������ ������������ �����������
	CParentLinkItem(const CParentLinkItem& src);
	void operator=(const CParentLinkItem& src);   

	DECLARE_XMLSERIAL(CParentLinkItem)

public:
	// ����������� �� ���������
	CParentLinkItem();

public:
	int FormulaNumber;    // ���������� ����� ������������ �������
	int VariableNumber;    // ���������� ����� ������������ ����������
	
// Implementation
public:
	// ����������
	virtual ~CParentLinkItem();
	// ������� ������������ (������ � ����/�������� �� �����)
	virtual void Serialize(CArchive &ar);
	// �����������, ����������� � �������� ���������� ���������� ����� ������� � ���������� ����� ���������� ��� �������� ������������ �����
	CParentLinkItem(int FormulaNumber_, int VariableNumber_);

};



/////////////////////////////////////////////////////////////////////////////
// CFormulaItem - ����� ��� ������������ ������ Formula, ������������ �������
//
class CFormulaItem : public CObject
{
	// ������ ������������ �����������
	CFormulaItem(const CFormulaItem& src);
	void operator=(const CFormulaItem& src);   

	DECLARE_XMLSERIAL(CFormulaItem)


public:
	// �����������
	CFormulaItem();

// Attributes
public:
	Formula_Feature Feature;    // ��� ������� (������������, ��������, ����������
	int Number;                 // ���������� ����� � ����� ������������ ������� �������
	int ParentSetNumber;          // ����� ������������� ��������� ���������� (��� ����������)
	int ReplacedNumber;          // ����� ���������, � ������� ���� �������� ����������
	CArrayXML <CVariableItem *, CVariableItem *> FreeVariables;  // ��������� ����������
	CArrayXML <CVariableItem *, CVariableItem *> LinkedVariables;  // �������� ����������
	CArrayXML <CParentLinkItem *, CParentLinkItem *> ParentLinks;  // ������������ �����
	CArrayXML <CVariableItem *, CVariableItem *> ReplaceVariables;  // ��������� ����������, ��������� � ��� ������, � ������ REPLACE_VARIABLE
	CString Description;  // �������� �������
	CString Addons;  // �������������� ��������
	CString Label; // �������� �����������
	CString Text; // ����� , ������������ ��� ��������, ������� � ��������� ����������, ����� �� ����������� ������ ��� 
	CString Redefined;
	bool Redefined_Flag;

	EntityBaseType EntityType; // ��� c�������, ���� �� �������� enum EntityBaseType::
	
// Implementation
public:
	// ����������
	virtual ~CFormulaItem();
	// ������� ������������ (������ � ����/�������� �� �����)
	virtual void Serialize(CArchive &ar);
	//  �����������, ����������� � �������� ��������� ������ �� ������ Formula
	CFormulaItem(Formula& ev);
	void SetNumber(int number) { Number = number; };
	void SetParentSetNumber(int number) { ParentSetNumber = number; };
};


/////////////////////////////////////////////////////////////////////////////
// CSetItem - ����� ��� ������������ ������ FormulaSet, ������������ ��������� ����������
//
class CSetItem : public CObject
{
	// ������ ������������ �����������
	CSetItem(const CSetItem& src);
	void operator=(const CSetItem& src);   

	DECLARE_XMLSERIAL(CSetItem)

public:
	// �����������
	CSetItem();

public:
	int Number;                 // ���������� ����� � ����� ������������ �������� ��������� ����������
	int FormulaNumber;          // ����� ������������ �������
	int ReplacedNumber;          // ����� ���������, � ������� ���� �������� ����������
	CArrayXML <CVariableItem *, CVariableItem *> FreeVariables;  // ��������� ����������
	CArrayXML <CVariableItem *, CVariableItem *> LinkedVariables;  // �������� ����������
	CArrayXML <CVariableItem *, CVariableItem *> BaseVariables;  // ������� ����������
	CArrayXML <CVariableItem *, CVariableItem *> ReplaceVariables;  // ��������� ����������, ��������� � ��� ������, � ������ REPLACE_VARIABLE
	CVariableItem Naming; // ������������ ��������� ����������
	CString Description;  // �������� �������
	CString Addons;  // �������������� ��������
	CString Label; // �������� �����������
	CString Text; // ���� , ������������ ��� ��������, ������� � ��������� ����������, ����� �� ����������� ������ ��� 
	CString Redefined;
	bool Redefined_Flag;
	EntityBaseType EntityType; // ��� c�������, ���� �� �������� enum EntityBaseType::
	
// Implementation
public:
	// ����������
	virtual ~CSetItem();
	// ������� ������������ (������ � ����/�������� �� �����)
	virtual void Serialize(CArchive &ar);
	//  �����������, ����������� � �������� ��������� ������ �� ������ FormulaSet
	CSetItem(FormulaSet& ev);
	void SetNumber(int number) { Number = number; };
};


/////////////////////////////////////////////////////////////////////////////




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_ITEM_H__9DD28C1C_C5C2_4CDB_9D09_D54FA75B418E__INCLUDED_)
