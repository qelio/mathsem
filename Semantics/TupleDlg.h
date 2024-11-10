#pragma once
#include "afxwin.h"
#include "Formula.h"


// ���������� ���� TupleDlg

class CTupleDlg : public CDialog
{
	vector <EntityBase *>  *all_entities;

	DECLARE_DYNAMIC(CTupleDlg)
	BOOL OnInitDialog();
public:
	CTupleDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CTupleDlg();

// ������ ����������� ����
	enum { IDD = IDD_TUPLEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CComboBox combo1;
	CComboBox combo2;
	afx_msg void OnBnClickedOk();
	CComboBox combo3;
	CEdit m_lowindex1;
	CEdit m_lowindex2;
	CEdit m_lowindex3;
	void SetEntities(vector <EntityBase *> *ent) {all_entities = ent; };
};
