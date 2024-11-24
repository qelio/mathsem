// SemanticsDlg.h : Заголовочный файл для класса CSemanticsDlg.

#pragma once

#include "Formula.h"
#include "ScientificStatic.h"
#include "ScientificButton.h"
#include "afxeditbrowsectrl.h"
#include "VUENode.h"
#include "VUELink.h"
#include "afxwin.h"
#include "resource.h"

// Подключение для libxml2 (отключено для компиляции в Windows)
// #include <libxml\parser.h>
// #include <libxml\tree.h>

// #define LIBXML_TREE_ENABLED
// #define LIBXML_OUTPUT_ENABLED

/**
 * @class CSemanticsDlg
 * @brief Основной класс диалога для приложения Semantics.
 *
 * Этот класс представляет собой окно диалога для приложения Semantics. Он управляет
 * созданием и взаимодействием различных элементов управления, таких как кнопки и поля ввода,
 * а также обработкой различных команд, инициируемых пользователем. Диалог взаимодействует
 * с формулами и сущностями, а также позволяет экспортировать и сохранять данные.
 */
class CSemanticsDlg : public CDialogEx
{
public:
    /**
     * @brief Конструктор по умолчанию для класса CSemanticsDlg.
     *
     * Инициализирует диалог с необязательным родительским окном.
     *
     * @param pParent Родительское окно. По умолчанию NULL.
     */
    CSemanticsDlg(CWnd* pParent = NULL);

    /**
     * @brief Деструктор для класса CSemanticsDlg.
     *
     * Очищает любые выделенные ресурсы при уничтожении диалога.
     */
    ~CSemanticsDlg();

    /**
     * @brief Идентификатор данных диалога (IDD).
     *
     * Это значение представляет идентификатор ресурса для диалога Semantics.
     */
    enum { IDD = IDD_SEMANTICS_DIALOG };

protected:
    /**
     * @brief Функция обмена данными.
     *
     * Эта функция обменивается данными между элементами управления и переменными, обеспечивая
     * правильное обновление всех данных во время взаимодействия с диалогом.
     *
     * @param pDX Указатель на объект CDataExchange.
     */
    virtual void DoDataExchange(CDataExchange* pDX);

protected:
    HICON m_hIcon; /**< Иконка для окна диалога. */

    /**
     * @brief Инициализирует диалог при создании.
     *
     * Эта функция вызывается при инициализации диалога. Она настраивает
     * иконку и начальные конфигурации для элементов управления.
     *
     * @return TRUE, если инициализация прошла успешно, иначе FALSE.
     */
    virtual BOOL OnInitDialog();

    /**
     * @brief Обрабатывает системные команды, такие как сворачивание или закрытие диалога.
     *
     * @param nID Идентификатор системной команды.
     * @param lParam Дополнительные параметры сообщения.
     */
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

    /**
     * @brief Обрабатывает отрисовку окна диалога.
     */
    afx_msg void OnPaint();

    /**
     * @brief Запрашивает курсор для использования при перетаскивании диалога.
     *
     * @return Курсор для перетаскивания диалога.
     */
    afx_msg HCURSOR OnQueryDragIcon();

    DECLARE_MESSAGE_MAP()

public:
    /**
     * @brief Обрабатывает событие клика по кнопке OK.
     */
    afx_msg void OnBnClickedOk();

    /**
     * @brief Обрабатывает событие клика для отображения всех формул.
     */
    afx_msg void OnBnClickedShowallformulas3();

    /**
     * @brief Обрабатывает событие клика для добавления новой атомной формулы.
     */
    afx_msg void OnBnClickedAddatomformula();

    vector <EntityBase *> all_entities; /**< Вектор, хранящий все сущности в приложении. */

    /**
     * @brief Обрабатывает событие клика для создания формул.
     */
    afx_msg void OnBnClickedBuildformula1();
    afx_msg void OnBnClickedBuildformula2();
    afx_msg void OnBnClickedBuildformula3();
    afx_msg void OnBnClickedBuildformula4();
    afx_msg void OnBnClickedBuildformula5();
    afx_msg void OnBnClickedShowallformulas();
    afx_msg void OnBnClickedChangeNewVariable();
    afx_msg void OnBnClickedHelp();

    /**
     * @brief Различные элементы управления кнопками научного характера.
     * Эти элементы управления используются для представления научных функций в диалоге.
     */
    CScientificButton m_button5;
    CScientificButton m_button4;
    CScientificButton m_button3;
    CScientificButton m_button2;
    CScientificButton m_button1;
    CScientificButton m_button6;
    CScientificButton m_button;
    CMFCEditBrowseCtrl m_fileFinder;

    /**
     * @brief Обрабатывает событие клика по кнопке Build Formula 6.
     */
    afx_msg void OnBnClickedBuildformula6();

    /**
     * @brief Обрабатывает событие клика для экспорта данных.
     */
    afx_msg void OnBnClickedExport();

    CMFCEditBrowseCtrl m_fileWordExport; /**< Элемент управления для поиска и выбора файла экспорта. */

    /**
     * @brief Обрабатывает событие клика для сохранения схемы.
     */
    afx_msg void OnBnClickedSavescheme();

    /**
     * @brief Обрабатывает событие клика для загрузки сохраненной схемы.
     */
    afx_msg void OnBnClickedLoadscheme();

    /**
     * @brief Обрабатывает событие клика для отмены текущей операции.
     */
    afx_msg void OnBnClickedCancel();

    /**
     * @brief Обрабатывает изменение события для элемента управления поиском файла.
     */
    afx_msg void OnEnChangeMfceditbrowse2();

    /**
     * @brief Обрабатывает событие клика по кнопке Build Formula 7.
     */
    afx_msg void OnBnClickedBuildformula7();

    CScientificButton m_button7; /**< Кнопка для создания формул (Formula 7). */

    /**
     * @brief Обрабатывает событие клика для создания кортежа.
     */
    afx_msg void OnBnClickedBuildtuple();

    CScientificButton m_KortegeButton; /**< Кнопка для создания картежа (Kortege). */

    /**
     * @brief Обрабатывает событие клика для изменения переменной.
     */
    afx_msg void OnBnClickedChangevariable();

    CScientificButton m_ChangeVariable; /**< Кнопка для изменения переменных. */

    int m_rbLang; /**< Переменная для хранения языковой настройки. */

    /**
     * @brief Обрабатывает событие клика для переключения на русский язык.
     */
    afx_msg void OnBnClickedRus();

    /**
     * @brief Обрабатывает событие клика для переключения на английский язык.
     */
    afx_msg void OnBnClickedEng();
};