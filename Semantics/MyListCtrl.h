// Заголовочный файл защиты от двойного включения
#pragma once
#include "stdafx.h"
#include "afxcmn.h"
#include "Formula.h"
#include "afxwin.h"

/**
 * @class CMyListCtrl
 * @brief Пользовательский класс элемента управления списком, расширяющий CMFCListCtrl.
 *
 * Этот класс настраивает поведение элемента управления списком, переопределяя функции для
 * цвета текста ячейки, цвета фона, шрифта, сравнения элементов и обработки изменений в списке.
 * Он также предоставляет функционал для сохранения формул и изменения свойств ячеек.
 */
class CMyListCtrl : public CMFCListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl)

	/**
	 * @brief Получает цвет текста ячейки.
	 * @param nRow Индекс строки ячейки.
	 * @param nColum Индекс столбца ячейки.
	 * @return Цвет текста ячейки.
	 */
	virtual COLORREF OnGetCellTextColor(int nRow, int nColum);

	/**
	 * @brief Получает цвет фона ячейки.
	 * @param nRow Индекс строки ячейки.
	 * @param nColum Индекс столбца ячейки.
	 * @return Цвет фона ячейки.
	 */
	virtual COLORREF OnGetCellBkColor(int nRow, int nColum);

	/**
	 * @brief Получает шрифт для текста ячейки.
	 * @param nRow Индекс строки ячейки.
	 * @param nColum Индекс столбца ячейки.
	 * @param dwData Дополнительные данные для настройки выбора шрифта.
	 * @return Шрифт, используемый для отображения текста ячейки.
	 */
	virtual HFONT OnGetCellFont(int nRow, int nColum, DWORD dwData = 0);

	/** Индекс подэлемента, который в данный момент редактируется. */
	int subItemEdit;

	/** Индекс элемента, который в данный момент редактируется. */
	int itemEdit;

	/** Флаг, указывающий был ли элемент управления списком изменен. */
	bool m_bIsModified;

	/** Флаг, указывающий включена ли настройка цвета ячейки. */
	BOOL m_bColor;

	/** Флаг, указывающий можно ли изменять шрифт ячейки. */
	BOOL m_bModifyFont;

	/** Указатель на вектор объектов Formula. */
	vector <Formula *> * formulas;

	/**
	 * @brief Сравнивает два элемента списка для сортировки.
	 * @param lParam1 Первый элемент для сравнения.
	 * @param lParam2 Второй элемент для сравнения.
	 * @param iColumn Индекс столбца для сравнения.
	 * @return Значение, указывающее результат сравнения.
	 */
	virtual int OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn);

	/**
	 * @brief Сохраняет формулы в элементе управления списком.
	 */
	void SaveFormulas();

protected:
	/** Указатель на элемент управления CEdit, используемый для редактирования ячеек. */
	CEdit * m_edit;

	/** Объявление карты сообщений для CMyListCtrl. */
	DECLARE_MESSAGE_MAP()

public:
	/**
	 * @brief Конструктор по умолчанию для CMyListCtrl.
	 */
	CMyListCtrl();

	/**
	 * @brief Деструктор для CMyListCtrl.
	 */
	virtual ~CMyListCtrl();

	/**
	 * @brief Обрабатывает событие клика по элементу в элементе управления списком.
	 * @param pNMHDR Указатель на структуру NMHDR, содержащую информацию о сообщении уведомления.
	 * @param pResult Указатель на результат обработки сообщения.
	 */
	afx_msg virtual void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);

	/**
	 * @brief Предварительно обрабатывает сообщения для элемента управления списком.
	 * @param pMsg Указатель на структуру MSG, содержащую сообщение для обработки.
	 * @return TRUE если сообщение было обработано; в противном случае FALSE.
	 */
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	/**
	 * @brief Устанавливает формулы для элемента управления списком.
	 * @param formulas_ Указатель на вектор объектов Formula.
	 */
	void setFormulas(vector <Formula *> * formulas_) { formulas = formulas_; };
};