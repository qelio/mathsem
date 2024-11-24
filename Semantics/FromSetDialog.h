#pragma once
#include "afxwin.h"
#include "afxbutton.h"
#include "ScientificListBox.h"
#include "Formula.h"
//#include "ScientificStatic.h"
//#include "afxcmn.h"

/**
 * @class FromSetDialog
 * @brief Диалог для управления и выбора наборов формул и сущностей.
 *
 * Этот диалог позволяет пользователям просматривать и выбирать наборы формул и сущностей из
 * предоставленных списков. Обычно используется в приложениях, работающих с математическими
 * формулами или сущностями, связанными с наборами формул.
 */
class FromSetDialog : public CDialogEx
{
    DECLARE_DYNAMIC(FromSetDialog)

    /**
     * @brief Вектор объектов FormulaSet, которые диалог будет отображать или с которыми будет взаимодействовать.
     */
    vector <FormulaSet *> * sets;

    /**
     * @brief Вектор всех доступных объектов EntityBase для выбора в диалоге.
     */
    vector <EntityBase *> * allEntities;

public:
    /**
     * @brief Конструктор класса FromSetDialog.
     * @param pParent Указатель на родительское окно (по умолчанию NULL).
     */
    FromSetDialog(CWnd* pParent = NULL);

    /**
     * @brief Деструктор класса FromSetDialog.
     */
    virtual ~FromSetDialog();

    /**
     * @brief Функция обмена данными диалога для инициализации диалога.
     * @param pDX Объект обмена данными.
     */
    virtual void DoDataExchange(CDataExchange* pDX);

    /**
     * @brief Инициализирует диалог. Эта функция автоматически вызывается при создании диалога.
     * @return TRUE, если инициализация прошла успешно, FALSE в противном случае.
     */
    virtual BOOL OnInitDialog();

    /**
     * @brief Обработчик изменения выбора в списке. Эта функция вызывается
     *        при изменении выбора в списке.
     */
    afx_msg void OnLbnSelchangeSetlist1();

    /**
     * @brief Обработчик нажатия кнопки OK. Эта функция вызывается при нажатии кнопки OK,
     *        обычно для подтверждения выбора и закрытия диалога.
     */
    afx_msg void OnBnClickedOk();

    /**
     * @brief Устанавливает вектор объектов EntityBase для использования в диалоге.
     * @param all_entities_ Указатель на вектор объектов EntityBase.
     */
    void setEntities(vector <EntityBase *> * all_entities_ = NULL) { allEntities = all_entities_; };

protected:
    /**
     * @brief Карта сообщений для обработки сообщений Windows, связанных с диалогом.
     */
    DECLARE_MESSAGE_MAP()

    /**
     * @brief Контрол списка для отображения доступных наборов или сущностей.
     */
    ScientificListBox m_ListBoxSource;

    /**
     * @brief Контрол кнопки OK для подтверждения выбора.
     */
    CButton m_ButtonOK;
};