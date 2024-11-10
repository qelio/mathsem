//  Автор кода: Татаринцев В.В., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014

// SemanticsDlg.cpp : файл реализации
//

//


#include "stdafx.h"
#include "Semantics.h"
#include "SemanticsDlg.h"
#include "afxdialogex.h"
#include "AtomFormulaDialog.h"
#include "SummaryDialog.h"
#include "common_functions.h"
#include "SetDialog.h"
#include "OperationDlg.h"
#include "FromSetDialog.h"
#include "SemanticString.h"
#include "TupleDlg.h"
#include "ReplaceVariableDialog.h"
#include "Item.h"
#include "xmlarchive.h"
#include <fstream>
#include "CHelpDialog.h"
//#include <afxdisp.h>


#define VUEATOMICWITHNEGATIVE


#pragma region Import the type libraries

#import "libid:2DF8D04C-5BFA-101B-BDE5-00AA0044DE52" \
	rename("RGB", "MSORGB") \
	rename("DocumentProperties", "MSODocumentProperties")
// [-or-]
//#import "C:\\Program Files\\Common Files\\Microsoft Shared\\OFFICE12\\MSO.DLL" \
//	rename("RGB", "MSORGB") \
//	rename("DocumentProperties", "MSODocumentProperties")

using namespace Office;

#import "libid:0002E157-0000-0000-C000-000000000046"
// [-or-]
//#import "C:\\Program Files\\Common Files\\Microsoft Shared\\VBA\\VBA6\\VBE6EXT.OLB"

using namespace VBIDE;

#import "libid:00020905-0000-0000-C000-000000000046" \
	rename("ExitWindows", "WordExitWindows") \
	rename("FindText", "WordFindText")
// [-or-]
//#import "C:\\Program Files\\Microsoft Office\\Office12\\MSWORD.OLB" \
//	rename("ExitWindows", "WordExitWindows") \
//	rename("FindText", "WordFindText")

#pragma endregion


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// диалоговое окно CSemanticsDlg




CSemanticsDlg::CSemanticsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSemanticsDlg::IDD, pParent)
	, m_rbLang(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_Mathsem);

}

void CSemanticsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUILDFORMULA5, m_button5);
	DDX_Control(pDX, IDC_BUILDFORMULA4, m_button4);
	DDX_Control(pDX, IDC_BUILDFORMULA3, m_button3);
	DDX_Control(pDX, IDC_BUILDFORMULA2, m_button2);
	DDX_Control(pDX, IDC_BUILDFORMULA1, m_button1);
	DDX_Control(pDX, IDC_ADDAKSIOMA, m_button);
	DDX_Control(pDX, IDC_SHOWALLFORMULAS, m_button6);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_fileFinder);
	DDX_Control(pDX, IDC_BUILDFORMULA6, m_buttonSet);
	DDX_Control(pDX, IDC_MFCEDITBROWSE2, m_fileWordExport);
	//	DDX_Control(pDX, IDC_BUILDFORMULA7, m_button7);
	//DDX_Control(pDX, IDC_BUILDTUPLE, m_KortegeButton);
	DDX_Control(pDX, IDC_CHANGEVARIABLE, m_ChangeVariable);
	DDX_Radio(pDX, RB_RUS, m_rbLang);
}

BEGIN_MESSAGE_MAP(CSemanticsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSemanticsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_ADDAKSIOMA, &CSemanticsDlg::OnBnClickedAddatomformula)
	ON_BN_CLICKED(IDC_BUILDFORMULA1, &CSemanticsDlg::OnBnClickedBuildformula1)
	ON_BN_CLICKED(IDC_BUILDFORMULA2, &CSemanticsDlg::OnBnClickedBuildformula2)
	ON_BN_CLICKED(IDC_BUILDFORMULA3, &CSemanticsDlg::OnBnClickedBuildformula3)
	ON_BN_CLICKED(IDC_BUILDFORMULA4, &CSemanticsDlg::OnBnClickedBuildformula4)
	ON_BN_CLICKED(IDC_BUILDFORMULA5, &CSemanticsDlg::OnBnClickedBuildformula5)
	ON_BN_CLICKED(IDC_SHOWALLFORMULAS, &CSemanticsDlg::OnBnClickedShowallformulas)
	ON_BN_CLICKED(IDC_BUILDFORMULA6, &CSemanticsDlg::OnBnClickedBuildformula6)
	ON_BN_CLICKED(IDEXPORT, &CSemanticsDlg::OnBnClickedExport)
	ON_BN_CLICKED(IDSAVESCHEME, &CSemanticsDlg::OnBnClickedSavescheme)
	ON_BN_CLICKED(IDLOADSCHEME, &CSemanticsDlg::OnBnClickedLoadscheme)
	ON_BN_CLICKED(ID_HELP, &CSemanticsDlg::OnBnClickedHelp)
	ON_BN_CLICKED(IDCANCEL, &CSemanticsDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE2, &CSemanticsDlg::OnEnChangeMfceditbrowse2)
//	ON_BN_CLICKED(IDC_BUILDFORMULA7, &CSemanticsDlg::OnBnClickedBuildformula7)
// ON_BN_CLICKED(IDC_BUILDTUPLE, &CSemanticsDlg::OnBnClickedBuildtuple)
ON_BN_CLICKED(IDC_CHANGEVARIABLE, &CSemanticsDlg::OnBnClickedChangevariable)
ON_BN_CLICKED(RB_RUS, &CSemanticsDlg::OnBnClickedRus)
ON_BN_CLICKED(RB_ENG, &CSemanticsDlg::OnBnClickedEng)
END_MESSAGE_MAP()


void CSemanticsDlg::OnBnClickedHelp()
{
	CHelpDialog helpDlg;
	helpDlg.DoModal(); // Показ окна как модального
}

void CSemanticsDlg::OnBnClickedChangeNewVariable()
{
	ReplaceVariableDialog* rvd = new ReplaceVariableDialog(this);
	rvd->setEntities(&all_entities);
	if (rvd->DoModal() == IDOK)
	{
		// Добавьте свой код для обработки подтверждения
	}
	delete rvd;
}

// обработчики сообщений CSemanticsDlg

BOOL CSemanticsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна. Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	m_button4.addSciCharAction(32,FirstQuantor);
	m_button5.addSciCharAction(32,SecondQuantor);
	m_button4.addSciCharAction(39,LowerIndex);
	m_button5.addSciCharAction(39,LowerIndex);
	m_button1.addSciCharAction(26,LowerIndex);
	m_button2.addSciCharAction(26,LowerIndex);
	m_button3.addSciCharAction(26,LowerIndex);
	m_button4.addSciCharAction(26,LowerIndex);
	m_button5.addSciCharAction(26,LowerIndex);
	m_button1.addSciCharAction(31,LowerIndex);
	m_button2.addSciCharAction(31,LowerIndex);
	m_button3.addSciCharAction(35,LowerIndex);
	m_button1.addSciCharAction(37,LowerIndex);
	m_button2.addSciCharAction(36,LowerIndex);
//	m_button1.addSciCharAction(25,LowerIndex);
//	CFont * m_fLabels = GetFont();
//	LOGFONT logf;
//	m_fLabels->GetLogFont(&logf);
//	logf.lfHeight += 10;
//	logf.lfWeight = FW_BOLD;
//	wcscpy(logf.lfFaceName, L"Symbol");
//	m_button4.setSciFont(&logf);
//	m_button5.setSciFont(&logf);
//	CString strBitmap1;
//	bool bNameValid = strBitmap1.LoadString(IDB_BITMAP1QUANTOR1);
//	bitmap1.LoadBitmapW(IDB_BITMAP1QUANTOR1);
//	m_button5.SetBitmap(bitmap1);
//	TCHAR currDir[MAX_PATH];
	TCHAR currentDir[MAX_PATH];
	GetCurrentDirectory( MAX_PATH, currentDir );
	_tcsncat_s(currentDir, ARRAYSIZE(currentDir), _T("\\Sample1.docx"), 13 );
	m_fileFinder.SetWindowTextT(_T("D:\\VUE\\VUE-launcher.exe"));
	m_fileWordExport.SetWindowTextT(currentDir);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CSemanticsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок. Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CSemanticsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CSemanticsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//
