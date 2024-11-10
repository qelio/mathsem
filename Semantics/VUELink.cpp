//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014

#include "StdAfx.h"
#include "VUELink.h"

//
//  конструктор с параметрами по умолчанию
//
VUELink::VUELink(void)
{
	strokeStyle = "strokeStyle=\"1\" ";
//	strokeColor = "#83CEFF";
	strokeColor = "#000000";
	textColor = "#404040";
	font = "Arial-plain-11";
	strokeWidth = "1.0";
}

//
// деструктор
//
VUELink::~VUELink(void)
{
	for(size_t i = 0; ctrlPoints.size(); i++)
		delete ctrlPoints.at(i);
}

//
// конструктор VUE-связи, два параметра: порядковый номер VUE-"единицы" и порядковый номер в группе, привязанной к атомарной формуле
//
VUELink::VUELink(int childID_, int numberInLayer_) 
{ 
	childID = childID_; 
	numberInLayer = numberInLayer_; 
	strokeStyle = "strokeStyle=\"1\" ";
//	strokeColor = "#83CEFF";
	strokeColor = "#000000";
	textColor = "#404040";
	font = "Arial-plain-11";
	strokeWidth = "1.0";
}

//
// задаёт текущую связь для  формулы  node1 и множества node2
//
void VUELink::setLink(VUEFormula * node1, VUESet * node2)
{
	setLinkType(FORMULA_SET);
	setLink( (VUENode *) node1, (VUENode *) node2);
}

//
//  задаёт текущую связь для двух формул node1 и node2
//
void VUELink::setLink(VUEFormula * node1, VUEFormula * node2)
{
	setLinkType(node2->formula->getType());
	setLink( (VUENode *) node1, (VUENode *) node2);
}

//
// рассчитывает координаты линии, отражающей связь исходя из определяющих связь свойств
//
void VUELink::setLink(VUENode * node1, VUENode * node2)
{
	nodeStart = node1;    // устанавливаем родительский узел для связи
	nodeFinish = node2;    // устанавливаем дочерний узел для связи
/*
предыдущий вариант отображения связей
	if((node1->x + node1->width) <= node2->x)    // если правая x-координата родительского узла левее левой x-координаты дочернего узла
	{
		start.x = node1->x + node1->width - 1.0;
		finish.x = node2->x + 1.0;
	}
	else if(node1->x >= ( node2->x - node2->width ))    // если правая x-координата родительского узла правее левой x-координаты дочернего узла, но левее правой
	{
		finish.x = node2->x + node2->width - 1.0;
		start.x = node2->x + 1.0;
	}
	else    // если левая x-координата родительского узла правее правой x-координаты дочернего узла
	{
		finish.x = node2->x + (node2->width/2);
		start.x = node1->x + (node1->width/2);
	}
	if((node1->y + node1->height) <= node2->y)    // если нижняя y-координата родительского узла выше верхней y-координаты дочернего узла
	{
		start.y = node1->y + node1->height - 1.0;
		finish.y = node2->y + 1.0;
	}
	else if(node1->y >= ( node2->y - node2->height ))    // если верхняя y-координата родительского узла выше нижней y-координаты дочернего узла,
	// но ниже верхней
	{
		finish.y = node2->y + node2->height - 1.0;
		start.y = node2->y + 1.0;
	}
	else    // если верхняя y-координата родительского узла ниже нижней y-координаты дочернего узла
	{
		finish.y = node2->y + (node2->height/2);
		start.y = node1->y + (node1->height/2);
	}	
	x = start.x;
	y = finish.y;
	if ( finish.x > (start.x + node1->width) )
		width = finish.x - (start.x + node1->width);
	else
		width = start.x - finish.x;
	if ( finish.y > start.y)
		height = finish.y - start.y;
	else
		height = start.y - finish.y;
*/
	x = node1->x + (node1->width/2);
	width =  node2->x - node1->x;
	y = node1->y;
	height = node2->y + node2->height - node1->y;
}


//
//  запись связи между двумя узлами в VUE-файл
//
void VUELink::print(ostream& os)
{
	os << "    <child ID=\"";
	os << to_string((long long)childID) <<"\" layerID=\"1\" created=\"1378800168781\" x=\"";
	os << to_string((long double)x) << "\"" << endl;
	os << "		y=\"";
	os << to_string((long double)y) << "\" width=\"";
	os << to_string((long double)width) << "\" height=\"";
	os << to_string((long double)height) << "\" strokeWidth=\""<< strokeWidth <<"\"" <<endl;
	os << "        " << strokeStyle << " autoSized=\"false\" controlCount=\"0\"" << endl;
	os << "        arrowState=\"2\" xsi:type=\"link\">" << endl;
	os << "        <strokeColor>" << strokeColor;
	os << "</strokeColor>" << endl;
	os << "        <textColor>" << textColor;
	os << "</textColor>" << endl;
	os << "        <font>" << font;
	os << "</font>" << endl;
	os << "        <URIString>http://vue.tufts.edu/rdf/resource/06e8c0f6c0a8000b00f95b1e49d4efa6</URIString>" << endl;
	os << "        <point1 x=\"" << start.x;
	os << "\" y=\"" << start.y;
	os << "\"/>" << endl;
	os << "        <point2 x=\"" << finish.x;
	os << "\" y=\"" << finish.y;
	os << "\"/>" << endl;
	os << "        <ID1 xsi:type=\"node\">" << to_string((long long)nodeStart->childID);
	os << "</ID1>" << endl;
	os << "        <ID2 xsi:type=\"node\">" << to_string((long long)nodeFinish->childID);
	os << "</ID2>";
	for(size_t i = 0; ctrlPoints.size(); i++)
	{
		VUEPoint * p = ctrlPoints.at(i);
		os << "        <ctrlPoint" << to_string((long long)i);
		os << " x=\"" << to_string((long double)p->x);
		os << "\" y=\"" << to_string((long double)p->y);
		os << "\" xsi:type=\"point\"/>" << endl;
	}
	os << "    </child>" << endl;

}

//
//  присваивает тип связи
//
void VUELink::setLinkType(EntityBaseType ft)
{
	switch(ft)
	{
	case NEGATIVE_OPERATION:
		strokeStyle = "strokeStyle=\"4\" ";
		strokeColor = "#8C8F72";
		break;
	case QUANTIFIER1_OPERATION:
	case QUANTIFIER2_OPERATION:
		strokeStyle = "strokeStyle=\"1\" ";
		break;
	case AND_OPERATION:
	case OR_OPERATION:
		strokeStyle = "strokeStyle=\"0\" ";
		break;
	case FORMULA_SET:  // связывает множество и формулу
		strokeStyle = "strokeStyle=\"0\" ";
		strokeWidth = "2.0";
		strokeColor = "#DD7B11";
		break;
	case ATOMIC_FORMULA:
	default:
		strokeStyle = "strokeStyle=\"3\" ";
		break;
	}
}
