#pragma once
#include "stdafx.h"
#include "afxcmn.h"
#include "Formula.h"
#include "afxwin.h"




class CMyListCtrl : public CMFCListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl)
	virtual COLORREF OnGetCellTextColor(int nRow, int nColum);
	virtual COLORREF OnGetCellBkColor(int nRow, int nColum);
	virtual HFONT OnGetCellFont(int nRow, int nColum, DWORD dwData = 0);

	int subItemEdit;
	int itemEdit;
	bool m_bIsModified;
	BOOL m_bColor;
	BOOL m_bModifyFont;
	vector <Formula *> * formulas;

	virtual int OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn);
	void SaveFormulas();
protected:
	CEdit * m_edit;
	DECLARE_MESSAGE_MAP()

public:
	CMyListCtrl();
	virtual ~CMyListCtrl();
	afx_msg virtual void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void setFormulas( vector <Formula *> * formulas_) { formulas = formulas_; };
};

