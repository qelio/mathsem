//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once

#include "common_functions.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ����� CScientificButton, ������ �� ����� ���������� ���� ��� ����������� �������������� ��������.
//  ������ � ��� ��� �� ��������� � ����� ���� (deprecated)
//  ������������� ��� ��������� �� ������� ��������� � ��������


// ������������ ���� ���������
enum ScientificCharacterAction
{
	NONE = 0,            // ������� ������
	FirstQuantor = 1,    // ������ ������� (��������������)
	SecondQuantor = 2,   // ������ ������� (�����������)
	LowerIndex = 3,      // ������ ������
	UpperIndex = 4       // ������� ������ (�� �����������, �� �� �������� � ������ �������� ����� ������� ������)
} ;



// CScientificButton

class CScientificButton : public CMFCButton
{
	DECLARE_DYNAMIC(CScientificButton)

	typedef map<int, ScientificCharacterAction, less<int>> SciCharMap;     // ����� ������������� ��������� �������������� �������� �� ����������� 
	// ������� ��������� (������ ������� � ������), ������ �������� - ��������� ��� ��������� �������, ������ �������� - ������� ����������

	typedef SciCharMap::iterator SciCharMapIterator;
	SciCharMap m_SciChars;

	// �����,������������ ��� ��������� �������������� �������� (����� ������ Symbol)
	CFont m_fSymbol;
public:
	// �����������
	CScientificButton();
	// ����������
	virtual ~CScientificButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	// ����� ���������, ��� ����� ��� ����������� �������������� ��������� (�� ����� ������� �� �������)
	void addSciCharAction(int pos, ScientificCharacterAction scichar) { m_SciChars[pos] = scichar; };
	// ����� ������������� ����� ��� �������������� ��������
	void setSciFont(LOGFONT * lf) { m_fSymbol.CreateFontIndirectW(lf); };
	// ������� ��������� ������ �� ������
	virtual void OnDrawText(CDC* pDC, const CRect& rect, const CString& strText, UINT uiDTFlags, UINT uiState);
};


