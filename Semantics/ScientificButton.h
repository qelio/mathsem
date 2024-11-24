//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once

#include "common_functions.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  @class CScientificButton
//  @brief This class defines a button for scientific characters with various actions
//         for different mathematical symbols. This class is deprecated and intended
//         for handling the drawing and actions related to scientific characters.
//
//  @note The functionality includes handling quantifiers, indices, and mathematical symbols.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Enum for defining the actions related to scientific characters on the button
/**
 * @enum ScientificCharacterAction
 * @brief Enum defining the possible actions associated with a scientific character button.
 *
 * This enum is used to determine the specific action or behavior a button represents.
 */
enum ScientificCharacterAction
{
    NONE = 0,            /**< No action */
    FirstQuantor = 1,    /**< First quantifier (for universal quantification) */
    SecondQuantor = 2,   /**< Second quantifier (for existential quantification) */
    LowerIndex = 3,      /**< Lower index */
    UpperIndex = 4       /**< Upper index (subscript or superscript) */
};

// CScientificButton class declaration
/**
 * @class CScientificButton
 * @brief Represents a button that can display and interact with scientific characters.
 *
 * This class extends from CMFCButton and adds functionality for handling different scientific characters,
 * such as quantifiers and indices, through various actions. It is used for creating customized scientific buttons
 * with special drawing and behavior.
 */
class CScientificButton : public CMFCButton
{
    DECLARE_DYNAMIC(CScientificButton)

    /**
     * @typedef SciCharMap
     * @brief Type alias for a map that associates a position with a scientific character action.
     *
     * The map holds positions as keys and the corresponding scientific character actions as values.
     */
    typedef map<int, ScientificCharacterAction, less<int>> SciCharMap;

    /**
     * @typedef SciCharMapIterator
     * @brief Type alias for an iterator for the SciCharMap.
     *
     * This alias is used to iterate over the map that associates positions with scientific actions.
     */
    typedef SciCharMap::iterator SciCharMapIterator;

    /**
     * @brief A map that stores scientific character actions for each button position.
     *
     * The map associates button positions with specific scientific actions such as quantifiers, indices, etc.
     */
    SciCharMap m_SciChars;

    /**
     * @brief Font used for rendering symbols in the scientific button.
     *
     * This font is used to display mathematical symbols in the button, using the Symbol font.
     */
    CFont m_fSymbol;

public:
    /**
     * @brief Constructor for the CScientificButton class.
     *
     * Initializes the scientific button, setting up the necessary properties and states.
     */
    CScientificButton();

    /**
     * @brief Destructor for the CScientificButton class.
     *
     * Cleans up any resources used by the scientific button.
     */
    virtual ~CScientificButton();

protected:
    DECLARE_MESSAGE_MAP()

public:
    /**
     * @brief Adds a scientific character action to the button at a specific position.
     *
     * This method allows associating a scientific character action with a given button position.
     * For example, a quantifier or index can be added for a specific button position.
     *
     * @param pos The position on the button where the scientific action is assigned.
     * @param scichar The scientific character action to be assigned to the position.
     */
    void addSciCharAction(int pos, ScientificCharacterAction scichar) { m_SciChars[pos] = scichar; };

    /**
     * @brief Sets the font for rendering scientific characters on the button.
     *
     * This method allows setting a custom font for rendering scientific symbols, based on the provided LOGFONT structure.
     *
     * @param lf The LOGFONT structure that defines the font to be used.
     */
    void setSciFont(LOGFONT * lf) { m_fSymbol.CreateFontIndirectW(lf); };

    /**
     * @brief Custom drawing method to render text on the button.
     *
     * This method overrides the default text drawing behavior to customize the appearance of the button text,
     * especially for rendering scientific characters using the defined font.
     *
     * @param pDC The device context to draw on.
     * @param rect The rectangle in which the text is to be drawn.
     * @param strText The text to be drawn.
     * @param uiDTFlags The flags controlling text drawing options.
     * @param uiState The state of the button (e.g., normal, pressed).
     */
    virtual void OnDrawText(CDC* pDC, const CRect& rect, const CString& strText, UINT uiDTFlags, UINT uiState);
};
