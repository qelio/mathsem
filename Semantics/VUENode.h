//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
//
//  заголовочный файл объявления классов VUENode, VUEFormula и VUESet, а также ряда вспомогательных функций для создания VUE-файлов
//

#pragma once

#include "common_functions.h"
#include "Formula.h"

//
//  перечисление видов узлов
//
enum VUENodeType
{
	VUENODE = 0,
	VUEFORMULA = 1,    // узел для формул
	VUESET = 2,    // узел для множеств истинности
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  класс VUENode, базовый для классов VUEFormula и VUESet, содержит общие определения, необходимые в дальнейшем для 
//  построения узлов в VUE-схеме
class VUENode
{
protected:
	string fillColor;    // цвет заливки узла
	string textColor;    // цвет текста надписи
	string strokeColor;  // цвет границы
	string font;         // название шрифта
	string xsi;          // вид фигуры (прямоугольник, прямоугольник с закругленными краями
	string strokeStyle;  // вид линии границы, от 1 до 5 (сплошная, прерывистая и так далее)
	VUENodeType type;    // формула или множество


public:
	double x;            // x-координата верхнего левого угла
	double y;            // y-координата верхнего левого угла
	double width;        // ширина узла
	double height;       // высота узла

	int numberInGroup;   // порядковый номер в атомарной группе
	int groupAtom;       // номер атомарной группы
	int numberInLayer;   // номер в VUE-cлое
	int childID;         // порядковый номер узла в VUE-схеме


	// конструктор по умолчанию
	VUENode();
	// деструктор
	~VUENode();
	// конструктор с двумя параметрами: порядковым номером узла в VUE-схеме и порядоковый номером в слое
	VUENode(int childID_, int numberInLayer_);
	// метод назначает координаты и размеры узла
	void SetPosition(double x_, double y_, double width_, double height_) {x = x_; y = y_; width = width_; height = height_;};
	// запись узла в VUE-файл на основе его свойств
	void print(ostream& os, string & str);  
	//  устанавливает параметры для любого узла-потомка (всех множеств и формул за исключением атомарных формул)
	void childProperties();  
	// возвращает тип узла
	VUENodeType GetType() { return type; };

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  класс узлов, представляющих формулы
//
class VUEFormula : public VUENode
{
public:
	Formula* formula;    // представляемая формула

	// конструктор с двумя параметрами, порядковыми номерами узла в VUE-схеме и слое
	VUEFormula(int childID_, int numberInLayer_) : VUENode(childID_, numberInLayer_) { type = VUEFORMULA; };
	// деструктор
	~VUEFormula();
	
	// запись узла-формулы в VUE-файл в файловый поток ввода
	void print(ostream& os);  
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  класс узлов, представляющих множества истинности
//
class VUESet : public VUENode
{
public:
	FormulaSet * parentSet;    // указатель на представляемое множество истинности

	// конструктор с двумя параметрами, порядковыми номерами узла в VUE-схеме и слое
	VUESet(int childID_, int numberInLayer_) : VUENode(childID_, numberInLayer_) { type = VUESET; };
	// деструктор
	~VUESet();
	
	
	// запись узла-формулы в VUE-файл в файловый поток ввода
	void print(ostream& os);  
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
// вспомогательные для создания VUE-файла функции
//

//  функция проводит подготовку строк c математическими тэгами к виду, пригодному для отображение в VUE-схемах
bool UnPrepareMathSymbols(tstring & tstr, double width);
//  функция конвертации всех русских символов в строке к виду, пригодному для VUE-схем
void convertVUERussianSymbols(tstring & tstr);
// запись в файл начала хидера VUE-файла
void printFirstPartVUEHeader(ostream& tof, string & filename, string & currentDir); 
// запись в файл части с легендой, графическим рисунком-пояснением и одновременно завершением хидера
void printVUELegend(ostream& tof, string & legend);  
//  запись заключительной части VUE-файла
void printVUEFooter(ostream& tof, string & filename, string & currentDir);  
//  запись уровня, пока что пишут только 1 уровень
void printVUELayer(ostream& tof);  