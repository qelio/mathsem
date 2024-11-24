/**
 * @class CXMLArchive
 * @brief Класс, обрабатывающий архивацию и извлечение XML данных для сериализации и десериализации.
 *
 * Этот класс отвечает за управление XML-документами и узлами. Он предоставляет функции для чтения и записи данных в XML-файл, а также для обхода и манипулирования XML-узлами.
 */
class CXMLArchive : public CArchive
{
    std::stack <CXMLArchiveNode*> m_nodeList; ///< Стек для управления XML-узлами во время чтения и записи.
    static CFile m_dummyFile; ///< Объект фиктивного файла, используемый в некоторых операциях.
    IStream* m_streamPtr; ///< Указатель на интерфейс IStream для операций на основе потоков.

public:
    /**
     * @brief Конструктор объекта CXMLArchive для заданного XML-файла.
     * @param fileName Имя XML-файла для архивирования.
     * @param nMode Режим открытия архива (например, чтение или запись).
     * @param streamPtr Необязательный указатель на интерфейс потока для операций на основе потоков.
     * @param docPtr Необязательный указатель на документ для дополнительной обработки.
     */
    CXMLArchive(const CString& fileName, UINT nMode,
                IStream* streamPtr = NULL,
                CDocument* docPtr = NULL);

    /**
     * @brief Деструктор CXMLArchive, освобождает ресурсы.
     */
    virtual ~CXMLArchive();

    /**
     * @brief Закрывает архив и освобождает ресурсы.
     */
    void Close();

    /**
     * @brief Получает узел по имени из XML-документа.
     * @param nodeNameStr Имя XML-узла, который нужно получить.
     * @return Указатель на соответствующий XML-узел.
     */
    CXMLArchiveNode* GetNode(LPCTSTR nodeNameStr);

#ifdef _UNICODE
    /**
     * @brief Получает узел по имени из XML-документа (для Unicode строк).
     * @param nodeNameStr Имя XML-узла, который нужно получить.
     * @return Указатель на соответствующий XML-узел.
     */
    CXMLArchiveNode* GetNode(LPCSTR nodeNameStr);
#endif

    /**
     * @brief Удаляет узел из архива.
     * @param xmlArchiveNodePtr Указатель на XML-узел, который нужно удалить.
     */
    void RemoveNode(CXMLArchiveNode* xmlArchiveNodePtr);

    /**
     * @brief Получает текущий узел из XML-архива.
     * @return Указатель на текущий XML-узел.
     */
    CXMLArchiveNode* GetCurrentNode();

    // Атрибуты
    const CString m_fileName; ///< Имя XML-файла.
    MSXML::IXMLDOMDocumentPtr m_xmlDocPtr; ///< Указатель на интерфейс DOM-документа MSXML.
};

/**
 * @class CXMLArchiveNode
 * @brief Класс, представляющий XML-узел в CXMLArchive.
 *
 * Этот класс предоставляет методы для манипуляции отдельными XML-узлами, такими как получение дочерних узлов, установка данных и создание новых узлов.
 * Его можно использовать для взаимодействия с XML-узлами в архиве, как с родительскими, так и с дочерними узлами.
 */
class CXMLArchiveNode
{
    friend class CXMLArchive; ///< Позволяет CXMLArchive доступ к приватным методам.

