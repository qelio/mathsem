//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
// Item.cpp : implementation file
//


//TRANSLATED


#include "stdafx.h"
#include "xmlarchive.h"
//#include "XMLSerialization.h"
#include "Item.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString version_of_file = _T("1.0.8");

/////////////////////////////////////////////////////////////////////////////
// CItem - класс описания xml-файла для сериализации схемы (.fms)

IMPLEMENT_XMLSERIAL(CItem, CObject)

//
// конструктор по умолчанию
//
CItem::CItem()
{
	static int sequentialNo = 0;    // осталось от примера 

	DateOfCreation = CTime::GetCurrentTime();    // текущее время
	Version = _T("1.0.8");    // текущая версия файла


// оставил как примеры
//	m_intAttribute = sequentialNo++;
//	m_stringAttribute.Format(_T("1.1"), m_intAttribute);
//	m_boolAtribute = false;
//	m_doubleAttribute = m_intAttribute;
//	m_stringArrayAttribute.Add(_T("Ciao"));
//	m_stringArrayAttribute.Add(_T("Hello"));
//	m_stringArrayAttribute.Add(_T("Goodbye"));
}


//
//  деструктор
//
CItem::~CItem()
{
}


//
// функция сериализации (записи в файл/загрузки из файла)
//
void CItem::Serialize(CArchive& ar)
{
	XMLCLASSNODE

	// Do not call CObject::Serialize() , it's not XML aware !
	
	XMLDATA(DateOfCreation);    // сериализация даты создания
	XMLDATA(Version);    // сериализация версии файла

//	XMLDATA(m_boolAtribute);
//	XMLDATA(m_doubleAttribute);
//	XMLDATA(m_stringArrayAttribute);
	
	XMLENDNODE
	version_of_file = Version;
}

////////////////////////////////////////////////////////////////////////////
// CDerivedItem производный класс от CItem

IMPLEMENT_XMLSERIAL(CDerivedItem, CItem)

//
// конструктор по умолчанию
//
CDerivedItem::CDerivedItem()
{
	static int sequentialNo = 0;

	m_enumAttribute = eFIRST;

}

//
// деструктор
//
CDerivedItem::~CDerivedItem()
{
}


//
// функция сериализации (записи в файл/загрузки из файла)
//
void CDerivedItem::Serialize(CArchive& ar)
{
	XMLCLASSNODE

	CItem::Serialize(ar);    // сериализация базового класса

	XMLINTDATA(m_enumAttribute);
	
	XMLENDNODE

}


////////////////////////////////////////////////////////////////////////////
// CVariableItem - класс для сериализации класса EntityVariable, описывающего переменные

IMPLEMENT_XMLSERIAL(CVariableItem, CObject)

//
// конструктор
// 
CVariableItem::CVariableItem()
{
	Variable = NONE_VARIABLE;    // "никакая" переменная
}

//
// деструктор
//
CVariableItem::~CVariableItem()
{
}

//
// функция сериализации (записи в файл/загрузки из файла)
//
void CVariableItem::Serialize(CArchive& ar)
{
	XMLCLASSNODE
//	XMLINTDATA(m_enumAttribute);
	XMLINTDATA(Variable);     // сериализация типа переменной
	XMLDATA(Label);           // сериализация переменной
	XMLDATA(Index);           // сериализация индекса
	XMLDATA(Text);            // сериализация текста переменной, текст в формате с тэгами
	if((version_of_file == _T("1.0.6")) || (version_of_file > _T("1.0.5")))
		XMLDATA(Level);		// сериализация уровня переменной
	if((version_of_file == _T("1.0.8")) || (version_of_file > _T("1.0.7")))
		XMLDATA(Redefinition);	// сериализация переобозначения текста переменной, в формате с тэгами
	XMLENDNODE
}

