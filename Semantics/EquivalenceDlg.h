// Автор: Татаринцев В.В., akizelokro@mail.ru, 2013-2014
#pragma once
#include "afxwin.h"
#include "afxbutton.h"
#include "ScientificListBox.h"
#include "Formula.h"
#include "ScientificStatic.h"
#include "afxcmn.h"

// Объявление класса EquivalenceDlg

/**
 * @brief Класс EquivalenceDlg представляет диалог для управления эквивалентностями.
 *
 * Этот класс используется для обработки взаимодействий пользователя в диалоговом окне для добавления, удаления,
 * и отображения научных формул и эквивалентностей.
 */
class EquivalenceDlg : public CDialogEx
{
    DECLARE_DYNAMIC(EquivalenceDlg)

    /**
     * @brief Перемещает выбранный элемент из одного списка в другой.
     *
     * Эта функция перемещает выбранный элемент из исходного списка в целевой список.
     *
     * @param Source Исходный список для перемещения элементов.
     * @param Destination Целевой список для перемещения элементов.
     */
    void MoveSelected(ScientificListBox &Source, ScientificListBox &Destination);

    /**
     * @brief Перемещает все элементы из одного списка в другой.
     *
     * Эта функция перемещает все элементы из исходного списка в целевой список.
     *
     * @param Source Исходный список для перемещения элементов.
     * @param Destination Целевой список для перемещения элементов.
     */
    void MoveAll(ScientificListBox &Source, ScientificListBox &Destination);

    vector <Formula *> * formulas; /**< Указатель на вектор формул */
    vector <EntityBase *> * allEntities; /**< Указатель на вектор всех сущностей */
    vector <Equivalence *> * allEquivalences; /**< Указатель на вектор всех эквивалентностей */

public:
    /**
     * @brief Конструктор для класса EquivalenceDlg.
     *
     * Инициализирует диалог и устанавливает родительское окно.
     *
     * @param pParent Указатель на родительское окно (по умолчанию NULL).
     */
    EquivalenceDlg(CWnd* pParent = NULL);

    /**
     * @brief Деструктор для класса EquivalenceDlg.
     *
     * Очистка ресурсов, используемых классом EquivalenceDlg.
     */
    virtual ~EquivalenceDlg();

    // Данные диалога
    enum { IDD = IDD_EQUIVALENCEDIALOG }; /**< Идентификатор ресурса диалога */

protected:
    /**
     * @brief Обмен данными между элементами интерфейса и переменными класса.
     *
     * Эта функция вызывается во время обмена данными диалога.
     * Она обрабатывает передачу данных между элементами интерфейса и внутренними переменными класса.
     *
     * @param pDX Указатель на объект CDataExchange для обмена данными.
     */
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()

public:
    // Элементы интерфейса
    ScientificListBox m_ListBoxSource; /**< Исходный список для формул */
    ScientificListBox m_ListBoxDestination1; /**< Целевой список 1 */
    ScientificListBox m_ListBoxDestination2; /**< Целевой список 2 */
    CMFCButton m_ButtonAdd1; /**< Кнопка добавления для списка 1 */
    CMFCButton m_ButtonRemove1; /**< Кнопка удаления для списка 1 */
    CScientificStatic m_StaticDescription; /**< Статический текст описания */
    CMFCButton m_ButtonAddAll1; /**< Кнопка добавления всех элементов для списка 1 */
    CMFCButton m_ButtonRemoveAll1; /**< Кнопка удаления всех элементов для списка 1 */
    CButton m_ButtonOK; /**< Кнопка OK */
    CFont * m_fIndexes; /**< Шрифт для индексов */
    CFont * m_fSymbol; /**< Шрифт для символов */
    CFont * m_fVariables; /**< Шрифт для переменных */
    CFont * m_fIndexesVariables; /**< Шрифт для индексированных переменных */
    CFont * m_fSymbolVariables; /**< Шрифт для символьных переменных */

    /**
     * @brief Обработчик события нажатия на кнопку "Check2".
     */
    afx_msg void OnBnClickedCheck2();

    /**
     * @brief Устанавливает формулы для диалога эквивалентностей.
     *
     * Эта функция используется для передачи вектора всех сущностей, содержащих формулы.
     *
     * @param all_entities_ Необязательный указатель на вектор всех сущностей.
     */
    void  setFormulas(vector <EntityBase *> * all_entities_ = NULL) { allEntities = all_entities_; };

    /**
     * @brief Устанавливает эквивалентности для диалога эквивалентностей.
     *
     * Эта функция используется для передачи вектора всех эквивалентностей.
     *
     * @param all_equivalences_ Необязательный указатель на вектор всех эквивалентностей.
     */
    void  setEquivalences(vector <Equivalence *> * all_equivalences_ = NULL) { allEquivalences = all_equivalences_; };

    /**
     * @brief Инициализирует элементы управления и настройки диалога.
     *
     * Эта функция вызывается при инициализации диалога и настраивает компоненты интерфейса.
     *
     * @return TRUE, если инициализация успешна, FALSE в противном случае.
     */
    virtual BOOL OnInitDialog();

    /**
     * @brief Обработчик события нажатия на кнопку "OK".
     */
    afx_msg void OnBnClickedOk();

    /**
     * @brief Обработчик события нажатия на кнопку "Mfcbutton1".
     */
    afx_msg void OnBnClickedMfcbutton1();

    /**
     * @brief Обработчик события нажатия на кнопку "Mfcbutton5".
     */
    afx_msg void OnBnClickedMfcbutton5();

    /**
     * @brief Обработчик события нажатия на кнопку "Mfcbutton2".
     */
    afx_msg void OnBnClickedMfcbutton2();

    /**
     * @brief Обработчик события нажатия на кнопку "Mfcbutton6".
     */
    afx_msg void OnBnClickedMfcbutton6();

    /**
     * @brief Обработчик события изменения выбора в целевом списке 1.
     */
    afx_msg void OnSelchangeListdest1();

    /**
     * @brief Показывает кандидатов для эквивалентностей.
     */
    void ShowCandidates();

    /**
     * @brief Скрывает кандидатов для эквивалентностей.
     */
    void HideCandidates();

    /**
     * @brief Устанавливает состояние эквивалентностей на основе ввода пользователя.
     */
    void SetEquivalenceState();
};