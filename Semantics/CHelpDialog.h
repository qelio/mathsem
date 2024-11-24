#pragma once
#include "afxdialogex.h"
#include "resource.h"

/**
 * @class CHelpDialog
 * @brief Этот класс представляет диалог "Помощь" в приложении.
 *
 * Класс CHelpDialog предоставляет диалоговое окно для отображения информации
 * справки пользователю. Он является частью пользовательского интерфейса приложения
 * и наследуется от класса CDialogEx для обработки поведения диалога и обмена данными.
 */
class CHelpDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CHelpDialog)

public:
    /**
     * @brief Конструктор класса CHelpDialog.
     *
     * Инициализирует диалог с указанным родительским окном.
     *
     * @param pParent Родительское окно для диалога (по умолчанию nullptr).
     */
    CHelpDialog(CWnd* pParent = nullptr);

    // Данные диалога
    enum { IDD = IDD_DIALOG4 }; /**< ID ресурса диалога. */

protected:
    /**
     * @brief Обрабатывает обмен данными между элементами управления диалога и переменными.
     *
     * Эта функция связывает элементы управления диалога с переменными-членами класса для
     * правильной передачи данных при инициализации или обновлении диалога.
     *
     * @param pDX Объект обмена данными, который облегчает связывание данных.
     */
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
};