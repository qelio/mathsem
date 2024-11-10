//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
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
//  класс связи между узлами в VUE-файле
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
	string strokeWidth;  // ширина линии
	string font;
	VUEPoint start;
	VUEPoint finish;
	VUENode * nodeStart;
	VUENode * nodeFinish;
	int numberInLayer;  // порядковый номер связи в слое
	int childID;
public:
	VUELink(void);
	~VUELink(void);
	VUELink(int childID_, int numberInLayer_);
	void print(ostream& os);  //  запись связи между двумя узлами в VUE-файл


	vector <VUEPoint *> ctrlPoints;
	void setLink(VUENode * node1, VUENode * node2);  // рассчитывает координаты линии, отражающей связь исходя из определяющих связь свойств
	void setLink(VUEFormula * node1, VUESet * node2);  // задаёт текущую связь для  формулы  node1 и множества node2
	void setLink(VUEFormula * node1, VUEFormula * node2); //  задаёт текущую связь для двух формул node1 и node2
	void setIDs(int childID_, int numberInLayer_) { childID = childID_; numberInLayer = numberInLayer_; };
	void setLinkType(EntityBaseType ft);  //  присваивает тип связи
};

