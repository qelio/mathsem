//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
//
//  ������������ ���� ���������� ������� VUENode, VUEFormula � VUESet, � ����� ���� ��������������� ������� ��� �������� VUE-������
//

#pragma once

#include "common_functions.h"
#include "Formula.h"

//
//  ������������ ����� �����
//
enum VUENodeType
{
	VUENODE = 0,
	VUEFORMULA = 1,    // ���� ��� ������
	VUESET = 2,    // ���� ��� �������� ����������
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ����� VUENode, ������� ��� ������� VUEFormula � VUESet, �������� ����� �����������, ����������� � ���������� ��� 
//  ���������� ����� � VUE-�����
class VUENode
{
protected:
	string fillColor;    // ���� ������� ����
	string textColor;    // ���� ������ �������
	string strokeColor;  // ���� �������
	string font;         // �������� ������
	string xsi;          // ��� ������ (�������������, ������������� � ������������� ������
	string strokeStyle;  // ��� ����� �������, �� 1 �� 5 (��������, ����������� � ��� �����)
	VUENodeType type;    // ������� ��� ���������


public:
	double x;            // x-���������� �������� ������ ����
	double y;            // y-���������� �������� ������ ����
	double width;        // ������ ����
	double height;       // ������ ����

	int numberInGroup;   // ���������� ����� � ��������� ������
	int groupAtom;       // ����� ��������� ������
	int numberInLayer;   // ����� � VUE-c���
	int childID;         // ���������� ����� ���� � VUE-�����


	// ����������� �� ���������
	VUENode();
	// ����������
	~VUENode();
	// ����������� � ����� �����������: ���������� ������� ���� � VUE-����� � ����������� ������� � ����
	VUENode(int childID_, int numberInLayer_);
	// ����� ��������� ���������� � ������� ����
	void SetPosition(double x_, double y_, double width_, double height_) {x = x_; y = y_; width = width_; height = height_;};
	// ������ ���� � VUE-���� �� ������ ��� �������
	void print(ostream& os, string & str);  
	//  ������������� ��������� ��� ������ ����-������� (���� �������� � ������ �� ����������� ��������� ������)
	void childProperties();  
	// ���������� ��� ����
	VUENodeType GetType() { return type; };

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ����� �����, �������������� �������
//
class VUEFormula : public VUENode
{
public:
	Formula* formula;    // �������������� �������

	// ����������� � ����� �����������, ����������� �������� ���� � VUE-����� � ����
	VUEFormula(int childID_, int numberInLayer_) : VUENode(childID_, numberInLayer_) { type = VUEFORMULA; };
	// ����������
	~VUEFormula();
	
	// ������ ����-������� � VUE-���� � �������� ����� �����
	void print(ostream& os);  
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ����� �����, �������������� ��������� ����������
//
class VUESet : public VUENode
{
public:
	FormulaSet * parentSet;    // ��������� �� �������������� ��������� ����������

	// ����������� � ����� �����������, ����������� �������� ���� � VUE-����� � ����
	VUESet(int childID_, int numberInLayer_) : VUENode(childID_, numberInLayer_) { type = VUESET; };
	// ����������
	~VUESet();
	
	
	// ������ ����-������� � VUE-���� � �������� ����� �����
	void print(ostream& os);  
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������������� ��� �������� VUE-����� �������
//

//  ������� �������� ���������� ����� c ��������������� ������ � ����, ���������� ��� ����������� � VUE-������
bool UnPrepareMathSymbols(tstring & tstr, double width);
//  ������� ����������� ���� ������� �������� � ������ � ����, ���������� ��� VUE-����
void convertVUERussianSymbols(tstring & tstr);
// ������ � ���� ������ ������ VUE-�����
void printFirstPartVUEHeader(ostream& tof, string & filename, string & currentDir); 
// ������ � ���� ����� � ��������, ����������� ��������-���������� � ������������ ����������� ������
void printVUELegend(ostream& tof, string & legend);  
//  ������ �������������� ����� VUE-�����
void printVUEFooter(ostream& tof, string & filename, string & currentDir);  
//  ������ ������, ���� ��� ����� ������ 1 �������
void printVUELayer(ostream& tof);  