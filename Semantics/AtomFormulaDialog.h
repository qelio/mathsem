// Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
#pragma once

#include "ScientificStatic.h"
#include "afxwin.h"

/*!
 * \class CAtomFormulaDialog
 * \brief Dialog window for working with atomic formulas.
 *
 * This class provides an interface for editing atomic formulas using various controls,
 * including labels, input fields, and combo boxes.
 */
class CAtomFormulaDialog : public CDialog
{
	DECLARE_DYNAMIC(CAtomFormulaDialog)

	/*!
	 * \brief Initializes the dialog.
	 *
	 * This function is called when the dialog is initialized. It is used to perform
	 * any setup or configuration for the dialog controls.
	 * \return TRUE if initialization is successful, FALSE otherwise.
	 */
	BOOL OnInitDialog();

public:
	/*!
	 * \brief Constructor for CAtomFormulaDialog.
	 *
	 * \param pParent The parent window for the dialog (default is NULL).
	 */
	CAtomFormulaDialog(CWnd* pParent = NULL);

	/*!
	 * \brief Destructor for CAtomFormulaDialog.
	 */
	virtual ~CAtomFormulaDialog();

	// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	/*!
	 * \brief Handles the data exchange between controls and variables.
	 *
	 * This function binds the dialog controls to class member variables.
	 * \param pDX Data exchange object.
	 */
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	// Character buffer for the first input field
	TCHAR * tbuf1;

	// Character buffer for the second input field
	TCHAR * tbuf2;

	// Character buffer for the index of the first input field
	TCHAR * tbuf_index1;

	// Character buffer for the index of the second input field
	TCHAR * tbuf_index2;

	// Static label for displaying description
	CScientificStatic m_lblDescription;

	/*!
	 * \brief Handler for the "OK" button click event.
	 *
	 * This function is called when the "OK" button is clicked in the dialog.
	 */
	afx_msg void OnBnClickedOk();

	// Font used for displaying indices
	CFont * m_fIndexes;

	// Font used for displaying symbols
	CFont * m_fSymbol;

	// Edit control for the first index input
	CEdit m_index1;

	// Edit control for the second index input
	CEdit m_index2;

	// Combo box for selecting the first option
	CComboBox m_combo1;

	// Combo box for selecting the second option
	CComboBox m_combo2;
};
