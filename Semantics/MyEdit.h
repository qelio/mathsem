#pragma once


// CMyEdit

class CMyEdit : public CEdit
{
	DECLARE_DYNAMIC(CMyEdit)

public:
	CMyEdit();
	virtual ~CMyEdit();

//    BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
 
//    CMenu m_PopupMenu;

//    virtual void OnInitialUpdate(); // called first time after construct
 
  


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
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


