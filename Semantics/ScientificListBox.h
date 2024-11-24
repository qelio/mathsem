//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once
#include "MathListCtrlEx.h"
#include "common_functions.h"

/**
 * @class ScientificListBox
 * @brief A custom list box class used to display scientific items with special formatting for mathematical symbols and indices.
 *
 * This class extends from CListBox and allows for customized drawing and sorting of list items,
 * particularly for displaying mathematical symbols and expressions.
 */
class ScientificListBox : public CListBox
{
    DECLARE_DYNAMIC(ScientificListBox)

    /**
     * @brief Flag indicating whether the list is sorted.
     *
     * This boolean variable determines if the list of items in the box should be sorted.
     */
    bool isSorted;

public:
    /**
     * @brief Constructor for the ScientificListBox class.
     *
     * Initializes the scientific list box, setting up the necessary properties and states.
     */
    ScientificListBox();

    /**
     * @brief Destructor for the ScientificListBox class.
     *
     * Cleans up any resources used by the scientific list box.
     */
    virtual ~ScientificListBox();

protected:
    DECLARE_MESSAGE_MAP()

    /**
     * @brief Font for rendering mathematical symbols in the list box.
     *
     * This font is used to render mathematical symbols in the list box.
     */
    CFont * m_fSymbol;

    /**
     * @brief Font for rendering indexes (subscripts or superscripts) in the list box.
     *
     * This font is used to render indexes in the list box, providing subscript and superscript functionality.
     */
    CFont * m_fIndexes;

public:
    /**
     * @brief Custom method for drawing list items.
     *
     * This method overrides the default drawing behavior of the list box items, enabling the drawing
     * of mathematical symbols and expressions with appropriate fonts.
     *
     * @param lpDrawItemStruct Pointer to the DRAWITEMSTRUCT that contains information about the item to be drawn.
     */
    virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);

    /**
     * @brief A vector of SemanticString pointers.
     *
     * This vector stores semantic strings, which can represent mathematical expressions or symbols in the list.
     */
    vector <SemanticString *> DCU;

    /**
     * @brief Sets the font for rendering indexes in the list box.
     *
     * This method sets the font to be used for rendering subscript and superscript indexes in the list box.
     *
     * @param m_fIndexes_ A pointer to the CFont to be used for indexes.
     */
    void SetIndexesFont(CFont * m_fIndexes_) { m_fIndexes = m_fIndexes_; };

    /**
     * @brief Compares two list items for sorting.
     *
     * This method provides a comparison function used for sorting the list items in the list box.
     *
     * @param lpCompareItemStruct Pointer to the COMPAREITEMSTRUCT that contains information about the items to be compared.
     * @return A value that indicates the relative order of the two items (negative, zero, or positive).
     */
    virtual int CompareItem(LPCOMPAREITEMSTRUCT /*lpCompareItemStruct*/);

    /**
     * @brief Sets whether the list should be sorted.
     *
     * This method allows enabling or disabling sorting for the list of items in the list box.
     *
     * @param toSort A boolean value indicating whether sorting should be enabled (true) or disabled (false).
     */
    void SetSorting(bool toSort = false) { isSorted = toSort; };
};
