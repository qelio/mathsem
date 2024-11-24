/**
 * @struct VUEPoint
 * @brief A structure representing a point in the VUE (Visual Understanding Environment) coordinate system.
 *
 * This structure holds the x and y coordinates of a point in a 2D space.
 */
struct VUEPoint
{
    double x; ///< X-coordinate of the point.
    double y; ///< Y-coordinate of the point.
};

/**
 * @class VUELink
 * @brief A class representing a link between two VUE nodes in the VUE environment.
 *
 * This class is used to model connections between nodes, including graphical properties such as position, size, stroke style, and color.
 * It provides methods to set and manage links between different types of entities, such as nodes and formulas.
 */
class VUELink
{
    double x; ///< X-coordinate of the link.
    double y; ///< Y-coordinate of the link.
    double width; ///< Width of the link.
    double height; ///< Height of the link.
    string strokeStyle; ///< Stroke style of the link.
    string strokeColor; ///< Stroke color of the link.
    string textColor; ///< Text color of the link.
    string strokeWidth; ///< Stroke width of the link.
    string font; ///< Font style of the link.
    VUEPoint start; ///< Starting point of the link.
    VUEPoint finish; ///< Ending point of the link.
    VUENode * nodeStart; ///< Pointer to the start node of the link.
    VUENode * nodeFinish; ///< Pointer to the finish node of the link.
    int numberInLayer; ///< Layer number of the link.
    int childID; ///< ID of the child entity associated with the link.

public:
    /**
     * @brief Default constructor for the VUELink class.
     * Initializes the VUELink with default values.
     */
    VUELink(void);

    /**
     * @brief Destructor for the VUELink class.
     * Cleans up any resources associated with the link.
     */
    ~VUELink(void);

    /**
     * @brief Parameterized constructor for creating a VUELink with specified child ID and layer number.
     * @param childID_ The ID of the child entity.
     * @param numberInLayer_ The layer number of the link.
     */
    VUELink(int childID_, int numberInLayer_);

    /**
     * @brief Prints the details of the VUELink to the given output stream.
     * @param os The output stream to which the link details will be printed.
     */
    void print(ostream& os);

    /**
     * @brief A vector of control points defining the link's shape.
     */
    vector <VUEPoint *> ctrlPoints;

    /**
     * @brief Sets the link between two VUE nodes.
     * @param node1 The start node of the link.
     * @param node2 The finish node of the link.
     */
    void setLink(VUENode * node1, VUENode * node2);

    /**
     * @brief Sets the link between a VUE formula node and a VUE set node.
     * @param node1 The start node of the link (a formula).
     * @param node2 The finish node of the link (a set).
     */
    void setLink(VUEFormula * node1, VUESet * node2);

    /**
     * @brief Sets the link between two VUE formula nodes.
     * @param node1 The start node of the link (a formula).
     * @param node2 The finish node of the link (a formula).
     */
    void setLink(VUEFormula * node1, VUEFormula * node2);

    /**
     * @brief Sets the child ID and layer number for the link.
     * @param childID_ The ID of the child entity.
     * @param numberInLayer_ The layer number of the link.
     */
    void setIDs(int childID_, int numberInLayer_);

    /**
     * @brief Sets the type of the link.
     * @param ft The entity base type that determines the link type.
     */
    void setLinkType(EntityBaseType ft);
};
