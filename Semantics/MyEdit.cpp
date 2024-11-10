// MyEdit.cpp: файл реализации
//

#include "stdafx.h"
#include "Semantics.h"
#include "MyEdit.h"


// CMyEdit

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)

CMyEdit::CMyEdit()
{

}

CMyEdit::~CMyEdit()
{
}

/*
void CMyEdit::OnInitialUpdate()
{
    m_PopupMenu.LoadMenu(IDR_MENU_SYMBOLS);
        ASSERT(m_PopupMenu!=NULL);
}
*/
BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_Menu_Low, &CMyEdit::OnMenuLow)
	ON_COMMAND(ID_Menu_Left_Tag, &CMyEdit::OnMenuLeftTag)
	ON_COMMAND(ID_Menu_Right_Tag, &CMyEdit::OnMenuRightTag)
	ON_COMMAND(ID_Menu_High, &CMyEdit::OnMenuHigh)
	ON_COMMAND(ID_Menu_First_Qwantor, &CMyEdit::OnMenuFirstQwantor)
	ON_COMMAND(ID_Menu_Second_Qwantor, &CMyEdit::OnMenuSecondQwantor)
	ON_COMMAND(ID_Menu_And, &CMyEdit::OnMenuAnd)
	ON_COMMAND(ID_Menu_Or, &CMyEdit::OnMenuOr)
	ON_COMMAND(ID_Menu_Have, &CMyEdit::OnMenuHave)
	ON_COMMAND(ID_Menu_Left, &CMyEdit::OnMenuLeft)
	ON_COMMAND(ID_Menu_Right, &CMyEdit::OnMenuRight)
	ON_COMMAND(ID_Menu_Not, &CMyEdit::OnMenuNot)
	ON_COMMAND(ID_Menu_Similar, &CMyEdit::OnMenuSimilar)
	ON_COMMAND(ID_Menu_Union, &CMyEdit::OnMenuUnion)
	ON_COMMAND(ID_Menu_Crossing, &CMyEdit::OnMenuCrossing)
	ON_COMMAND(ID_Menu_EmptySet, &CMyEdit::OnMenuEmptyset)
	ON_COMMAND(ID_MENU_FUZZY_INCLUSION, &CMyEdit::OnMenuFuzzyInclusion)
END_MESSAGE_MAP()



// обработчики сообщений CMyEdit




void CMyEdit::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений
//        m_PopupMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, pos.x, pos.y, AfxGetMainWnd());
     CMenu menu;
    menu.LoadMenu(IDR_MENU_SYMBOLS);
 
    CMenu* pPopup = menu.GetSubMenu(0);
	int nStartChar = 0;
	int nEndChar = 0;
	GetSel(nStartChar, nEndChar);
	if(nStartChar!=nEndChar)
	{
		pPopup->EnableMenuItem(ID_Menu_Low, MF_ENABLED | MF_BYCOMMAND);
		pPopup->EnableMenuItem(ID_Menu_High, MF_ENABLED | MF_BYCOMMAND);
	} 
     ASSERT(pPopup != NULL);
 
    pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}


void CMyEdit::OnMenuLow()
{
	int nStartChar = 0;
	int nEndChar = 0;
	GetSel(nStartChar, nEndChar);
	if(nStartChar!=nEndChar)
	{
		CString newstr;
		CString str;
		this->GetWindowText(str);
		for(int i = nStartChar; i < nEndChar; i++)
		{
			if((str[i] != '\r') && (str[i] != '\r'))
			{
				newstr += _T("<Symbol=/low>");
				newstr += str[i];
			}
		}
		this->ReplaceSel(newstr);
	}
	// TODO: добавьте свой код обработчика команд
}


void CMyEdit::OnMenuLeftTag()
{
	// TODO: добавьте свой код обработчика команд
	CString newstr;
	newstr += _T("<Symbol=/left_tag>");
	this->ReplaceSel(newstr);
}


void CMyEdit::OnMenuRightTag()
{
	// TODO: добавьте свой код обработчика команд
	CString newstr;
	newstr += _T("<Symbol=/right_tag>");
	this->ReplaceSel(newstr);
}


void CMyEdit::OnMenuHigh()
{
	int nStartChar = 0;
	int nEndChar = 0;
	GetSel(nStartChar, nEndChar);
	if(nStartChar!=nEndChar)
	{
		CString newstr;
		CString str;
		this->GetWindowText(str);
		for(int i = nStartChar; i < nEndChar; i++)
		{
			if((str[i] != '\r') && (str[i] != '\r'))
			{
				newstr += _T("<Symbol=/high>");
				newstr += str[i];
			}
		}
		this->ReplaceSel(newstr);
	}	// TODO: добавьте свой код обработчика команд
}


void CMyEdit::OnMenuFirstQwantor()
{
	// TODO: добавьте свой код обработчика команд
	CString newstr;
	newstr += _T("<Symbol=/34>");
	this->ReplaceSel(newstr);
}


void CMyEdit::OnMenuSecondQwantor()
{
	// TODO: добавьте свой код обработчика команд
	CString newstr;
	newstr += _T("<Symbol=/36>");
	this->ReplaceSel(newstr);
}


void CMyEdit::OnMenuAnd()
{
	// TODO: добавьте свой код обработчика команд
	CString newstr;
	newstr += _T("<Symbol=/and>");
	this->ReplaceSel(newstr);
}


void CMyEdit::OnMenuOr()
{
	// TODO: добавьте свой код обработчика команд
	CString newstr;
	newstr += _T("<Symbol=/or>");
	this->ReplaceSel(newstr);
}


void CMyEdit::OnMenuHave()
{
	// TODO: добавьте свой код обработчика команд
	CString newstr;
	newstr += _T("<Symbol=/in>");
	this->ReplaceSel(newstr);
}


void CMyEdit::OnMenuLeft()
{
	// TODO: добавьте свой код обработчика команд
	CString newstr;
	newstr += _T("<Symbol=/123>");
	this->ReplaceSel(newstr);
}


void CMyEdit::OnMenuRight()
{
	// TODO: добавьте свой код обработчика команд
	CString newstr;
	newstr += _T("<Symbol=/125>");
	this->ReplaceSel(newstr);
}


void CMyEdit::OnMenuNot()
{
	// TODO: добавьте свой код обработчика команд
	CString newstr;
	newstr += _T("<Symbol=/not>");
	this->ReplaceSel(newstr);
}


void CMyEdit::OnMenuSimilar()
{
	// TODO: добавьте свой код обработчика команд
	CString newstr;
	newstr += _T("<Symbol=/similar>");
	this->ReplaceSel(newstr);
}


void CMyEdit::OnMenuUnion()
{
	// TODO: добавьте свой код обработчика команд
	CString newstr;
	newstr += _T("<Symbol=/union>");
	this->ReplaceSel(newstr);
}


void CMyEdit::OnMenuCrossing()
{
	// TODO: добавьте свой код обработчика команд
	CString newstr;
	newstr += _T("<Symbol=/crossing>");
	this->ReplaceSel(newstr);
}


void CMyEdit::OnMenuEmptyset()
{
	// TODO: добавьте свой код обработчика команд
		CString newstr;
	newstr += _T("<Symbol=/empty>");
	this->ReplaceSel(newstr);
}


void CMyEdit::OnMenuFuzzyInclusion()
{
	// TODO: добавьте свой код обработчика команд
		CString newstr;
	newstr += _T("<Symbol=/fuzzy>");
	this->ReplaceSel(newstr);
}