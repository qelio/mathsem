//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once

#include "SemanticString.h"

// CScientificStatic

class CScientificStatic : public CStatic
{
	DECLARE_DYNAMIC(CScientificStatic)

public:
	CScientificStatic();
	virtual ~CScientificStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	SemanticString * dsi;
	CFont * m_fSymbol;
	CFont * m_fIndexes;
};