//
// конструктор, принимающий в качестве параметра ссылку на объект EntityVariable
//
CVariableItem::CVariableItem(EntityVariable& ev)
{
	Variable = ev.GetType();    // тип переменной
	Label = ev.GetLabel().data();   // символ переменной
	Index = ev.GetIndex().data();   // символ индекса
	Text = ev.GetInitialText()->data();   // текст переменной, текст в формате с тэгами
	Level = ev.GetLevel().data(); // уровень переменной
	Redefinition = ev.GetRedefinition().data(); // переобозначение текста переменной
}


////////////////////////////////////////////////////////////////////////////
// CParentLinkItem - класс для сериализации родительских связей ParentLink

IMPLEMENT_XMLSERIAL(CParentLinkItem, CObject)

//
// конструктор по умолчанию
//
CParentLinkItem::CParentLinkItem()
{
	FormulaNumber = -1;
	VariableNumber = -1;
}


//
// деструктор
//
CParentLinkItem::~CParentLinkItem()
{
}


//
// функция сериализации (записи в файл/загрузки из файла)
//
void CParentLinkItem::Serialize(CArchive& ar)
{
	XMLCLASSNODE
	// сериализуем порядковые номера родительской формулы и родительской переменной
	XMLINTDATA(FormulaNumber);
	XMLINTDATA(VariableNumber);
	
	XMLENDNODE
}

//
// конструктор, принимающий в качестве параметров порядковый номер формулы и порядковый номер переменной для указания родительской связи
//
CParentLinkItem::CParentLinkItem(int FormulaNumber_, int VariableNumber_)
{
	VariableNumber = VariableNumber_;
	FormulaNumber = FormulaNumber_;
}



////////////////////////////////////////////////////////////////////////////
// CFormulaItem

IMPLEMENT_XMLSERIAL(CFormulaItem, CObject)

//
// конструктор по умолчанию
//
CFormulaItem::CFormulaItem()
{
	Feature = NONE_FEATURE;
	EntityType = NONE_FORMULA;
	Number = -1;
	ParentSetNumber = -1;
	ReplacedNumber = -1;
	Redefined = "";
	Redefined_Flag = false;
}


//
// деструктор
//
CFormulaItem::~CFormulaItem()
{
	// освобождаю свободные переменные
	for ( int i = 0; i < FreeVariables.GetSize(); i++)
	{
		delete FreeVariables[i];
	}
	FreeVariables.RemoveAll();
	for ( int i = 0; i < LinkedVariables.GetSize(); i++)
	{
		delete LinkedVariables[i];
	}
	LinkedVariables.RemoveAll();
	for ( int i = 0; i < ReplaceVariables.GetSize(); i++)
	{
		delete ReplaceVariables[i];
	}
	ReplaceVariables.RemoveAll();
}


//
// функция сериализации (записи в файл/загрузки из файла)
//
void CFormulaItem::Serialize(CArchive& ar)
{
	XMLCLASSNODE
	
	// сериализуем аттрибуты класса
	XMLINTDATA(Number);
	if((version_of_file == _T("1.0.3")) || (version_of_file > _T("1.0.3")))
		XMLDATA(ParentSetNumber);
	if((version_of_file == _T("1.0.4")) || (version_of_file > _T("1.0.3")))
		XMLDATA(ReplacedNumber);
	XMLINTDATA(Feature);
	XMLINTDATA(EntityType);
	XMLDATA(Description);
	XMLDATA(Label);
	XMLDATA(Addons);
	XMLDATA(Text);
	if(version_of_file != _T("1.0"))
		XMLDATA(Redefined);
	if((version_of_file != _T("1.0")) && (version_of_file != _T("1.0.1")))
		XMLDATA(Redefined_Flag);

	XMLDATA(FreeVariables);
	XMLDATA(ParentLinks);
	if((version_of_file == _T("1.0.4")) || (version_of_file > _T("1.0.3")))
		XMLDATA(ReplaceVariables);
	if((version_of_file == _T("1.0.6")) || (version_of_file > _T("1.0.5")))
		XMLDATA(LinkedVariables);
	XMLENDNODE
}


