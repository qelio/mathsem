//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
// Node.cpp: файл реализации
//

#include "stdafx.h"
//#include "Semantics.h"
#include "VUENode.h"

/////////////////////////////////////////////////////////////////////
// Node

//
// конструктор по умолчанию
// 
VUENode::VUENode()
{
	// устанавливаем значения по умолчанию
	fillColor = "#F1A83E";  
	textColor = "#000000";
	strokeColor = "#000000";
	font = "Arial-bold-12";
	width = 133.0;
	height = 167.0;
	strokeStyle = "";
	xsi = "roundRect";
	numberInGroup = 0;
	groupAtom = 0;
}

//
// деструктор
//
VUENode::~VUENode()
{

}

//
// конструктор с двумя параметрами, порядковыми номерами узла в VUE-схеме и слое
//
VUENode::VUENode(int childID_, int numberInLayer_) 
{ 
	childID = childID_;    // порядковый номер узла в VUE-схеме
	numberInLayer = numberInLayer_;    // порядковый номер узла в слое
	// устанавливаем значения по умолчанию
	fillColor = "#F1A83E";
	textColor = "#000000";
	strokeColor = "#000000";
	font = "Arial-bold-12";
	width = 133.0;
	height = 167.0;
	strokeStyle = "";
	xsi = "roundRect";
	numberInGroup = 0;
	groupAtom = 0;
};


//
//  вывод информации об узла в виде, пригодном для VUE-схемы, строка label содержит текст выводимой надписи на узле
//
void VUENode::print(ostream& os, string & label)
{
	os << "    <child ID=\"";
	os << to_string((long long)childID) << "\"" << endl;
	os << "        label=\"";
	os << label;
	os << "\"" << endl;
	os << "        layerID=\"1\" created=\"1378800156937\" x=\"";
	os << to_string((long double)x) << "\" y=\"";
	os << to_string((long double)y) << "\"" << endl;
	os << "        width=\"" << to_string((long double)width);
	os << "\" height=\"" << to_string((long double)height);
	os << "\" strokeWidth=\"2.0\""<< strokeStyle << endl;
	os << "        autoSized=\"false\" xsi:type=\"node\">" << endl;
	os << "        <fillColor>" << fillColor;
	os << "</fillColor>" << endl;
	os << "        <strokeColor>" << strokeColor;
	os << "</strokeColor>" << endl;
	os << "        <textColor>" <<  textColor;
	os << "</textColor>" << endl;
	os << "        <font>" << font;
	os << "</font>" << endl;
	os << "        <URIString>http://vue.tufts.edu/rdf/resource/06e8c0d7c0a8000b00f95b1eac61c244</URIString>" << endl;
	os << "        <shape xsi:type=\"" << xsi;
	os << "\"/>" << endl;
	os << "    </child>" << endl;
}


//
//  устанавливает параметры для любого узла-потомка (всех множеств и формул за исключением атомарных формул)
//
void VUENode::childProperties()
{
	if(type == VUESET)  // если множество
	{
		fillColor = "#EEEEEE";
		strokeColor = "#000000";
		strokeStyle = " strokeStyle=\"4\"";
	}
	else  // в случае формулы
	{
		fillColor = "#0AAD1D";
		strokeColor = "#000000";
		strokeStyle = " strokeStyle=\"2\"";
	}
	textColor = "#000000";
	font = "Arial-bold-12";
	width = 133.0;
	height = 167.0;
	xsi = "rectangle";
}


////////////////////////////////////////////////////////////
///  VUEFormula

//
//  деструктор
//
VUEFormula::~VUEFormula()
{
}

//
//  подготовка к выводу и вывод информации об узла в VUE-виде
//
void VUEFormula::print(ostream& os)
{
	char buf[2048];
	tstring tstr(formula->getText());    // текст формулы
	UnPrepareMathSymbols(tstr, width);    // переводим математические тэги к VUE-виду строк
	wcstombs(buf, tstr.data(), 2048);    // конвертация строки из UNICODE в multibyte
	string label = buf;	   // строка надписи на узле 
	label += "&#xa;&#x41e;&#x431;&#x43e;&#x437;&#x43d;&#x430;&#x447;&#x435;&#x43d;&#x438;&#x435;&#xa;";    // добавляю слово "Обозначение"
	// подготавливаю и вывожу обозначение формулы
	tstr = *formula->getLabel();    // обозначение формулы
	UnPrepareMathSymbols(tstr, width);    // переводим математические тэги и русские символы к VUE-виду строк
	wcstombs(buf, tstr.data(), 2048);    // конвертация строки из UNICODE в multibyte
	label += buf;    // добавляю подготовленную строку ообозначения к строке надписи
	// если задано описание, подготавливаю и добавляю в строку надписи на узле
	tstr = *formula->getDescription();    // описание формулы
	if(tstr.length() > 0)    // если описание было введено
	{
		label += "&#xa;&#x41e;&#x43f;&#x438;&#x441;&#x430;&#x43d;&#x438;&#x435;&#xa;";    // добавляю слово "Описание"
		UnPrepareMathSymbols(tstr, width);    // переводим математические тэги и русские символы к VUE-виду строк
		convertVUERussianSymbols(tstr);    // конвертирую русские символы к VUE-виду
		wcstombs(buf, tstr.data(), 2048);    // конвертация строки из UNICODE в multibyte
		label += buf;    // добавляю подготовленную строку описания к строке надписи
	}
	VUENode::print(os, label);    // вызываю функции записи в VUE-файл информации об узле
}


