#pragma once
#include "afxdialogex.h"
#include "resource.h"

class CHelpDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CHelpDialog)

public:
    CHelpDialog(CWnd* pParent = nullptr); // ����������� �����������
    enum { IDD = IDD_DIALOG4 }; // ���������, ��� ��� ��������� � ��������������� �������

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // ��������� DDX/DDV
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedButtonPrev();
    afx_msg void OnBnClickedButtonNext();

    DECLARE_MESSAGE_MAP()

private:
    int m_nCurrentImage;
    std::vector<int> m_vImageIDs;
    void UpdateImage();
};