//
//  конструктор, принимающий в качестве аргумента ссылку на объект Formula
//
CFormulaItem::CFormulaItem(Formula& f)
{
	ReplacedNumber = -1;
	// инициализация аттрибутов значениями из объекта Formula
	bool wasRedefined = f.isRedefined();
	if(wasRedefined)
		f.setTemporarilyUnredefined();
	Feature =  f.getFeature();
	Description = f.getDescription()->data();
	Label = f.getLabel()->data();
	Addons = f.getAddOns()->data();
	EntityType = f.getType();
	Text = f.getInitialText()->data();
	vector <EntityVariable *> * freeVariables = f.getFreeVariables();
	for ( size_t i = 0; i < freeVariables->size(); i++)
	{
		EntityVariable * pev = freeVariables->at(i);
		CVariableItem * pvi = new CVariableItem(*pev);
		FreeVariables.Add(pvi);
	}
	vector <EntityVariable *> * linkedVariables = f.getLinkedVariables();
	for ( size_t i = 0; i < linkedVariables->size(); i++)
	{
		EntityVariable * pev = linkedVariables->at(i);
		CVariableItem * pvi = new CVariableItem(*pev);
		LinkedVariables.Add(pvi);
	}
	if(f.getType() == REPLACE_VARIABLE)
	{
//		ReplacedNumber
		CVariableItem * pvi = new CVariableItem(*f.getInitialVariable());
		ReplaceVariables.Add(pvi);
		pvi = new CVariableItem(*f.getNewVariable());
		ReplaceVariables.Add(pvi);
	}
	if(wasRedefined)
		f.setRedefined();
	Redefined = f.getRedefinedText()->data();
	Redefined_Flag = f.isRedefined();
}


////////////////////////////////////////////////////////////////////////////
// CSetItem

IMPLEMENT_XMLSERIAL(CSetItem, CObject)

//
// конструктор по умолчанию
//
CSetItem::CSetItem()
{
	EntityType = FORMULA_SET;
	FormulaNumber = -1;
	ReplacedNumber = -1;
	Number = -1;
	Redefined = "";
	Redefined_Flag = false;}


//
// деструктор
//
CSetItem::~CSetItem()
{
	for ( int i = 0; i < FreeVariables.GetSize(); i++)
	{
		delete FreeVariables[i];
	}
	FreeVariables.RemoveAll();
	for ( int i = 0; i < LinkedVariables.GetSize(); i++)
	{
		delete LinkedVariables[i];
	}
	LinkedVariables.RemoveAll();
	for ( int i = 0; i < BaseVariables.GetSize(); i++)
	{
		delete BaseVariables[i];
	}
	BaseVariables.RemoveAll();
	for ( int i = 0; i < ReplaceVariables.GetSize(); i++)
	{
		delete ReplaceVariables[i];
	}
	ReplaceVariables.RemoveAll();
}


//
// функция сериализации (записи в файл/загрузки из файла)
//
void CSetItem::Serialize(CArchive& ar)
{
	XMLCLASSNODE

	// инициализация аттрибутов значениями из объекта FormulaSet
	XMLINTDATA(Number);
	XMLINTDATA(FormulaNumber);
	if((version_of_file == _T("1.0.4")) || (version_of_file > _T("1.0.3")))
		XMLINTDATA(ReplacedNumber);
	XMLINTDATA(EntityType);
	XMLDATA(Description);
	XMLDATA(Label);
	XMLDATA(Addons);
	XMLDATA(Text);
	if(version_of_file != _T("1.0"))
		XMLDATA(Redefined);
	if((version_of_file != _T("1.0")) && (version_of_file != _T("1.0.1")))
		XMLDATA(Redefined_Flag);

	XMLDATA(FreeVariables);
	XMLDATA(BaseVariables);	
	if((version_of_file == _T("1.0.4")) || (version_of_file > _T("1.0.3")))
		XMLDATA(ReplaceVariables);	
	if((version_of_file == _T("1.0.6")) || (version_of_file > _T("1.0.5")))
		XMLDATA(LinkedVariables);
	if((version_of_file == _T("1.0.6")) || (version_of_file > _T("1.0.5")))
		XMLDATA(Naming);

	XMLENDNODE
}