////////////////////////////////////////////////////////////
///  VUESet

//
//  деструктор
//
VUESet::~VUESet()
{
}

//
//  подготовка к выводу и вывод информации об узла в VUE-виде
//
void VUESet::print(ostream& os)
{
	char buf[2048];
	tstring tstr(parentSet->getText());    // текст множества истинности
	UnPrepareMathSymbols(tstr, width);    // переводим математические тэги к VUE-виду строк
	wcstombs(buf, tstr.data(), 2048);    // конвертация строки из UNICODE в multibyte
	string label = buf;// строка надписи на узле 
	label += "&#xa;&#x41e;&#x431;&#x43e;&#x437;&#x43d;&#x430;&#x447;&#x435;&#x43d;&#x438;&#x435;&#xa;";    // вывожу слово "Обозначение"
	// подготавливаю и вывожу обозначение множества истинности
	tstr = *parentSet->getLabel();    // обозначение формулы
	UnPrepareMathSymbols(tstr, width);    // переводим математические тэги к VUE-виду строк
	wcstombs(buf, tstr.data(), 2048);    // конвертация строки из UNICODE в multibyte
	label += buf;    // добавляю подготовленную строку ообозначения к строке надписи
	// если задано описание, подготавливаю и добавляю встроку надписи на узле
	tstr = *parentSet->getDescription();    // описание формулы
	if(tstr.length() > 0)    // если описание было введено
	{
		label += "&#xa;&#x41e;&#x43f;&#x438;&#x441;&#x430;&#x43d;&#x438;&#x435;&#xa;";    // вывожу слово "Описание"
		UnPrepareMathSymbols(tstr, width);    // переводим математические тэги к VUE-виду строк
		convertVUERussianSymbols(tstr);    // конвертирую русские символы к VUE-виду
		wcstombs(buf, tstr.data(), 2048);    // конвертация строки из UNICODE в multibyte
		label += buf;
	}
	VUENode::print(os, label);    // вызываю функции записи в VUE-файл информации об узле
}


/////////////////////////////////////////////////////////
// вспомогательные функции
//


