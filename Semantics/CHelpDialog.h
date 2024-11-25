#pragma once
#include "afxdialogex.h"
#include "resource.h"

class CHelpDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CHelpDialog)

public:
    CHelpDialog(CWnd* pParent = nullptr); // стандартный конструктор
    enum { IDD = IDD_DIALOG4 }; // Убедитесь, что это совпадает с идентификатором ресурса

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // поддержка DDX/DDV
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedButtonPrev();
    afx_msg void OnBnClickedButtonNext();

    DECLARE_MESSAGE_MAP()

private:
    int m_nCurrentImage;
    std::vector<int> m_vImageIDs;
    void UpdateImage();
};
