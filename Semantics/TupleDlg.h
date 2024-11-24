#pragma once
#include "afxwin.h"
#include "Formula.h"

/**
 * @class CTupleDlg
 * @brief A dialog class for handling tuple selection and display.
 *
 * This dialog allows the user to select values for tuples and manage the corresponding entities. It includes combo boxes for tuple selection and edit controls for displaying and modifying values.
 */
class CTupleDlg : public CDialog
{
	/**
	 * @var all_entities
	 * @brief A pointer to a vector of EntityBase pointers.
	 * Stores all the entities associated with the dialog for tuple selection.
	 */
	vector <EntityBase *>  *all_entities;

	DECLARE_DYNAMIC(CTupleDlg)

	/**
	 * @brief Initializes the dialog.
	 * This function is called when the dialog is first created and is responsible for setting up any necessary data.
	 * @return BOOL Returns TRUE if the dialog was initialized successfully.
	 */
	BOOL OnInitDialog();

public:
	/**
	 * @brief Default constructor for the CTupleDlg class.
	 * Initializes the dialog without any data.
	 * @param pParent A pointer to the parent window, default is NULL.
	 */
	CTupleDlg(CWnd* pParent = NULL);

	/**
	 * @brief Destructor for the CTupleDlg class.
	 * Cleans up any resources used by the dialog.
	 */
	virtual ~CTupleDlg();

	/**
	 * @enum IDD
	 * @brief The resource ID for this dialog.
	 */
	enum { IDD = IDD_TUPLEDIALOG };

protected:
	/**
	 * @brief Handles data exchange between controls and variables.
	 * This function ensures that the data entered into the controls is properly transferred to the class variables.
	 * @param pDX Pointer to the CDataExchange object used to exchange data.
	 */
	virtual void DoDataExchange(CDataExchange* pDX);

	/**
	 * @brief Message map for handling dialog messages.
	 */
	DECLARE_MESSAGE_MAP()

public:
	/**
	 * @var combo1
	 * @brief A combo box for selecting the first value of the tuple.
	 */
	CComboBox combo1;

	/**
	 * @var combo2
	 * @brief A combo box for selecting the second value of the tuple.
	 */
	CComboBox combo2;

	/**
	 * @brief Handles the OK button click event.
	 * This function is called when the user clicks the "OK" button in the dialog.
	 */
	afx_msg void OnBnClickedOk();

	/**
	 * @var combo3
	 * @brief A combo box for selecting the third value of the tuple.
	 */
	CComboBox combo3;

	/**
	 * @var m_lowindex1
	 * @brief An edit control for entering the first index value.
	 */
	CEdit m_lowindex1;

	/**
	 * @var m_lowindex2
	 * @brief An edit control for entering the second index value.
	 */
	CEdit m_lowindex2;

	/**
	 * @var m_lowindex3
	 * @brief An edit control for entering the third index value.
	 */
	CEdit m_lowindex3;

	/**
	 * @brief Sets the vector of entities for the dialog.
	 * This function sets the pointer to the list of entities that will be used in the dialog.
	 * @param ent A pointer to the vector of EntityBase objects.
	 */
	void SetEntities(vector <EntityBase *> *ent) {all_entities = ent; };
};
