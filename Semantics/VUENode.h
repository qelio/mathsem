//  Автор кода: Татаринцев В.В., akizelokro@mail.ru, 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
//
//  Определение классов VUENode, VUEFormula и VUESet, а также функций, используемых для построения VUE-карт
//

#pragma once

#include "common_functions.h"
#include "Formula.h"

//
//  Перечисление типов узлов
//
/**
 * @enum VUENodeType
 * @brief Перечисление типов узлов в VUE-карте.
 */
enum VUENodeType
{
    VUENODE = 0,   /**< Базовый тип узла */
    VUEFORMULA = 1, /**< Узел, представляющий формулу */
    VUESET = 2      /**< Узел, представляющий набор формул */
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Класс VUENode, базовый для классов VUEFormula и VUESet, содержит общие свойства и методы для узлов VUE-карты
/**
 * @class VUENode
 * @brief Базовый класс для VUEFormula и VUESet, содержащий общие свойства и методы для узлов VUE-карты.
 */
class VUENode
{
protected:
    string fillColor;    /**< Цвет заливки узла */
    string textColor;    /**< Цвет текста внутри узла */
    string strokeColor;  /**< Цвет границы узла */
    string font;         /**< Шрифт, используемый для метки узла */
    string xsi;          /**< Тип формы узла (например, прямоугольник, округленный прямоугольник) */
    string strokeStyle;  /**< Стиль границы узла */
    VUENodeType type;    /**< Тип узла (VUENODE, VUEFORMULA, VUESET) */

public:
    double x;            /**< Координата X позиции узла */
    double y;            /**< Координата Y позиции узла */
    double width;        /**< Ширина узла */
    double height;       /**< Высота узла */

    int numberInGroup;   /**< Номер узла в своей группе */
    int groupAtom;       /**< Идентификатор группы, к которой принадлежит узел */
    int numberInLayer;   /**< Номер узла в своем слое */
    int childID;         /**< Уникальный идентификатор для узла в VUE-карте */

    /**
     * @brief Конструктор по умолчанию инициализирует свойства по умолчанию.
     */
    VUENode();

    /**
     * @brief Деструктор.
     */
    ~VUENode();

    /**
     * @brief Параметризованный конструктор для создания узла с заданными идентификаторами.
     * @param childID_ Уникальный идентификатор для узла.
     * @param numberInLayer_ Номер узла в его слое.
     */
    VUENode(int childID_, int numberInLayer_);

    /**
     * @brief Устанавливает положение и размер узла.
     * @param x_ Координата X позиции узла.
     * @param y_ Координата Y позиции узла.
     * @param width_ Ширина узла.
     * @param height_ Высота узла.
     */
    void SetPosition(double x_, double y_, double width_, double height_) { x = x_; y = y_; width = width_; height = height_; };

    /**
     * @brief Выводит узел в файл VUE-карты.
     * @param os Поток вывода для записи данных узла.
     * @param str Дополнительные строковые данные для включения в вывод.
     */
    void print(ostream& os, string& str);

    /**
     * @brief Устанавливает свойства, специфичные для дочерних узлов, в зависимости от их типа.
     */
    void childProperties();

    /**
     * @brief Получает тип узла.
     * @return Тип узла.
     */
    VUENodeType GetType() { return type; };
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Класс формулы, наследующий общие свойства узла
/**
 * @class VUEFormula
 * @brief Представляет узел формулы в VUE-карте.
 */
class VUEFormula : public VUENode
{
public:
    Formula* formula;    /**< Указатель на связанный объект формулы */

    /**
     * @brief Параметризованный конструктор для создания узла формулы с заданными идентификаторами.
     * @param childID_ Уникальный идентификатор для узла.
     * @param numberInLayer_ Номер узла в его слое.
     */
    VUEFormula(int childID_, int numberInLayer_) : VUENode(childID_, numberInLayer_) { type = VUEFORMULA; };

    /**
     * @brief Деструктор.
     */
    ~VUEFormula();

    /**
     * @brief Выводит узел формулы в файл VUE-карты.
     * @param os Поток вывода для записи данных узла.
     */
    void print(ostream& os);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Класс набора формул, наследующий общие свойства узла
/**
 * @class VUESet
 * @brief Представляет узел набора формул в VUE-карте.
 */
class VUESet : public VUENode
{
public:
    FormulaSet* parentSet;    /**< Указатель на связанный объект набора формул */

    /**
     * @brief Параметризованный конструктор для создания узла набора с заданными идентификаторами.
     * @param childID_ Уникальный идентификатор для узла.
     * @param numberInLayer_ Номер узла в его слое.
     */
    VUESet(int childID_, int numberInLayer_) : VUENode(childID_, numberInLayer_) { type = VUESET; };

    /**
     * @brief Деструктор.
     */
    ~VUESet();

    /**
     * @brief Выводит узел набора в файл VUE-карты.
     * @param os Поток вывода для записи данных узла.
     */
    void print(ostream& os);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Функции, используемые для построения VUE-карт
//

/**
 * @brief Заменяет символы математической нотации в строке символами, подходящими для VUE-карт.
 * @param tstr Строка для обработки.
 * @param width Параметр ширины, влияющий на замену символов.
 * @return true, если операция выполнена успешно, false в противном случае.
 */
bool UnPrepareMathSymbols(tstring& tstr, double width);

/**
 * @brief Преобразует русские символы в строке в символы, подходящие для VUE-карт.
 * @param tstr Строка для обработки.
 */
void convertVUERussianSymbols(tstring& tstr);

/**
 * @brief Записывает начальную часть заголовка VUE-карты в файл.
 * @param tof Поток вывода для записи заголовка.
 * @param filename Имя записываемого файла.
 * @param currentDir Текущий путь к каталогу.
 */
void printFirstPartVUEHeader(ostream& tof, string& filename, string& currentDir);

/**
 * @brief Записывает легенду в файл VUE-карты.
 * @param tof Поток вывода для записи легенды.
 * @param legend Строка, содержащая информацию о легенде.
 */
void printVUELegend(ostream& tof, string& legend);

/**
 * @brief Записывает завершающую часть VUE-карты в файл.
 * @param tof Поток вывода для записи заключительной части.
 * @param filename Имя записываемого файла.
 * @param currentDir Текущий путь к каталогу.
 */
void printVUEFooter(ostream& tof, string& filename, string& currentDir);

/**
 * @brief Записывает информацию о слоях в файл VUE-карты.
 * @param tof Поток вывода для записи информации о слоях.
 */
void printVUELayer(ostream& tof);