//  построение схемы визуализации для построенных формул
//
void CSemanticsDlg::OnBnClickedOk()
{
//	SetDialog sd;
//	sd.DoModal();
	if(all_entities.size() < 1)
	{	
		if(CURRENT_LANG_OF=="rus")
			MessageBox(_T("Не определено ни одной формулы. Схема не будет построена"), _T("Замечание"), MB_OK);
		else
			MessageBox(_T("No formula has been defined. The scheme will not be built"), _T("Remark"), MB_OK);

		return;
	}
	int n = 1;
	setlocale(LC_ALL, "rus");
	// определение имени файла и текущего каталога, а также пути к фалу "легенды" для записи VUE-файла
	char currentDir[MAX_PATH];
	GetCurrentDirectoryA( MAX_PATH, currentDir );
	string legend(currentDir);
	legend += "\\";
	int pos = -1;
	while ( (pos = legend.find("\\", pos)) != string::npos )
	{
		legend.replace(pos, 1, "\\\\");
		pos += 2;
	}
//	legend.replace("\\", 0, "\\\\",);
	string filename("New-map");
	filename += to_string((long long)n);
	filename += "-copy.vue";
	string filename_with_path = currentDir;
	filename_with_path += "\\";
	filename_with_path += filename;
	ofstream tof(filename_with_path, ofstream::trunc | ofstream::out);
//	tof.open(filename_with_path, ofstream::out | ofstream::app | ofstream::trunc);
	string currentDirStr(currentDir);
	if(!tof.bad())
	{
		printFirstPartVUEHeader(tof, filename, currentDirStr); // вывожу в файл первую часть заголовка формируемого VUE-файла
		printVUELegend(tof, legend); // выводим легенду (фигурки с расшифровкой что кто обзоначает)

	// параметры по умолчанию
	double x= -354.0;
	double y = -199.0;
	double height = 160.0;  // высота узла
	double height_interval = 30.;  // расстояние между узлами по высоте
/*
	старое значение, использовалось при горизонтальной компоновке групп и с картинкой в качестве легенды
	int numberOfFirst = 8; // порядковый номер узла в самой компоновке схемы, не считая легенды
	double height_offset_atom = (1.5 *height) + (1.5 * height_interval); // смещение узла атомарной формулы от начала группы по высоте
	double offsetOfGroup = (height + height_interval) * 4;
	double interval = 200.0;  
	double width = 120.0;  // ширина узла
*/
	// новое значение, используется при вертикальной компоновке
	double width = 240.0;  // ширина узла
	int numberOfFirst = 13; // порядковый номер узла в самой компоновке схемы, не считая легенды
	double interval = 200.0;  
	double height_offset_atom = (1.5 * width) + (1.5 * height_interval); // смещение узла атомарной формулы от начала группы по высоте
	double offsetOfGroup = interval * 4;
//	int groupAtom = 0;
	int numberTotal = 0;
	vector <VUENode *> nodes;  // контейнер узлов схемы, узлы- атомарные формулы дублируются в контейнере atomics
	vector <VUEFormula *> atomics; // контейнер атомарных формул, самых "узловых" узлов, потому что от них строятся группы узлов
	vector <VUENode *> loose;  // контейнер узлов, оказавшихся несвязанными ни с одной из групп, основанных на атомарных формулах
	vector <VUELink *> links;  // контейнер связей между узлами

	//  подготовка списка узлов (формул и множеств) для дальнейшей обработки и записи в VUE-файл
	int numberOfSets = 0;	// число множеств истинности
	int numberOfNonAtomicFormulas = 0;	// число неатомарных формул
	int numberOfAtomicFormulas = 0;	// число атомарных формул
	// подсчитываем множества истинности, атомарные и прочие формулы в схеме
	for(size_t i = 0; i < all_entities.size(); i++)
	{
		EntityBase * base = all_entities.at(i);
		if( base->getType() == FORMULA_SET )    // если сущность - множество истинности
			numberOfSets++;    // учитываем
		else    // иначе формула
		{
			Formula * pFormula = (Formula *)base;    // указатель на объект класса Formula
#ifdef VUEATOMICWITHNEGATIVE
			if(pFormula->isAtom() || (pFormula->isNegative() && get<0>(*pFormula->getParentLink(0))->isAtom() ) )  // если атомарная формула
			// или негативная формула, построенная применением операции отрицания к атомарной формуле
#else
			if(pFormula->isAtom())  // если атомарная формула
#endif
				numberOfAtomicFormulas++;    // суммируем как атомарную
			else
				numberOfNonAtomicFormulas++;    // суммируем как неатомарную
		}
	}
	// заранее определяем расположение атомарных формул (третья версия, в которой неатомарные формулы располагаются в первом ряду, а множества во втором
	// определяем макимальное число в любом из трёх рядов (атомарных, неатомарных формул и множеств истинности)
	int maxNodesAtRows = numberOfAtomicFormulas;
	if( numberOfSets > maxNodesAtRows)
		maxNodesAtRows = numberOfSets;
	if( numberOfNonAtomicFormulas > maxNodesAtRows)
		maxNodesAtRows = numberOfNonAtomicFormulas;
	// вычисляем необходимое смещение для атомарных формул
	int offsetForAtomic = 0;
	int intervalForAtomic = (width + height_interval) * (maxNodesAtRows - 1);
	if(maxNodesAtRows > numberOfAtomicFormulas)
	{
		intervalForAtomic += width;
		intervalForAtomic -= width * numberOfAtomicFormulas;
//		if(intervalForAtomic > 0)
//			intervalForAtomic -= height_interval;
		intervalForAtomic = (int)( ( (double)intervalForAtomic )/( (double)(numberOfAtomicFormulas + 1) ) );
		offsetForAtomic = intervalForAtomic;
	}
	else
	{
		intervalForAtomic = height_interval;
		offsetForAtomic = 0;
	}

	numberOfSets = 0;	// обнуляем число множеств истинности
	numberOfNonAtomicFormulas = 0;	// обнуляем число неатомарных формул
	numberOfAtomicFormulas = 0;	// обнуляем число атомарных формул


	for(size_t i = 0; i < all_entities.size(); i++)
	{
		EntityBase * base = all_entities.at(i);
		VUENode * newNode;
		if ( base->getType() == FORMULA_SET ) // если очередной экземпляр - множество
		{
			VUESet * node = new VUESet(numberOfFirst + numberTotal, 1 + numberTotal);
			newNode = (VUESet *)node;
			node->parentSet = (FormulaSet *)all_entities.at(i);
			numberTotal++;
			Formula * curr = node->parentSet->getParentFormula(); // родительская формула множества
			while( curr->getNumberOfParents() > 0) // проходим по самому быстрому перебору цепочки формул-родителей до той, у которой родителей нет
			{
//					curr = curr->getParentLink(0);
					curr = get<0>(*curr->getParentLink(0));
			}
			bool existAtomicLink = false;
			// 
			for(size_t j = 0; j < atomics.size(); j++)  // перебираем вектор атомарных формул, чтобы найти совпадающую с полученной curr
			{
//				VUENode * centerNode = atomics.at(j);
				VUEFormula * centerNode = (VUEFormula *)atomics.at(j);
				if ( centerNode->formula == curr ) // базовая для множества атомарная формула и, соответственно, группа
				{
					existAtomicLink = true;
					centerNode->numberInGroup++;
					node->groupAtom = centerNode->groupAtom;
					node->childProperties();
/*
предыдущий код с горизонтальным расположением
					node->SetPosition(x + (interval * ((centerNode->numberInGroup/4) + 1)), 
						y + (offsetOfGroup * (node->groupAtom - 1)) + (height + height_interval) * ((centerNode->numberInGroup%4) - 1), 
						width, 
						height);
*/
/*
предыдущий код с разсположением по три узла в ряд в атомарной группе

					node->SetPosition(x + (offsetOfGroup * (node->groupAtom - 1)) + ((width + height_interval) * ((centerNode->numberInGroup - 1)%3)), 
						y + (interval * ((centerNode->numberInGroup/4) + 1)), 
						width, 
						height);
*/
					numberOfSets++;
#ifdef VUEATOMICWITHNEGATIVE
					node->SetPosition(x + ((width + height_interval) * (numberOfSets - 1)), 
						y + ( (interval) * 2 + height + height_interval), 
						width, 
						height);
#else
					numberOfSets++;
					node->SetPosition(x + ((width + height_interval) * (numberOfSets - 1)), 
						y + ( (interval) * 2), 
						width, 
						height);
#endif
					break;
				}
			}
			if( !existAtomicLink )
				loose.push_back(newNode); // если родительской атомарной формулы не найдено, вносим в список "потерянных" узлов
		}
		else // если очередной экземпляр - формула
		{
			VUEFormula * node = new VUEFormula(numberOfFirst + numberTotal, 1 + numberTotal);
			newNode = (VUENode *)node;
			node->formula = (Formula *)all_entities.at(i);
			numberTotal++;
#ifndef VUEATOMICWITHNEGATIVE
			if(!node->formula->isAtom())  // если не атомарная формула
			{
				Formula * curr = node->formula;
				while( curr->getNumberOfParents() > 0)  // проходим по самому быстрому перебору цепочки формул-родителей до той, у которой родителей нет
				{
//					curr = curr->getParentLink(0);
					curr = get<0>(*curr->getParentLink(0));
				}
				bool existAtomicLink = false;
				for(size_t j = 0; j < atomics.size(); j++)  // перебираем вектор атомарных формул, чтобы найти совпадающую с полученной curr
				{
//					VUENode * centerNode = atomics.at(j);
					VUEFormula * centerNode = (VUEFormula *)atomics.at(j);
					if ( centerNode->formula == curr ) // базовая для множества атомарная формула и, соответственно, группа
					{
						existAtomicLink = true;
						centerNode->numberInGroup++;
						node->groupAtom = centerNode->groupAtom;
						node->childProperties();
/*
предыдущий код с горизонтальным расположением
						node->SetPosition(x + (interval * ((centerNode->numberInGroup/4) + 1)), 
							y + (offsetOfGroup * (node->groupAtom - 1)) + (height + height_interval) * ((centerNode->numberInGroup%4) - 1), 
							width, 
							height);
*/
/*
предыдущий код с разсположением по три узла в ряд в атомарной группе
						node->SetPosition(x + (offsetOfGroup * (node->groupAtom - 1)) + ((width + height_interval) * ((centerNode->numberInGroup - 1)%3)), 
							y + (interval * ((centerNode->numberInGroup/4) + 1)), 
							width, 
							height);
*/
						numberOfNonAtomicFormulas++;
						node->SetPosition(x + ((width + height_interval) * (numberOfNonAtomicFormulas - 1)), 
							y + (interval), 
							width, 
							height);
						break;
					}
				}
				if( !existAtomicLink )
					loose.push_back(newNode); // если родительской атомарной формулы не найдено, вносим в список "потерянных" узлов
			}
			else
			{
				// атомарная формула
				atomics.push_back(node);
				node->groupAtom = atomics.size();
/*
предыдущий код с горизонтальным расположением
				node->SetPosition(x , 
					y + (offsetOfGroup * (node->groupAtom - 1)) + height_offset_atom , 
						width, 
						height);
*/
/*
предыдущий код с разсположением по три узла в ряд в атомарной группе
				node->SetPosition(x + (offsetOfGroup * (node->groupAtom - 1)) + height_offset_atom , 
					y, 
						width, 
						height);
*/
//				numberOfAtomicFormulas++;
				node->SetPosition(x + ((intervalForAtomic + width) * (node->groupAtom - 1)) +  offsetForAtomic, 
					y, 
					width, 
					height);
			}
#else
			if(!node->formula->isAtom() )  // если не атомарная формула
			// и не формула, построенная применением операции отрицания к атомарной формуле
			{
				Formula * curr = node->formula;
				while( curr->getNumberOfParents() > 0)  // проходим по самому быстрому перебору цепочки формул-родителей до той, у которой родителей нет
				{
//					curr = curr->getParentLink(0);
					curr = get<0>(*curr->getParentLink(0));
				}
				bool existAtomicLink = false;
				for(size_t j = 0; j < atomics.size(); j++)  // перебираем вектор атомарных формул, чтобы найти совпадающую с полученной curr
				{
//					VUENode * centerNode = atomics.at(j);
					VUEFormula * centerNode = (VUEFormula *)atomics.at(j);
					if ( centerNode->formula == curr ) // базовая для множества атомарная формула и, соответственно, группа
					{
						existAtomicLink = true;
						node->groupAtom = centerNode->groupAtom;
						node->childProperties();
						if ( !(node->formula->isNegative() && get<0>(*node->formula->getParentLink(0))->isAtom() ) )
						{
							centerNode->numberInGroup++;
/*
предыдущий код с горизонтальным расположением
						node->SetPosition(x + (interval * ((centerNode->numberInGroup/4) + 1)), 
							y + (offsetOfGroup * (node->groupAtom - 1)) + (height + height_interval) * ((centerNode->numberInGroup%4) - 1), 
							width, 
							height);
*/
/*
предыдущий код с разсположением по три узла в ряд в атомарной группе
						node->SetPosition(x + (offsetOfGroup * (node->groupAtom - 1)) + ((width + height_interval) * ((centerNode->numberInGroup - 1)%3)), 
							y + (interval * ((centerNode->numberInGroup/4) + 1)), 
							width, 
							height);
*/
							numberOfNonAtomicFormulas++;
							node->SetPosition(x + ((width + height_interval) * (numberOfNonAtomicFormulas - 1)), 
								y + (interval) + height_interval + height, 
								width, 
								height);
							break;
						}
						else
						{
/*
							node->SetPosition(x + ((width + height_interval) * (numberOfNonAtomicFormulas - 1)), 
								y + height_interval + height, 
								width, 
								height);
*/
							node->SetPosition(x + ((intervalForAtomic + width) * (node->groupAtom - 1)) +  offsetForAtomic, 
								y + (interval), 
								width, 
								height);
						}
					}
				}
				if( !existAtomicLink )
					loose.push_back(newNode); // если родительской атомарной формулы не найдено, вносим в список "потерянных" узлов
			}
			else
			{
				// атомарная формула 
				atomics.push_back(node);
				node->groupAtom = atomics.size();
/*
предыдущий код с горизонтальным расположением
				node->SetPosition(x , 
					y + (offsetOfGroup * (node->groupAtom - 1)) + height_offset_atom , 
						width, 
						height);
*/
/*
предыдущий код с разсположением по три узла в ряд в атомарной группе
				node->SetPosition(x + (offsetOfGroup * (node->groupAtom - 1)) + height_offset_atom , 
					y, 
						width, 
						height);
*/
//				numberOfAtomicFormulas++;
				node->SetPosition(x + ((intervalForAtomic + width) * (node->groupAtom - 1)) +  offsetForAtomic, 
					y, 
					width, 
					height);
			}
#endif
		}
		nodes.push_back(newNode);
//		node->SetPosition(x + (width + 30.0)* i, y + (height + 30.0) * i, 133.0, 167.0);
//		tof << node << endl;
//		node.print(tof);
	}

	// запись информации в файл об узлах
	for(size_t j = 0; j < nodes.size(); j++)
	{
		VUENode * node = nodes.at(j);
		if(node->GetType() == VUEFORMULA)
		{
			((VUEFormula *)node)->print(tof);
		}
		else if(node->GetType() == VUESET)
		{
			((VUESet *)node)->print(tof);
		}
	}

	// подготовка информации о существующих связях
	// цикл по всем узлам
	for(size_t j = 0; j < nodes.size(); j++)
	{
		VUENode * node = nodes.at(j);
		if(node->GetType() == VUEFORMULA)    // если узел представляет формулу
		{
			Formula * curr = ((VUEFormula *)nodes.at(j))->formula;
			// цикл по всем родительским связям
			for ( size_t j1 = 0 ; j1 < curr->getNumberOfParents(); j1++)
			{
				Formula * parent = get<0>(*curr->getParentLink(j1));    // указатель на формулу-родитель в связи
				for(size_t j2 = 0; j2 < nodes.size(); j2++)    // цикл по всем узлам
				{
					if(nodes.at(j)->GetType() == VUEFORMULA)
					{
						if( ((VUEFormula *)nodes.at(j2))->formula == parent)    // если формула очередного узла является родительской
						{
							VUELink * link = new VUELink(numberOfFirst + numberTotal, 1 + numberTotal);    // создаём объект для связи
							numberTotal++;     // инкремент  числа всех "единиц" в VUE-схеме
							links.push_back(link);    // добавляем в контейнер VUE-связей
							link->setLink((VUEFormula *)nodes.at(j2), (VUEFormula *)node);    // назначаем для VIE-связи родительский и дочерный узлы
							break;
						}
					}
				}
			}
		}
		else if(node->GetType() == VUESET)    // если узел представляет множество истинности
		{
			Formula * parent = ((VUESet *)node)->parentSet->getParentFormula();    // получаем указатель на формулу-родителся
			for(size_t j2 = 0; j2 < nodes.size(); j2++)    // перебор всех узлов
			{
				if(nodes.at(j2)->GetType() == VUEFORMULA)     // если очередной узел представляет формулу
				{
					if( ((VUEFormula *)nodes.at(j2))->formula == parent)    // и если эта формула является родителем множества истинности
					{
						VUELink * link = new VUELink(8 + numberTotal, 1 + numberTotal);    // создаём новую VUE-связь
						numberTotal++;    // инкремент  числа всех "единиц" в VUE-схеме
						links.push_back(link);    // добавляем в контейнер VUE-связей
						link->setLink((VUEFormula *)nodes.at(j2), (VUESet *)node);    // назначаем для VIE-связи родительский и дочерный узлы
						break;
					}
				}
			}
		}
	}

	// вывожу связи
	for(size_t j = 0; j < links.size(); j++)
	{
		links.at(j)->print(tof);
	}


	/*
	tof << "    <child ID=\"6\"" << endl;
	tof << "        label=\"";
	tof << "Node 1";
	tof << "\"" << endl;
	tof << "        layerID=\"1\" created=\"1378800156937\" x=\"107.0\" y=\"78.0\"" << endl;
	tof << "        width=\"133.0\" height=\"167.0\" strokeWidth=\"2.0\" strokeStyle=\"2\"" << endl;
	tof << "        autoSized=\"false\" xsi:type=\"node\">" << endl;
	tof << "        <fillColor>#0AAD1D</fillColor>" << endl;
	tof << "        <strokeColor>#000000</strokeColor>" << endl;
	tof << "        <textColor>#000000</textColor>" << endl;
	tof << "        <font>Arial-bold-12</font>" << endl;
	tof << "        <URIString>http://vue.tufts.edu/rdf/resource/06e8c0d7c0a8000b00f95b1eac61c244</URIString>" << endl;
	tof << "        <shape xsi:type=\"rectangle\"/>" << endl;
	tof << "    </child>" << endl;
	*/
	printVUELayer(tof);  //  запись уровня
	printVUEFooter(tof, filename, currentDirStr); // запись "подвала" VUE-файла	
	tof.close();



	// удаляю созданные объекты
	for(size_t j = 0; j < nodes.size(); j++)
	{
		VUENode * node = nodes.at(j);
		if(node->GetType() == VUEFORMULA)
			delete ( (VUEFormula *) node );
		else if(node->GetType() == VUESET)
			delete ( (VUESet *) node );
		else
			delete node;
	}
	for(size_t j = 0; j < loose.size(); j++)
	{
		VUENode * node = loose.at(j);
		if(node->GetType() == VUEFORMULA)
			delete ( (VUEFormula *) node );
		else if(node->GetType() == VUESET)
			delete ( (VUESet *) node );
		else
			delete node;
	}
	for(size_t j = 0; j < links.size(); j++)
	{
		delete links.at(j);
	}



	// запуск созданного файла в VUE-редакторе
	TCHAR vueFile[MAX_PATH];
	m_fileFinder.GetWindowTextT(vueFile, MAX_PATH-1);
	char cvueFile[MAX_PATH];
	wcstombs(cvueFile, vueFile, MAX_PATH - 1);
	
		STARTUPINFOA sti;
		memset(&sti, 0, sizeof(STARTUPINFO));
		sti.cb = sizeof(STARTUPINFO);
		PROCESS_INFORMATION pi;
//		string path_to_vue = "D:\\VUE\\VUE-launcher.exe";
		string path_to_vue = cvueFile;
		path_to_vue += " ";
		path_to_vue += filename_with_path;
//		if(CreateProcessA(path_to_vue.data(), (LPSTR)filename_with_path.c_str(), NULL, NULL, false, NULL, NULL, NULL, &sti, &pi) != false)	
		if(CreateProcessA(NULL, (LPSTR)path_to_vue.data(), NULL, NULL, false, NULL, NULL, NULL, &sti, &pi) != false)	
		{
			/* Watch the process. */
			Sleep(6000);				// подождать
//			TerminateProcess(pi.hProcess,NO_ERROR);	// убрать процесс    
		}
	}
}


