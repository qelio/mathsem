// Заголовочный файл защиты от двойного включения
#pragma once

// CMyEdit

/**
 * @class CMyEdit
 * @brief Пользовательский класс элемента управления редактирования, расширяющий CEdit.
 *
 * Этот класс предоставляет функционал для обработки пользовательского контекстного меню для элемента управления редактирования.
 * Он включает различные обработчики сообщений для конкретных действий, связанных с контекстным меню.
 */
class CMyEdit : public CEdit
{
	DECLARE_DYNAMIC(CMyEdit)

public:
	/**
	 * @brief Конструктор по умолчанию для CMyEdit.
	 */
	CMyEdit();

	/**
	 * @brief Деструктор для CMyEdit.
	 */
	virtual ~CMyEdit();

	// Раскомментируйте и реализуйте, если нужно
	// BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	/** Переменная-член для управления всплывающим меню (в настоящее время закомментирована). */
	// CMenu m_PopupMenu;

	// Раскомментируйте и реализуйте, если нужно
	// virtual void OnInitialUpdate(); // Вызывается первый раз после создания

protected:
	/**
	 * @brief Объявление карты сообщений для CMyEdit.
	 * Этот макрос связывает обработчики сообщений с соответствующими сообщениями Windows.
	 */
	DECLARE_MESSAGE_MAP()

public:
	/**
	 * @brief Обрабатывает событие контекстного меню для элемента управления редактирования.
	 * @param pWnd Указатель на окно, которое отправило сообщение.
	 * @param point Точка, в которой было запрошено контекстное меню.
	 */
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

	/** Действия элементов меню для различных команд. */
	afx_msg void OnMenuLow();
	afx_msg void OnMenuLeftTag();
	afx_msg void OnMenuRightTag();
	afx_msg void OnMenuHigh();
	afx_msg void OnMenuFirstQwantor();
	afx_msg void OnMenuSecondQwantor();
	afx_msg void OnMenuAnd();
	afx_msg void OnMenuOr();
	afx_msg void OnMenuHave();
	afx_msg void OnMenuLeft();
	afx_msg void OnMenuRight();
	afx_msg void OnMenuNot();
	afx_msg void OnMenuSimilar();
	afx_msg void OnMenuUnion();
	afx_msg void OnMenuCrossing();
	afx_msg void OnMenuEmptyset();
	afx_msg void OnMenuFuzzyInclusion();
};