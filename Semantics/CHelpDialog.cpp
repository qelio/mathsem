#include "stdafx.h"
#include "SemanticsDlg.h"
#include "CHelpDialog.h"

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG4, pParent)
{
    // ��������������� ������ ��������������� �����������
    m_vImageIDs = {
        IDB_BITMAP1,
        IDB_BITMAP2,
        IDB_BITMAP3,
        IDB_BITMAP4,
        IDB_BITMAP5,
        IDB_BITMAP6,
        IDB_BITMAP7,
        IDB_BITMAP8
    };
    m_nCurrentImage = 0;
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
ON_BN_CLICKED(IDC_BUTTON_PREV, &CHelpDialog::OnBnClickedButtonPrev)
ON_BN_CLICKED(IDC_BUTTON_NEXT, &CHelpDialog::OnBnClickedButtonNext)
END_MESSAGE_MAP()

BOOL CHelpDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // ��������� ������ �����������
    UpdateImage();

    return TRUE;
}

void CHelpDialog::OnBnClickedButtonPrev()
{
    // ������������ �� ���������� �����������
    if (m_nCurrentImage > 0) {
        m_nCurrentImage--;
        UpdateImage();
    }
}

void CHelpDialog::OnBnClickedButtonNext()
{
    // ������������ �� ��������� �����������
    if (m_nCurrentImage < m_vImageIDs.size() - 1) {
        m_nCurrentImage++;
        UpdateImage();
    }
}

void CHelpDialog::UpdateImage()
{
    CStatic *pPictureControl = (CStatic *) GetDlgItem(IDC_PICTURE_CONTROL);
    if (pPictureControl && m_nCurrentImage >= 0 && m_nCurrentImage < m_vImageIDs.size()) {
        // ��������� ����������� �� ��������
        HBITMAP hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(m_vImageIDs[m_nCurrentImage]));
        if (hBitmap) {
            // ���������� ����������� � Picture Control
            pPictureControl->SetBitmap(hBitmap);
        }
    }
}