void CSemanticsDlg::OnBnClickedShowallformulas3()
{
	// TODO: добавьте свой код обработчика уведомлений
}

//
//  создание атомарной формулы
//
void CSemanticsDlg::OnBnClickedAddatomformula()
{
	CAtomFormulaDialog * cad = new CAtomFormulaDialog(this);
//	cad->SetStrings( _T("a1") , _T("A") );
	if(cad->DoModal() == IDOK)
	{
		Formula * formula1 = new Formula;
		tstring label1 = cad->tbuf1;
		tstring label2 = cad->tbuf2;
		EntityVariable ev1(label1, cad->tbuf_index1, VARIABLE);
		EntityVariable ev2(label2, cad->tbuf_index2, SET);
		if(!formula1->setAtomFormula(&all_entities, ev1, ev2))
		{
			if (CURRENT_LANG_OF == "rus")
				MessageBox(_T("Формула с такими же переменными уже существует и не может быть создана"), _T("Предупреждение"), MB_OK );
			else
				MessageBox(_T("A formula with the same variables already exists and cannot be created"), _T("Warning"), MB_OK );
			delete formula1;
		}
//		all_formulas.push_back(formula1);
	}
	delete cad;
	// TODO: добавьте свой код обработчика уведомлений
}


CSemanticsDlg::~CSemanticsDlg()
{
	for ( size_t i = all_entities.size(); i > 0 ; i--)
	{
		EntityBase * base = all_entities.at(i-1);
		if ( base->isSet())
		{
			FormulaSet * fs = (FormulaSet *)base;
			delete fs;
		}
		else
		{
			Formula * f = (Formula *)base;
			if(f->isTuple())
				delete (Tuple *)f;
			else
				delete f;
		}
	}
}

