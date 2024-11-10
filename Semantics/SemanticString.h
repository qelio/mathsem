//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once

#include "common_functions.h"
#include "Formula.h"

// ������������ ����� �������������� ��������
enum MathStyle { 
	NONE_MATHSTYLE,			// �� �������������� ������, �������
	LOW_MATHINDEX = 1,		// ������ ������
	HIGH_MATHINDEX = 2,		// ������� ������
	SYMBOL_TYPEFACE =3		// �������������� ������, ������� ������������ ������� Symbol
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ����� SemanticString ������������ ��� �������������� ����������� ���� ��������, ���� �� ������� Symbol ��� �������������� ��������
//
class SemanticString
{
public:
	// ����� �������� " � �����", ���������� �� ������� ���, ��� ��� �������� ����� ���� '0', �������� ��� ��� ������ ���������, ���� �������� 
	// � ��������������� �������� ������� symbolics. ����� � ��������������� �������� symbolics �����������, ������� ��� ������ ��� ��������������,
	// ������� ������ ������������ ������� Symbol
#ifdef _UNICODE
	WCHAR tchars[256];
#else
	unsigned char tchars[256];
#endif
	// ������ �������� MathStyle, ����������� ��������������� ������� ������� tchars (��� ��� �� �������)
	int symbolics[256];
	// ���������� �������� � tchars � symbolics
	int count;
	// ��������� �� ��������������� �������, ������� ��������� ������ ������ SemanticString
//	Formula * formula;
	EntityBase * formula;
	// ��������������� �����
	tstring * text;
	// �������������� ������� ������ ��� ��������� (���� ���� ����������� ������� �� ������������)
	CSize size;

public:
	// ����������� �� ���������
	SemanticString();
	// ����������
	~SemanticString();

	// ����� �������� ������ � ��������������� ������ � ��������� �� �� ����� ������� ������ SemanticString. �������������� � Word ��������� ���������� ��
	// �������������� ��� ��������� ������, ���������� � ������ forWordExport, ������������ � true
	bool PrepareSubItemData(tstring & tstr, bool forWordExport = false);
	// ����� ������������ ������ SemanticString, ������� �������������� ������� 'PrepareSubItemData' � �������������� rectSubItem ��� ��������� 
	// ���������� dc. ��� ��������� �������� ������������ ����� m_fIndexes, ��� ��������� �������������� �������� m_fSymbol (��� �������, ����� Symbol)
	void DrawItem(CDC &dc, CRect &rectSubItem, CFont * m_fSymbol, CFont * m_fIndexes);

	SemanticString operator=(SemanticString &str); // ����������
};
