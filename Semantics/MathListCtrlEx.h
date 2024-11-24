/**
 * @class CMathListCtrlEx
 * @brief A custom list control with advanced sorting, editing, and item management features.
 *
 * This class extends the CListCtrl and adds functionality for custom item editing,
 * sorting, and management. It provides methods for adding, removing, and sorting
 * items, as well as setting custom editors for specific columns, rows, or cells.
 */
class CMathListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CMathListCtrlEx)

public:
	/**
	 * @brief Default constructor for CMathListCtrlEx.
	 */
	CMathListCtrlEx();

	/**
	 * @brief Destructor for CMathListCtrlEx.
	 */
	virtual ~CMathListCtrlEx();

	/**
	 * @brief Retrieves the data (lParam) associated with a particular item.
	 * @param nItem The index of the item.
	 * @return The item data (lParam).
	 */
	DWORD_PTR GetItemData(int nItem) const;

	/**
	 * @brief Retrieves the internal data associated with a particular item.
	 * @param nItem The index of the item.
	 * @return The item data (lParam).
	 */
	DWORD_PTR GetItemDataInternal(int nItem) const;

	/**
	 * @brief Sets the data (lParam) associated with a particular item.
	 * @param nItem The index of the item.
	 * @param dwData The data to set.
	 * @return TRUE if the data was successfully set.
	 */
	BOOL SetItemData(int nItem, DWORD_PTR dwData);

	/**
	 * @brief Removes a single item from the control.
	 * @param nItem The index of the item to remove.
	 * @return TRUE if the item was successfully removed.
	 */
	BOOL DeleteItem(int nItem);

	/**
	 * @brief Removes all items from the control.
	 * @return TRUE if all items were successfully removed.
	 */
	BOOL DeleteAllItems();

	/**
	 * @brief Finds an item that matches the specified search criteria.
	 * @param pFindInfo The search criteria.
	 * @param nStart The starting index for the search.
	 * @return The index of the found item, or -1 if no item matches.
	 */
	int FindItem(LVFINDINFO* pFindInfo, int nStart = -1) const;

	/**
	 * @brief Sorts the items in the control using a custom comparison function.
	 * @param pfnCompare The custom comparison function.
	 * @param dwData Additional data to pass to the comparison function.
	 * @return TRUE if the sorting was successful.
	 */
	BOOL SortItems(PFNLVCOMPARE pfnCompare, DWORD_PTR dwData);

	/**
	 * @brief Adds an item to the control.
	 * @param pItem The item to insert.
	 * @return The index of the newly inserted item.
	 */
	int InsertItem(const LVITEM* pItem);

	/**
	 * @brief Adds an item to the control with a specified index and label.
	 * @param nItem The index of the item.
	 * @param lpszItem The label of the item.
	 * @return The index of the newly inserted item.
	 */
	int InsertItem(int nItem, LPCTSTR lpszItem);

	/**
	 * @brief Adds an item to the control with a specified index, label, and image index.
	 * @param nItem The index of the item.
	 * @param lpszItem The label of the item.
	 * @param nImage The index of the image associated with the item.
	 * @return The index of the newly inserted item.
	 */
	int InsertItem(int nItem, LPCTSTR lpszItem, int nImage);

	/**
	 * @brief Ensures that a specific subitem is visible.
	 * @param nItem The index of the item.
	 * @param nSubItem The index of the subitem.
	 * @param pRect The rectangle representing the area of the subitem.
	 * @return TRUE if the subitem is successfully made visible.
	 */
	BOOL EnsureSubItemVisible(int nItem, int nSubItem, CRect *pRect = NULL);

	/**
	 * @brief Defines the sorting states for columns.
	 */
	typedef enum Sort
	{
		None = 0, /**< No sorting. */
		Ascending = 1, /**< Ascending order. */
		Descending = 2, /**< Descending order. */
		Auto = 4, /**< Automatic sorting. */
		SortBits = 7 /**< All possible sorting states. */
	} Sort;

	/**
	 * @brief Defines the comparison types for column sorting.
	 */
	typedef enum Comparer
	{
		NotSet, /**< No comparison set. */
		Int, /**< Integer comparison. */
		Double, /**< Double comparison. */
		String, /**< String comparison. */
		StringNumber, /**< String number comparison. */
		StringNoCase, /**< Case-insensitive string comparison. */
		StringNumberNoCase, /**< Case-insensitive string number comparison. */
		Date /**< Date comparison. */
	} Comparer;