//
//  функция проводит подготовку строк c математическими тэгами к виду, пригодному для отображение в VUE-схемах
//
bool UnPrepareMathSymbols(tstring & tstr, double width)
{
	bool result = true;
//	count = 0;
	// начали разбор на математические симовлы в виде <symbol=..>
	bool isFound = false;
	int pos = 0;
	// находим все вхождения левого тега в строке
	while ( (pos = tstr.find(_T("<"), pos)) != -1)   // пока положение левого тега не равно -1
	{
		isFound = false;
		int pos1 = tstr.find(_T(">"), pos + 1);    // находим позицию первого от текущего левого правого тэга
		if ( pos1 > 0 )    // если правый тэг существует
		{
			tstring part_tstr = tstr.substr(pos + 1, pos1 - pos - 1);    // подстрока, заключенная между левым и правым тэгами
			trimWhitespaces(&part_tstr);    // вырезает левые и правые пробельные символы
			int pos_of_equal = part_tstr.find(_T("="));    // находим положение символа "="
			if ( (pos_of_equal > 0) && (pos_of_equal < ((int)part_tstr.size() - 1)) )    // если он находится внутри подстроки ( не на крайних позициях)
			{
				tstring beforeDelim = part_tstr.substr(0, pos_of_equal);    // подстрока до "="
				tstring afterDelim = part_tstr.substr(pos_of_equal + 1, part_tstr.size() - pos_of_equal);   // подстрока после "="
				// вырезаемкрайные левые и крайние правые пробельные символы из обеих подстрок
				trimWhitespaces(&beforeDelim);    
				trimWhitespaces(&afterDelim);
				transform(beforeDelim.begin(), beforeDelim.end(), beforeDelim.begin(), ::tolower); // переводим подстроку до "=" в lower case
				if (!beforeDelim.compare(_T("s")) || !beforeDelim.compare(_T("symbol")) )    // если она имеет вид "s" или "symbol", то это вся строка корректна
				{
					// сравниваем правую подстроку совсеми разрешёнными вариантами значений, найденные заменяются на вид, пригодный для VUE-cхемы
					if(!afterDelim.compare(_T("/low")) )  //low index
					{
						tstr.replace(pos, pos1 + 1 - pos, _T(""));
						isFound = true;
					}
					else if(!afterDelim.compare(_T("/high")) ) //high index
					{
						tstr.replace(pos, pos1 + 1 - pos, _T(""));
						isFound = true;
					}
					else if(!afterDelim.compare(_T("/34")) )  // first quantor
					{
						tstr.replace(pos, pos1 + 1 - pos, _T("K1"));
						isFound = true;
					}
					else if(!afterDelim.compare(_T("/36")) )  //second quantor
					{
						tstr.replace(pos, pos1 + 1 - pos, _T("K2"));
						isFound = true;
					}
					else if ( (!afterDelim.compare(_T("/38")) )  || (!afterDelim.compare(_T("/and")) ) )//and
					{
						tstr.replace(pos, pos1 + 1 - pos, _T("AND"));
						isFound = true;
					}
					else if(!afterDelim.compare(_T("/123")) )  //левая фигурная скобка
					{
						tstr.replace(pos, pos1 + 1 - pos, _T("{"));
						isFound = true;
					}
					else if(!afterDelim.compare(_T("/125")) )  //правая фигурная скобка
					{
						tstr.replace(pos, pos1 + 1 - pos, _T("}"));
						isFound = true;
					}
					else if ( (!afterDelim.compare(_T("/216")) )  || (!afterDelim.compare(_T("/not")) ) ) //not
					{
						tstr.replace(pos, pos1 + 1 - pos, _T("NOT"));
						isFound = true;
					}
					else if ( (!afterDelim.compare(_T("/218")) ) || (!afterDelim.compare(_T("/or")) ) )//или
					{
						tstr.replace(pos, pos1 + 1 - pos, _T("OR"));
						isFound = true;
					}
					else if ( (!afterDelim.compare(_T("/0xCE")) ) || (!afterDelim.compare(_T("/206")) ) || (!afterDelim.compare(_T("/in")) ) )//принадлежноть
					{
						tstr.replace(pos, pos1 + 1 - pos, _T("(-"));
						isFound = true;
					}
				}
				if ( !isFound )  // если строка имеет некорректный вид, то вырезаем её вместе с левым и правым тэгами
				{
					tstr.replace(pos, pos1 + 1 - pos, _T(""));
				}
			}
			pos++; // выставляем pos для новой итерации поиска
		}
		else
			break;
		if( pos >= ((int)tstr.size() - 2) )
			break;
	}
	// расставляю символы переноса строки в зависимости от ширины узла, сравниваю с базовой шириной (120.00), которой соотвествуют 18 символов
	double otn = width/120.;    // вычисляю отношение установленной ширины width к "эталонной"
	int symbolsInRow = (int)(otn * 20.0);    // максимальное число символов для строки в надписи на узле шириной width
	if(symbolsInRow < 1)    
		symbolsInRow = 1;    // максимальное число символов не может быть меньше 1
	int ik = 1;    // номер текущей строки
	while((ik * symbolsInRow) < (int)tstr.length())    // пока число рассмотренных символов меньше длины строки
	{
		tstr.insert(symbolsInRow*ik, _T("&#xa;"));    // ставлю символ перевода на новую строку
		ik++;    // следующая строка
	}
	return result;
}

