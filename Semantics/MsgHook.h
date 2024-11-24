// Заголовочный файл защиты от двойного включения
#pragma once

// Пользовательское сообщение для скрытия редактора
#define UM_HIDEEDITOR (WM_USER+10)

/**
 * @class CMsgHook
 * @brief Класс для обработки хук-сообщений для окон и их родительско-дочерних связей.
 *
 * Этот класс предоставляет функционал для присоединения и отсоединения хуков к/от окон.
 * Он управляет взаимодействием между хук-сообщениями и связанными окнами.
 */
class CMsgHook
{
public:
	/**
	 * @brief Конструктор по умолчанию для CMsgHook.
	 */
	CMsgHook(void);

	/**
	 * @brief Деструктор для CMsgHook.
	 */
	virtual ~CMsgHook(void);

	/**
	 * @brief Присоединяет хук к определенному окну.
	 * @param hWnd Дескриптор окна, к которому нужно присоединить хук.
	 * @param hParent Дескриптор родительского окна.
	 * @param hNotify Дополнительный дескриптор окна уведомления (по умолчанию NULL).
	 * @return TRUE, если хук был успешно присоединен, FALSE в противном случае.
	 */
	BOOL Attach(HWND hWnd, HWND hParent, HWND hNotify = NULL);

	/**
	 * @brief Отсоединяет хук от окна.
	 * @return TRUE, если хук был успешно отсоединен, FALSE в противном случае.
	 */
	BOOL Detach(void);

	/**
	 * @brief Проверяет, присоединен ли хук к окну в данный момент.
	 * @return TRUE, если хук присоединен, FALSE в противном случае.
	 */
	inline BOOL IsAttached() { return m_hWnd != NULL; }

protected:
	/**
	 * @brief Процедура обратного вызова, обрабатывающая хук-сообщения.
	 * @param nCode Код хука.
	 * @param wParam Дополнительная информация специфичная для сообщения.
	 * @param lParam Дополнительная информация специфичная для сообщения.
	 * @return Результат обработки сообщения.
	 */
	static LRESULT CALLBACK CallWndRetProc(int nCode, WPARAM wParam, LPARAM lParam);

	/** Статический дескриптор хука для глобального хука. */
	static HHOOK m_hHook;

	/** Количество экземпляров активных хуков. */
	static int m_nInstances;

	/**
	 * @brief Карта, связывающая окна с их хуками.
	 * Эта карта хранит сопоставление между дескриптором окна (HWND) и соответствующим экземпляром CMsgHook.
	 */
	static CMap<HWND, HWND&, CMsgHook*, CMsgHook*&> m_mapHookedWindows;

	/** Дескриптор окна, к которому присоединен хук. */
	HWND m_hWnd;

	/** Дескриптор родительского окна захуканного окна. */
	HWND m_hParent;

	/** Дескриптор окна уведомления. */
	HWND m_hNotify;

	/** Флаг, указывающий, активен ли dropdown. */
	BOOL m_bDropDown;
};