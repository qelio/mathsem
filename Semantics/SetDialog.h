/**
 * @class SetDialog
 * @brief This class represents the dialog for setting operations on sets.
 *
 * It is associated with the IDD_SETDIALOG resource and allows users to perform operations related to sets,
 * such as displaying and managing sets and variables.
 * The class also provides functionality for interacting with set elements, like checking set memberships or
 * creating subsets.
 */
class SetDialog : public CDialogEx
{
	DECLARE_DYNAMIC(SetDialog)

    /**
     * @var entities
     * @brief A pointer to a vector of EntityBase objects, used for manipulating the data associated with sets.
     * This is passed from other parts of the application to provide the relevant entities for the dialog operations.
     */
	vector <EntityBase *> * entities;

public:
	/**
	 * @brief Default constructor for the SetDialog class.
	 * @param pParent The parent window for the dialog (optional).
	 */
	SetDialog(CWnd* pParent = NULL);

	/**
	 * @brief Destructor for the SetDialog class.
	 */
	virtual ~SetDialog();

	/** @enum IDD
	 * @brief The ID for this dialog's resource, used by the dialog system.
	 */
	enum { IDD = IDD_SETDIALOG };

protected:
	/**
	 * @brief Exchanges data between the dialog and the associated variables.
	 * @param pDX Pointer to the data exchange object.
	 */
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	/**
	 * @var m_list
	 * @brief A list box control for displaying a list of elements in a set.
	 */
	ScientificListBox m_list;

	/**
	 * @var m_fIndexes
	 * @brief Font object for indexing the list elements.
	 */
	CFont * m_fIndexes;

	/**
	 * @var m_fSymbol
	 * @brief Font object for displaying symbols, typically from the Symbol font.
	 */
	CFont * m_fSymbol;

	/**
	 * @var m_listVariables
	 * @brief A list box control for displaying a list of free variables associated with sets.
	 */
	ScientificListBox m_listVariables;

	/**
	 * @var m_buttonOK
	 * @brief The "OK" button control to confirm changes or selections in the dialog.
	 */
	CButton m_buttonOK;

	/**
	 * @brief Called when the "OK" button is clicked.
	 */
	afx_msg void OnBnClickedOk();

	/**
	 * @brief Initializes the dialog and prepares it for interaction with the user.
	 * @return TRUE if initialization is successful, otherwise FALSE.
	 */
	virtual BOOL OnInitDialog();

	/**
	 * @brief Sets the entities used for the dialog operations.
	 * @param all_entities A pointer to a vector of EntityBase objects to be used in the dialog. Default is NULL.
	 */
	void setEntities(vector <EntityBase *> * all_entities = NULL) { entities = all_entities; };

	/**
	 * @brief Displays the list of free variables in the m_listVariables control.
	 */
	void ShowFreeVariables();

	/**
	 * @brief Hides the list of free variables from the m_listVariables control.
	 */
	void HideFreeVariables();

	/**
	 * @brief Called when the selection changes in the first set list.
	 */
	afx_msg void OnSelchangeSetlist1();

	/**
	 * @var m_CheckBelonging
	 * @brief A checkbox that checks if an element belongs to a set.
	 */
	CButton m_CheckBelonging;

	/**
	 * @var m_CheckSubSet
	 * @brief A checkbox that checks if a set is a subset of another.
	 */
	CButton m_CheckSubSet;

	/**
	 * @brief Called when the "Build Subset" button is clicked.
	 */
	afx_msg void OnClickedBuildsubset();

	/**
	 * @var m_ComboSubSet
	 * @brief A combo box for selecting a subset.
	 */
	CComboBox m_ComboSubSet;

	/**
	 * @var m_IndexSubSet
	 * @brief A text box for entering the index of the subset.
	 */
	CEdit m_IndexSubSet;

	/**
	 * @var m_comboSet
	 * @brief A combo box for selecting a set.
	 */
	CComboBox m_comboSet;

	/**
	 * @var m_indexSet
	 * @brief A text box for entering the index of the set.
	 */
	CEdit m_indexSet;

	/**
	 * @var m_label
	 * @brief A static label for displaying information about the set.
	 */
	CScientificStatic m_label;

	/**
	 * @var m_level
	 * @brief A static label for displaying the level of the set.
	 */
	CScientificStatic m_level;

	/**
	 * @brief Called when the selection changes in the second set list.
	 */
	afx_msg void OnSelchangeSetlist2();

	/**
	 * @brief Checks the user's selection to validate the set operation.
	 */
	void CheckSelection();

	/**
	 * @brief Called when the selected set in the combo box changes.
	 */
	afx_msg void OnSelchangeSetcombo();

	/**
	 * @brief Called when the set index changes.
	 */
	afx_msg void OnChangeSetindex();
};