//
// запись в файл начала хидера VUE-файла
//
void printFirstPartVUEHeader(ostream& tof, string & filename, string & currentDir)
{
	tof << "<!-- Tufts VUE 3.2.2 concept-map (";
	tof << filename;
	tof << ") 2013-09-10 -->" << endl;
	tof << "<!-- Tufts VUE: http://vue.tufts.edu/ -->" << endl;
	tof << "<!-- Do Not Remove: VUE mapping @version(1.1) jar:file:/D:/VUE/VUE.jar!/tufts/vue/resources/lw_mapping_1_1.xml -->" << endl;
	tof << "<!-- Do Not Remove: Saved date Tue Sep 10 14:15:28 YEKT 2013 by user on platform Windows XP 5.1 in JVM 1.7.0_21-b11 -->" << endl;
	tof << "<!-- Do Not Remove: Saving version @(#)VUE: built May 23 2013 at 2146 by tomadm on Linux 2.6.18-348.2.1.el5 i386 JVM 1.7.0_21-b11(bits=32) -->" << endl;
	tof << "<?xml version=\"1.0\" encoding=\"US-ASCII\"?>" << endl;
	tof << "<LW-MAP xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << endl;
	tof << "    xsi:noNamespaceSchemaLocation=\"none\" ID=\"0\"" << endl;
	tof << "    label=\"";
	tof << filename;
	tof << "\"" << endl;
	tof << "    created=\"1378800153093\" x=\"0.0\" y=\"0.0\" width=\"1.4E-45\"" << endl;
	tof << "    height=\"1.4E-45\" strokeWidth=\"0.0\" autoSized=\"false\">" << endl;
	tof << "    <resource referenceCreated=\"1378800928968\"" << endl;
	tof << "        spec=\"";

	tof << currentDir;
	tof << filename;
	tof << "\"" << endl;
	tof << "        type=\"1\" xsi:type=\"URLResource\">" << endl;
	tof << "        <title>";
	tof << filename;
	tof << "</title>" << endl;
	tof << "        <property key=\"File\" value=\"";
	tof << currentDir;
	tof << filename;
	tof << "\"/>" << endl;
	tof << "    </resource>" << endl;
	tof << "    <fillColor>#FFFFFF</fillColor>" << endl;
	tof << "    <strokeColor>#404040</strokeColor>" << endl;
	tof << "    <textColor>#000000</textColor>" << endl;
	tof << "    <font>SansSerif-plain-14</font>" << endl;
	tof << "    <URIString>http://vue.tufts.edu/rdf/resource/06e8c0d7c0a8000b00f95b1e7c5003d1</URIString>" << endl;
}

