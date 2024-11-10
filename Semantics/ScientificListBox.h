//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once
#include "MathListCtrlEx.h"
#include "common_functions.h"

// ScientificListBox

class ScientificListBox : public CListBox
{
	DECLARE_DYNAMIC(ScientificListBox)

	bool isSorted;
public:
	ScientificListBox();
	virtual ~ScientificListBox();

protected:
	DECLARE_MESSAGE_MAP()

	CFont * m_fSymbol;
	CFont * m_fIndexes;

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
//	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	vector <SemanticString *> DCU;
	void SetIndexesFont(CFont * m_fIndexes_)  { m_fIndexes = m_fIndexes_; };
	virtual int CompareItem(LPCOMPAREITEMSTRUCT /*lpCompareItemStruct*/);
	void SetSorting(bool toSort = false) { isSorted = toSort; };
};


