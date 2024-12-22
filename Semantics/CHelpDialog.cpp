#include "stdafx.h"
#include "SemanticsDlg.h"
#include "CHelpDialog.h"

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG4, pParent)
{
    // Инициализируйте массив идентификаторов изображений
    m_vImageIDs = {
        IDB_BITMAP9,
        IDB_BITMAP10,
        IDB_BITMAP11,
        IDB_BITMAP12,
        IDB_BITMAP13,
        IDB_BITMAP14,
        IDB_BITMAP15,
        IDB_BITMAP16,
        IDB_BITMAP17
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

    // Загрузите первое изображение
    UpdateImage();

    return TRUE;
}

void CHelpDialog::OnBnClickedButtonPrev()
{
    // Переключение на предыдущее изображение
    if (m_nCurrentImage > 0) {
        m_nCurrentImage--;
        UpdateImage();
    }
}

void CHelpDialog::OnBnClickedButtonNext()
{
    // Переключение на следующее изображение
    if (m_nCurrentImage < m_vImageIDs.size() - 1) {
        m_nCurrentImage++;
        UpdateImage();
    }
}

void CHelpDialog::UpdateImage()
{
    CStatic *pPictureControl = (CStatic *) GetDlgItem(IDC_PICTURE_CONTROL);
    if (pPictureControl && m_nCurrentImage >= 0 && m_nCurrentImage < m_vImageIDs.size()) {
        // Загрузите изображение из ресурсов
        HBITMAP hBitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(m_vImageIDs[m_nCurrentImage]));
        if (hBitmap) {
            // Установите изображение в Picture Control
            pPictureControl->SetBitmap(hBitmap);
        }
    }
}