//
// запись в файл части с легендой, графическим рисунком-пояснением и одновременно завершением хидера
//
void printVUELegend(ostream& tof, string & legend)
{
/*
	старый вариант, с картинкой легенды
	tof << "    <child ID=\"6\" layerID=\"1\" created=\"1373631072250\" x=\"-695.0\"" << endl;
	tof << "        y=\"-300.0\" width=\"295.0\" height=\"270.05835\" strokeWidth=\"2.0\"" << endl;
	tof << "        strokeStyle=\"2\" autoSized=\"true\" xsi:type=\"node\">" << endl;
	tof << "        <resource referenceCreated=\"0\" accessAttempted=\"1373631233515\"" << endl;
	tof << "            accessSuccessful=\"1373631233609\" size=\"9688\"" << endl;
	tof << "            spec=\"" << legend;
	tof << "legend.JPG\" type=\"1\" xsi:type=\"URLResource\">" << endl;
	tof << "            <title>legend.JPG</title>" << endl;
	tof << "            <property key=\"Content.size\" value=\"9688\"/>" << endl;
	tof << "            <property key=\"Content.modified\" value=\"Fri Jul 12 18:10:16 YEKT 2013\"/>" << endl;
	tof << "            <property key=\"image.width\" value=\"257\"/>" << endl;
	tof << "            <property key=\"image.height\" value=\"242\"/>" << endl;
	tof << "            <property key=\"image.format\" value=\"JPEG\"/>" << endl;
	tof << "            <property key=\"@file.relative\" value=\"legend.JPG\"/>" << endl;
	tof << "            <property key=\"File\" value=\"legend.JPG\"/>" << endl;
	tof << "        </resource>" << endl;
	tof << "        <fillColor>#0AAD1D</fillColor>" << endl;
	tof << "        <strokeColor>#000000</strokeColor>" << endl;
	tof << "        <textColor>#000000</textColor>" << endl;
	tof << "        <font>Arial-bold-12</font>" << endl;
	tof << "        <URIString>http://vue.tufts.edu/rdf/resource/d2cdd634c0a8000b01592170d07ead80</URIString>" << endl;
	tof << "        <child ID=\"7\" created=\"1373631127984\" x=\"34.0\" y=\"23.0\"" << endl;
	tof << "            width=\"256.0\" height=\"241.05836\" strokeWidth=\"0.0\"" << endl;
	tof << "            autoSized=\"false\" xsi:type=\"image\">" << endl;
	tof << "            <resource referenceCreated=\"0\"" << endl;
	tof << "                accessAttempted=\"1373631233515\"" << endl;
	tof << "                accessSuccessful=\"1373631233609\" size=\"9688\"" << endl;
	tof << "            spec=\"" << legend;
	tof << "legend.JPG\"" << endl;
//	tof << "                spec=\"D:\\project2010\\Semantics\\Release\\legend.JPG\"" << endl;
	tof << "                type=\"1\" xsi:type=\"URLResource\">" << endl;
	tof << "                <title>legend.JPG</title>" << endl;
	tof << "                <property key=\"Content.size\" value=\"9688\"/>" << endl;
	tof << "                <property key=\"Content.modified\" value=\"Fri Jul 12 18:10:16 YEKT 2013\"/>" << endl;
	tof << "                <property key=\"image.width\" value=\"257\"/>" << endl;
	tof << "                <property key=\"image.height\" value=\"242\"/>" << endl;
	tof << "                <property key=\"image.format\" value=\"JPEG\"/>" << endl;
	tof << "                <property key=\"@file.relative\" value=\"legend.JPG\"/>" << endl;
	tof << "                <property key=\"File\" value=\"legend.JPG\"/>" << endl;
	tof << "            </resource>" << endl;
	tof << "            <strokeColor>#404040</strokeColor>" << endl;
	tof << "            <textColor>#000000</textColor>" << endl;
	tof << "            <font>SansSerif-plain-14</font>" << endl;
	tof << "            <URIString>http://vue.tufts.edu/rdf/resource/d2cdd643c0a8000b01592170df367645</URIString>" << endl;
	tof << "        </child>" << endl;
	tof << "        <shape xsi:type=\"rectangle\"/>" << endl;
	tof << "    </child>" << endl;
*/

    tof << "    <child ID=\"6\"" << endl;
    tof << "        label=\"&#x410;&#x442;&#x43e;&#x43c;&#x430;&#x440;&#x43d;&#x430;&#x44f;&#xa;&#x444;&#x43e;&#x440;&#x43c;&#x443;&#x43b;&#x430;\"" << endl;
    tof << "        layerID=\"1\" created=\"1373629525875\" x=\"-950.6667\" y=\"-224.0\"" << endl;
    tof << "        width=\"120.0\" height=\"158.66666\" strokeWidth=\"2.0\"" << endl;
    tof << "        autoSized=\"false\" xsi:type=\"node\">" << endl;
    tof << "        <fillColor>#F1A83E</fillColor>" << endl;
    tof << "        <strokeColor>#000000</strokeColor>" << endl;
    tof << "        <textColor>#000000</textColor>" << endl;
    tof << "        <font>Arial-bold-16</font>" << endl;
    tof << "        <URIString>http://vue.tufts.edu/rdf/resource/d2c7042bc0a8000b01592170c4e507f0</URIString>" << endl;
    tof << "        <shape arcwidth=\"20.0\" archeight=\"20.0\" xsi:type=\"roundRect\"/>" << endl;
    tof << "    </child>" << endl;
    tof << "    <child ID=\"7\"" << endl;
    tof << "        label=\"&#x424;&#x43e;&#x440;&#x43c;&#x443;&#x43b;&#x430;&#xa;&#x43f;&#x43e;&#x442;&#x43e;&#x43c;&#x43e;&#x43a;\"" << endl;
    tof << "        layerID=\"1\" created=\"1373629629671\" x=\"-818.3334\" y=\"-223.33333\"" << endl;
    tof << "        width=\"120.0\" height=\"160.0\" strokeWidth=\"2.0\" strokeStyle=\"2\"" << endl;
    tof << "        autoSized=\"false\" xsi:type=\"node\">" << endl;
    tof << "        <fillColor>#0AAD1D</fillColor>" << endl;
    tof << "        <strokeColor>#000000</strokeColor>" << endl;
    tof << "        <textColor>#000000</textColor>" << endl;
    tof << "        <font>Arial-bold-16</font>" << endl;
    tof << "        <URIString>http://vue.tufts.edu/rdf/resource/d2c7042bc0a8000b01592170262f4b1f</URIString>" << endl;
    tof << "        <shape xsi:type=\"rectangle\"/>" << endl;
    tof << "    </child>" << endl;
    tof << "    <child ID=\"8\"" << endl;
    tof << "        label=\"&#x41e;&#x431;&#x44a;&#x435;&#x434;&#x438;&#x43d;&#x435;&#x43d;&#x438;&#x435;&#xa;&#x438;&#x43b;&#x438; &#x43f;&#x435;&#x440;&#x435;&#x441;&#x435;&#x447;&#x435;&#x43d;&#x438;&#x435;\"" << endl;
    tof << "        layerID=\"1\" created=\"1373629689609\" x=\"-890.16675\"" << endl;
    tof << "        y=\"-51.000015\" width=\"275.6667\" height=\"38.0\" strokeWidth=\"1.0\"" << endl;
    tof << "        autoSized=\"false\" controlCount=\"0\" arrowState=\"2\" xsi:type=\"link\">" << endl;
    tof << "        <strokeColor>#000000</strokeColor>" << endl;
    tof << "        <textColor>#404040</textColor>" << endl;
    tof << "        <font>Arial-bold-16</font>" << endl;
    tof << "        <URIString>http://vue.tufts.edu/rdf/resource/d2c7042bc0a8000b0159217084313b0f</URIString>" << endl;
    tof << "        <point1 x=\"-889.6667\" y=\"-31.33336\"/>" << endl;
    tof << "        <point2 x=\"-615.0\" y=\"-32.666668\"/>" << endl;
    tof << "    </child>" << endl;
    tof << "    <child ID=\"9\"" << endl;
    tof << "        label=\"&#x41d;&#x430;&#x43b;&#x43e;&#x436;&#x435;&#x43d;&#x438;&#x435; &#x43a;&#x432;&#x430;&#x43d;&#x442;&#x43e;&#x440;&#x430;\"" << endl;
    tof << "        layerID=\"1\" created=\"1373629849031\" x=\"-891.5\" y=\"-3.5000095\"" << endl;
    tof << "        width=\"275.6667\" height=\"19.0\" strokeWidth=\"1.0\" strokeStyle=\"1\"" << endl;
    tof << "        autoSized=\"false\" controlCount=\"0\" arrowState=\"2\" xsi:type=\"link\">" << endl;
    tof << "        <strokeColor>#000000</strokeColor>" << endl;
    tof << "        <textColor>#404040</textColor>" << endl;
    tof << "        <font>Arial-bold-16</font>" << endl;
    tof << "        <URIString>http://vue.tufts.edu/rdf/resource/d2c7042bc0a8000b0159217099631663</URIString>" << endl;
    tof << "        <point1 x=\"-891.0\" y=\"5.99998\"/>" << endl;
    tof << "        <point2 x=\"-616.3333\" y=\"6.000001\"/>" << endl;
    tof << "    </child>" << endl;
    tof << "    <child ID=\"10\"" << endl;
    tof << "        label=\"&#x41e;&#x442;&#x440;&#x438;&#x446;&#x430;&#x43d;&#x438;&#x435;\"" << endl;
    tof << "        layerID=\"1\" created=\"1373629912140\" x=\"-891.5\" y=\"31.166672\"" << endl;
    tof << "        width=\"278.3333\" height=\"19.0\" strokeWidth=\"1.0\" strokeStyle=\"4\"" << endl;
    tof << "        autoSized=\"false\" controlCount=\"0\" arrowState=\"2\" xsi:type=\"link\">" << endl;
    tof << "        <strokeColor>#000000</strokeColor>" << endl;
    tof << "        <textColor>#404040</textColor>" << endl;
    tof << "        <font>Arial-bold-16</font>" << endl;
    tof << "        <URIString>http://vue.tufts.edu/rdf/resource/d2c7042bc0a8000b01592170595f33f4</URIString>" << endl;
    tof << "        <point1 x=\"-891.0\" y=\"40.666668\"/>" << endl;
    tof << "        <point2 x=\"-613.6667\" y=\"40.66668\"/>" << endl;
    tof << "    </child>" << endl;
    tof << "    <child ID=\"11\"" << endl;
    tof << "        label=\"&#x41c;&#x43d;&#x43e;&#x436;&#x435;&#x441;&#x442;&#x432;&#x43e;\"" << endl;
    tof << "        layerID=\"1\" created=\"1387363871531\" x=\"-687.0\" y=\"-223.41666\"" << endl;
    tof << "        width=\"120.0\" height=\"160.0\" strokeWidth=\"2.0\" strokeStyle=\"4\"" << endl;
    tof << "        autoSized=\"false\" xsi:type=\"node\">" << endl;
    tof << "        <fillColor>#EEEEEE</fillColor>" << endl;
    tof << "        <strokeColor>#000000</strokeColor>" << endl;
    tof << "        <textColor>#000000</textColor>" << endl;
    tof << "        <font>Arial-bold-16</font>" << endl;
    tof << "        <URIString>http://vue.tufts.edu/rdf/resource/05585c3cc0a8000b0120d5615e1751e5</URIString>" << endl;
    tof << "        <shape xsi:type=\"rectangle\"/>" << endl;
    tof << "    </child>" << endl;
    tof << "    <child ID=\"12\"" << endl;
    tof << "        label=\"&#x41c;&#x43d;&#x43e;&#x436;&#x435;&#x441;&#x442;&#x432;&#x43e; - &#x444;&#x43e;&#x440;&#x43c;&#x443;&#x43b;&#x430;\"" << endl;
    tof << "        layerID=\"1\" created=\"1387364022531\" x=\"-891.1666\" y=\"61.083344\"" << endl;
    tof << "        width=\"278.3333\" height=\"19.0\" strokeWidth=\"2.0\"" << endl;
    tof << "        autoSized=\"false\" controlCount=\"0\" arrowState=\"2\" xsi:type=\"link\">" << endl;
    tof << "        <strokeColor>#DD7B11</strokeColor>" << endl;
    tof << "        <textColor>#404040</textColor>" << endl;
    tof << "        <font>Arial-bold-16</font>" << endl;
    tof << "        <URIString>http://vue.tufts.edu/rdf/resource/05585c3cc0a8000b0120d561fc5caba6</URIString>" << endl;
    tof << "        <point1 x=\"-890.6666\" y=\"70.58334\"/>" << endl;
    tof << "        <point2 x=\"-613.3333\" y=\"70.58335\"/>" << endl;
    tof << "    </child>" << endl;

}

