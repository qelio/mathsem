/**
 * @file SemanticString.h
 * @brief Defines the SemanticString class and related enumerations for mathematical text styling.
 */

#pragma once

#include "common_functions.h"
#include "Formula.h"

/**
 * @enum MathStyle
 * @brief Specifies the mathematical styling for characters.
 */
enum MathStyle {
    NONE_MATHSTYLE = 0,  /**< No special styling, regular text */
    LOW_MATHINDEX = 1,   /**< Subscript styling */
    HIGH_MATHINDEX = 2,  /**< Superscript styling */
    SYMBOL_TYPEFACE = 3  /**< Symbol typeface styling */
};

/**
 * @class SemanticString
 * @brief Represents a semantic string for rendering mathematical expressions with styling.
 *
 * The SemanticString class is responsible for preparing and rendering a string that contains mathematical
 * expressions with various styles such as subscripts, superscripts, and special symbols.
 */
class SemanticString
{
public:
    /**
     * @brief Constructs a new SemanticString object.
     */
    SemanticString();

    /**
     * @brief Destructs the SemanticString object.
     */
    ~SemanticString();

    /**
     * @brief Prepares the internal data from the input string for rendering.
     *
     * Parses the given text string and fills the character and style arrays accordingly.
     * Optionally formats the string for Word export if @p forWordExport is true.
     *
     * @param tstr The input text string to prepare.
     * @param forWordExport Indicates if the preparation is for Word export.
     * @return True if preparation is successful, false otherwise.
     */
    bool PrepareSubItemData(tstring& tstr, bool forWordExport = false);

    /**
     * @brief Draws the SemanticString content in the specified rectangle.
     *
     * Renders the prepared string onto the device context @p dc within the rectangle @p rectSubItem.
     * Uses the provided fonts for symbols and indexes.
     *
     * @param dc The device context to draw on.
     * @param rectSubItem The rectangle area to draw the content.
     * @param m_fSymbol Font used for symbol typeface characters.
     * @param m_fIndexes Font used for subscript and superscript characters.
     */
    void DrawItem(CDC& dc, CRect& rectSubItem, CFont* m_fSymbol, CFont* m_fIndexes);

    // Additional methods and members can be added here...

private:
    /**
     * @brief Character buffer containing the semantic string.
     *
     * Holds the characters to be rendered, with support for Unicode if applicable.
     * The buffer size is fixed to 256 characters.
     */
#ifdef _UNICODE
    WCHAR tchars[256];
#else
    unsigned char tchars[256];
#endif

    /**
     * @brief Array of MathStyle values corresponding to each character in @c tchars.
     *
     * Determines the styling for each character, such as subscript, superscript, or symbol typeface.
     */
    int symbolics[256];

    /**
     * @brief Number of characters in the @c tchars and @c symbolics arrays.
     */
    int count;

    /**
     * @brief Pointer to the mathematical entity associated with this string.
     *
     * Typically points to a Formula or EntityBase object that is the source of the string data.
     */
    EntityBase* formula;

    /**
     * @brief Original text string used to prepare the semantic string.
     */
    tstring* text;

    /**
     * @brief Precomputed size of the rendered string.
     *
     * Calculated during drawing operations to optimize rendering.
     */
    CSize size;

	SemanticString operator=(SemanticString &str); // ����������
};