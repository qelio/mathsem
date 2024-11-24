// Semantics.h : Header file for the CSemanticsApp class in the PROJECT_NAME application.

#pragma once

#ifndef __AFXWIN_H__
	#error "Include 'stdafx.h' before including this file for PCH."
#endif

#include "resource.h"    // Resource file
#include <string>

// A global variable to store the current language setting of the application
__declspec(selectany) std::string CURRENT_LANG_OF("eng");

/**
 * @class CSemanticsApp
 * @brief Represents the application class for the Semantics project.
 *
 * The CSemanticsApp class is derived from CWinApp and contains the initialization
 * and setup logic for the application. It serves as the entry point to the Semantics application.
 */
class CSemanticsApp : public CWinApp
{
public:
	/**
	 * @brief Default constructor for the CSemanticsApp class.
	 *
	 * Initializes the CSemanticsApp object, setting up any necessary properties
	 * for the application.
	 */
	CSemanticsApp();

	// Initialization

public:
	/**
	 * @brief Initializes the application instance.
	 *
	 * This method is called to initialize the application, setting up the necessary
	 * resources and state for the application to run.
	 *
	 * @return TRUE if the initialization is successful, FALSE otherwise.
	 */
	virtual BOOL InitInstance();

	// Implementation

	/**
	 * @brief Declares the message map for the application.
	 *
	 * This section is used to map messages (e.g., events, user actions) to
	 * appropriate handler functions in the application.
	 */
	DECLARE_MESSAGE_MAP()
};

// A global instance of the CSemanticsApp class
extern CSemanticsApp theApp;