//
//  создание формулы операцией объединения "и"
//
void CSemanticsDlg::OnBnClickedBuildformula1()
{
//	if(all_formulas.size() > 1)
//	{
//		joinAllFormulas(&all_formulas, AND_OPERATION);
//	}
	OperationDlg operationDlg;
	operationDlg.SetOperation(AND_OPERATION);
	operationDlg.setFormulas(&all_entities);
	
	if(operationDlg.DoModal() == IDOK)
	{
	}

//	  objedinjem('1');   // & - 1
	// TODO: добавьте свой код обработчика уведомлений
}

//
//  создание формулы операцией объединения "или"
//
void CSemanticsDlg::OnBnClickedBuildformula2()
{
	OperationDlg operationDlg;
	operationDlg.SetOperation(OR_OPERATION);
	operationDlg.setFormulas(&all_entities);
	
	if(operationDlg.DoModal() == IDOK)
	{
	}
//	objedinjem('2');    // v -2
	// TODO: добавьте свой код обработчика уведомлений
}

//
//  создание формулы операцией отрицания
//
void CSemanticsDlg::OnBnClickedBuildformula3()
{
	OperationDlg operationDlg;
	operationDlg.SetOperation(NEGATIVE_OPERATION);
	operationDlg.setFormulas(&all_entities);
	
	if(operationDlg.DoModal() == IDOK)
	{
	}

	// TODO: добавьте свой код обработчика уведомлений
}

//
//  создание формулы операцией навешивания квантора всеобщности
//
void CSemanticsDlg::OnBnClickedBuildformula4()
{
	OperationDlg operationDlg;
	operationDlg.SetOperation(QUANTIFIER1_OPERATION);
	operationDlg.setFormulas(&all_entities);
	
	if(operationDlg.DoModal() == IDOK)
	{
	}
	// TODO: добавьте свой код обработчика уведомлений
}

//
//  создание формулы операцией навешивания квантора принадлежности
//
void CSemanticsDlg::OnBnClickedBuildformula5()
{
	OperationDlg operationDlg;
	operationDlg.SetOperation(QUANTIFIER2_OPERATION);
	operationDlg.setFormulas(&all_entities);
	
	if(operationDlg.DoModal() == IDOK)
	{
	}
	// TODO: добавьте свой код обработчика уведомлений
}

//
//  показ списка сформированных формул
//
void CSemanticsDlg::OnBnClickedShowallformulas()
{
	SummaryDialog sd;
	sd.setFormulas(&all_entities);
	sd.DoModal();
	// TODO: добавьте свой код обработчика уведомлений
}


//
//  функция строит множество истинности на основе формулы
//
void CSemanticsDlg::OnBnClickedBuildformula6()
{
	SetDialog setd;
	setd.setEntities(&all_entities);
	setd.DoModal();
	// TODO: добавьте свой код обработчика уведомлений
}


//
// вывод строки tstr, содержащей строку с принятым в программе форматом для представления математических символов, в spParaRng
//
void ExportMathString(tstring & tstr_in, Word::RangePtr & spParaRng)
{
	bool prevSymbolFont = false;
	int indexing = 0;  // переменная для установки флага индекса очередного символа
	SemanticString * dsi = new SemanticString();
	dsi->PrepareSubItemData(tstr_in, true);  // 
	for (int j = 0; j < dsi->count; j++)
	{
		TCHAR tch[4];
		tch[0] = dsi->tchars[j];
		tch[1] = TCHAR(0x00);
		if( ( dsi->symbolics[j] == LOW_MATHINDEX ) || ( dsi->symbolics[j] == HIGH_MATHINDEX ) )
		{
			indexing = dsi->symbolics[j];
			continue;
		}
		string tstr;
		tstr.push_back(dsi->tchars[j]);
		Word::CharactersPtr spCharactersPtr = spParaRng->Characters;
		Word::RangePtr spRangePtr1 = spCharactersPtr->Last;
//		spRangePtr1->Text = tstr.data();
		spRangePtr1->Text = tch;
		Word::_FontPtr spFont = spRangePtr1->Font;
//		spRangePtr1->InsertAfter(tstr.c_str());
		spFont->Size = 8;
		if ( dsi->symbolics[j] == SYMBOL_TYPEFACE )  // если математический символ
		{
			if(!prevSymbolFont)
				spFont->Name = L"Symbol"; // выставляем шрифт Symbol
			prevSymbolFont = true;
		}
		else  // в случае обычного символа
		{
			spFont->Name = L"Times New Roman";
			prevSymbolFont = false;
		}
		if ( indexing == LOW_MATHINDEX ) // если нижний индекс
		{
			spFont->Subscript = true; // выставляем нижний индекс для шрифта, используемого при отображении очередного символа
		}
		else if ( indexing == HIGH_MATHINDEX ) // если верхний индекс
		{
			spFont->Superscript = true; // выставляем верхний индекс для шрифта, используемого при отображении очередного символа
		}
		else
		{
			// указываем, что обычный шрифт (без индексов)
			spFont->Subscript = false;
			spFont->Superscript = false;
		}

		if(indexing) // если был верхний или нижний индекс
			indexing = 0;	// убираю флаг индекса
	}
	delete dsi;
}