protected:
	/**
	 * @brief Static callback function used for item comparison during sorting.
	 * @param lParam1 The first item to compare.
	 * @param lParam2 The second item to compare.
	 * @param lParamSort Sorting data.
	 * @return A value indicating the result of the comparison.
	 */
	static int CALLBACK CompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	/**
	 * @brief Performs the actual comparison of two items.
	 * @param lParam1 The first item to compare.
	 * @param lParam2 The second item to compare.
	 * @param lParamSort Sorting data.
	 * @return A value indicating the result of the comparison.
	 */
	static int Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	/**
	 * @brief Compares two items as integers.
	 * @param pLeftText The first text to compare.
	 * @param pRightText The second text to compare.
	 * @return A value indicating the result of the comparison.
	 */
	static int CompareInt(LPCTSTR pLeftText, LPCTSTR pRightText);

	/**
	 * @brief Compares two items as doubles.
	 * @param pLeftText The first text to compare.
	 * @param pRightText The second text to compare.
	 * @return A value indicating the result of the comparison.
	 */
	static int CompareDouble(LPCTSTR pLeftText, LPCTSTR pRightText);

	/**
	 * @brief Compares two items as strings.
	 * @param pLeftText The first text to compare.
	 * @param pRightText The second text to compare.
	 * @return A value indicating the result of the comparison.
	 */
	static int CompareString(LPCTSTR pLeftText, LPCTSTR pRightText);

	/**
	 * @brief Compares two items as number strings.
	 * @param pLeftText The first text to compare.
	 * @param pRightText The second text to compare.
	 * @return A value indicating the result of the comparison.
	 */
	static int CompareNumberString(LPCTSTR pLeftText, LPCTSTR pRightText);

	/**
	 * @brief Compares two items as case-insensitive number strings.
	 * @param pLeftText The first text to compare.
	 * @param pRightText The second text to compare.
	 * @return A value indicating the result of the comparison.
	 */
	static int CompareNumberStringNoCase(LPCTSTR pLeftText, LPCTSTR pRightText);

	/**
	 * @brief Compares two items as case-insensitive strings.
	 * @param pLeftText The first text to compare.
	 * @param pRightText The second text to compare.
	 * @return A value indicating the result of the comparison.
	 */
	static int CompareStringNoCase(LPCTSTR pLeftText, LPCTSTR pRightText);

	/**
	 * @brief Compares two items as dates.
	 * @param pLeftText The first text to compare.
	 * @param pRightText The second text to compare.
	 * @return A value indicating the result of the comparison.
	 */
	static int CompareDate(LPCTSTR pLeftText, LPCTSTR pRightText);

	/** Critical section for thread-safety. */
	CCriticalSection m_oLock;

protected:
	DECLARE_MESSAGE_MAP()

	/**
	 * @brief The editor information structure.
	 */
	typedef struct EditorInfo
	{
		PFNEDITORCALLBACK m_pfnInitEditor; /**< Function to initialize the editor. */
		PFNEDITORCALLBACK m_pfnEndEditor; /**< Function to end the editor. */
		CWnd *m_pWnd; /**< The window associated with the editor. */
		BOOL m_bReadOnly; /**< Whether the editor is read-only. */
		EditorInfo(); /**< Default constructor. */
		EditorInfo(PFNEDITORCALLBACK pfnInitEditor, PFNEDITORCALLBACK pfnEndEditor, CWnd *pWnd = NULL); /**< Parameterized constructor. */
		inline BOOL IsSet(){return (m_pfnInitEditor || m_pWnd);} /**< Checks if the editor is set. */
	} EditorInfo;

	/** Structure representing cell information. */
	typedef struct CellInfo
	{
		EditorInfo m_eiEditor; /**< The editor for the cell. */
		COLORREF m_clrBack; /**< The background color of the cell. */
		COLORREF m_clrText; /**< The text color of the cell. */
		DWORD_PTR m_dwData; /**< The data associated with the cell. */
		BOOL m_bReadOnly; /**< Whether the cell is read-only. */
	} CellInfo;

	/** Array to store cell information for each item and subitem. */
	CArray<CellInfo> m_arrCellInfo;
};
