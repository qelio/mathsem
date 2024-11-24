// Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once
#include "afxwin.h"
#include "afxbutton.h"
#include "ScientificListBox.h"
#include "Formula.h"
#include "ScientificStatic.h"
#include "afxcmn.h"

// Declaration of the EquivalenceDlg class

/**
 * @brief The EquivalenceDlg class represents a dialog for managing equivalences.
 *
 * This class is used to handle user interactions within a dialog for adding, removing,
 * and displaying scientific formulas and equivalences.
 */
class EquivalenceDlg : public CDialogEx
{
    DECLARE_DYNAMIC(EquivalenceDlg)

    /**
     * @brief Moves a selected item from one list box to another.
     *
     * This function moves a selected item from the source list box to the destination list box.
     *
     * @param Source The source list box to move items from.
     * @param Destination The destination list box to move items to.
     */
    void MoveSelected(ScientificListBox &Source, ScientificListBox &Destination);

    /**
     * @brief Moves all items from one list box to another.
     *
     * This function moves all items from the source list box to the destination list box.
     *
     * @param Source The source list box to move items from.
     * @param Destination The destination list box to move items to.
     */
    void MoveAll(ScientificListBox &Source, ScientificListBox &Destination);

    vector <Formula *> * formulas; /**< Pointer to the vector of formulas */
    vector <EntityBase *> * allEntities; /**< Pointer to the vector of all entities */
    vector <Equivalence *> * allEquivalences; /**< Pointer to the vector of all equivalences */

public:
    /**
     * @brief Constructor for the EquivalenceDlg class.
     *
     * Initializes the dialog and sets the parent window.
     *
     * @param pParent Pointer to the parent window (default is NULL).
     */
    EquivalenceDlg(CWnd* pParent = NULL);

    /**
     * @brief Destructor for the EquivalenceDlg class.
     *
     * Cleans up resources used by the EquivalenceDlg class.
     */
    virtual ~EquivalenceDlg();

    // Dialog data
    enum { IDD = IDD_EQUIVALENCEDIALOG }; /**< Dialog resource ID */

protected:
    /**
     * @brief Exchanges data between UI controls and class variables.
     *
     * This function is called during the dialog data exchange process.
     * It handles the transfer of data between UI elements and internal class variables.
     *
     * @param pDX Pointer to the CDataExchange object for the data exchange.
     */
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()

public:
    // UI controls
    ScientificListBox m_ListBoxSource; /**< Source list box for formulas */
    ScientificListBox m_ListBoxDestination1; /**< Destination list box 1 */
    ScientificListBox m_ListBoxDestination2; /**< Destination list box 2 */
    CMFCButton m_ButtonAdd1; /**< Add button for list box 1 */
    CMFCButton m_ButtonRemove1; /**< Remove button for list box 1 */
    CScientificStatic m_StaticDescription; /**< Static description text */
    CMFCButton m_ButtonAddAll1; /**< Add all button for list box 1 */
    CMFCButton m_ButtonRemoveAll1; /**< Remove all button for list box 1 */
    CButton m_ButtonOK; /**< OK button */
    CFont * m_fIndexes; /**< Font for indexes */
    CFont * m_fSymbol; /**< Font for symbols */
    CFont * m_fVariables; /**< Font for variables */
    CFont * m_fIndexesVariables; /**< Font for indexed variables */
    CFont * m_fSymbolVariables; /**< Font for symbol variables */

    /**
     * @brief Handles the click event for the "Check2" button.
     */
    afx_msg void OnBnClickedCheck2();

    /**
     * @brief Sets the formulas for the equivalence dialog.
     *
     * This function is used to pass a vector of all entities that contain formulas.
     *
     * @param all_entities_ Optional pointer to a vector of all entities.
     */
    void  setFormulas(vector <EntityBase *> * all_entities_ = NULL) { allEntities = all_entities_; };

    /**
     * @brief Sets the equivalences for the equivalence dialog.
     *
     * This function is used to pass a vector of all equivalences.
     *
     * @param all_equivalences_ Optional pointer to a vector of all equivalences.
     */
    void  setEquivalences(vector <Equivalence *> * all_equivalences_ = NULL) { allEquivalences = all_equivalences_; };

    /**
     * @brief Initializes the dialog controls and settings.
     *
     * This function is called when the dialog is initialized and sets up the UI components.
     *
     * @return TRUE if initialization is successful, FALSE otherwise.
     */
    virtual BOOL OnInitDialog();

    /**
     * @brief Handles the click event for the "OK" button.
     */
    afx_msg void OnBnClickedOk();

    /**
     * @brief Handles the click event for the "Mfcbutton1" button.
     */
    afx_msg void OnBnClickedMfcbutton1();

    /**
     * @brief Handles the click event for the "Mfcbutton5" button.
     */
    afx_msg void OnBnClickedMfcbutton5();

    /**
     * @brief Handles the click event for the "Mfcbutton2" button.
     */
    afx_msg void OnBnClickedMfcbutton2();

    /**
     * @brief Handles the click event for the "Mfcbutton6" button.
     */
    afx_msg void OnBnClickedMfcbutton6();

    /**
     * @brief Handles the selection change event in the destination list box 1.
     */
    afx_msg void OnSelchangeListdest1();

    /**
     * @brief Shows the candidate formulas for equivalences.
     */
    void ShowCandidates();

    /**
     * @brief Hides the candidate formulas for equivalences.
     */
    void HideCandidates();

    /**
     * @brief Sets the state of equivalences based on user input.
     */
    void SetEquivalenceState();
};