//
//  заполнение ячеек таблицы spTable с математическими символами очередной строки  под номером (i + 2) на основе указателя peb на объект EntityBase
//
void ExportToWordRow(EntityBase * peb, Word::TablePtr & spTable, int i)
{
	tstring tstr;

	//  вывод текста формулы
	tstr = peb->getText();
	Word::RangePtr spParaRng = spTable->Cell(i + 2, 2)->Range;
	ExportMathString(tstr, spParaRng);

	// вывод обозначения формулы
	tstr = *(peb->getLabel());
	spParaRng = spTable->Cell(i + 2, 5)->Range;
	ExportMathString(tstr, spParaRng);

	// вывод свободных переменных
	tstr.clear();
	vector <EntityVariable *> * fv = peb->getFreeVariables();
	for (size_t j = 0; j < fv->size(); j++)
	{
		EntityVariable * ev = fv->at(j);
		if( j > 0 )
			tstr += _T(", ");
		tstr += *ev->GetText() + _T(" ");
	}
	if(!tstr.empty())
	{
		spParaRng = spTable->Cell(i + 2, 4)->Range;
		ExportMathString(tstr, spParaRng);
	}

	// вывод описания формулы
	tstr = *(peb->getDescription());
	spParaRng = spTable->Cell(i + 2, 6)->Range;
	ExportMathString(tstr, spParaRng);

	// вывод первоначального текста формулы, если переобозначена
	tstring redefined_text = *peb->getRedefinedText(); 
	tstring initial_text = *peb->getInitialText();
	trimWhitespaces(&redefined_text);
	trimWhitespaces(&initial_text);
	if((redefined_text.length() > 0) && (redefined_text.compare(initial_text))) 
	{
		spParaRng = spTable->Cell(i + 2, 7)->Range;
		ExportMathString(initial_text, spParaRng);
	}

	// вывод дополнительного описания формулы
	tstr = *(peb->getAddOns());
	spParaRng = spTable->Cell(i + 2, 8)->Range;
	ExportMathString(tstr, spParaRng);


}


//
//  вывод в таблицу созданных в текущей схеме формул и множеств построчно, без таблицы, первоначальный вариант, от которого отказались
//
void ExportToWord(SemanticString * dsi, Word::RangePtr & spParaRng)
{
	int indexing = 0;
	for (int j = 0; j < dsi->count; j++)
	{
		TCHAR tch[4];
		tch[0] = dsi->tchars[j];
		tch[1] = TCHAR(0x00);
		if( ( dsi->symbolics[j] == LOW_MATHINDEX ) || ( dsi->symbolics[j] == HIGH_MATHINDEX ) )
		{
			indexing = dsi->symbolics[j];
			continue;
		}
		string tstr;
		tstr.push_back(dsi->tchars[j]);
		spParaRng->InsertAfter(tstr.c_str());
		Word::CharactersPtr spCharactersPtr = spParaRng->Characters;
		Word::RangePtr spRangePtr1 = spCharactersPtr->Last;
		Word::_FontPtr spFont = spRangePtr1->Font;
		spFont->Name = L"Times New Roman";
		spFont->Subscript = false;
		spFont->Superscript = false;
		if ( indexing == LOW_MATHINDEX ) // пока что реализуем для нижних индексов
		{
			// блочок для получения размеров верхнего или нижнего индексов
			spFont->Subscript = true;
		}
		else if ( indexing == HIGH_MATHINDEX ) // пока что реализуем для нижних индексов
		{
			// блочок для получения размеров верхнего или нижнего индексов
			spFont->Superscript = true;
		}
		else
		{
			if ( dsi->symbolics[j] == SYMBOL_TYPEFACE )
			{
				// выставляем шрифт Symbol
				spFont->Name = L"Symbol";
			}
		}
		if(indexing)
			indexing = 0;		
	}
}





DWORD GetModuleDirectory(LPTSTR ptszDir, DWORD nSize)
{
	// Retrieve the path of the executable file of the current process.
	nSize = GetModuleFileName(NULL, ptszDir, nSize);
	if (!nSize || GetLastError() == ERROR_INSUFFICIENT_BUFFER)
	{
		*ptszDir = TCHAR('\0'); // Ensure it's NULL terminated
		return 0;
	}

	// Run through looking for the last slash in the file path.
    // When we find it, NULL it to truncate the following filename part.

    for (int i = nSize - 1; i >= 0; i--)
	{
        if (ptszDir[i] == TCHAR('\\') || ptszDir[i] == TCHAR('/'))
		{
			ptszDir[i + 1] = TCHAR('\0');
			nSize = i + 1;
            break;
		}
    }
	return nSize;
}


//DWORD WINAPI AutomateWordByImport(LPVOID lpParam)
DWORD WINAPI AutomateWordByImport(vector <EntityBase *> * all_entities, TCHAR * docFileName)
{
	// Initializes the COM library on the current thread and identifies the
	// concurrency model as single-thread apartment (STA). 
	// [-or-] CoInitialize(NULL);
	// [-or-] CoCreateInstance(NULL);
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	try
	{
		
		/////////////////////////////////////////////////////////////////////
		// Create the Word.Application COM object using the #import directive
		// and smart pointers.
		// 

		// Option 1) Create the object using the smart pointer's constructor
		// _ApplicationPtr is the original interface name, _Application, with a 
		// "Ptr" suffix.
		//Word::_ApplicationPtr spWordApp(
		//	__uuidof(Word::Application)	// CLSID of the component
		//	);
		
		// [-or-]

		// Option 2) Create the object using the smart pointer's function,
		// CreateInstance
		Word::_ApplicationPtr spWordApp;
		HRESULT hr = spWordApp.CreateInstance(__uuidof(Word::Application));
		if (FAILED(hr))
		{
			wprintf(L"CreateInstance failed w/err 0x%08lx\n", hr);
			return 1;
		}
		if (CURRENT_LANG_OF == "rus")
			AfxMessageBox(_T("Приложение Word.Application запущено"));
		else
			AfxMessageBox(_T("Application Word.Application is running"));

		/////////////////////////////////////////////////////////////////////
		// Make Word invisible. (i.e. Application.Visible = 0)
		// 
		spWordApp->Visible = VARIANT_FALSE;

		/////////////////////////////////////////////////////////////////////
		// Create a new Document. (i.e. Application.Documents.Add)
		// 
		Word::DocumentsPtr spDocs = spWordApp->Documents;
		Word::_DocumentPtr spDoc = spDocs->Add(); 
		spDoc->DeleteAllEditableRanges();

		Word::ParagraphsPtr spParas = spDoc->Paragraphs;
		Word::ParagraphPtr spPara = spParas->Add();
		Word::RangePtr spParaRng = spPara->Range;

		variant_t par = 1;
		Word::TablesPtr spTables = spDoc->Tables;
		Word::TablePtr spTable = spTables->Add(spParaRng, all_entities->size() + 1, 8, &par, &par);
//		spTable->OleFunction("Cell", 1, 1)->OlePropertyGet("Range")->OlePropertySet("Text", "Столбец 1, строка 1");


		// установка шрифта для ячеек с заголовками столбцов
		for ( size_t i = 0; i < 8; i++)
		{
			Word::_FontPtr spFont = spTable->Cell(1, i + 1)->Range->Font;
			spFont->Size = 8;
			spFont->Name = L"Times New Roman";
		}

		//  определение текста заголовков и предпочтительной ширины столбцов таблицы Word
		if (CURRENT_LANG_OF == "rus") {

			spTable->Cell(1, 1)->Range->InsertAfter(L"Номер формулы");
			spTable->Cell(1, 1)->PutPreferredWidth(20);
			spTable->Cell(1, 2)->Range->InsertAfter(L"Формула");
			spTable->Cell(1, 2)->PutPreferredWidth(60);
			spTable->Cell(1, 3)->Range->InsertAfter(L"Тип");
			spTable->Cell(1, 3)->PutPreferredWidth(20);
			spTable->Cell(1, 4)->Range->InsertAfter(L"Свободные переменные");
			spTable->Cell(1, 4)->PutPreferredWidth(20);
			spTable->Cell(1, 5)->Range->InsertAfter(L"Обозначение");
			spTable->Cell(1, 5)->PutPreferredWidth(60);
			spTable->Cell(1, 6)->Range->InsertAfter(L"Символьное обозначение");
			spTable->Cell(1, 6)->PutPreferredWidth(60);
			spTable->Cell(1, 7)->Range->InsertAfter(L"Начальный текст");
			spTable->Cell(1, 7)->PutPreferredWidth(60);
			spTable->Cell(1, 8)->Range->InsertAfter(L"Перевод на естественный язык");
			spTable->Cell(1, 8)->PutPreferredWidth(60);
			//		spTable->Cell(1, 5)->Range->Text(WideString(L"Обозначение"));
		}
		else {
			spTable->Cell(1, 1)->Range->InsertAfter(L"Formula number");
			spTable->Cell(1, 1)->PutPreferredWidth(20);
			spTable->Cell(1, 2)->Range->InsertAfter(L"Formula");
			spTable->Cell(1, 2)->PutPreferredWidth(60);
			spTable->Cell(1, 3)->Range->InsertAfter(L"Type");
			spTable->Cell(1, 3)->PutPreferredWidth(20);
			spTable->Cell(1, 4)->Range->InsertAfter(L"Free variables");
			spTable->Cell(1, 4)->PutPreferredWidth(20);
			spTable->Cell(1, 5)->Range->InsertAfter(L"Designation");
			spTable->Cell(1, 5)->PutPreferredWidth(60);
			spTable->Cell(1, 6)->Range->InsertAfter(L"Symbolic designation");
			spTable->Cell(1, 6)->PutPreferredWidth(60);
			spTable->Cell(1, 7)->Range->InsertAfter(L"The initial text");
			spTable->Cell(1, 7)->PutPreferredWidth(60);
			spTable->Cell(1, 8)->Range->InsertAfter(L"Natural language translation");
			spTable->Cell(1, 8)->PutPreferredWidth(60);
			//		spTable->Cell(1, 5)->Range->Text(WideString(L"Обозначение"));
		}


		for ( size_t i = 0; i < all_entities->size(); i++)  // перебор по всем созданным в текущей схеме сущностям
		{
			tstring tstr;
			Word::_FontPtr spFont = spTable->Cell(i + 2, 1)->Range->Font;
			spFont->Size = 8;
			spFont->Name = L"Times New Roman";
			spTable->Cell(i + 2, 1)->Range->InsertAfter(to_tstring((int) (i + 1)).c_str());
			EntityBase * peb = all_entities->at(i);

			// вывод в столбец "Тип" таблицы Word
			tstr.clear();
			if(peb->isFormula())
			{
				Formula * icurr = (Formula *)peb;
				if (icurr->getFeature() == PERFORMED_FEATURE) 
					if (CURRENT_LANG_OF == "rus")
						tstr = _T("выполнимая");
					else
						tstr = _T("workable");

				else if (icurr->getFeature() == TRUTH_FEATURE) 
					if (CURRENT_LANG_OF == "rus")
						tstr = _T("истинная");
					else
						tstr = _T("true");
				else if (icurr->getFeature() == FALSE_FEATURE) 
					if (CURRENT_LANG_OF == "rus")
						tstr = _T("ложная"); 
					else
						tstr = _T("false");
				else if (icurr->getFeature() == ATOMARN_FEATURE)
					if (CURRENT_LANG_OF == "rus")
						tstr = _T("атомарная");
					else
						tstr = _T("atomic");
				if(tstr.size() > 0)
				{
					Word::_FontPtr spFont1 = spTable->Cell(i + 2, 3)->Range->Font;
					spFont1->Size = 8;
					spFont1->Name = L"Times New Roman";
					spTable->Cell(i + 2, 3)->Range->InsertAfter(tstr.c_str());
				}
			}

			ExportToWordRow(peb, spTable, i);  // вывод столбцов с математическими символами
		}


		/////////////////////////////////////////////////////////////////////
		// Save the document as a docx file and close it.
		// 

		// Make the file name

		// Get the directory of the current exe.
		TCHAR tszFileName[MAX_PATH];
		if (!GetModuleDirectory(tszFileName, ARRAYSIZE(tszFileName)))
		{
			if (CURRENT_LANG_OF == "rus")
				AfxMessageBox(_T("GetModuleDirectory ошибка"));
			else
				AfxMessageBox(_T("GetModuleDirectory Error"));
			return 1;
		}

		// Concat "Sample1.docx" to the directory

//		wcsncat_s(tszFileName, ARRAYSIZE(tszFileName), _T("Sample1.docx"), 12);

		// Convert the NULL-terminated string to BSTR
		variant_t vtFileName(docFileName);

		spDoc->SaveAs(&vtFileName);
		spDoc->Close();
		if (CURRENT_LANG_OF == "rus")
			AfxMessageBox(_T("Экспорт осуществлён"));
		else
			AfxMessageBox(_T("The export has been carried out"));

		spWordApp->Quit();


		/////////////////////////////////////////////////////////////////////
		// Release the COM objects.
		// 

		// Releasing the references is not necessary for the smart pointers
		// ...
		// spWordApp.Release();
		// ...
//		spDoc->Release();
//		spWordApp->Release();

	}
	catch (_com_error &err)
	{
//		wprintf(L"Word throws the error: %s\n", err.ErrorMessage());
//		wprintf(L"Description: %s\n", (LPCWSTR) err.Description());
		AfxMessageBox(_T("Error of export"));
	}

	// Uninitialize COM for this thread
	CoUninitialize();

	return 0;
}


