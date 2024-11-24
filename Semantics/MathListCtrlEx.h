/**
 * @class CMathListCtrlEx
 * @brief Пользовательский элемент управления списком с расширенными функциями сортировки, редактирования и управления элементами.
 *
 * Этот класс расширяет CListCtrl и добавляет функционал для пользовательского редактирования элементов,
 * сортировки и управления. Он предоставляет методы для добавления, удаления и сортировки элементов,
 * а также установки пользовательских редакторов для определенных столбцов, строк или ячеек.
 */
class CMathListCtrlEx : public CListCtrl
{
	DECLARE_DYNAMIC(CMathListCtrlEx)

public:
	/**
	 * @brief Конструктор по умолчанию для CMathListCtrlEx.
	 */
	CMathListCtrlEx();

	/**
	 * @brief Деструктор для CMathListCtrlEx.
	 */
	virtual ~CMathListCtrlEx();

	/**
	 * @brief Получает данные (lParam), связанные с конкретным элементом.
	 * @param nItem Индекс элемента.
	 * @return Данные элемента (lParam).
	 */
	DWORD_PTR GetItemData(int nItem) const;

	/**
	 * @brief Получает внутренние данные, связанные с конкретным элементом.
	 * @param nItem Индекс элемента.
	 * @return Данные элемента (lParam).
	 */
	DWORD_PTR GetItemDataInternal(int nItem) const;

	/**
	 * @brief Устанавливает данные (lParam), связанные с конкретным элементом.
	 * @param nItem Индекс элемента.
	 * @param dwData Данные для установки.
	 * @return TRUE, если данные успешно установлены.
	 */
	BOOL SetItemData(int nItem, DWORD_PTR dwData);

	/**
	 * @brief Удаляет один элемент из элемента управления.
	 * @param nItem Индекс элемента для удаления.
	 * @return TRUE, если элемент был успешно удалён.
	 */
	BOOL DeleteItem(int nItem);

	/**
	 * @brief Удаляет все элементы из элемента управления.
	 * @return TRUE, если все элементы были успешно удалены.
	 */
	BOOL DeleteAllItems();

	/**
	 * @brief Находит элемент, который соответствует указанным критериям поиска.
	 * @param pFindInfo Критерии поиска.
	 * @param nStart Начальный индекс для поиска.
	 * @return Индекс найденного элемента или -1, если элемент не найден.
	 */
	int FindItem(LVFINDINFO* pFindInfo, int nStart = -1) const;

	/**
	 * @brief Сортирует элементы в элементе управления с использованием пользовательской функции сравнения.
	 * @param pfnCompare Пользовательская функция сравнения.
	 * @param dwData Дополнительные данные для передачи в функцию сравнения.
	 * @return TRUE, если сортировка была успешной.
	 */
	BOOL SortItems(PFNLVCOMPARE pfnCompare, DWORD_PTR dwData);

	/**
	 * @brief Добавляет элемент в элемент управления.
	 * @param pItem Элемент для вставки.
	 * @return Индекс вновь вставленного элемента.
	 */
	int InsertItem(const LVITEM* pItem);

	/**
	 * @brief Добавляет элемент в элемент управления с указанным индексом и меткой.
	 * @param nItem Индекс элемента.
	 * @param lpszItem Метка элемента.
	 * @return Индекс вновь вставленного элемента.
	 */
	int InsertItem(int nItem, LPCTSTR lpszItem);

	/**
	 * @brief Добавляет элемент в элемент управления с указанным индексом, меткой и индексом изображения.
	 * @param nItem Индекс элемента.
	 * @param lpszItem Метка элемента.
	 * @param nImage Индекс изображения, связанного с элементом.
	 * @return Индекс вновь вставленного элемента.
	 */
	int InsertItem(int nItem, LPCTSTR lpszItem, int nImage);

	/**
	 * @brief Обеспечивает, чтобы конкретный подэлемент был видим.
	 * @param nItem Индекс элемента.
	 * @param nSubItem Индекс подэлемента.
	 * @param pRect Прямоугольник, представляющий область подэлемента.
	 * @return TRUE, если подэлемент успешно сделан видимым.
	 */
	BOOL EnsureSubItemVisible(int nItem, int nSubItem, CRect *pRect = NULL);

	/**
	 * @brief Определяет состояния сортировки для столбцов.
	 */
	typedef enum Sort
	{
		None = 0, /**< Без сортировки. */
		Ascending = 1, /**< По возрастанию. */
		Descending = 2, /**< По убыванию. */
		Auto = 4, /**< Автоматическая сортировка. */
		SortBits = 7 /**< Все возможные состояния сортировки. */
	} Sort;

