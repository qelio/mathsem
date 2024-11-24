// Автор: Татаринцев В.В., akizelokro@mail.ru, 2013-2014
#pragma once

#include "ScientificStatic.h"
#include "afxwin.h"

/*!
 * \class CAtomFormulaDialog
 * \brief Диалоговое окно для работы с атомными формулами.
 *
 * Этот класс предоставляет интерфейс для редактирования атомных формул с использованием различных элементов управления,
 * включая метки, поля ввода и комбинированные списки.
 */
class CAtomFormulaDialog : public CDialog
{
	DECLARE_DYNAMIC(CAtomFormulaDialog)

	/*!
	 * \brief Инициализация диалога.
	 *
	 * Эта функция вызывается при инициализации диалога. Она используется для выполнения
	 * любой настройки или конфигурации элементов управления диалогом.
	 * \return TRUE, если инициализация прошла успешно, FALSE в противном случае.
	 */
	BOOL OnInitDialog();

public:
	/*!
	 * \brief Конструктор для CAtomFormulaDialog.
	 *
	 * \param pParent Родительское окно для диалога (по умолчанию NULL).
	 */
	CAtomFormulaDialog(CWnd* pParent = NULL);

	/*!
	 * \brief Деструктор для CAtomFormulaDialog.
	 */
	virtual ~CAtomFormulaDialog();

	// Данные диалога
	enum { IDD = IDD_DIALOG1 };

protected:
	/*!
	 * \brief Обработка обмена данными между элементами управления и переменными.
	 *
	 * Эта функция связывает элементы управления диалогом с переменными-членами класса.
	 * \param pDX Объект обмена данными.
	 */
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	// Буфер символов для первого поля ввода
	TCHAR * tbuf1;

	// Буфер символов для второго поля ввода
	TCHAR * tbuf2;

	// Буфер символов для индекса первого поля ввода
	TCHAR * tbuf_index1;

	// Буфер символов для индекса второго поля ввода
	TCHAR * tbuf_index2;

	// Статическая метка для отображения описания
	CScientificStatic m_lblDescription;

	/*!
	 * \brief Обработчик события нажатия кнопки "OK".
	 *
	 * Эта функция вызывается при нажатии кнопки "OK" в диалоговом окне.
	 */
	afx_msg void OnBnClickedOk();

	// Шрифт для отображения индексов
	CFont * m_fIndexes;

	// Шрифт для отображения символов
	CFont * m_fSymbol;

	// Элемент управления редактированием для ввода первого индекса
	CEdit m_index1;

	// Элемент управления редактированием для ввода второго индекса
	CEdit m_index2;

	// Комбинированный список для выбора первой опции
	CComboBox m_combo1;

	// Комбинированный список для выбора второй опции
	CComboBox m_combo2;
};