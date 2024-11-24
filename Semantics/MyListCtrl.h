#pragma once
#include "stdafx.h"
#include "afxcmn.h"
#include "Formula.h"
#include "afxwin.h"

/**
 * @class CMyListCtrl
 * @brief Custom list control class that extends CMFCListCtrl.
 *
 * This class customizes the behavior of the list control by overriding functions for
 * cell text color, background color, font, item comparison, and handling list edits.
 * It also provides functionality for saving formulas and modifying cell properties.
 */
class CMyListCtrl : public CMFCListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl)

	/**
	 * @brief Gets the text color of a cell.
	 * @param nRow The row index of the cell.
	 * @param nColum The column index of the cell.
	 * @return The color of the cell's text.
	 */
	virtual COLORREF OnGetCellTextColor(int nRow, int nColum);

	/**
	 * @brief Gets the background color of a cell.
	 * @param nRow The row index of the cell.
	 * @param nColum The column index of the cell.
	 * @return The color of the cell's background.
	 */
	virtual COLORREF OnGetCellBkColor(int nRow, int nColum);

	/**
	 * @brief Gets the font for the cell text.
	 * @param nRow The row index of the cell.
	 * @param nColum The column index of the cell.
	 * @param dwData Additional data for customizing font selection.
	 * @return The font used to display the cell's text.
	 */
	virtual HFONT OnGetCellFont(int nRow, int nColum, DWORD dwData = 0);

	/** The index of the sub-item currently being edited. */
	int subItemEdit;

	/** The index of the item currently being edited. */
	int itemEdit;

	/** Flag indicating whether the list control has been modified. */
	bool m_bIsModified;

	/** Flag indicating whether the cell has color customization enabled. */
	BOOL m_bColor;

	/** Flag indicating whether the cell font can be modified. */
	BOOL m_bModifyFont;

	/** Pointer to a vector of Formula objects. */
	vector <Formula *> * formulas;

	/**
	 * @brief Compares two list items for sorting.
	 * @param lParam1 The first item to compare.
	 * @param lParam2 The second item to compare.
	 * @param iColumn The column index to compare by.
	 * @return A value indicating the comparison result.
	 */
	virtual int OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn);

	/**
	 * @brief Saves the formulas in the list control.
	 */
	void SaveFormulas();

protected:
	/** Pointer to a CEdit control used for editing cells. */
	CEdit * m_edit;

	/** Message map declaration for CMyListCtrl. */
	DECLARE_MESSAGE_MAP()

public:
	/**
	 * @brief Default constructor for CMyListCtrl.
	 */
	CMyListCtrl();

	/**
	 * @brief Destructor for CMyListCtrl.
	 */
	virtual ~CMyListCtrl();

	/**
	 * @brief Handles the item click event in the list control.
	 * @param pNMHDR Pointer to the NMHDR structure that contains the notification message information.
	 * @param pResult A pointer to the result of the message processing.
	 */
	afx_msg virtual void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);

	/**
	 * @brief Pre-translates messages for the list control.
	 * @param pMsg Pointer to the MSG structure that contains the message to be processed.
	 * @return TRUE if the message was processed; otherwise, FALSE.
	 */
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	/**
	 * @brief Sets the formulas for the list control.
	 * @param formulas_ A pointer to a vector of Formula objects.
	 */
	void setFormulas(vector <Formula *> * formulas_) { formulas = formulas_; };
};
