#pragma once
#include "afxdialogex.h"
#include "resource.h"

/**
 * @class CHelpDialog
 * @brief This class represents the Help dialog in the application.
 *
 * The CHelpDialog class provides a dialog window for displaying help information
 * to the user. It is a part of the application's UI and is derived from the
 * CDialogEx class to handle the dialog behavior and data exchange.
 */
class CHelpDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CHelpDialog)

public:
    /**
     * @brief Constructor for the CHelpDialog class.
     *
     * Initializes the dialog with the specified parent window.
     *
     * @param pParent The parent window for the dialog (default is nullptr).
     */
    CHelpDialog(CWnd* pParent = nullptr);

    // Dialog Data
    enum { IDD = IDD_DIALOG4 }; /**< Dialog resource ID. */

protected:
    /**
     * @brief Handles data exchange between the dialog controls and the variables.
     *
     * This function binds the dialog controls to class member variables for
     * proper data transfer when the dialog is initialized or updated.
     *
     * @param pDX Data exchange object that facilitates data binding.
     */
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
};