//
// функция экспорта отчёта в Word
//
void CSemanticsDlg::OnBnClickedExport()
{
	// TODO: добавьте свой код обработчика уведомлений
	// диалог для определения просмотрщика
	TCHAR docFileName[MAX_PATH];
	m_fileWordExport.GetWindowTextT(docFileName, MAX_PATH-1);

	AutomateWordByImport(&all_entities, docFileName);
}


//
// сохраняю постренную схему в xml-файл
//
void CSemanticsDlg::OnBnClickedSavescheme()
{
	CString strExt((LPCSTR)"*.fms");
	CString strTitle;
	if (CURRENT_LANG_OF == "rus")
		strTitle = CString((LPCSTR)"Выберите файл для записи схемы");
	else
		strTitle = CString((LPCSTR)"Выберите файл для записи схемы");

	CString strFilter((LPCSTR)"Semantics Files (*.fms)|*.fms||");
	CString strPathName;

	CFileDialog fileDialog(FALSE, strExt, NULL, OFN_ENABLESIZING | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
							strFilter, this);
	fileDialog.m_ofn.lpstrTitle = strTitle;

	int ret = fileDialog.DoModal();
	bool toProccess = false;
	if (IDOK == ret)
	{
		strPathName = fileDialog.GetPathName();
		if (!strPathName.IsEmpty())
		{
			toProccess = true;
		}
	}
	if(!toProccess)
		return;

#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
	// здесь код, который я начала писать для бибилиотеки libxml2, но не стал, использовать только как пример
	xmlDocPtr doc = NULL;       /* document pointer */
	xmlNodePtr root_node = NULL, node = NULL, node1 = NULL;/* node pointers */
	xmlDtdPtr dtd = NULL;       /* DTD pointer */
	char buff[256];

    LIBXML_TEST_VERSION;

    /* 
     * Creates a new document, a node and set it as a root node
     */
    doc = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST "root");
    xmlDocSetRootElement(doc, root_node);

    /*
     * Creates a DTD declaration. Isn't mandatory. 
     */
    dtd = xmlCreateIntSubset(doc, BAD_CAST "root", NULL, BAD_CAST "tree2.dtd");


    /* 
     * xmlNewChild() creates a new node, which is "attached" as child node
     * of root_node node. 
     */
    xmlNewChild(root_node, NULL, BAD_CAST "node1",
                BAD_CAST "content of node 1");
    /* 
     * The same as above, but the new child node doesn't have a content 
     */
    xmlNewChild(root_node, NULL, BAD_CAST "node2", NULL);

    /* 
     * xmlNewProp() creates attributes, which is "attached" to an node.
     * It returns xmlAttrPtr, which isn't used here.
     */
    node =
        xmlNewChild(root_node, NULL, BAD_CAST "node3",
                    BAD_CAST "this node has attributes");
    xmlNewProp(node, BAD_CAST "attribute", BAD_CAST "yes");
    xmlNewProp(node, BAD_CAST "foo", BAD_CAST "bar");

    /*
     * Here goes another way to create nodes. xmlNewNode() and xmlNewText
     * creates a node and a text node separately. They are "attached"
     * by xmlAddChild() 
     */
    node = xmlNewNode(NULL, BAD_CAST "node4");
    node1 = xmlNewText(BAD_CAST
                   "other way to create content (which is also a node)");
    xmlAddChild(node, node1);
    xmlAddChild(root_node, node);

    /* 
     * A simple loop that "automates" nodes creation 
     */
    for (int i = 5; i < 7; i++) {
        sprintf(buff, "node%d", i);
        node = xmlNewChild(root_node, NULL, BAD_CAST buff, NULL);
        for (int j = 1; j < 4; j++) {
            sprintf(buff, "node%d%d", i, j);
            node1 = xmlNewChild(node, NULL, BAD_CAST buff, NULL);
            xmlNewProp(node1, BAD_CAST "odd", BAD_CAST((j % 2) ? "no" : "yes"));
        }
    }

    /* 
     * Dumping document to stdio or file
     */
    xmlSaveFormatFileEnc( "-", doc, "UTF-8", 1);

    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
