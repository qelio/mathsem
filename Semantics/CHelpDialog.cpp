#include "stdafx.h"
#include "SemanticsDlg.h"
#include "CHelpDialog.h"

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG4, pParent)
{
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
END_MESSAGE_MAP()