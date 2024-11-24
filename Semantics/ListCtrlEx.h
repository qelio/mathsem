#pragma once
#include "MsgHook.h"
#include <Afxmt.h>

// CListCtrlEx
typedef BOOL (*PFNEDITORCALLBACK)(CWnd** pWnd, int nRow, int nColumn, CString& strSubItemText, DWORD_PTR dwItemData, void* pThis, BOOL bUpdate);

/**
 * @class CListCtrlEx
 * @brief Расширенная версия CListCtrl, поддерживающая дополнительные функции, такие как пользовательская сортировка, редакторы и обработка данных ячеек/элементов.
 *
 * Этот класс расширяет функциональность стандартного элемента управления списком, добавляя поддержку пользовательской сортировки,
 * редактирования ячеек и обработки данных элементов. Он позволяет пользователю определять редакторы, сортировать столбцы
 * и настраивать внешний вид отдельных строк и ячеек.
 */
class CListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlEx)

public:
    /**
     * @brief Конструктор по умолчанию.
     */
	CListCtrlEx();

    /**
     * @brief Деструктор.
     */
	virtual ~CListCtrlEx();

    /**
     * @brief Получает данные (lParam), связанные с конкретным элементом.
     * @param nItem Индекс элемента, данные которого нужно получить.
     * @return Данные (lParam), связанные с элементом.
     */
	DWORD_PTR GetItemData(int nItem) const;

    /**
     * @brief Получает внутренние данные (lParam), связанные с конкретным элементом.
     * @param nItem Индекс элемента, данные которого нужно получить.
     * @return Внутренние данные (lParam), связанные с элементом.
     */
	DWORD_PTR GetItemDataInternal(int nItem) const;

    /**
     * @brief Устанавливает данные (lParam), связанные с конкретным элементом.
     * @param nItem Индекс элемента, данные которого нужно установить.
     * @param dwData Данные для связывания с элементом.
     * @return TRUE, если операция удалась, FALSE в противном случае.
     */
	BOOL SetItemData(int nItem, DWORD_PTR dwData);

    /**
     * @brief Удаляет отдельный элемент из элемента управления.
     * @param nItem Индекс элемента, который нужно удалить.
     * @return TRUE, если элемент был успешно удалён, FALSE в противном случае.
     */
	BOOL DeleteItem(int nItem);

    /**
     * @brief Удаляет все элементы из элемента управления.
     * @return TRUE, если все элементы были успешно удалены, FALSE в противном случае.
     */
	BOOL DeleteAllItems();

    /**
     * @brief Ищет элемент в элементе управления, соответствующий указанным критериям.
     * @param pFindInfo Указатель на структуру, содержащую критерии поиска.
     * @param nStart Начальный индекс для поиска.
     * @return Индекс найденного элемента или -1, если элемент не найден.
     */
	int FindItem(LVFINDINFO* pFindInfo, int nStart = -1) const;

    /**
     * @brief Сортирует элементы в элементе управления с использованием пользовательской функции сравнения.
     * @param pfnCompare Указатель на функцию сравнения.
     * @param dwData Дополнительные данные для передачи в функцию сравнения.
     * @return TRUE, если сортировка удалась, FALSE в противном случае.
     */
	BOOL SortItems(PFNLVCOMPARE pfnCompare, DWORD_PTR dwData);

    /**
     * @brief Вставляет новый элемент в элемент управления.
     * @param pItem Указатель на структуру LVITEM, содержащую детали элемента.
     * @return Индекс вставленного элемента или -1, если вставка не удалась.
     */
	int InsertItem(const LVITEM* pItem);

    /**
     * @brief Вставляет новый элемент с текстом в элемент управления.
     * @param nItem Индекс, по которому нужно вставить элемент.
     * @param lpszItem Текст для элемента.
     * @return Индекс вставленного элемента или -1, если вставка не удалась.
     */
	int InsertItem(int nItem, LPCTSTR lpszItem);

    /**
     * @brief Вставляет новый элемент с текстом и изображением в элемент управления.
     * @param nItem Индекс, по которому нужно вставить элемент.
     * @param lpszItem Текст для элемента.
     * @param nImage Индекс изображения для связывания с элементом.
     * @return Индекс вставленного элемента или -1, если вставка не удалась.
     */
	int InsertItem(int nItem, LPCTSTR lpszItem, int nImage);

    /**
     * @brief Обеспечивает видимость подэлемента в списке.
     * @param nItem Индекс элемента.
     * @param nSubItem Индекс подэлемента.
     * @param pRect Опциональный указатель на объект CRect для получения прямоугольника элемента.
     * @return TRUE, если подэлемент видим, FALSE в противном случае.
     */
	BOOL EnsureSubItemVisible(int nItem, int nSubItem, CRect *pRect = NULL);

    /**
     * @brief Перечисление для опций порядка сортировки.
     */
	typedef enum Sort
	{
		None = 0,          ///< Без сортировки.
		Ascending = 1,     ///< По возрастанию.
		Descending = 2,    ///< По убыванию.
		Auto = 4,          ///< Автоматическая сортировка.
		SortBits = 7       ///< Маска для опций сортировки.
	} Sort;

    /**
     * @brief Перечисление для типов сравнения столбцов.
     */
	typedef enum Comparer
	{
		NotSet,            ///< Сравнение не установлено.
		Int,               ///< Сравнение целых чисел.
		Double,            ///< Сравнение чисел с плавающей точкой.
		String,            ///< Сравнение строк.
		StringNumber,      ///< Сравнение строк с числами.
		StringNoCase,      ///< Сравнение строк без учета регистра.
		StringNumberNoCase, ///< Сравнение строк с числами без учета регистра.
		Date               ///< Сравнение дат.
	} Comparer;