#else

	CoInitialize(NULL);
	CArrayXML <CFormulaItem*, CFormulaItem*> Formulas;
	CArrayXML <CSetItem*, CSetItem*> Sets;
	CItem Header;
	//  заполняю классы массивов Formulas и Sets через перебор всех построенных на данный момент экземляров класса EntityBase
	for ( size_t i = 0; i < all_entities.size(); i ++)
	{
		EntityBase * base = all_entities.at(i);
//		if ( base->getType() == FORMULA_SET ) // если множество или переобозначение свободной переменной в множестве
		EntityBase * preplaced = base->getReplacedBase();
		if (( base->getType() == FORMULA_SET ) || ( (base->getType() == REPLACE_VARIABLE) && (preplaced != nullptr) && preplaced->isSet() )) // если множество 
		{
			FormulaSet * pfs = (FormulaSet *)base;
			CSetItem * si = new CSetItem(*pfs);	
			si->SetNumber((int)i); // присваиваю порядковый номер в схеме
			if ( base->getType() == FORMULA_SET ) // если множество
			{
				Formula * parent = pfs->getParentFormula();
				for ( size_t i1 = 0; i1 < all_entities.size(); i1 ++)
				{
					EntityBase * pbase = all_entities.at(i1);
					if ( pbase->getType() != FORMULA_SET )
					{
						Formula * pfbase = (Formula *)pbase;
						if ( pfbase == parent )
						{
							si->FormulaNumber = i1;
							break;
						}
					}
				}
			}
			else if((base->getType() == REPLACE_VARIABLE) && (preplaced != nullptr)) // если переобозначение свободной переменной в множестве
			{
				for ( size_t i1 = 0; i1 < all_entities.size(); i1 ++)
				{
					EntityBase * pbase = all_entities.at(i1);
					if ( pbase == preplaced )
					{
						si->ReplacedNumber = i1;
						break;
					}
				}
			}
			Sets.Add(si);
		}
		else  // если формула
		{
			Formula * pf = (Formula *)base;
			CFormulaItem * fi = new CFormulaItem(*pf);
			fi->SetNumber((int)i); // присваиваю порядковый номер в схеме
			// для предиката принадлежности определяю порядковый номер родительского множества истинности
			if(pf->isBelongingPredicate() || pf->isSubset())
			{
				int count_of_sets = 0;
				FormulaSet * parent_set = pf->getParentSet();
				for ( size_t i1 = 0; i1 < all_entities.size(); i1 ++)
				{
					EntityBase * base1 = all_entities.at(i1);
					if ( base1->getType() == FORMULA_SET ) // если множество
					{
						if(parent_set == (FormulaSet *)base1)
						{
							fi->SetParentSetNumber((int)count_of_sets); // присваиваю порядковый номер в схеме для родительского множества истинности
							break;
						}
						count_of_sets++;
					}
				}
			}
			else if((base->getType() == REPLACE_VARIABLE) && (preplaced != nullptr))  // если переобозначение свободной переменной в множестве
			{
				for ( size_t i1 = 0; i1 < all_entities.size(); i1 ++)
				{
					EntityBase * pbase = all_entities.at(i1);
					if ( pbase == preplaced )
					{
						fi->ReplacedNumber = i1;
						break;
					}
				}
			}
			// перебираю для данной формулы все родительские пары "формула-переменная" и заношу их порядковые номера в ParentsLinks
			for ( size_t i1 = 0; i1 < pf->getNumberOfParents(true); i1++)
			{
				ParentLink * ppl = pf->getParentLink(i1, true);
				Formula * parentFormula = get<0>(*ppl);
				int formulaNumber = -1;
				// ищу порядковый номер родительской формулы
				for ( size_t i2 = 0; i2 < all_entities.size(); i2++)
				{
					if ( parentFormula == all_entities.at(i2) )
					{
						formulaNumber = i2;
						break;
					}
				}
				int variableNumber = -1;
				EntityVariable * ptstr = get<1>(*ppl);
				// ищу порядковый номер свободной переменной из родительской пары, если null_ptr, то оставляю номер равным -1
				if ( ptstr != NULL )
				{
					vector <EntityVariable *> * freeVariables = parentFormula->getFreeVariables();
					for ( size_t i2 = 0; i2 < freeVariables->size(); i2++)
					{
						if ( ptstr->compare(*freeVariables->at(i2)) )
						{
							variableNumber = i2;
							break;
						}
					}
				}
				CParentLinkItem * ppli = new CParentLinkItem(formulaNumber, variableNumber);
				fi->ParentLinks.Add(ppli);
			}
			Formulas.Add(fi);
		}
	}
	try
	{
		CWaitCursor wait;
		CXMLArchive ar(strPathName, CArchive::store, NULL, NULL);
		CXMLArchive& xmlArchive = static_cast<CXMLArchive&>(ar);
		xmlArchive.GetNode(_T("Semantics")); 
//		XMLCLASSNODE;
		XMLDATA(Header);
		XMLDATA(Formulas);
		XMLDATA(Sets);
//		XMLENDNODE;
		CXMLArchiveNode* nodePtr = xmlArchive.GetCurrentNode();
		if (nodePtr != NULL) 
			nodePtr->Close(); 
	}
	catch (_com_error &err)
	{
//		wprintf(L"Word throws the error: %s\n", err.ErrorMessage());
//		wprintf(L"Description: %s\n", (LPCWSTR) err.Description());
		if (CURRENT_LANG_OF == "rus")
			AfxMessageBox(_T("Ошибка сохранения схемы"));
		else 
			AfxMessageBox(_T("Error saving the schema"));
	}
	CoUninitialize();
	for (int i = 0; i < Formulas.GetSize(); i++)
	{
		for ( int i1 = 0; i1 < Formulas[i]->ParentLinks.GetSize(); i1++)
			delete Formulas[i]->ParentLinks[i1];
		delete Formulas[i];
	}
	Formulas.RemoveAll();
	for (int i = 0; i < Sets.GetSize(); i++)
	{
		delete Sets[i];
	}
	Sets.RemoveAll();

#endif
	// TODO: добавьте свой код обработчика уведомлений
}

//
// загружаю ранее построенную схему из сохранённого xml-файла
//
void CSemanticsDlg::OnBnClickedLoadscheme()
{
	CString strExt((LPCSTR)"*.fms");
	CString strTitle;
	if (CURRENT_LANG_OF == "rus")
		strTitle = CString((LPCSTR)"Выберите файл для загрузки схемы");
	else 
		strTitle = CString((LPCSTR)"Select the file to download the schema");

	CString strFilter((LPCSTR)"Semantics Files (*.fms)|*.fms||");
	CString strPathName;

	CFileDialog fileDialog(TRUE, strExt, NULL, OFN_ENABLESIZING | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST,
							strFilter, this);
	fileDialog.m_ofn.lpstrTitle = strTitle;

	int ret = fileDialog.DoModal();
	bool toProccess = false;
	if (IDOK == ret)
	{
		strPathName = fileDialog.GetPathName();
		if (!strPathName.IsEmpty())
		{
			toProccess = true;
		}
	}
	if(!toProccess)
		return;
#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
#else
	CoInitialize(NULL);
	CArrayXML <CFormulaItem*, CFormulaItem*> Formulas;
	CArrayXML <CSetItem*, CSetItem*> Sets;
	CItem Header;
	try
	{
		CWaitCursor wait;
		CXMLArchive ar(strPathName, CArchive::load, NULL, NULL);
		CXMLArchive& xmlArchive = static_cast<CXMLArchive&>(ar);
		xmlArchive.GetNode(_T("Semantics")); //		XMLCLASSNODE;
		XMLDATA(Header);
		XMLDATA(Formulas);
		XMLDATA(Sets);
//		XMLENDNODE;
		CXMLArchiveNode* nodePtr = xmlArchive.GetCurrentNode();
		if (nodePtr != NULL) 
			nodePtr->Close(); 
//		Serialize(xmlArchive);     // load me
	}
	catch (_com_error &err)
	{
//		DeleteContents();   // remove failed contents

//		ReportSaveLoadException(lpszPathName, e,
//			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);

//		delete e;
//		wprintf(L"Word throws the error: %s\n", err.ErrorMessage());
//		wprintf(L"Description: %s\n", (LPCWSTR) err.Description());
		if (CURRENT_LANG_OF == "rus")
			AfxMessageBox(_T("Ошибка загрузки схемы"));
		else
			AfxMessageBox(_T("Schema loading error"));
	}
	CoUninitialize();
	// очищаю уже созданную схему
	for ( size_t i = all_entities.size() ; i > 0 ; i-- )
	{
		EntityBase * base = all_entities.at(i - 1);
		if ( base->isSet() )
		{
			FormulaSet * fs = (FormulaSet *)base;
			delete fs;
		}
		else
		{
			Formula * pf = (Formula *)base;
			if(pf->isTuple())
			{
				Tuple * pt = (Tuple *)pf;
				delete pt;
			}
			else
			{
				delete pf;
			}
		}
	}
	all_entities.clear();
	// заполняю схему из полученных из сохранённого xml-файла массивов Formulas и Sets
	// делаю одновременный перебор по Formulas и Sets, находя соотвествующие порядковые номера, соответствующие элементы заношу в схему
	for (int i = 0; i < (Formulas.GetSize() + Sets.GetSize()); i++)
	{
		bool cond = false;
		for (int i1 = 0; i1 < Formulas.GetSize(); i1++)
		{
			if(Formulas[i1]->Number == i)
			{
				cond = true;
				
				Formula * pf = new Formula(*(Formulas[i1]));
				if(Formulas[i1]->ReplacedNumber != -1)
					((EntityBase *)pf)->setReplacedBase(all_entities.at(Formulas[i1]->ReplacedNumber));

				if(pf->isTuple())
				{
					Tuple * pt = new Tuple(*(Formulas[i1]));
					delete pf;
					pf = (Formula *)pt;
				}
				all_entities.push_back(pf);
				for ( int i2 = 0; i2 < Formulas[i1]->ParentLinks.GetSize(); i2++)
				{
					Formula * curr = (Formula *)all_entities.at(Formulas[i1]->ParentLinks[i2]->FormulaNumber);
					EntityVariable * pev = NULL;
					if ( Formulas[i1]->ParentLinks[i2]->VariableNumber >= 0)
						pev = new EntityVariable( *curr->getFreeVariables()->at( Formulas[i1]->ParentLinks[i2]->VariableNumber) );
					ParentLink * ppl = new ParentLink( curr, pev );
					pf->parents.push_back(ppl);
					delete Formulas[i1]->ParentLinks[i2];
				}
	//			delete Formulas[i1];
				// для предиката принадлежности записываю указатель на родительское множество истинности
//				if(pf->isBelongingPredicate() || pf->isSubset())
				if((Formulas[i1]->EntityType == BELONGING_PREDICATE) || pf->isSubset())
				{
					int count_of_sets = 0;
					int num = Formulas[i1]->ParentSetNumber;
					for(int ii1 = 0; ii1 < all_entities.size(); ii1++)
					{
						EntityBase * base1 = all_entities.at(ii1);
						if ( base1->isSet() )
						{
							if(count_of_sets == Formulas[i1]->ParentSetNumber)
							{
								pf->setParentSet((FormulaSet *)base1);
								break;
							}
							count_of_sets++;
						}
					}
				}
				break;
			}
		}
		if(cond)
			continue;
		for (int i1 = 0; i1 < Sets.GetSize(); i1++)
		{
			if(Sets[i1]->Number == i)
			{
				FormulaSet * pfs = new FormulaSet(*(Sets[i1]));
				all_entities.push_back(pfs);
				if(Sets[i1]->ReplacedNumber != -1) // если это замена переменной для множества
					pfs->setReplacedBase(all_entities.at(Sets[i1]->ReplacedNumber));
				else // если обычное множество
					pfs->setParentFormula((Formula *)all_entities.at(Sets[i1]->FormulaNumber));
//				delete Sets[i1];
				break;
			}
		}
	}
	for (int i1 = 0; i1 < Formulas.GetSize(); i1++)
	{
		delete Formulas[i1];
	}
	for (int i1 = 0; i1 < Sets.GetSize(); i1++)
	{
		delete Sets[i1];
	}
	Formulas.RemoveAll();
	Sets.RemoveAll();
#endif

	// TODO: добавьте свой код обработчика уведомлений
}


