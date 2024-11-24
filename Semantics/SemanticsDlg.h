// SemanticsDlg.h : Header file for the CSemanticsDlg class.

#pragma once

#include "Formula.h"
#include "ScientificStatic.h"
#include "ScientificButton.h"
#include "afxeditbrowsectrl.h"
#include "VUENode.h"
#include "VUELink.h"
#include "afxwin.h"
#include "resource.h"

// Include for libxml2 (disabled for Windows compilation)
// #include <libxml\parser.h>
// #include <libxml\tree.h>

// #define LIBXML_TREE_ENABLED
// #define LIBXML_OUTPUT_ENABLED

/**
 * @class CSemanticsDlg
 * @brief The main dialog class for the Semantics application.
 *
 * This class represents the dialog window for the Semantics application. It handles
 * the creation and interaction of various controls such as buttons and edit boxes,
 * as well as the processing of different commands triggered by the user. The dialog
 * interacts with formulas and entities, and allows for exporting and saving data.
 */
class CSemanticsDlg : public CDialogEx
{
public:
    /**
     * @brief Default constructor for CSemanticsDlg.
     *
     * Initializes the dialog with an optional parent window.
     *
     * @param pParent The parent window. Default is NULL.
     */
    CSemanticsDlg(CWnd* pParent = NULL);

    /**
     * @brief Destructor for CSemanticsDlg.
     *
     * Cleans up any allocated resources when the dialog is destroyed.
     */
    ~CSemanticsDlg();

    /**
     * @brief Dialog Data Identifier (IDD).
     *
     * This value represents the resource ID for the Semantics dialog.
     */
    enum { IDD = IDD_SEMANTICS_DIALOG };

protected:
    /**
     * @brief Data Exchange Function.
     *
     * This function exchanges data between the controls and variables, ensuring
     * that all data is updated properly during the dialog interaction.
     *
     * @param pDX A pointer to a CDataExchange object.
     */
    virtual void DoDataExchange(CDataExchange* pDX);

protected:
    HICON m_hIcon; /**< Icon for the dialog window. */

    /**
     * @brief Initializes the dialog on creation.
     *
     * This function is called when the dialog is initialized. It sets up the
     * icon and any initial configurations for the controls.
     *
     * @return TRUE if initialization is successful, otherwise FALSE.
     */
    virtual BOOL OnInitDialog();

    /**
     * @brief Handles system commands, such as minimizing or closing the dialog.
     *
     * @param nID The system command ID.
     * @param lParam Additional message parameters.
     */
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

    /**
     * @brief Handles the painting of the dialog window.
     */
    afx_msg void OnPaint();

    /**
     * @brief Queries for the cursor to use when dragging the dialog.
     *
     * @return The cursor for dragging the dialog.
     */
    afx_msg HCURSOR OnQueryDragIcon();

    DECLARE_MESSAGE_MAP()

public:
    /**
     * @brief Handles the click event for the OK button.
     */
    afx_msg void OnBnClickedOk();

    /**
     * @brief Handles the click event to show all formulas.
     */
    afx_msg void OnBnClickedShowallformulas3();

    /**
     * @brief Handles the click event to add a new atomic formula.
     */
    afx_msg void OnBnClickedAddatomformula();

    vector <EntityBase *> all_entities; /**< A vector storing all entities in the application. */

    /**
     * @brief Handles the click event for building formulas.
     */
    afx_msg void OnBnClickedBuildformula1();
    afx_msg void OnBnClickedBuildformula2();
    afx_msg void OnBnClickedBuildformula3();
    afx_msg void OnBnClickedBuildformula4();
    afx_msg void OnBnClickedBuildformula5();
    afx_msg void OnBnClickedShowallformulas();
    afx_msg void OnBnClickedChangeNewVariable();
    afx_msg void OnBnClickedHelp();

    /**
     * @brief Various scientific button controls.
     * These controls are used to represent scientific functions in the dialog.
     */
    CScientificButton m_button5;
    CScientificButton m_button4;
    CScientificButton m_button3;
    CScientificButton m_button2;
    CScientificButton m_button1;
    CScientificButton m_button6;
    CScientificButton m_button;
    CMFCEditBrowseCtrl m_fileFinder;

    /**
     * @brief Handles the click event for the Build Formula 6 button.
     */
    afx_msg void OnBnClickedBuildformula6();

    /**
     * @brief Handles the click event to export data.
     */
    afx_msg void OnBnClickedExport();

    CMFCEditBrowseCtrl m_fileWordExport; /**< Control for browsing and selecting export file. */

    /**
     * @brief Handles the click event to save the scheme.
     */
    afx_msg void OnBnClickedSavescheme();

    /**
     * @brief Handles the click event to load a saved scheme.
     */
    afx_msg void OnBnClickedLoadscheme();

    /**
     * @brief Handles the click event to cancel the current operation.
     */
    afx_msg void OnBnClickedCancel();

    /**
     * @brief Handles the change event for the file browse control.
     */
    afx_msg void OnEnChangeMfceditbrowse2();

    /**
     * @brief Handles the click event for the Build Formula 7 button.
     */
    afx_msg void OnBnClickedBuildformula7();

    CScientificButton m_button7; /**< Button for building formulas (Formula 7). */

    /**
     * @brief Handles the click event to build a tuple.
     */
    afx_msg void OnBnClickedBuildtuple();

    CScientificButton m_KortegeButton; /**< Button for building a Kortege. */

    /**
     * @brief Handles the click event to change a variable.
     */
    afx_msg void OnBnClickedChangevariable();

    CScientificButton m_ChangeVariable; /**< Button for changing variables. */

    int m_rbLang; /**< Variable to store the language setting. */

    /**
     * @brief Handles the click event to switch to Russian language.
     */
    afx_msg void OnBnClickedRus();

    /**
     * @brief Handles the click event to switch to English language.
     */
    afx_msg void OnBnClickedEng();
};
