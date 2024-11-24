// Semantics.h : Заголовочный файл для класса CSemanticsApp в приложении PROJECT_NAME.

#pragma once

#ifndef __AFXWIN_H__
	#error "Включите 'stdafx.h' перед включением этого файла для PCH."
#endif

#include "resource.h"    // Файл ресурсов
#include <string>

// Глобальная переменная для хранения текущей языковой настройки приложения
__declspec(selectany) std::string CURRENT_LANG_OF("eng");

/**
 * @class CSemanticsApp
 * @brief Представляет класс приложения для проекта Semantics.
 *
 * Класс CSemanticsApp наследуется от CWinApp и содержит логику инициализации
 * и настройки приложения. Он служит точкой входа в приложение Semantics.
 */
class CSemanticsApp : public CWinApp
{
public:
	/**
	 * @brief Конструктор по умолчанию для класса CSemanticsApp.
	 *
	 * Инициализирует объект CSemanticsApp, настраивая необходимые свойства
	 * для приложения.
	 */
	CSemanticsApp();

	// Инициализация

public:
	/**
	 * @brief Инициализирует экземпляр приложения.
	 *
	 * Этот метод вызывается для инициализации приложения, настраивая необходимые
	 * ресурсы и состояния для работы приложения.
	 *
	 * @return TRUE, если инициализация прошла успешно, FALSE в противном случае.
	 */
	virtual BOOL InitInstance();

	// Реализация

	/**
	 * @brief Объявляет таблицу сообщений для приложения.
	 *
	 * Этот раздел используется для отображения сообщений (например, событий, действий пользователя) на
	 * соответствующие функции-обработчики в приложении.
	 */
	DECLARE_MESSAGE_MAP()
};

// Глобальный экземпляр класса CSemanticsApp
extern CSemanticsApp theApp;