void CSemanticsDlg::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnCancel();
}


void CSemanticsDlg::OnEnChangeMfceditbrowse2()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}

// создание предиката принадлежности из множества истинности
void CSemanticsDlg::OnBnClickedBuildformula7()
{
	FromSetDialog setd;
	setd.setEntities(&all_entities);
	setd.DoModal();

	// TODO: добавьте свой код обработчика уведомлений
}


//создание кортежа
void CSemanticsDlg::OnBnClickedBuildtuple()
{
	CTupleDlg * ctd = new CTupleDlg(this);
	ctd->SetEntities(&all_entities);
	if(ctd->DoModal() == IDOK)
	{

	}
	delete ctd;
	// TODO: добавьте свой код обработчика уведомлений
}

// вызов формы замены переменных
void CSemanticsDlg::OnBnClickedChangevariable()
{
	ReplaceVariableDialog * rvd = new ReplaceVariableDialog(this);
	rvd->setEntities(&all_entities);
	if(rvd->DoModal() == IDOK)
	{

	}
	delete rvd;
	// TODO: добавьте свой код обработчика уведомлений
}


void CSemanticsDlg::OnBnClickedRus()
{
	// TODO: Add your control notification handler code here
	
	CURRENT_LANG_OF = "rus";
	GetDlgItem(RB_RUS)->SetWindowTextW(L"Русский");
	GetDlgItem(RB_ENG)->SetWindowTextW(L"Английский");
	m_rbLang = 0;

	GetDlgItem(IDC_ADDAKSIOMA)->SetWindowTextW(L"Добавить атомарную формулу");
	
	GetDlgItem(IDC_SHOWALLFORMULAS)->SetWindowTextW(L"Посмотреть все формулы");

	GetDlgItem(IDC_BUILDFORMULA1)->SetWindowTextW(L"Построение новой формулы Pk:= Pi && Pj");

	GetDlgItem(IDC_BUILDFORMULA2)->SetWindowTextW(L"Построение новой формулы Pk:= Pi V Pj");

	GetDlgItem(IDC_BUILDFORMULA3)->SetWindowTextW(L"Построение новой формулы Pk:=not (Pi)");

	GetDlgItem(IDC_BUILDFORMULA4)->SetWindowTextW(L"Построение новой формулы Pk:= ( K a ) Pi, где a - свободная переменная");
												  //    Building new formula
	GetDlgItem(IDC_BUILDFORMULA5)->SetWindowTextW(L"Построение новой формулы Pk:= ( K a ) Pj, где a - свободная переменная");

	GetDlgItem(IDC_BUILDFORMULA6)->SetWindowTextW(L"Построение множества на основе формулы");

	GetDlgItem(IDC_CHANGEVARIABLE)->SetWindowTextW(L"Замена переменных");



	GetDlgItem(IDEXPORT)->SetWindowTextW(L"Экспорт в WORD");

	GetDlgItem(IDOK)->SetWindowTextW(L"Схема");



	GetDlgItem(IDCANCEL)->SetWindowTextW(L"Отмена");

	GetDlgItem(IDSAVESCHEME)->SetWindowTextW(L"Сохранить");

	GetDlgItem(IDLOADSCHEME)->SetWindowTextW(L"Загрузить");

	GetDlgItem(ID_HELP)->SetWindowTextW(L"Справка");

	//DDX_Control(pDX, IDC_BUILDFORMULA5, m_button5);
	//DDX_Control(pDX, IDC_BUILDFORMULA4, m_button4);
	//DDX_Control(pDX, IDC_BUILDFORMULA3, m_button3);
	//DDX_Control(pDX, IDC_BUILDFORMULA2, m_button2);
	//DDX_Control(pDX, IDC_BUILDFORMULA1, m_button1);
	//DDX_Control(pDX, IDC_ADDAKSIOMA, m_button);
	//DDX_Control(pDX, IDC_SHOWALLFORMULAS, m_button6);
	//DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_fileFinder);
	//DDX_Control(pDX, IDC_BUILDFORMULA6, m_buttonSet);
	//DDX_Control(pDX, IDC_MFCEDITBROWSE2, m_fileWordExport);
	//DDX_Control(pDX, IDC_BUILDFORMULA7, m_button7);
	//DDX_Control(pDX, IDC_BUILDTUPLE, m_KortegeButton);
	//DDX_Control(pDX, IDC_CHANGEVARIABLE, m_ChangeVariable);


	//Построение новой формулы Pk:=not (Pi)

	//IDR_MENU_SYMBOLS -- выподающие окно
	//IDD_SEMANTICS_DIALOG -- Главное меню
	//IDD_REPLACEVARIABLE -- заменить свободную переменную
	//IDD_CHOOSEDIALOG -- Создание новых формул

	UpdateData(TRUE);
}

std::map<std::string, std::string> dictanary;

void CSemanticsDlg::OnBnClickedEng()
{

	CURRENT_LANG_OF = "eng";

	// TODO: Add your control notification handler code here
	GetDlgItem(RB_RUS)->SetWindowTextW(L"Russian");
	GetDlgItem(RB_ENG)->SetWindowTextW(L"English");
	//m_rbLang = 1;
	//CString langStr;
	//langStr.Format(_T("%d"), m_rbLang);

	//MessageBox(NULL, langStr, MB_OK);
	GetDlgItem(IDC_ADDAKSIOMA)->SetWindowTextW(L"Add an atomatic formula");

	GetDlgItem(IDC_SHOWALLFORMULAS)->SetWindowTextW(L"View all formulas");

	GetDlgItem(IDC_BUILDFORMULA1)->SetWindowTextW(L"  Building a new formula Pk:= Pi && Pj");

	GetDlgItem(IDC_BUILDFORMULA2)->SetWindowTextW(L"  Building a new formula Pk:= Pi V Pj");

	GetDlgItem(IDC_BUILDFORMULA3)->SetWindowTextW(L"  Building a new formula Pk:=not (Pi)");

	GetDlgItem(IDC_BUILDFORMULA4)->SetWindowTextW(L"  Building a new formula Pk:= ( K a ) Pi, where a - free variable");

	GetDlgItem(IDC_BUILDFORMULA5)->SetWindowTextW(L"  Building a new formula Pk:= ( K a ) Pj, where a - free variable");

	GetDlgItem(IDC_BUILDFORMULA6)->SetWindowTextW(L"    Building set based on a formula");

	GetDlgItem(IDC_CHANGEVARIABLE)->SetWindowTextW(L"Replacing variables");

	


	GetDlgItem(IDEXPORT)->SetWindowTextW(L"Exporting to WORD");

	GetDlgItem(IDOK)->SetWindowTextW(L"Sceme");



	GetDlgItem(IDCANCEL)->SetWindowTextW(L"Cancel");

	GetDlgItem(IDSAVESCHEME)->SetWindowTextW(L"Save");

	GetDlgItem(IDLOADSCHEME)->SetWindowTextW(L"Load");

	GetDlgItem(ID_HELP)->SetWindowTextW(L"&help");
	
	
	
	
	GetDlgItem(IDD_BELONGING_DIALOG)->SetWindowText(L"Getting the inclusion predicate");

	UpdateData(TRUE);
}
