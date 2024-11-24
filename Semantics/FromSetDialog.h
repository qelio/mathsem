#pragma once
#include "afxwin.h"
#include "afxbutton.h"
#include "ScientificListBox.h"
#include "Formula.h"
//#include "ScientificStatic.h"
//#include "afxcmn.h"

/**
 * @class FromSetDialog
 * @brief Dialog for managing and selecting sets of formulas and entities.
 *
 * This dialog allows users to view and select formula sets and entities from
 * the provided lists. It is typically used in applications that deal with
 * mathematical formulas or entities related to formula sets.
 */
class FromSetDialog : public CDialogEx
{
    DECLARE_DYNAMIC(FromSetDialog)

    /**
     * @brief Vector of FormulaSet objects that the dialog will display or interact with.
     */
    vector <FormulaSet *> * sets;

    /**
     * @brief Vector of all available EntityBase objects for selection in the dialog.
     */
    vector <EntityBase *> * allEntities;

public:
    /**
     * @brief Constructor for the FromSetDialog class.
     * @param pParent Pointer to the parent window (default is NULL).
     */
    FromSetDialog(CWnd* pParent = NULL);

    /**
     * @brief Destructor for the FromSetDialog class.
     */
    virtual ~FromSetDialog();

    /**
     * @brief Dialog Data Exchange function for initializing the dialog.
     * @param pDX Data exchange object.
     */
    virtual void DoDataExchange(CDataExchange* pDX);

    /**
     * @brief Initializes the dialog. This function is automatically called when
     *        the dialog is created.
     * @return TRUE if initialization is successful, FALSE otherwise.
     */
    virtual BOOL OnInitDialog();

    /**
     * @brief Handler for list box selection change. This function is called
     *        when the selection in the list box changes.
     */
    afx_msg void OnLbnSelchangeSetlist1();

    /**
     * @brief Button OK click handler. This function is called when the OK button
     *        is clicked, typically to confirm the selection and close the dialog.
     */
    afx_msg void OnBnClickedOk();

    /**
     * @brief Sets the vector of EntityBase objects to be used in the dialog.
     * @param all_entities_ Pointer to a vector of EntityBase objects.
     */
    void setEntities(vector <EntityBase *> * all_entities_ = NULL) { allEntities = all_entities_; };

protected:
    /**
     * @brief Message map for handling Windows messages related to the dialog.
     */
    DECLARE_MESSAGE_MAP()

    /**
     * @brief List box control for displaying the available sets or entities.
     */
    ScientificListBox m_ListBoxSource;

    /**
     * @brief OK button control for confirming the selection.
     */
    CButton m_ButtonOK;
};
