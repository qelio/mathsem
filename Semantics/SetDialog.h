/**
 * @class SetDialog
 * @brief Этот класс представляет диалог для выполнения операций с множествами.
 *
 * Он связан с ресурсом IDD_SETDIALOG и позволяет пользователям выполнять операции, связанные с множествами,
 * такие как отображение и управление множествами и переменными.
 * Класс также предоставляет функции для взаимодействия с элементами множества, такие как проверка принадлежности к множеству
 * или создание подмножеств.
 */
class SetDialog : public CDialogEx
{
	DECLARE_DYNAMIC(SetDialog)

    /**
     * @var entities
     * @brief Указатель на вектор объектов EntityBase, используемый для манипулирования данными, связанными с множествами.
     * Передается из других частей приложения для обеспечения соответствующих сущностей для операций в диалоге.
     */
	vector <EntityBase *> * entities;

public:
	/**
	 * @brief Конструктор по умолчанию для класса SetDialog.
	 * @param pParent Родительское окно для диалога (необязательно).
	 */
	SetDialog(CWnd* pParent = NULL);

	/**
	 * @brief Деструктор для класса SetDialog.
	 */
	virtual ~SetDialog();

	/** @enum IDD
	 * @brief Идентификатор ресурса для этого диалога, используемый системой диалога.
	 */
	enum { IDD = IDD_SETDIALOG };

protected:
	/**
	 * @brief Обмен данными между диалогом и связанными с ним переменными.
	 * @param pDX Указатель на объект обмена данными.
	 */
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	/**
	 * @var m_list
	 * @brief Элемент управления списком для отображения списка элементов в множестве.
	 */
	ScientificListBox m_list;

	/**
	 * @var m_fIndexes
	 * @brief Объект шрифта для индексации элементов списка.
	 */
	CFont * m_fIndexes;

	/**
	 * @var m_fSymbol
	 * @brief Объект шрифта для отображения символов, обычно из шрифта Symbol.
	 */
	CFont * m_fSymbol;

	/**
	 * @var m_listVariables
	 * @brief Элемент управления списком для отображения списка свободных переменных, связанных с множествами.
	 */
	ScientificListBox m_listVariables;

	/**
	 * @var m_buttonOK
	 * @brief Элемент управления кнопкой "OK" для подтверждения изменений или выборов в диалоге.
	 */
	CButton m_buttonOK;

	/**
	 * @brief Вызывается при нажатии кнопки "OK".
	 */
	afx_msg void OnBnClickedOk();

	/**
	 * @brief Инициализирует диалог и подготавливает его для взаимодействия с пользователем.
	 * @return TRUE, если инициализация прошла успешно, иначе FALSE.
	 */
	virtual BOOL OnInitDialog();

	/**
	 * @brief Устанавливает сущности, используемые для операций в диалоге.
	 * @param all_entities Указатель на вектор объектов EntityBase для использования в диалоге. По умолчанию NULL.
	 */
	void setEntities(vector <EntityBase *> * all_entities = NULL) { entities = all_entities; };

	/**
	 * @brief Отображает список свободных переменных в элементе управления m_listVariables.
	 */
	void ShowFreeVariables();

	/**
	 * @brief Скрывает список свободных переменных из элемента управления m_listVariables.
	 */
	void HideFreeVariables();

	/**
	 * @brief Вызывается при изменении выбора в первом списке множеств.
	 */
	afx_msg void OnSelchangeSetlist1();

	/**
	 * @var m_CheckBelonging
	 * @brief Флажок для проверки принадлежности элемента множеству.
	 */
	CButton m_CheckBelonging;

	/**
	 * @var m_CheckSubSet
	 * @brief Флажок для проверки, является ли множество подмножеством другого.
	 */
	CButton m_CheckSubSet;

	/**
	 * @brief Вызывается при нажатии кнопки "Построить подмножество".
	 */
	afx_msg void OnClickedBuildsubset();

	/**
	 * @var m_ComboSubSet
	 * @brief Комбинированный список для выбора подмножества.
	 */
	CComboBox m_ComboSubSet;

	/**
	 * @var m_IndexSubSet
	 * @brief Поле ввода текста для ввода индекса подмножества.
	 */
	CEdit m_IndexSubSet;

	/**
	 * @var m_comboSet
	 * @brief Комбинированный список для выбора множества.
	 */
	CComboBox m_comboSet;

	/**
	 * @var m_indexSet
	 * @brief Поле ввода текста для ввода индекса множества.
	 */
	CEdit m_indexSet;

	/**
	 * @var m_label
	 * @brief Статическая метка для отображения информации о множестве.
	 */
	CScientificStatic m_label;

	/**
	 * @var m_level
	 * @brief Статическая метка для отображения уровня множества.
	 */
	CScientificStatic m_level;

	/**
	 * @brief Вызывается при изменении выбора во втором списке множеств.
	 */
	afx_msg void OnSelchangeSetlist2();

	/**
	 * @brief Проверяет выбор пользователя для проверки операции с множествами.
	 */
	void CheckSelection();

	/**
	 * @brief Вызывается при изменении выбранного множества в комбинированном списке.
	 */
	afx_msg void OnSelchangeSetcombo();

	/**
	 * @brief Вызывается при изменении индекса множества.
	 */
	afx_msg void OnChangeSetindex();
};