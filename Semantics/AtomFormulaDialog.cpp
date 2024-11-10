//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014
// AksiomaDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "Semantics.h"
#include "AtomFormulaDialog.h"
#include "afxdialogex.h"
#include "common_functions.h"


//TRANSLATED

// диалоговое окно CAtomFormulaDialog

IMPLEMENT_DYNAMIC(CAtomFormulaDialog, CDialog)

//
// конструктор
//
CAtomFormulaDialog::CAtomFormulaDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAtomFormulaDialog::IDD, pParent)
{
	tbuf1 = NULL;
	tbuf2 = NULL;
	tbuf_index1 = NULL;
	tbuf_index2 = NULL;
	m_fSymbol = NULL;
	m_fIndexes = NULL;
}

//
// деструктор
//
CAtomFormulaDialog::~CAtomFormulaDialog()
{
	// свобождаю созданные ресурсы
	if(tbuf1)
		delete tbuf1;
	if(tbuf2)
		delete tbuf2;
	if(tbuf_index1)
		delete tbuf_index1;
	if(tbuf_index2)
		delete tbuf_index2;
	if(m_fSymbol)
		delete m_fSymbol;
	if(m_fIndexes)
		delete m_fIndexes;
}

void CAtomFormulaDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DESCRIPTION, m_lblDescription);
	DDX_Control(pDX, IDC_EDIT3, m_index1);
	DDX_Control(pDX, IDC_EDIT4, m_index2);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
}


BEGIN_MESSAGE_MAP(CAtomFormulaDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CAtomFormulaDialog::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL CAtomFormulaDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_index1.SetWindowText(_T("0"));  // задаю по умолчанию индекс для переменной
	m_index2.SetWindowText(_T("0"));  // задаю по умолчанию индекс для множества
	LPCTSTR lpszSelect1 = _T("x");    // задаю по умолчанию обозначение переменной
	LPCTSTR lpszSelect2 = _T("A");    // задаю по умолчанию обозначение множества

	// задаю элементы комбо, которые отображаются первоначально
	int nSel = m_combo1.SelectString(0, lpszSelect1);
	int nSel1 = m_combo2.SelectString(0, lpszSelect2);
	
	// создаю шрифт по умолчанию
	m_fIndexes = new CFont;
	m_fIndexes->CreatePointFont(70, L"Arial Unicode MS");
//	m_fIndexes->CreatePointFont(70, L"Microsoft San Serif");
	m_lblDescription.m_fIndexes = m_fIndexes;
	// создаю шрифт для математических символов
	m_fSymbol = new CFont;
//	m_fSymbol->CreatePointFont(140, L"Symbol");
	m_fSymbol->CreatePointFont(140, L"Arial Unicode MS");
	m_lblDescription.m_fSymbol = m_fSymbol;
	CString cs;
	m_lblDescription.GetWindowTextT(cs);
	tstring tstr = cs;
	m_lblDescription.dsi->PrepareSubItemData(tstr);

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}


// обработчики сообщений CAtomFormulaDialog

//
// обработчик нажатия кнопки "Добавить"
//
void CAtomFormulaDialog::OnBnClickedOk()
{
	// очищаю созданные перед этим буферы данных
	if(tbuf1)
		delete tbuf1;
	if(tbuf2)
		delete tbuf2;
	if(tbuf_index1)
		delete tbuf_index1;
	if(tbuf_index2)
		delete tbuf_index2;
	tbuf1 = NULL;
	tbuf2 = NULL;
	tbuf_index1 = NULL;
	tbuf_index2 = NULL;

	int nIndex = m_combo1.GetCurSel();    // получаю индекс выбранного элемента для обозначения переменной
	int nCount = m_combo1.GetCount();    // получаю количество элементов всписке обозначений переменной
	if ((nIndex != CB_ERR) && (nCount > 1))    // если выбран
	{
		int len = m_combo1.GetLBTextLen(nIndex);    // длина текста элемента
		tbuf1 = new TCHAR[len + 2];    // создаю буфер для хранения текста переменной
		m_combo1.GetLBText(nIndex, (LPTSTR)tbuf1);    // сохраняю текст переменной в созданный буфер
		nIndex = m_combo2.GetCurSel();    // получаю индекс выбранного элемента для обозначения множества
		nCount = m_combo2.GetCount();    // получаю количество элементов в списке обозначений множества
		if ((nIndex != CB_ERR) && (nCount > 1))   // если выбран
		{
			int len = m_combo1.GetLBTextLen(nIndex);    // длина текста элемента
			tbuf2 = new TCHAR[len + 2];    // создаю буфер для хранения текста множества
			m_combo2.GetLBText(nIndex, (LPTSTR)tbuf2);    // сохраняю текст множества в созданный буфер
			len = m_index1.GetWindowTextLengthW();    // длина текста индекса переменной
			tbuf_index1 = new TCHAR[len + 2];    // создаю буфер для хранения текста индекса переменной
			m_index1.GetWindowTextT(tbuf_index1, len + 1);    // сохраняю текст индекса переменной в созданный буфер
			tstring ind1 = tbuf_index1;
			trimWhitespaces(&ind1);
			if(ind1.length() > 0)
			{
				if(find_if_not(ind1.begin(), ind1.end(), istdigit) == ind1.end())
				{
					len = m_index2.GetWindowTextLengthW();    // длина текста индекса множества
					tbuf_index2 = new TCHAR[len + 2];    // создаю буфер для хранения текста индекса множества
					m_index2.GetWindowTextT(tbuf_index2, len + 1);    // сохраняю текст индекса множества в созданный буфер
					tstring ind2 = tbuf_index2;
					trimWhitespaces(&ind2);
					if(ind2.length() > 0)
					{
						if(find_if_not(ind2.begin(), ind2.end(), istdigit) == ind2.end())
						{
							// TODO: добавьте свой код обработчика уведомлений
							CDialog::OnOK();
						}
						else

						{

							if (CURRENT_LANG_OF == "rus") 
								AfxMessageBox(_T("В индексе для второй переменной указано не число"));
							else 
								AfxMessageBox(_T("The index for the second variable does not specify a number"));
							m_index2.SetFocus();
						}
					}
					else
					{
						if (CURRENT_LANG_OF == "rus")
							AfxMessageBox(_T("Индекс для второй переменной не введен"));
						else
							AfxMessageBox(_T("The index for the second variable has not been entered"));
						m_index1.SetFocus();
					}
				}
				else
				{
					if (CURRENT_LANG_OF == "rus")
						AfxMessageBox(_T("В индексе для первой переменной указано не число"));
					else
						AfxMessageBox(_T("The index for the first variable does not specify a number"));
					m_index1.SetFocus();
				}
			}
			else
			{
				if (CURRENT_LANG_OF == "rus")
					AfxMessageBox(_T("Индекс для первой переменной не введен"));
				else
					AfxMessageBox(_T("The index for the first variable is not entered"));
				m_index1.SetFocus();
			}
		}
		else
		{
			if (CURRENT_LANG_OF == "rus")
				AfxMessageBox(_T("Не выбрано обозначение для второй переменной"));
			else
				AfxMessageBox(_T("The designation for the second variable is not selected"));
			m_combo2.SetFocus();
		}
	}
	else
	{
		if (CURRENT_LANG_OF == "rus")
			AfxMessageBox(_T("Не выбрано обозначение для первой переменной"));
		else
			AfxMessageBox(_T("The designation for the first variable is not selected"));
		m_combo1.SetFocus();
	}
}
