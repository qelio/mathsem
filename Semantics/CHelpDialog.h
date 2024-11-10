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

    DECLARE_MESSAGE_MAP()
};