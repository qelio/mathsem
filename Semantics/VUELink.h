//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once

#include "common_functions.h"
#include "VUENode.h"


struct VUEPoint
{
	double x;
	double y;
};

//
//  ����� ����� ����� ������ � VUE-�����
//
class VUELink
{
	double x;
	double y;
	double width;
	double height;
	string strokeStyle;
	string strokeColor;
	string textColor;
	string strokeWidth;  // ������ �����
	string font;
	VUEPoint start;
	VUEPoint finish;
	VUENode * nodeStart;
	VUENode * nodeFinish;
	int numberInLayer;  // ���������� ����� ����� � ����
	int childID;
public:
	VUELink(void);
	~VUELink(void);
	VUELink(int childID_, int numberInLayer_);
	void print(ostream& os);  //  ������ ����� ����� ����� ������ � VUE-����


	vector <VUEPoint *> ctrlPoints;
	void setLink(VUENode * node1, VUENode * node2);  // ������������ ���������� �����, ���������� ����� ������ �� ������������ ����� �������
	void setLink(VUEFormula * node1, VUESet * node2);  // ����� ������� ����� ���  �������  node1 � ��������� node2
	void setLink(VUEFormula * node1, VUEFormula * node2); //  ����� ������� ����� ��� ���� ������ node1 � node2
	void setIDs(int childID_, int numberInLayer_) { childID = childID_; numberInLayer = numberInLayer_; };
	void setLinkType(EntityBaseType ft);  //  ����������� ��� �����
};

