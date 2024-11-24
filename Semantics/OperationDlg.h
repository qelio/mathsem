// Заголовочный файл защиты от двойного включения
#pragma once

#include "afxwin.h"
#include "afxbutton.h"
#include "ScientificListBox.h"
#include "Formula.h"
#include "ScientificStatic.h"
#include "afxcmn.h"

/**
 * @file OperationDlg.h
 * @brief Определяет класс OperationDlg для выполнения операций с формулами.
 */

/**
 * @brief Класс диалогового окна для различных операций с формулами.
 */
class OperationDlg : public CDialogEx
{
    DECLARE_DYNAMIC(OperationDlg)

    /**
     * @brief Обновляет состояние операции на основе взаимодействия с пользователем.
     */
    void SetOperationState();

    /**
     * @brief Перемещает выбранные элементы из исходного списка в целевой список.
     * @param Source Исходный ScientificListBox.
     * @param Destination Целевой ScientificListBox.
     */
    void MoveSelected(ScientificListBox& Source, ScientificListBox& Destination);

    /**
     * @brief Перемещает все элементы из исходного списка в целевой список.
     * @param Source Исходный ScientificListBox.
     * @param Destination Целевой ScientificListBox.
     */
    void MoveAll(ScientificListBox& Source, ScientificListBox& Destination);

    /**
     * @brief Указатель на вектор формул, используемых в операциях.
     */
    std::vector<Formula*>* formulas;

    /**
     * @brief Указатель на вектор всех сущностей, задействованных в операциях.
     */
    std::vector<EntityBase*>* allEntities;

public:
    /**
     * @brief Конструктор диалогового окна OperationDlg.
     * @param pParent Родительское окно диалога.
     */
    OperationDlg(CWnd* pParent = NULL);

    /**
     * @brief Деструктор диалогового окна OperationDlg.
     */
    virtual ~OperationDlg();

    /**
     * @brief Идентификатор данных диалога.
     */
    enum { IDD = IDD_CHOOSEDIALOG };

protected:
    /**
     * @brief Метод обмена данными для элементов управления диалогом.
     * @param pDX Указатель на объект обмена данными.
     */
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
};