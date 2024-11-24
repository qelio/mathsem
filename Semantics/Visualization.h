/**
* @class Visualization
 * @brief A class responsible for handling the visualization of graphical elements in a static control.
 *
 * This class inherits from CStatic and is used for rendering and displaying graphical elements, such as drawings or images, in a window.
 */
class Visualization : public CStatic
{
	/**
	 * @brief Declares the dynamic creation of the Visualization class.
	 * This macro enables the use of runtime class information for the class.
	 */
	DECLARE_DYNAMIC(Visualization)

public:
	/**
	 * @brief Default constructor for the Visualization class.
	 * Initializes the visualization control.
	 */
	Visualization();

	/**
	 * @brief Destructor for the Visualization class.
	 * Cleans up any resources used by the visualization control.
	 */
	virtual ~Visualization();

protected:
	/**
	 * @brief Message map for handling messages related to the Visualization class.
	 * This macro sets up the message map for processing window messages.
	 */
	DECLARE_MESSAGE_MAP()

public:
	/**
	 * @brief Handles the paint event for the visualization.
	 * This function is called when the window needs to be redrawn. It is responsible for painting the graphical elements in the visualization control.
	 */
	afx_msg void OnPaint();
};