//
//  запись заключительной части VUE-файла
//
void printVUEFooter(ostream& tof, string & filename, string & currentDir)
{
	tof << "    <userZoom>1.0</userZoom>" << endl;
	tof << "    <userOrigin x=\"-14.0\" y=\"-14.0\"/>" << endl;
	tof << "    <presentationBackground>#202020</presentationBackground>" << endl;
	tof << "    <PathwayList currentPathway=\"0\" revealerIndex=\"-1\">" << endl;
	tof << "        <pathway ID=\"0\"" << endl;
	tof << "            label=\"&#x41c;&#x430;&#x440;&#x448;&#x440;&#x443;&#x442; &#x431;&#x435;&#x437; &#x438;&#x43c;&#x435;&#x43d;&#x438;\"" << endl;
	tof << "            created=\"1378800153078\" x=\"0.0\" y=\"0.0\" width=\"1.4E-45\"";
	tof << "            height=\"1.4E-45\" strokeWidth=\"0.0\" autoSized=\"false\"" << endl;
	tof << "            currentIndex=\"-1\" open=\"true\">" << endl;
	tof << "            <strokeColor>#B3CC33CC</strokeColor>" << endl;
	tof << "            <textColor>#000000</textColor>" << endl;
	tof << "            <font>SansSerif-plain-14</font>" << endl;
	tof << "            <URIString>http://vue.tufts.edu/rdf/resource/06e8c0f6c0a8000b00f95b1e5052945b</URIString>" << endl;
	tof << "            <masterSlide ID=\"2\" created=\"1378800153125\" x=\"0.0\" y=\"0.0\"" << endl;
	tof << "                width=\"800.0\" height=\"600.0\" locked=\"true\"" << endl;
	tof << "                strokeWidth=\"0.0\" autoSized=\"false\">" << endl;
	tof << "                <fillColor>#000000</fillColor>" << endl;
	tof << "                <strokeColor>#404040</strokeColor>" << endl;
	tof << "                <textColor>#000000</textColor>" << endl;
	tof << "                <font>SansSerif-plain-14</font>" << endl;
	tof << "                <URIString>http://vue.tufts.edu/rdf/resource/06e8c0f6c0a8000b00f95b1ea03139ac</URIString>" << endl;
	tof << "                <titleStyle ID=\"3\" label=\"Header\"" << endl;
	tof << "                    created=\"1378800153156\" x=\"335.5\" y=\"172.5\"" << endl;
	tof << "                    width=\"129.0\" height=\"55.0\" strokeWidth=\"0.0\"" << endl;
	tof << "                    autoSized=\"true\" isStyle=\"true\" xsi:type=\"node\">" << endl;
	tof << "                    <strokeColor>#404040</strokeColor>" << endl;
	tof << "                    <textColor>#FFFFFF</textColor>" << endl;
	tof << "                    <font>Gill Sans-plain-36</font>" << endl;
	tof << "                    <URIString>http://vue.tufts.edu/rdf/resource/06e8c0f6c0a8000b00f95b1e7c83bf85</URIString>" << endl;
	tof << "                    <shape xsi:type=\"rectangle\"/>" << endl;
	tof << "                </titleStyle>" << endl;
	tof << "                <textStyle ID=\"4\" label=\"Slide Text\"" << endl;
	tof << "                    created=\"1378800153156\" x=\"346.5\" y=\"281.5\"" << endl;
	tof << "                    width=\"107.0\" height=\"37.0\" strokeWidth=\"0.0\"" << endl;
	tof << "                    autoSized=\"true\" isStyle=\"true\" xsi:type=\"node\">" << endl;
	tof << "                    <strokeColor>#404040</strokeColor>" << endl;
	tof << "                    <textColor>#FFFFFF</textColor>" << endl;
	tof << "                    <font>Gill Sans-plain-22</font>" << endl;
	tof << "                    <URIString>http://vue.tufts.edu/rdf/resource/06e8c106c0a8000b00f95b1e33dc73d4</URIString>" << endl;
	tof << "                    <shape xsi:type=\"rectangle\"/>" << endl;
	tof << "                </textStyle>" << endl;
	tof << "                <linkStyle ID=\"5\" label=\"Links\" created=\"1378800153171\"" << endl;
	tof << "                    x=\"373.5\" y=\"384.0\" width=\"53.0\" height=\"32.0\"" << endl;
	tof << "                    strokeWidth=\"0.0\" autoSized=\"true\" isStyle=\"true\" xsi:type=\"node\">" << endl;
	tof << "                    <strokeColor>#404040</strokeColor>" << endl;
	tof << "                    <textColor>#B3BFE3</textColor>" << endl;
	tof << "                    <font>Gill Sans-plain-18</font>" << endl;
	tof << "                    <URIString>http://vue.tufts.edu/rdf/resource/06e8c106c0a8000b00f95b1ea93b8699</URIString>" << endl;
	tof << "                    <shape xsi:type=\"rectangle\"/>" << endl;
	tof << "                </linkStyle>" << endl;
	tof << "            </masterSlide>" << endl;
	tof << "        </pathway>" << endl;
	tof << "    </PathwayList>" << endl;
	tof << "    <date>2013-09-10</date>" << endl;
	tof << "    <modelVersion>6</modelVersion>" << endl;
	
	tof << "    <saveLocation>";
	tof << currentDir;
	tof << "</saveLocation>" << endl;
	tof << "    <saveFile>";
	tof << currentDir;
	tof << filename;
	tof << "</saveFile>" << endl;
	tof << "</LW-MAP>";
}