protected:
    /**
     * @brief Статическая процедура сравнения, используемая SortItems.
     * @param lParam1 Первые данные элемента.
     * @param lParam2 Вторые данные элемента.
     * @param lParamSort Параметры сортировки.
     * @return Результат сравнения.
     */
	static int CALLBACK CompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

    /**
     * @brief Сравнивает два элемента, используя указанную логику сравнения.
     * @param lParam1 Первые данные элемента.
     * @param lParam2 Вторые данные элемента.
     * @param lParamSort Параметры сортировки.
     * @return Результат сравнения.
     */
	static int Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

    /**
     * @brief Сравнивает два значения целых чисел как строки.
     * @param pLeftText Текст первого элемента.
     * @param pRightText Текст второго элемента.
     * @return Результат сравнения.
     */
	static int CompareInt(LPCTSTR pLeftText, LPCTSTR pRightText);

    /**
     * @brief Сравнивает два значения с плавающей точкой как строки.
     * @param pLeftText Текст первого элемента.
     * @param pRightText Текст второго элемента.
     * @return Результат сравнения.
     */
	static int CompareDouble(LPCTSTR pLeftText, LPCTSTR pRightText);

    /**
     * @brief Сравнивает две строки.
     * @param pLeftText Текст первого элемента.
     * @param pRightText Текст второго элемента.
     * @return Результат сравнения.
     */
	static int CompareString(LPCTSTR pLeftText, LPCTSTR pRightText);

    /**
     * @brief Сравнивает две числовые строки.
     * @param pLeftText Текст первого элемента.
     * @param pRightText Текст второго элемента.
     * @return Результат сравнения.
     */
	static int CompareNumberString(LPCTSTR pLeftText, LPCTSTR pRightText);

    /**
     * @brief Сравнивает две числовые строки без учета регистра.
     * @param pLeftText Текст первого элемента.
     * @param pRightText Текст второго элемента.
     * @return Результат сравнения.
     */
	static int CompareNumberStringNoCase(LPCTSTR pLeftText, LPCTSTR pRightText);

    /**
     * @brief Сравнивает две строки без учета регистра.
     * @param pLeftText Текст первого элемента.
     * @param pRightText Текст второго элемента.
     * @return Результат сравнения.
     */
	static int CompareStringNoCase(LPCTSTR pLeftText, LPCTSTR pRightText);

    /**
     * @brief Сравнивает два значения дат как строки.
     * @param pLeftText Текст первого элемента.
     * @param pRightText Текст второго элемента.
     * @return Результат сравнения.
     */
	static int CompareDate(LPCTSTR pLeftText, LPCTSTR pRightText);

    /**
     * @brief Объект критической секции для синхронизации потоков.
     */
	CCriticalSection m_oLock;

protected:
	DECLARE_MESSAGE_MAP()

    // Другие частные/защищенные переменные и методы опущены для краткости
}; // Конец класса CListCtrlEx