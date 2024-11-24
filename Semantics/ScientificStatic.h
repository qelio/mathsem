//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once

#include "SemanticString.h"

/**
 * @class CScientificStatic
 * @brief A custom static control class for rendering mathematical expressions with special formatting for symbols and indices.
 *
 * This class extends from CStatic and is used to display static text that may include mathematical symbols,
 * subscripts, and superscripts, with customizable font settings.
 */
class CScientificStatic : public CStatic
{
    DECLARE_DYNAMIC(CScientificStatic)

public:
    /**
     * @brief Default constructor for CScientificStatic class.
     *
     * Initializes the CScientificStatic object, setting up the necessary properties and states for rendering.
     */
    CScientificStatic();

    /**
     * @brief Destructor for CScientificStatic class.
     *
     * Cleans up any resources used by the CScientificStatic object.
     */
    virtual ~CScientificStatic();

protected:
    DECLARE_MESSAGE_MAP()

public:
    /**
     * @brief Paints the content of the static control.
     *
     * This method is called to paint or redraw the content of the static control, rendering mathematical symbols
     * and expressions with the appropriate fonts (symbols, subscripts, superscripts).
     */
    afx_msg void OnPaint();

    /**
     * @brief Pointer to a SemanticString object.
     *
     * This pointer holds a reference to a SemanticString, which can represent a mathematical expression or symbol
     * that is rendered in the static control.
     */
    SemanticString * dsi;

    /**
     * @brief Font used for rendering mathematical symbols in the static control.
     *
     * This font is used to display the mathematical symbols in the static control.
     */
    CFont * m_fSymbol;

    /**
     * @brief Font used for rendering subscripts and superscripts in the static control.
     *
     * This font is used for rendering subscript and superscript elements in the static control, allowing for
     * proper formatting of mathematical expressions.
     */
    CFont * m_fIndexes;
};
