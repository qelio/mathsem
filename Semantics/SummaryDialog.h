/**
 * @class SummaryDialog
 * @brief Dialog class that displays a summary of formulas and allows interaction with them.
 *
 * This dialog handles the display of formulas and provides options for modifying and managing them.
 */
class SummaryDialog : public CDialog
{
	DECLARE_DYNAMIC(SummaryDialog)

	/**
	 * @brief Initializes the dialog.
	 * This function is called when the dialog is first created and is responsible for setting up any necessary data.
	 * @return BOOL Returns TRUE if the dialog was initialized successfully.
	 */
	BOOL OnInitDialog();

	/**
	 * @var entities
	 * @brief A pointer to a vector of EntityBase pointers.
	 * Used to store the list of entities associated with the formulas.
	 */
	vector <EntityBase *> * entities;

	/**
	 * @brief Checks if the redefinition of an entity is correct.
	 * This function validates if a new text definition can replace the old one for a given entity.
	 * @param pbase A pointer to the EntityBase object to be redefined.
	 * @param new_text A string containing the new definition for the entity.
	 * @return bool Returns true if the redefinition is valid, otherwise false.
	 */
	bool IfCorrectRedefinition(EntityBase * pbase, tstring & new_text);

public:
	/**
	 * @brief Default constructor for the SummaryDialog class.
	 * Initializes the dialog without any data.
	 * @param pParent A pointer to the parent window, default is NULL.
	 */
	SummaryDialog(CWnd* pParent = NULL);

	/**
	 * @brief Destructor for the SummaryDialog class.
	 * Cleans up any resources used by the dialog.
	 */
	virtual ~SummaryDialog();

	/**
	 * @enum IDD
	 * @brief The resource ID for this dialog.
	 */
	enum { IDD = IDD_SUMMARYDIALOG };

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
	 * @var m_list
	 * @brief A custom list control that displays mathematical formulas.
	 */
	CMathListCtrlEx m_list;

	/**
	 * @var m_edit
	 * @brief A custom edit control used for entering and modifying formulas.
	 */
	CMyEdit m_edit;

	/**
	 * @brief Sets the formulas to be displayed in the dialog.
	 * This function populates the list of formulas based on the given entities.
	 * @param all_entities A pointer to a vector of EntityBase objects, default is NULL.
	 */
	void setFormulas(vector <EntityBase *> * all_entities = NULL);

	/**
	 * @brief Pre-translates messages before they are dispatched to the control.
	 * This function processes key presses and other input before they reach the controls.
	 * @param pMsg Pointer to the MSG object containing message details.
	 * @return BOOL Returns TRUE if the message is processed, otherwise FALSE.
	 */
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	/**
	 * @brief Handles the cancel button press in the dialog.
	 * This function is called when the user clicks the "Cancel" button.
	 */
	virtual void OnCancel();

	/**
	 * @brief Handles the OK button press in the dialog.
	 * This function is called when the user clicks the "OK" button.
	 */
	// virtual void OnOK();

	/**
	 * @brief Handles the measurement of list items for the control.
	 * This function adjusts the size of list items based on their content.
	 * @param nIDCtl The control ID.
	 * @param lpMeasureItemStruct Pointer to the MEASUREITEMSTRUCT structure containing item size details.
	 */
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	/**
	 * @brief Saves the formulas and exits the dialog.
	 * This function saves any changes made to the formulas and closes the dialog.
	 */
	void SaveAndExit();

	/**
	 * @brief Handles the OK button click event.
	 * This function is called when the user clicks the "OK" button in the dialog.
	 */
	afx_msg void OnBnClickedOk();

	/**
	 * @brief Handles the redefinition of a formula.
	 * This function is triggered when the user attempts to redefine a formula.
	 */
	afx_msg void OnBnClickedPereopisanie();

	/**
	 * @brief Handles changes to the summary list control.
	 * This function is called when an item in the summary list is changed.
	 * @param pNMHDR Pointer to the NMHDR structure containing details about the notification.
	 * @param pResult Pointer to the result of the notification.
	 */
	afx_msg void OnLvnOdstatechangedSummarylist(NMHDR *pNMHDR, LRESULT *pResult);

	/**
	 * @var m_RedefineBtn
	 * @brief A button control that triggers the redefinition of formulas.
	 */
	CButton m_RedefineBtn;

	/**
	 * @brief Handles the right-click event in the dialog.
	 * This function is triggered when the user right-clicks inside the dialog.
	 * @param nFlags Flags specifying the state of the mouse buttons and keys.
	 * @param point The cursor position when the right-click occurred.
	 */
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

/**
 * @brief Reverses the definition of formulas between two entities.
 * This function swaps the definitions of two entities in the given range.
 * @param temp_entities A pointer to a temporary vector of EntityBase objects.
 * @param entities A pointer to the vector of EntityBase objects containing the entities to be swapped.
 * @param first The index of the first entity to swap.
 * @param last The index of the last entity to swap.
 * @param psd A pointer to the SummaryDialog object, default is NULL.
 */
void ReverseDefinition(vector <EntityBase *> * temp_entities, vector <EntityBase *> * entities, int first, int last, SummaryDialog *psd = nullptr);
