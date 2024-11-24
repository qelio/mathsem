//  Author: Tatarintsev V.V., tatarintsev_vv@mail.ru, 2013-2017
#pragma once

#include "afxwin.h"
#include "Formula.h"
#include "ScientificListBox.h"

/**
 * @class ReplaceVariableDialog
 * @brief A dialog box for replacing variables in a formula.
 *
 * This class provides functionality for managing and replacing variables
 * in a formula. It includes list boxes for displaying variables and free variables,
 * combo boxes for selecting names, and methods to handle variable replacement logic.
 */
class ReplaceVariableDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ReplaceVariableDialog)

    /**
     * @brief Pointer to a list of entities that store variable data.
     *
     * This list is used to populate the dialog with variables that can be replaced.
     */
	vector <EntityBase *> * entities;

public:
    /**
     * @brief Constructor for the ReplaceVariableDialog class.
     *
     * Initializes the dialog, setting the parent window to `pParent` if specified.
     *
     * @param pParent The parent window for the dialog (default is NULL).
     */
	ReplaceVariableDialog(CWnd* pParent = NULL);

    /**
     * @brief Destructor for the ReplaceVariableDialog class.
     *
     * Cleans up any resources used by the dialog.
     */
	virtual ~ReplaceVariableDialog();

    /** Dialog Data */
	enum { IDD = IDD_REPLACEVARIABLE };

protected:
    /**
     * @brief Exchanges data between the dialog and the controls.
     *
     * This method is used to transfer data to and from the controls in the dialog box.
     *
     * @param pDX The data exchange object.
     */
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
    /**
     * @brief Called when the OK button is clicked.
     *
     * This method handles the logic to finalize the replacement of variables
     * when the user clicks the "OK" button.
     */
	afx_msg void OnBnClickedOk();

    /** Font for indexes */
	CFont * m_fIndexes;

    /** Font for symbols (using the Symbol font) */
	CFont * m_fSymbol;

    /** Edit control for entering the index */
	CEdit m_editIndex;

    /** List box for displaying scientific items */
	ScientificListBox m_list;

    /** List box for displaying free variables */
	ScientificListBox m_listFreeVariables;

    /** List box for displaying existing variables */
	ScientificListBox m_listVariables;

    /** Combo box for selecting the name of the variable */
	CComboBox m_comboName;

    /**
     * @brief Initializes the dialog.
     *
     * This method is called when the dialog is initialized to set up the initial state
     * of controls such as list boxes and combo boxes.
     *
     * @return TRUE if initialization is successful, otherwise FALSE.
     */
	virtual BOOL OnInitDialog();

    /**
     * @brief Sets the list of entities for the dialog.
     *
     * This method sets the list of all available entities, which can be used to populate
     * the dialog with the appropriate data for variable replacement.
     *
     * @param all_entities The list of entities to set (default is NULL).
     */
	void setEntities(vector <EntityBase *> * all_entities = NULL) {entities = all_entities; };

    /**
     * @brief Displays the list of free variables.
     *
     * This method populates the list of free variables and makes it visible in the dialog.
     */
	void ShowFreeVariables();

    /**
     * @brief Hides the list of free variables.
     *
     * This method hides the list of free variables from the dialog.
     */
	void HideFreeVariables();

    /**
     * @brief Displays the list of existing variables.
     *
     * This method populates the list of variables and makes it visible in the dialog.
     */
	void ShowVariables();

    /**
     * @brief Hides the list of variables.
     *
     * This method hides the list of variables from the dialog.
     */
	void HideVariables();

    /**
     * @brief Resets the names in the combo box.
     *
     * This method updates the combo box with names based on the given symbol.
     * It ensures that the displayed names are synchronized with the selected symbol.
     *
     * @param symbol The symbol used to filter or reset the names in the combo box.
     */
	void ResetComboNames(TCHAR symbol);

    /** Data for radio buttons */
	int m_dataRadio;

    /** Vector of new entity variables */
	vector <EntityVariable *> pev_new;

    /** Button for confirming the variable replacement */
	CButton m_buttonOK;

    /**
     * @brief Called when the first set list selection changes.
     *
     * This method handles changes to the selection in the first set list.
     */
	afx_msg void OnSelchangeSetlist1();

    /**
     * @brief Called when the second set list selection changes.
     *
     * This method handles changes to the selection in the second set list.
     */
	afx_msg void OnSelchangeSetlist2();

    /**
     * @brief Called when the input text radio button is clicked.
     *
     * This method handles logic when the "input text" radio button is selected.
     */
	afx_msg void OnBnClickedRadioinputtext();

    /**
     * @brief Called when the "select variable" radio button is clicked.
     *
     * This method handles logic when the "select variable" radio button is selected.
     */
	afx_msg void OnBnClickedRadioselectvariable();
};