//
//  запись уровня, пока что пишут только один уровень
//
void printVUELayer(ostream& tof)
{
	tof << "    <layer ID=\"1\" label=\"Layer 1\" created=\"1378800153093\" x=\"0.0\"" << endl;
	tof << "        y=\"0.0\" width=\"1.4E-45\" height=\"1.4E-45\" strokeWidth=\"0.0\" autoSized=\"false\">" << endl;
	tof << "        <URIString>http://vue.tufts.edu/rdf/resource/06e8c0f6c0a8000b00f95b1e0b908b0f</URIString>" << endl;
	tof << "    </layer>" << endl;
}



//
//  функция конвертации всех русских символов в строке к виду, пригодному для VUE-схем
//
void convertVUERussianSymbols(tstring & tstr)
{
	tstring russians = _T("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦШЩЬЪЭЮЯЫЧабвгдеёжзийклмнопрстуфхцшщьъэюяыч");
	tstring converted[] = {_T("&#x410;"),_T("&#x411;"),_T("&#x412;"),_T("&#x413;"),_T("&#x414;"),_T("&#x415;"),_T("&#x401;"),_T("&#x416;"),_T("&#x417;"),
		_T("&#x418;"),_T("&#x419;"),_T("&#x41a;"),_T("&#x41b;"),_T("&#x41c;"),_T("&#x41d;"),_T("&#x41e;"),_T("&#x41f;"),_T("&#x420;"),_T("&#x421;"),
		_T("&#x422;"),_T("&#x423;"),_T("&#x424;"),_T("&#x425;"),_T("&#x426;"),_T("&#x428;"),_T("&#x429;"),_T("&#x42c;"),_T("&#x42a;"),
		_T("&#x42d;"),_T("&#x42e;"),_T("&#x42f;"),_T("&#x42b;"),_T("&#x427;"),_T("&#x430;"),_T("&#x431;"),_T("&#x432;"),_T("&#x433;"),_T("&#x434;"),
		_T("&#x435;"),_T("&#x451;"),_T("&#x436;"),_T("&#x437;"),_T("&#x438;"),_T("&#x439;"),_T("&#x43a;"),_T("&#x43b;"),_T("&#x43c;"),_T("&#x43d;"),
		_T("&#x43e;"),_T("&#x43f;"),_T("&#x440;"),_T("&#x441;"),_T("&#x442;"),_T("&#x443;"),_T("&#x444;"),_T("&#x445;"),_T("&#x446;"),_T("&#x448;"),
		_T("&#x449;"),_T("&#x44c;"),_T("&#x44a;"),_T("&#x44d;"),_T("&#x44e;"),_T("&#x44f;"),_T("&#x44b;"),_T("&#x447;")};
	
	// цикл по всем буквам русского алфавита
	for(size_t i = 0; i < russians.length(); i++)
	{
		int pos = -1;    // позиция вхождения очередного символа
		while( (pos = tstr.find(russians.substr(i, 1) ) ) >= 0)    // если найдено очередное вхождение
		{
			tstr.replace(pos, 1 , converted[i]);    // заменяем русский символ на VUE-вид
		}
	}
}