/**
 * @file OperationDlg.h
 * @brief Defines the OperationDlg class for performing operations on formulas.
 */

#pragma once

#include "afxwin.h"
#include "afxbutton.h"
#include "ScientificListBox.h"
#include "Formula.h"
#include "ScientificStatic.h"
#include "afxcmn.h"

/**
 * @brief Dialog class for various formula operations.
 */
class OperationDlg : public CDialogEx
{
    DECLARE_DYNAMIC(OperationDlg)

    /**
     * @brief Updates the state of the operation based on user interaction.
     */
    void SetOperationState();

    /**
     * @brief Moves selected items from the source list box to the destination list box.
     * @param Source The source ScientificListBox.
     * @param Destination The destination ScientificListBox.
     */
    void MoveSelected(ScientificListBox& Source, ScientificListBox& Destination);

    /**
     * @brief Moves all items from the source list box to the destination list box.
     * @param Source The source ScientificListBox.
     * @param Destination The destination ScientificListBox.
     */
    void MoveAll(ScientificListBox& Source, ScientificListBox& Destination);

    /**
     * @brief Pointer to a vector of formulas used in operations.
     */
    std::vector<Formula*>* formulas;

    /**
     * @brief Pointer to a vector of all entities involved in operations.
     */
    std::vector<EntityBase*>* allEntities;

public:
    /**
     * @brief Constructs the OperationDlg dialog.
     * @param pParent Parent window of the dialog.
     */
    OperationDlg(CWnd* pParent = NULL);

    /**
     * @brief Destructs the OperationDlg dialog.
     */
    virtual ~OperationDlg();

    /**
     * @brief Dialog Data Identifier.
     */
    enum { IDD = IDD_CHOOSEDIALOG };

protected:
    /**
     * @brief Data exchange method for dialog controls.
     * @param pDX Pointer to the data exchange object.
     */
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
};