	/**
	 * @brief Определяет типы сравнения для сортировки столбцов.
	 */
	typedef enum Comparer
	{
		NotSet, /**< Сравнение не установлено. */
		Int, /**< Сравнение целых чисел. */
		Double, /**< Сравнение чисел с плавающей точкой. */
		String, /**< Сравнение строк. */
		StringNumber, /**< Сравнение строк с числами. */
		StringNoCase, /**< Сравнение строк без учета регистра. */
		StringNumberNoCase, /**< Сравнение строк с числами без учета регистра. */
		Date /**< Сравнение дат. */
	} Comparer;

protected:
	/**
	 * @brief Статическая функция обратного вызова, используемая для сравнения элементов при сортировке.
	 * @param lParam1 Первые данные элемента для сравнения.
	 * @param lParam2 Вторые данные элемента для сравнения.
	 * @param lParamSort Данные для сортировки.
	 * @return Значение, указывающее результат сравнения.
	 */
	static int CALLBACK CompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	/**
	 * @brief Выполняет фактическое сравнение двух элементов.
	 * @param lParam1 Первые данные элемента для сравнения.
	 * @param lParam2 Вторые данные элемента для сравнения.
	 * @param lParamSort Данные для сортировки.
	 * @return Значение, указывающее результат сравнения.
	 */
	static int Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	/**
	 * @brief Сравнивает два элемента как целые числа.
	 * @param pLeftText Первый текст для сравнения.
	 * @param pRightText Второй текст для сравнения.
	 * @return Значение, указывающее результат сравнения.
	 */
	static int CompareInt(LPCTSTR pLeftText, LPCTSTR pRightText);

	/**
	 * @brief Сравнивает два элемента как числа с плавающей точкой.
	 * @param pLeftText Первый текст для сравнения.
	 * @param pRightText Второй текст для сравнения.
	 * @return Значение, указывающее результат сравнения.
	 */
	static int CompareDouble(LPCTSTR pLeftText, LPCTSTR pRightText);

	/**
	 * @brief Сравнивает два элемента как строки.
	 * @param pLeftText Первый текст для сравнения.
	 * @param pRightText Второй текст для сравнения.
	 * @return Значение, указывающее результат сравнения.
	 */
	static int CompareString(LPCTSTR pLeftText, LPCTSTR pRightText);

	/**
	 * @brief Сравнивает два элемента как числовые строки.
	 * @param pLeftText Первый текст для сравнения.
	 * @param pRightText Второй текст для сравнения.
	 * @return Значение, указывающее результат сравнения.
	 */
	static int CompareNumberString(LPCTSTR pLeftText, LPCTSTR pRightText);

	/**
	 * @brief Сравнивает два элемента как безрегистровые числовые строки.
	 * @param pLeftText Первый текст для сравнения.
	 * @param pRightText Второй текст для сравнения.
	 * @return Значение, указывающее результат сравнения.
	 */
	static int CompareNumberStringNoCase(LPCTSTR pLeftText, LPCTSTR pRightText);

	/**
	 * @brief Сравнивает два элемента как безрегистровые строки.
	 * @param pLeftText Первый текст для сравнения.
	 * @param pRightText Второй текст для сравнения.
	 * @return Значение, указывающее результат сравнения.
	 */
	static int CompareStringNoCase(LPCTSTR pLeftText, LPCTSTR pRightText);

	/**
	 * @brief Сравнивает два элемента как даты.
	 * @param pLeftText Первый текст для сравнения.
	 * @param pRightText Второй текст для сравнения.
	 * @return Значение, указывающее результат сравнения.
	 */
	static int CompareDate(LPCTSTR pLeftText, LPCTSTR pRightText);

	/** Критическая секция для безопасности потоков. */
	CCriticalSection m_oLock;

protected:
	DECLARE_MESSAGE_MAP()

	/**
	 * @brief Структура информации о редакторе.
	 */
	typedef struct EditorInfo
	{
		PFNEDITORCALLBACK m_pfnInitEditor; /**< Функция инициализации редактора. */
		PFNEDITORCALLBACK m_pfnEndEditor; /**< Функция завершения работы редактора. */
		CWnd *m_pWnd; /**< Окно, связанное с редактором. */
		BOOL m_bReadOnly; /**< Является ли редактор только для чтения. */
		EditorInfo(); /**< Конструктор по умолчанию. */
		EditorInfo(PFNEDITORCALLBACK pfnInitEditor, PFNEDITORCALLBACK pfnEndEditor, CWnd *pWnd = NULL); /**< Параметризованный конструктор. */
		inline BOOL IsSet(){return (m_pfnInitEditor || m_pWnd);} /**< Проверяет, установлен ли редактор. */
	} EditorInfo;

	/** Структура, представляющая информацию о ячейке. */
	typedef struct CellInfo
	{
		EditorInfo m_eiEditor; /**< Редактор для ячейки. */
		COLORREF m_clrBack; /**< Цвет фона ячейки. */
		COLORREF m_clrText; /**< Цвет текста ячейки. */
		DWORD_PTR m_dwData; /**< Данные, связанные с ячейкой. */
		BOOL m_bReadOnly; /**< Является ли ячейка только для чтения. */
	} CellInfo;

	/** Массив для хранения информации о ячейках для каждого элемента и подэлемента. */
	CArray<CellInfo> m_arrCellInfo;
};