//
//  конструктор, принимающий в качестве аргумента ссылку на объект FormulaSet
//
CSetItem::CSetItem(FormulaSet& f)
{
	// инициализация аттрибутов значениями из объекта FormulaSet
	bool wasRedefined = f.isRedefined();
	if(wasRedefined)
		f.setTemporarilyUnredefined();
	Description = f.getDescription()->data();
	Label = f.getLabel()->data();
	Addons = f.getAddOns()->data();
	EntityType = f.getType();
	ReplacedNumber = -1;
//	Text = f.getText().data();
	// указываю свободные переменные
	Text = f.getInitialText()->data();
	vector <EntityVariable *> * freeVariables = f.getFreeVariables();
	for ( size_t i = 0; i < freeVariables->size(); i++)
	{
		EntityVariable * pev = freeVariables->at(i);
		CVariableItem * pvi = new CVariableItem(*pev);
		FreeVariables.Add(pvi);
	}
	if(f.getType() == REPLACE_VARIABLE)
	{
//		ReplacedNumber
		CVariableItem * pvi = new CVariableItem(*f.getInitialVariable());
		ReplaceVariables.Add(pvi);
		pvi = new CVariableItem(*f.getNewVariable());
		ReplaceVariables.Add(pvi);
	}
//	else
	{
		// присваиваю базовые переменные
		vector <EntityVariable *> * baseVariables = f.getBaseVariables();
		for ( size_t i = 0; i < baseVariables->size(); i++)
		{
			EntityVariable * pev = baseVariables->at(i);
			CVariableItem * pvi = new CVariableItem(*pev);
			BaseVariables.Add(pvi);
		}
	}
	if(wasRedefined)
		f.setRedefined();
	Redefined = f.getRedefinedText()->data();
	Redefined_Flag = f.isRedefined();

//	pnaming = new EntityVariable(f.Naming);
	EntityVariable * pvi = f.getNaming();
	if(pvi != nullptr)
	{
//		Naming(*pvi);
		Naming.Variable = pvi->GetType();    // тип переменной
		Naming.Label = pvi->GetLabel().data();   // символ переменной
		Naming.Index = pvi->GetIndex().data();   // символ индекса
		Naming.Text = pvi->GetInitialText()->data();   // текст переменной, текст в формате с тэгами
		Naming.Level = pvi->GetLevel().data(); // уровень переменной
		Naming.Redefinition = pvi->GetRedefinition().data(); // переобозначение текста переменной
	}
}



#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
#else
//  если запись/загрузка схемы проводится стандартными средствами сериализации

//
// конструкторы объектов EntityVariable, Formula и FormulaSet из CVariableItem, CFormulaItem и CSetItem
// объявления приведены в файле Formula.h
//

//
//	конструктор для построения EntityVariable из соотвествущего классов CVariableItem
//
EntityVariable::EntityVariable(const CVariableItem& vi)
{
	type = vi.Variable;
	label = vi.Label;
	index = vi.Index;
	text = vi.Text;
	tstring level = vi.Level;
	SetLevel(level);
	tstring redefinition = vi.Redefinition;
	SetRedefinition(redefinition);
}


