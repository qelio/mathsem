/**
 * @class CXMLArchive
 * @brief A class that handles the archiving and retrieval of XML data for serialization and deserialization.
 *
 * This class is responsible for managing XML documents and nodes. It provides functionality for reading and writing data to an XML file, as well as traversing and manipulating XML nodes.
 */
class CXMLArchive : public CArchive
{
    std::stack <CXMLArchiveNode*> m_nodeList; ///< Stack to manage XML nodes during reading and writing.
    static CFile m_dummyFile; ///< A dummy file object used in certain operations.
    IStream* m_streamPtr; ///< Pointer to an IStream interface for stream-based operations.

public:
    /**
     * @brief Constructs a CXMLArchive object for the given XML file.
     * @param fileName The name of the XML file to archive.
     * @param nMode The mode in which to open the archive (e.g., read or write).
     * @param streamPtr Optional pointer to a stream interface for stream-based operations.
     * @param docPtr Optional pointer to a document for additional processing.
     */
    CXMLArchive(const CString& fileName, UINT nMode,
                IStream* streamPtr = NULL,
                CDocument* docPtr = NULL);

    /**
     * @brief Destructor for CXMLArchive, cleans up resources.
     */
    virtual ~CXMLArchive();

    /**
     * @brief Closes the archive and releases any resources.
     */
    void Close();

    /**
     * @brief Retrieves a node by name from the XML document.
     * @param nodeNameStr The name of the XML node to retrieve.
     * @return A pointer to the corresponding XML node.
     */
    CXMLArchiveNode* GetNode(LPCTSTR nodeNameStr);

#ifdef _UNICODE
    /**
     * @brief Retrieves a node by name from the XML document (for Unicode strings).
     * @param nodeNameStr The name of the XML node to retrieve.
     * @return A pointer to the corresponding XML node.
     */
    CXMLArchiveNode* GetNode(LPCSTR nodeNameStr);
#endif

    /**
     * @brief Removes a node from the archive.
     * @param xmlArchiveNodePtr A pointer to the XML node to be removed.
     */
    void RemoveNode(CXMLArchiveNode* xmlArchiveNodePtr);

    /**
     * @brief Retrieves the current node from the XML archive.
     * @return A pointer to the current XML node.
     */
    CXMLArchiveNode* GetCurrentNode();

    // Attributes
    const CString m_fileName; ///< The name of the XML file.
    MSXML::IXMLDOMDocumentPtr m_xmlDocPtr; ///< Pointer to the MSXML DOM document interface.
};

/**
 * @class CXMLArchiveNode
 * @brief A class representing an XML node in the CXMLArchive.
 *
 * This class provides methods for manipulating individual XML nodes, such as retrieving child nodes, setting data, and creating new nodes.
 * It can be used to interact with XML nodes within an archive, either as a parent or child node.
 */
class CXMLArchiveNode
{
    friend class CXMLArchive; ///< Allows CXMLArchive to access private members.

    /**
     * @brief Private constructor, can only be constructed by CXMLArchive.
     * @param archivePtr A pointer to the CXMLArchive instance.
     * @param newNodePtr A pointer to the MSXML DOM element representing this node.
     * @param fatherNodePtr A pointer to the parent node in the XML tree.
     */
    CXMLArchiveNode(CXMLArchive* archivePtr, MSXML::IXMLDOMElementPtr newNodePtr, MSXML::IXMLDOMNodePtr fatherNodePtr);

protected:
    static CMapStringToPtr m_classMap; ///< Cache for RUNTIME_CLASS to speed up object creation.
    MSXML::IXMLDOMElementPtr const m_nodePtr; ///< Pointer to the DOM element for this node.
    MSXML::IXMLDOMNodePtr const m_fatherNodePtr; ///< Pointer to the parent node.
    CXMLArchive* const m_archivePtr; ///< Pointer to the CXMLArchive instance.
    MSXML::IXMLDOMNodeListPtr m_childNodeListPtr; ///< Pointer to the list of child nodes.
    int m_childIndex; ///< Index of the current child node.

public:
    /**
     * @brief Destructor for CXMLArchiveNode, cleans up resources.
     */
    virtual ~CXMLArchiveNode();

    /**
     * @brief Creates a new data node in the XML document.
     * @param attrName The name of the data attribute.
     * @param attrValue The value of the attribute.
     * @return A pointer to the created data node.
     */
    MSXML::IXMLDOMNodePtr CreateDataNode(LPCTSTR attrName, CString attrValue);

    /**
     * @brief Retrieves the data node for a given name from the XML document.
     * @param nodeName The name of the data node.
     * @param nodeText A reference to store the node's text value.
     * @return A pointer to the data node.
     */
    MSXML::IXMLDOMNodePtr GetDataNode(LPCTSTR nodeName, CString& nodeText);

    /**
     * @brief Retrieves the number of children for the current node.
     * @return The number of child nodes.
     */
    int GetNoChildren();

    /**
     * @brief Retrieves the name of a child node at a specific index.
     * @param childIndex The index of the child node.
     * @return The name of the child node.
     */
    CString GetChildName(int childIndex);

    /**
     * @brief Retrieves the next child index for iterating over children.
     * @return The next child index.
     */
    int GetNextChildIndex();

    /**
     * @brief Closes the current node, ending its processing.
     */
    void Close();

    /**
     * @brief Sets data for an attribute with various types.
     * @param attrName The name of the attribute.
     * @param attrValue The value of the attribute.
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
     * @brief Loads data into an existing object.
     * @param attrName The name of the attribute.
     * @param object The object to load data into.
     */
    void DataNode(LPCTSTR attrName, CObject& object);

    /**
     * @brief Creates a new object when loading data.
     * @param attrName The name of the attribute.
     * @param objectPtr A pointer to the object to be created.
     */
    void DataNode(LPCTSTR attrName, CObject*& objectPtr);

    /**
     * @brief Creates a new object based on the node's name.
     * @param className The class name used to create the object.
     * @return A pointer to the created object.
     */
    static CObject* CreateObject(const CString& className);
};
