#pragma once
#include "MsgHook.h"
#include <Afxmt.h>

// CListCtrlEx
typedef BOOL (*PFNEDITORCALLBACK)(CWnd** pWnd, int nRow, int nColumn, CString& strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate);

/**
 * @class CListCtrlEx
 * @brief Extended version of CListCtrl that supports advanced features like custom sorting, editors, and cell/item data handling.
 *
 * This class extends the functionality of a standard list control by adding support for custom sorting,
 * editing of cells, and handling of item-specific data. It allows the user to define editors, sort columns,
 * and customize the appearance of individual rows and cells.
 */
class CListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlEx)

public:
    /**
     * @brief Default constructor.
     */
	CListCtrlEx();

    /**
     * @brief Destructor.
     */
	virtual ~CListCtrlEx();

    /**
     * @brief Retrieves the data (lParam) associated with a particular item.
     * @param nItem The index of the item to retrieve data for.
     * @return The data (lParam) associated with the item.
     */
	DWORD_PTR GetItemData(int nItem) const;

    /**
     * @brief Retrieves the internal data (lParam) associated with a particular item.
     * @param nItem The index of the item to retrieve data for.
     * @return The internal data (lParam) associated with the item.
     */
	DWORD_PTR GetItemDataInternal(int nItem) const;

    /**
     * @brief Sets the data (lParam) associated with a particular item.
     * @param nItem The index of the item to set data for.
     * @param dwData The data to associate with the item.
     * @return TRUE if the operation succeeded, FALSE otherwise.
     */
	BOOL SetItemData(int nItem, DWORD_PTR dwData);

    /**
     * @brief Removes a single item from the control.
     * @param nItem The index of the item to remove.
     * @return TRUE if the item was successfully removed, FALSE otherwise.
     */
	BOOL DeleteItem(int nItem);

    /**
     * @brief Removes all items from the control.
     * @return TRUE if all items were successfully removed, FALSE otherwise.
     */
	BOOL DeleteAllItems();

    /**
     * @brief Finds an item in the control matching the specified criteria.
     * @param pFindInfo A pointer to a structure containing the search criteria.
     * @param nStart The starting index for the search.
     * @return The index of the found item, or -1 if not found.
     */
	int FindItem(LVFINDINFO* pFindInfo, int nStart = -1) const;

    /**
     * @brief Sorts items in the control using a custom comparison function.
     * @param pfnCompare A pointer to the comparison function.
     * @param dwData Additional data to pass to the comparison function.
     * @return TRUE if the sorting succeeded, FALSE otherwise.
     */
	BOOL SortItems(PFNLVCOMPARE pfnCompare, DWORD_PTR dwData);

    /**
     * @brief Inserts a new item into the control.
     * @param pItem A pointer to the LVITEM structure containing item details.
     * @return The index of the inserted item, or -1 if the insertion failed.
     */
	int InsertItem(const LVITEM* pItem);

    /**
     * @brief Inserts a new item with text into the control.
     * @param nItem The index at which to insert the item.
     * @param lpszItem The text for the item.
     * @return The index of the inserted item, or -1 if the insertion failed.
     */
	int InsertItem(int nItem, LPCTSTR lpszItem);

    /**
     * @brief Inserts a new item with text and an image into the control.
     * @param nItem The index at which to insert the item.
     * @param lpszItem The text for the item.
     * @param nImage The index of the image to associate with the item.
     * @return The index of the inserted item, or -1 if the insertion failed.
     */
	int InsertItem(int nItem, LPCTSTR lpszItem, int nImage);

    /**
     * @brief Ensures a subitem is visible in the list.
     * @param nItem The index of the item.
     * @param nSubItem The index of the subitem.
     * @param pRect Optional pointer to a CRect object to receive the item's rectangle.
     * @return TRUE if the subitem is visible, FALSE otherwise.
     */
	BOOL EnsureSubItemVisible(int nItem, int nSubItem, CRect *pRect = NULL);

    /**
     * @brief Enumeration for sort order options.
     */
	typedef enum Sort
	{
		None = 0,          ///< No sorting applied.
		Ascending = 1,     ///< Ascending order.
		Descending = 2,    ///< Descending order.
		Auto = 4,          ///< Automatic sorting.
		SortBits = 7       ///< Mask for sorting options.
	} Sort;

    /**
     * @brief Enumeration for column comparison types.
     */
	typedef enum Comparer
	{
		NotSet,            ///< No comparison set.
		Int,               ///< Integer comparison.
		Double,            ///< Double comparison.
		String,            ///< String comparison.
		StringNumber,      ///< String with numeric comparison.
		StringNoCase,      ///< Case-insensitive string comparison.
		StringNumberNoCase, ///< Case-insensitive string with numeric comparison.
		Date               ///< Date comparison.
	} Comparer;

protected:
    /**
     * @brief Static comparison procedure used by SortItems.
     * @param lParam1 First item data.
     * @param lParam2 Second item data.
     * @param lParamSort Sorting parameters.
     * @return The result of the comparison.
     */
	static int CALLBACK CompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

    /**
     * @brief Compares two items using the specified comparison logic.
     * @param lParam1 First item data.
     * @param lParam2 Second item data.
     * @param lParamSort Sorting parameters.
     * @return The result of the comparison.
     */
	static int Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

    /**
     * @brief Compares two integer values as strings.
     * @param pLeftText The left item text.
     * @param pRightText The right item text.
     * @return The result of the comparison.
     */
	static int CompareInt(LPCTSTR pLeftText, LPCTSTR pRightText);

    /**
     * @brief Compares two double values as strings.
     * @param pLeftText The left item text.
     * @param pRightText The right item text.
     * @return The result of the comparison.
     */
	static int CompareDouble(LPCTSTR pLeftText, LPCTSTR pRightText);

    /**
     * @brief Compares two strings.
     * @param pLeftText The left item text.
     * @param pRightText The right item text.
     * @return The result of the comparison.
     */
	static int CompareString(LPCTSTR pLeftText, LPCTSTR pRightText);

    /**
     * @brief Compares two numeric strings.
     * @param pLeftText The left item text.
     * @param pRightText The right item text.
     * @return The result of the comparison.
     */
	static int CompareNumberString(LPCTSTR pLeftText, LPCTSTR pRightText);

    /**
     * @brief Compares two numeric strings case-insensitively.
     * @param pLeftText The left item text.
     * @param pRightText The right item text.
     * @return The result of the comparison.
     */
	static int CompareNumberStringNoCase(LPCTSTR pLeftText, LPCTSTR pRightText);

    /**
     * @brief Compares two strings case-insensitively.
     * @param pLeftText The left item text.
     * @param pRightText The right item text.
     * @return The result of the comparison.
     */
	static int CompareStringNoCase(LPCTSTR pLeftText, LPCTSTR pRightText);

    /**
     * @brief Compares two date values as strings.
     * @param pLeftText The left item text.
     * @param pRightText The right item text.
     * @return The result of the comparison.
     */
	static int CompareDate(LPCTSTR pLeftText, LPCTSTR pRightText);

    /**
     * @brief Critical section object for thread synchronization.
     */
	CCriticalSection m_oLock;

protected:
	DECLARE_MESSAGE_MAP()

    // Other private/protected member variables and methods omitted for brevity

}; // End of class CListCtrlEx