    /**
     * @brief Приватный конструктор, может быть создан только CXMLArchive.
     * @param archivePtr Указатель на экземпляр CXMLArchive.
     * @param newNodePtr Указатель на элемент DOM MSXML, представляющий этот узел.
     * @param fatherNodePtr Указатель на родительский узел в XML-дереве.
     */
    CXMLArchiveNode(CXMLArchive* archivePtr, MSXML::IXMLDOMElementPtr newNodePtr, MSXML::IXMLDOMNodePtr fatherNodePtr);

protected:
    static CMapStringToPtr m_classMap; ///< Кэш для RUNTIME_CLASS для ускорения создания объекта.
    MSXML::IXMLDOMElementPtr const m_nodePtr; ///< Указатель на элемент DOM для этого узла.
    MSXML::IXMLDOMNodePtr const m_fatherNodePtr; ///< Указатель на родительский узел.
    CXMLArchive* const m_archivePtr; ///< Указатель на экземпляр CXMLArchive.
    MSXML::IXMLDOMNodeListPtr m_childNodeListPtr; ///< Указатель на список дочерних узлов.
    int m_childIndex; ///< Индекс текущего дочернего узла.

public:
    /**
     * @brief Деструктор CXMLArchiveNode, освобождает ресурсы.
     */
    virtual ~CXMLArchiveNode();

    /**
     * @brief Создает новый узел данных в XML-документе.
     * @param attrName Имя атрибута данных.
     * @param attrValue Значение атрибута.
     * @return Указатель на созданный узел данных.
     */
    MSXML::IXMLDOMNodePtr CreateDataNode(LPCTSTR attrName, CString attrValue);

    /**
     * @brief Получает узел данных по заданному имени из XML-документа.
     * @param nodeName Имя узла данных.
     * @param nodeText Переменная для хранения текстового значения узла.
     * @return Указатель на узел данных.
     */
    MSXML::IXMLDOMNodePtr GetDataNode(LPCTSTR nodeName, CString& nodeText);

    /**
     * @brief Получает количество дочерних узлов текущего узла.
     * @return Количество дочерних узлов.
     */
    int GetNoChildren();

    /**
     * @brief Получает имя дочернего узла по заданному индексу.
     * @param childIndex Индекс дочернего узла.
     * @return Имя дочернего узла.
     */
    CString GetChildName(int childIndex);

    /**
     * @brief Получает следующий индекс дочернего узла для перебора дочерних узлов.
     * @return Следующий индекс дочернего узла.
     */
    int GetNextChildIndex();

    /**
     * @brief Закрывает текущий узел, завершая его обработку.
     */
    void Close();

    /**
     * @brief Устанавливает данные для атрибута с различными типами.
     * @param attrName Имя атрибута.
     * @param attrValue Значение атрибута.
     */
    void DataNode(LPCTSTR attrName, CTime& attrValue);
    void DataNode(LPCTSTR attrName, CTimeSpan& attrValue);
    void DataNode(LPCTSTR attrName, CString& attrValue);
    void DataNode(LPCTSTR attrName, bool& attrValue);
    void DataNode(LPCTSTR attrName, int& attrValue);
    void DataNode(LPCTSTR attrName, double& attrValue);
    void DataNode(LPCTSTR attrName, LONG& attrValue);
    void DataNode(LPCTSTR attrName, BYTE& attrValue);
    void DataNode(LPCTSTR attrName, UINT& attrValue);
    void DataNode(LPCTSTR attrName, CMapStringToPtr& pointerMap);
    void DataNode(LPCTSTR attrName, CMapStringToString& stringMap);
    void DataNode(LPCTSTR attrName, CStringArray& stringArray);
    void DataNode(LPCTSTR attrName, CByteArray& byteArray);
    void DataNode(LPCTSTR attrName, CDWordArray& wordArray);

    /**
     * @brief Загружает данные в существующий объект.
     * @param attrName Имя атрибута.
     * @param object Объект для загрузки данных.
     */
    void DataNode(LPCTSTR attrName, CObject& object);

    /**
     * @brief Создает новый объект при загрузке данных.
     * @param attrName Имя атрибута.
     * @param objectPtr Указатель на объект для создания.
     */
    void DataNode(LPCTSTR attrName, CObject*& objectPtr);

    /**
     * @brief Создает новый объект на основе имени узла.
     * @param className Имя класса, используемого для создания объекта.
     * @return Указатель на созданный объект.
     */
    static CObject* CreateObject(const CString& className);
};