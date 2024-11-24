#pragma once

// CMyEdit

/**
 * @class CMyEdit
 * @brief A custom edit control class that extends CEdit.
 *
 * This class provides custom context menu handling for an edit control.
 * It includes various message handlers for specific actions related to the context menu.
 */
class CMyEdit : public CEdit
{
	DECLARE_DYNAMIC(CMyEdit)

public:
	/**
	 * @brief Default constructor for CMyEdit.
	 */
	CMyEdit();

	/**
	 * @brief Destructor for CMyEdit.
	 */
	virtual ~CMyEdit();

	// Uncomment and implement if needed
	// BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	/** A member variable for managing a popup menu (currently commented out). */
	// CMenu m_PopupMenu;

	// Uncomment and implement if needed
	// virtual void OnInitialUpdate(); // Called first time after construction

protected:
	/**
	 * @brief Message map declaration for CMyEdit.
	 * This macro connects the message handlers to the appropriate Windows messages.
	 */
	DECLARE_MESSAGE_MAP()

public:
	/**
	 * @brief Handles the context menu event for the edit control.
	 * @param pWnd Pointer to the window that sent the message.
	 * @param point The point where the context menu was requested.
	 */
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

	/** Menu item actions for different commands. */
	afx_msg void OnMenuLow();
	afx_msg void OnMenuLeftTag();
	afx_msg void OnMenuRightTag();
	afx_msg void OnMenuHigh();
	afx_msg void OnMenuFirstQwantor();
	afx_msg void OnMenuSecondQwantor();
	afx_msg void OnMenuAnd();
	afx_msg void OnMenuOr();
	afx_msg void OnMenuHave();
	afx_msg void OnMenuLeft();
	afx_msg void OnMenuRight();
	afx_msg void OnMenuNot();
	afx_msg void OnMenuSimilar();
	afx_msg void OnMenuUnion();
	afx_msg void OnMenuCrossing();
	afx_msg void OnMenuEmptyset();
	afx_msg void OnMenuFuzzyInclusion();
};