//
//	конструктор для построения Formula  из соотвествущего класса CFormulaItem  для сериализации
//
Formula::Formula(const CFormulaItem& fi)
{
	label = fi.Label;
	description = fi.Description;
	addons = fi.Addons;
	text = fi.Text;
	feature = fi.Feature;
	type = fi.EntityType;
	redefined_text = fi.Redefined;
	redefined = fi.Redefined_Flag;
	trimWhitespaces(&redefined_text);
	removeDoubledWhitespaces(&redefined_text);
	if(redefined_text.length() > 0)
		redefined = true;
	for ( int i = 0; i < fi.FreeVariables.GetSize(); i++)
	{
		EntityVariable * pv = new EntityVariable(*(fi.FreeVariables[i]));
		freeVariables.push_back(pv);
	}
	for ( int i = 0; i < fi.LinkedVariables.GetSize(); i++)
	{
		EntityVariable * pv = new EntityVariable(*(fi.LinkedVariables[i]));
		linkedVariables.push_back(pv);
	}
	if( fi.ReplaceVariables.GetSize() == 2)
	{
		initial_variable = new EntityVariable(*(fi.ReplaceVariables[0]));
		new_variable = new EntityVariable(*(fi.ReplaceVariables[1]));
	}
}


//
//	конструктор для построения Tuple  из соотвествущего класса CFormulaItem  для сериализации
//
Tuple::Tuple(const CFormulaItem& fi)
{
	label = fi.Label;
	description = fi.Description;
	addons = fi.Addons;
	text = fi.Text;
	feature = PERFORMED_FEATURE;
	type = TUPLE;
	redefined_text = fi.Redefined;
	redefined = fi.Redefined_Flag;
	trimWhitespaces(&redefined_text);
	removeDoubledWhitespaces(&redefined_text);
	if(redefined_text.length() > 0)
		redefined = true;
	for ( int i = 0; i < fi.FreeVariables.GetSize(); i++)
	{
		EntityVariable * pv = new EntityVariable(*(fi.FreeVariables[i]));
		freeVariables.push_back(pv);
	}
	for ( int i = 0; i < fi.LinkedVariables.GetSize(); i++)
	{
		EntityVariable * pv = new EntityVariable(*(fi.LinkedVariables[i]));
		linkedVariables.push_back(pv);
	}
	if( fi.ReplaceVariables.GetSize() == 2)
	{
		initial_variable = new EntityVariable(*(fi.ReplaceVariables[0]));
		new_variable = new EntityVariable(*(fi.ReplaceVariables[1]));
	}
}


//
//	конструктор для построения FormulaSet из соотвествущего класса  CSetItem для сериализации
//
FormulaSet::FormulaSet(const CSetItem& si)
{
	label = si.Label;
	description = si.Description;
	addons = si.Addons;
	text = si.Text;
	redefined_text = si.Redefined;
	trimWhitespaces(&redefined_text);
	removeDoubledWhitespaces(&redefined_text);
	redefined = si.Redefined_Flag;
	if(redefined_text.length() > 0)
		redefined = true;
	type = si.EntityType;
	for ( int i = 0; i < si.FreeVariables.GetSize(); i++)
	{
		EntityVariable * pv = new EntityVariable(*(si.FreeVariables[i]));
		freeVariables.push_back(pv);
	}
	for ( int i = 0; i < si.BaseVariables.GetSize(); i++)
	{
		EntityVariable * pv = new EntityVariable(*(si.BaseVariables[i]));
		baseVariables.push_back(pv);
	}
	if( si.ReplaceVariables.GetSize() == 2)
	{
		initial_variable = new EntityVariable(*(si.ReplaceVariables[0]));
		new_variable = new EntityVariable(*(si.ReplaceVariables[1]));
	}
	for ( int i = 0; i < si.LinkedVariables.GetSize(); i++)
	{
		EntityVariable * pv = new EntityVariable(*(si.LinkedVariables[i]));
		linkedVariables.push_back(pv);
	}
//	pnaming = new NamingVariable(si.Naming);
	pnaming = new EntityVariable(si.Naming);
}
#endif