#pragma once

#define UM_HIDEEDITOR (WM_USER+10)

/**
 * @class CMsgHook
 * @brief A class for handling message hooks for windows and their parent-child relationships.
 *
 * This class provides functionality for attaching and detaching hooks to/from windows.
 * It manages the interaction between the hook and the associated windows.
 */
class CMsgHook
{
public:
	/**
	 * @brief Default constructor for CMsgHook.
	 */
	CMsgHook(void);

	/**
	 * @brief Destructor for CMsgHook.
	 */
	virtual ~CMsgHook(void);

	/**
	 * @brief Attaches a hook to a specific window.
	 * @param hWnd The handle of the window to attach the hook to.
	 * @param hParent The handle of the parent window.
	 * @param hNotify Optional handle of a notification window (default is NULL).
	 * @return TRUE if the hook was successfully attached, FALSE otherwise.
	 */
	BOOL Attach(HWND hWnd, HWND hParent, HWND hNotify = NULL);

	/**
	 * @brief Detaches the hook from the window.
	 * @return TRUE if the hook was successfully detached, FALSE otherwise.
	 */
	BOOL Detach(void);

	/**
	 * @brief Checks if the hook is currently attached to a window.
	 * @return TRUE if the hook is attached, FALSE otherwise.
	 */
	inline BOOL IsAttached() { return m_hWnd != NULL; }

protected:
	/**
	 * @brief Callback procedure that processes hook messages.
	 * @param nCode The hook code.
	 * @param wParam Additional message-specific information.
	 * @param lParam Additional message-specific information.
	 * @return The result of the message processing.
	 */
	static LRESULT CALLBACK CallWndRetProc(int nCode, WPARAM wParam, LPARAM lParam);

	/** Static hook handle for the global hook. */
	static HHOOK m_hHook;

	/** The number of instances of active hooks. */
	static int m_nInstances;

	/**
	 * @brief A map associating windows with their hooks.
	 * This map stores a mapping between the window handle (HWND) and the corresponding CMsgHook instance.
	 */
	static CMap<HWND, HWND&, CMsgHook*, CMsgHook*&> m_mapHookedWindows;

	/** Handle to the window that the hook is attached to. */
	HWND m_hWnd;

	/** Handle to the parent window of the hooked window. */
	HWND m_hParent;

	/** Handle to the notification window. */
	HWND m_hNotify;

	/** A flag indicating if the dropdown is active. */
	BOOL m_bDropDown;
};
