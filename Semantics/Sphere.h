/**
* @class Sphere
 * @brief This class represents a sphere with position and radius.
 *
 * The class provides methods for calculating the volume and surface area of the sphere, as well as displaying
 * and resizing the sphere in a graphical context using OpenGL.
 */
class Sphere
{
public:
	/**
	 * @brief Default constructor for the Sphere class.
	 * Initializes the position (x, y, z) and radius (r) of the sphere to default values.
	 */
	Sphere(void);

	/**
	 * @brief Destructor for the Sphere class.
	 * Cleans up any resources used by the Sphere object.
	 */
	~Sphere(void);

	/**
	 * @var x, y, z
	 * @brief The coordinates of the center of the sphere.
	 */
	double x, y, z;

	/**
	 * @var r
	 * @brief The radius of the sphere.
	 */
	double r;

	/**
	 * @brief Parameterized constructor for the Sphere class.
	 * Initializes the sphere with the specified position (x, y, z) and radius (r).
	 * @param xc The x-coordinate of the center of the sphere.
	 * @param yc The y-coordinate of the center of the sphere.
	 * @param zc The z-coordinate of the center of the sphere.
	 * @param rc The radius of the sphere.
	 */
	Sphere (double xc, double yc, double zc, double rc)
	{ x=xc; y=yc; z=zc; r=rc; }

	/**
	 * @brief Calculates the volume of the sphere.
	 * The formula used is V = (4/3) * π * r^3.
	 * @return The volume of the sphere.
	 */
	double ob()
	{
		return r*r*r*4*M_PI/3;
	}

	/**
	 * @brief Calculates the surface area of the sphere.
	 * The formula used is A = 4 * π * r^2.
	 * @return The surface area of the sphere.
	 */
	double pov()
	{
		return r*r*4*M_PI;
	}

	/**
	 * @brief Resizes the OpenGL viewport when the window is resized.
	 * @param width The new width of the window.
	 * @param height The new height of the window.
	 */
	void CALLBACK resize(int width,int height);

	/**
	 * @brief Displays the sphere in the OpenGL context.
	 * This function is called to render the sphere using OpenGL drawing functions.
	 */
	void CALLBACK display(void);
};
