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
/**
 * @enum VUENodeType
 * @brief Enumeration of node types in the VUE-map.
 */
enum VUENodeType
{
    VUENODE = 0,   /**< Base node type */
    VUEFORMULA = 1, /**< Node representing a formula */
    VUESET = 2      /**< Node representing a formula set */
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ����� VUENode, ������� ��� ������� VUEFormula � VUESet, �������� ����� �����������, ����������� � ���������� ���
//  ���������� ����� � VUE-�����
/**
 * @class VUENode
 * @brief Base class for VUEFormula and VUESet, containing common properties and methods for VUE-map nodes.
 */
class VUENode
{
protected:
    string fillColor;    /**< Fill color of the node */
    string textColor;    /**< Text color inside the node */
    string strokeColor;  /**< Border color of the node */
    string font;         /**< Font used for the node's label */
    string xsi;          /**< Shape type of the node (e.g., rectangle, roundRect) */
    string strokeStyle;  /**< Style of the node's border */
    VUENodeType type;    /**< Type of the node (VUENODE, VUEFORMULA, VUESET) */

public:
    double x;            /**< X-coordinate of the node's position */
    double y;            /**< Y-coordinate of the node's position */
    double width;        /**< Width of the node */
    double height;       /**< Height of the node */

    int numberInGroup;   /**< Number of the node within its group */
    int groupAtom;       /**< Identifier of the group the node belongs to */
    int numberInLayer;   /**< Position of the node within its layer */
    int childID;         /**< Unique identifier for the node in the VUE-map */

    /**
     * @brief Default constructor initializes default property values.
     */
    VUENode();

    /**
     * @brief Destructor.
     */
    ~VUENode();

    /**
     * @brief Parameterized constructor for creating a node with specific IDs.
     * @param childID_ Unique identifier for the node.
     * @param numberInLayer_ Position of the node within its layer.
     */
    VUENode(int childID_, int numberInLayer_);

    /**
     * @brief Sets the position and size of the node.
     * @param x_ X-coordinate of the node's position.
     * @param y_ Y-coordinate of the node's position.
     * @param width_ Width of the node.
     * @param height_ Height of the node.
     */
    void SetPosition(double x_, double y_, double width_, double height_) { x = x_; y = y_; width = width_; height = height_; };

    /**
     * @brief Outputs the node to the VUE-map file.
     * @param os Output stream to write the node data.
     * @param str Additional string data to include in the output.
     */
    void print(ostream& os, string& str);

    /**
     * @brief Sets properties specific to child nodes based on their type.
     */
    void childProperties();

    /**
     * @brief Gets the type of the node.
     * @return The type of the node.
     */
    VUENodeType GetType() { return type; };
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ����� �����, �������������� �������
/**
 * @class VUEFormula
 * @brief Represents a formula node in the VUE-map.
 */
class VUEFormula : public VUENode
{
public:
    Formula* formula;    /**< Pointer to the associated formula object */

    /**
     * @brief Parameterized constructor for creating a formula node with specific IDs.
     * @param childID_ Unique identifier for the node.
     * @param numberInLayer_ Position of the node within its layer.
     */
    VUEFormula(int childID_, int numberInLayer_) : VUENode(childID_, numberInLayer_) { type = VUEFORMULA; };

    /**
     * @brief Destructor.
     */
    ~VUEFormula();

    /**
     * @brief Outputs the formula node to the VUE-map file.
     * @param os Output stream to write the node data.
     */
    void print(ostream& os);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ����� �����, �������������� ��������� ����������
/**
 * @class VUESet
 * @brief Represents a formula set node in the VUE-map.
 */
class VUESet : public VUENode
{
public:
    FormulaSet* parentSet;    /**< Pointer to the associated formula set object */

    /**
     * @brief Parameterized constructor for creating a set node with specific IDs.
     * @param childID_ Unique identifier for the node.
     * @param numberInLayer_ Position of the node within its layer.
     */
    VUESet(int childID_, int numberInLayer_) : VUENode(childID_, numberInLayer_) { type = VUESET; };

    /**
     * @brief Destructor.
     */
    ~VUESet();

    /**
     * @brief Outputs the set node to the VUE-map file.
     * @param os Output stream to write the node data.
     */
    void print(ostream& os);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������������� ��� �������� VUE-����� �������
//

/**
 * @brief Replaces mathematical notation symbols in the string with symbols suitable for VUE-maps.
 * @param tstr The string to process.
 * @param width Width parameter affecting symbol replacement.
 * @return True if the operation was successful, false otherwise.
 */
bool UnPrepareMathSymbols(tstring& tstr, double width);

/**
 * @brief Converts Russian characters in the string to symbols suitable for VUE-maps.
 * @param tstr The string to process.
 */
void convertVUERussianSymbols(tstring& tstr);

/**
 * @brief Writes the initial part of the VUE-map header to a file.
 * @param tof Output stream to write the header.
 * @param filename Name of the file being written.
 * @param currentDir Current directory path.
 */
void printFirstPartVUEHeader(ostream& tof, string& filename, string& currentDir);

/**
 * @brief Writes the legend to the VUE-map file.
 * @param tof Output stream to write the legend.
 * @param legend String containing the legend information.
 */
void printVUELegend(ostream& tof, string& legend);

/**
 * @brief Writes the closing part of the VUE-map to the file.
 * @param tof Output stream to write the footer.
 * @param filename Name of the file being written.
 * @param currentDir Current directory path.
 */
void printVUEFooter(ostream& tof, string& filename, string& currentDir);

/**
 * @brief Writes the layer information to the VUE-map file.
 * @param tof Output stream to write the layer information.
 */
void printVUELayer(ostream& tof);