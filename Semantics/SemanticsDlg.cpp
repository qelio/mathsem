//  ����� ����: ���������� �.�., akizelokro@mail.ru , 2013-2014
//  Author: Tatarintsev V.V., akizelokro@mail.ru, 2013-2014

// SemanticsDlg.cpp : ���� ����������
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



// ���������� ���� CAboutDlg ������������ ��� �������� �������� � ����������

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ������ ����������� ����
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

// ����������
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


// ���������� ���� CSemanticsDlg




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
	helpDlg.DoModal(); // ����� ���� ��� ����������
}

void CSemanticsDlg::OnBnClickedChangeNewVariable()
{
	ReplaceVariableDialog* rvd = new ReplaceVariableDialog(this);
	rvd->setEntities(&all_entities);
	if (rvd->DoModal() == IDOK)
	{
		// �������� ���� ��� ��� ��������� �������������
	}
	delete rvd;
}

// ����������� ��������� CSemanticsDlg

BOOL CSemanticsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���������� ������ "� ���������..." � ��������� ����.

	// IDM_ABOUTBOX ������ ���� � �������� ��������� �������.
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

	// ������ ������ ��� ����� ����������� ����. ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������
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

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
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

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������. ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CSemanticsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CSemanticsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//
//  ���������� ����� ������������ ��� ����������� ������
//
void CSemanticsDlg::OnBnClickedOk()
{
//	SetDialog sd;
//	sd.DoModal();
	if(all_entities.size() < 1)
	{	
		if(CURRENT_LANG_OF=="rus")
			MessageBox(_T("�� ���������� �� ����� �������. ����� �� ����� ���������"), _T("���������"), MB_OK);
		else
			MessageBox(_T("No formula has been defined. The scheme will not be built"), _T("Remark"), MB_OK);

		return;
	}
	int n = 1;
	setlocale(LC_ALL, "rus");
	// ����������� ����� ����� � �������� ��������, � ����� ���� � ���� "�������" ��� ������ VUE-�����
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
		printFirstPartVUEHeader(tof, filename, currentDirStr); // ������ � ���� ������ ����� ��������� ������������ VUE-�����
		printVUELegend(tof, legend); // ������� ������� (������� � ������������ ��� ��� ����������)

	// ��������� �� ���������
	double x= -354.0;
	double y = -199.0;
	double height = 160.0;  // ������ ����
	double height_interval = 30.;  // ���������� ����� ������ �� ������
/*
	������ ��������, �������������� ��� �������������� ���������� ����� � � ��������� � �������� �������
	int numberOfFirst = 8; // ���������� ����� ���� � ����� ���������� �����, �� ������ �������
	double height_offset_atom = (1.5 *height) + (1.5 * height_interval); // �������� ���� ��������� ������� �� ������ ������ �� ������
	double offsetOfGroup = (height + height_interval) * 4;
	double interval = 200.0;  
	double width = 120.0;  // ������ ����
*/
	// ����� ��������, ������������ ��� ������������ ����������
	double width = 240.0;  // ������ ����
	int numberOfFirst = 13; // ���������� ����� ���� � ����� ���������� �����, �� ������ �������
	double interval = 200.0;  
	double height_offset_atom = (1.5 * width) + (1.5 * height_interval); // �������� ���� ��������� ������� �� ������ ������ �� ������
	double offsetOfGroup = interval * 4;
//	int groupAtom = 0;
	int numberTotal = 0;
	vector <VUENode *> nodes;  // ��������� ����� �����, ����- ��������� ������� ����������� � ���������� atomics
	vector <VUEFormula *> atomics; // ��������� ��������� ������, ����� "�������" �����, ������ ��� �� ��� �������� ������ �����
	vector <VUENode *> loose;  // ��������� �����, ����������� ������������ �� � ����� �� �����, ���������� �� ��������� ��������
	vector <VUELink *> links;  // ��������� ������ ����� ������

	//  ���������� ������ ����� (������ � ��������) ��� ���������� ��������� � ������ � VUE-����
	int numberOfSets = 0;	// ����� �������� ����������
	int numberOfNonAtomicFormulas = 0;	// ����� ����������� ������
	int numberOfAtomicFormulas = 0;	// ����� ��������� ������
	// ������������ ��������� ����������, ��������� � ������ ������� � �����
	for(size_t i = 0; i < all_entities.size(); i++)
	{
		EntityBase * base = all_entities.at(i);
		if( base->getType() == FORMULA_SET )    // ���� �������� - ��������� ����������
			numberOfSets++;    // ���������
		else    // ����� �������
		{
			Formula * pFormula = (Formula *)base;    // ��������� �� ������ ������ Formula
#ifdef VUEATOMICWITHNEGATIVE
			if(pFormula->isAtom() || (pFormula->isNegative() && get<0>(*pFormula->getParentLink(0))->isAtom() ) )  // ���� ��������� �������
			// ��� ���������� �������, ����������� ����������� �������� ��������� � ��������� �������
#else
			if(pFormula->isAtom())  // ���� ��������� �������
#endif
				numberOfAtomicFormulas++;    // ��������� ��� ���������
			else
				numberOfNonAtomicFormulas++;    // ��������� ��� �����������
		}
	}
	// ������� ���������� ������������ ��������� ������ (������ ������, � ������� ����������� ������� ������������� � ������ ����, � ��������� �� ������
	// ���������� ����������� ����� � ����� �� ��� ����� (���������, ����������� ������ � �������� ����������)
	int maxNodesAtRows = numberOfAtomicFormulas;
	if( numberOfSets > maxNodesAtRows)
		maxNodesAtRows = numberOfSets;
	if( numberOfNonAtomicFormulas > maxNodesAtRows)
		maxNodesAtRows = numberOfNonAtomicFormulas;
	// ��������� ����������� �������� ��� ��������� ������
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

	numberOfSets = 0;	// �������� ����� �������� ����������
	numberOfNonAtomicFormulas = 0;	// �������� ����� ����������� ������
	numberOfAtomicFormulas = 0;	// �������� ����� ��������� ������


	for(size_t i = 0; i < all_entities.size(); i++)
	{
		EntityBase * base = all_entities.at(i);
		VUENode * newNode;
		if ( base->getType() == FORMULA_SET ) // ���� ��������� ��������� - ���������
		{
			VUESet * node = new VUESet(numberOfFirst + numberTotal, 1 + numberTotal);
			newNode = (VUESet *)node;
			node->parentSet = (FormulaSet *)all_entities.at(i);
			numberTotal++;
			Formula * curr = node->parentSet->getParentFormula(); // ������������ ������� ���������
			while( curr->getNumberOfParents() > 0) // �������� �� ������ �������� �������� ������� ������-��������� �� ���, � ������� ��������� ���
			{
//					curr = curr->getParentLink(0);
					curr = get<0>(*curr->getParentLink(0));
			}
			bool existAtomicLink = false;
			// 
			for(size_t j = 0; j < atomics.size(); j++)  // ���������� ������ ��������� ������, ����� ����� ����������� � ���������� curr
			{
//				VUENode * centerNode = atomics.at(j);
				VUEFormula * centerNode = (VUEFormula *)atomics.at(j);
				if ( centerNode->formula == curr ) // ������� ��� ��������� ��������� ������� �, ��������������, ������
				{
					existAtomicLink = true;
					centerNode->numberInGroup++;
					node->groupAtom = centerNode->groupAtom;
					node->childProperties();
/*
���������� ��� � �������������� �������������
					node->SetPosition(x + (interval * ((centerNode->numberInGroup/4) + 1)), 
						y + (offsetOfGroup * (node->groupAtom - 1)) + (height + height_interval) * ((centerNode->numberInGroup%4) - 1), 
						width, 
						height);
*/
/*
���������� ��� � �������������� �� ��� ���� � ��� � ��������� ������

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
				loose.push_back(newNode); // ���� ������������ ��������� ������� �� �������, ������ � ������ "����������" �����
		}
		else // ���� ��������� ��������� - �������
		{
			VUEFormula * node = new VUEFormula(numberOfFirst + numberTotal, 1 + numberTotal);
			newNode = (VUENode *)node;
			node->formula = (Formula *)all_entities.at(i);
			numberTotal++;
#ifndef VUEATOMICWITHNEGATIVE
			if(!node->formula->isAtom())  // ���� �� ��������� �������
			{
				Formula * curr = node->formula;
				while( curr->getNumberOfParents() > 0)  // �������� �� ������ �������� �������� ������� ������-��������� �� ���, � ������� ��������� ���
				{
//					curr = curr->getParentLink(0);
					curr = get<0>(*curr->getParentLink(0));
				}
				bool existAtomicLink = false;
				for(size_t j = 0; j < atomics.size(); j++)  // ���������� ������ ��������� ������, ����� ����� ����������� � ���������� curr
				{
//					VUENode * centerNode = atomics.at(j);
					VUEFormula * centerNode = (VUEFormula *)atomics.at(j);
					if ( centerNode->formula == curr ) // ������� ��� ��������� ��������� ������� �, ��������������, ������
					{
						existAtomicLink = true;
						centerNode->numberInGroup++;
						node->groupAtom = centerNode->groupAtom;
						node->childProperties();
/*
���������� ��� � �������������� �������������
						node->SetPosition(x + (interval * ((centerNode->numberInGroup/4) + 1)), 
							y + (offsetOfGroup * (node->groupAtom - 1)) + (height + height_interval) * ((centerNode->numberInGroup%4) - 1), 
							width, 
							height);
*/
/*
���������� ��� � �������������� �� ��� ���� � ��� � ��������� ������
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
					loose.push_back(newNode); // ���� ������������ ��������� ������� �� �������, ������ � ������ "����������" �����
			}
			else
			{
				// ��������� �������
				atomics.push_back(node);
				node->groupAtom = atomics.size();
/*
���������� ��� � �������������� �������������
				node->SetPosition(x , 
					y + (offsetOfGroup * (node->groupAtom - 1)) + height_offset_atom , 
						width, 
						height);
*/
/*
���������� ��� � �������������� �� ��� ���� � ��� � ��������� ������
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
			if(!node->formula->isAtom() )  // ���� �� ��������� �������
			// � �� �������, ����������� ����������� �������� ��������� � ��������� �������
			{
				Formula * curr = node->formula;
				while( curr->getNumberOfParents() > 0)  // �������� �� ������ �������� �������� ������� ������-��������� �� ���, � ������� ��������� ���
				{
//					curr = curr->getParentLink(0);
					curr = get<0>(*curr->getParentLink(0));
				}
				bool existAtomicLink = false;
				for(size_t j = 0; j < atomics.size(); j++)  // ���������� ������ ��������� ������, ����� ����� ����������� � ���������� curr
				{
//					VUENode * centerNode = atomics.at(j);
					VUEFormula * centerNode = (VUEFormula *)atomics.at(j);
					if ( centerNode->formula == curr ) // ������� ��� ��������� ��������� ������� �, ��������������, ������
					{
						existAtomicLink = true;
						node->groupAtom = centerNode->groupAtom;
						node->childProperties();
						if ( !(node->formula->isNegative() && get<0>(*node->formula->getParentLink(0))->isAtom() ) )
						{
							centerNode->numberInGroup++;
/*
���������� ��� � �������������� �������������
						node->SetPosition(x + (interval * ((centerNode->numberInGroup/4) + 1)), 
							y + (offsetOfGroup * (node->groupAtom - 1)) + (height + height_interval) * ((centerNode->numberInGroup%4) - 1), 
							width, 
							height);
*/
/*
���������� ��� � �������������� �� ��� ���� � ��� � ��������� ������
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
					loose.push_back(newNode); // ���� ������������ ��������� ������� �� �������, ������ � ������ "����������" �����
			}
			else
			{
				// ��������� ������� 
				atomics.push_back(node);
				node->groupAtom = atomics.size();
/*
���������� ��� � �������������� �������������
				node->SetPosition(x , 
					y + (offsetOfGroup * (node->groupAtom - 1)) + height_offset_atom , 
						width, 
						height);
*/
/*
���������� ��� � �������������� �� ��� ���� � ��� � ��������� ������
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

	// ������ ���������� � ���� �� �����
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

	// ���������� ���������� � ������������ ������
	// ���� �� ���� �����
	for(size_t j = 0; j < nodes.size(); j++)
	{
		VUENode * node = nodes.at(j);
		if(node->GetType() == VUEFORMULA)    // ���� ���� ������������ �������
		{
			Formula * curr = ((VUEFormula *)nodes.at(j))->formula;
			// ���� �� ���� ������������ ������
			for ( size_t j1 = 0 ; j1 < curr->getNumberOfParents(); j1++)
			{
				Formula * parent = get<0>(*curr->getParentLink(j1));    // ��������� �� �������-�������� � �����
				for(size_t j2 = 0; j2 < nodes.size(); j2++)    // ���� �� ���� �����
				{
					if(nodes.at(j)->GetType() == VUEFORMULA)
					{
						if( ((VUEFormula *)nodes.at(j2))->formula == parent)    // ���� ������� ���������� ���� �������� ������������
						{
							VUELink * link = new VUELink(numberOfFirst + numberTotal, 1 + numberTotal);    // ������ ������ ��� �����
							numberTotal++;     // ���������  ����� ���� "������" � VUE-�����
							links.push_back(link);    // ��������� � ��������� VUE-������
							link->setLink((VUEFormula *)nodes.at(j2), (VUEFormula *)node);    // ��������� ��� VIE-����� ������������ � �������� ����
							break;
						}
					}
				}
			}
		}
		else if(node->GetType() == VUESET)    // ���� ���� ������������ ��������� ����������
		{
			Formula * parent = ((VUESet *)node)->parentSet->getParentFormula();    // �������� ��������� �� �������-���������
			for(size_t j2 = 0; j2 < nodes.size(); j2++)    // ������� ���� �����
			{
				if(nodes.at(j2)->GetType() == VUEFORMULA)     // ���� ��������� ���� ������������ �������
				{
					if( ((VUEFormula *)nodes.at(j2))->formula == parent)    // � ���� ��� ������� �������� ��������� ��������� ����������
					{
						VUELink * link = new VUELink(8 + numberTotal, 1 + numberTotal);    // ������ ����� VUE-�����
						numberTotal++;    // ���������  ����� ���� "������" � VUE-�����
						links.push_back(link);    // ��������� � ��������� VUE-������
						link->setLink((VUEFormula *)nodes.at(j2), (VUESet *)node);    // ��������� ��� VIE-����� ������������ � �������� ����
						break;
					}
				}
			}
		}
	}

	// ������ �����
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
	printVUELayer(tof);  //  ������ ������
	printVUEFooter(tof, filename, currentDirStr); // ������ "�������" VUE-�����	
	tof.close();



	// ������ ��������� �������
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



	// ������ ���������� ����� � VUE-���������
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
			Sleep(6000);				// ���������
//			TerminateProcess(pi.hProcess,NO_ERROR);	// ������ �������    
		}
	}
}


void CSemanticsDlg::OnBnClickedShowallformulas3()
{
	// TODO: �������� ���� ��� ����������� �����������
}

//
//  �������� ��������� �������
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
				MessageBox(_T("������� � ������ �� ����������� ��� ���������� � �� ����� ���� �������"), _T("��������������"), MB_OK );
			else
				MessageBox(_T("A formula with the same variables already exists and cannot be created"), _T("Warning"), MB_OK );
			delete formula1;
		}
//		all_formulas.push_back(formula1);
	}
	delete cad;
	// TODO: �������� ���� ��� ����������� �����������
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
//  �������� ������� ��������� ����������� "�"
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
	// TODO: �������� ���� ��� ����������� �����������
}

//
//  �������� ������� ��������� ����������� "���"
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
	// TODO: �������� ���� ��� ����������� �����������
}

//
//  �������� ������� ��������� ���������
//
void CSemanticsDlg::OnBnClickedBuildformula3()
{
	OperationDlg operationDlg;
	operationDlg.SetOperation(NEGATIVE_OPERATION);
	operationDlg.setFormulas(&all_entities);
	
	if(operationDlg.DoModal() == IDOK)
	{
	}

	// TODO: �������� ���� ��� ����������� �����������
}

//
//  �������� ������� ��������� ����������� �������� �����������
//
void CSemanticsDlg::OnBnClickedBuildformula4()
{
	OperationDlg operationDlg;
	operationDlg.SetOperation(QUANTIFIER1_OPERATION);
	operationDlg.setFormulas(&all_entities);
	
	if(operationDlg.DoModal() == IDOK)
	{
	}
	// TODO: �������� ���� ��� ����������� �����������
}

//
//  �������� ������� ��������� ����������� �������� ��������������
//
void CSemanticsDlg::OnBnClickedBuildformula5()
{
	OperationDlg operationDlg;
	operationDlg.SetOperation(QUANTIFIER2_OPERATION);
	operationDlg.setFormulas(&all_entities);
	
	if(operationDlg.DoModal() == IDOK)
	{
	}
	// TODO: �������� ���� ��� ����������� �����������
}

//
//  ����� ������ �������������� ������
//
void CSemanticsDlg::OnBnClickedShowallformulas()
{
	SummaryDialog sd;
	sd.setFormulas(&all_entities);
	sd.DoModal();
	// TODO: �������� ���� ��� ����������� �����������
}


//
//  ������� ������ ��������� ���������� �� ������ �������
//
void CSemanticsDlg::OnBnClickedBuildformula6()
{
	SetDialog setd;
	setd.setEntities(&all_entities);
	setd.DoModal();
	// TODO: �������� ���� ��� ����������� �����������
}


//
// ����� ������ tstr, ���������� ������ � �������� � ��������� �������� ��� ������������� �������������� ��������, � spParaRng
//
void ExportMathString(tstring & tstr_in, Word::RangePtr & spParaRng)
{
	bool prevSymbolFont = false;
	int indexing = 0;  // ���������� ��� ��������� ����� ������� ���������� �������
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
		if ( dsi->symbolics[j] == SYMBOL_TYPEFACE )  // ���� �������������� ������
		{
			if(!prevSymbolFont)
				spFont->Name = L"Symbol"; // ���������� ����� Symbol
			prevSymbolFont = true;
		}
		else  // � ������ �������� �������
		{
			spFont->Name = L"Times New Roman";
			prevSymbolFont = false;
		}
		if ( indexing == LOW_MATHINDEX ) // ���� ������ ������
		{
			spFont->Subscript = true; // ���������� ������ ������ ��� ������, ������������� ��� ����������� ���������� �������
		}
		else if ( indexing == HIGH_MATHINDEX ) // ���� ������� ������
		{
			spFont->Superscript = true; // ���������� ������� ������ ��� ������, ������������� ��� ����������� ���������� �������
		}
		else
		{
			// ���������, ��� ������� ����� (��� ��������)
			spFont->Subscript = false;
			spFont->Superscript = false;
		}

		if(indexing) // ���� ��� ������� ��� ������ ������
			indexing = 0;	// ������ ���� �������
	}
	delete dsi;
}

//
//  ���������� ����� ������� spTable � ��������������� ��������� ��������� ������  ��� ������� (i + 2) �� ������ ��������� peb �� ������ EntityBase
//
void ExportToWordRow(EntityBase * peb, Word::TablePtr & spTable, int i)
{
	tstring tstr;

	//  ����� ������ �������
	tstr = peb->getText();
	Word::RangePtr spParaRng = spTable->Cell(i + 2, 2)->Range;
	ExportMathString(tstr, spParaRng);

	// ����� ����������� �������
	tstr = *(peb->getLabel());
	spParaRng = spTable->Cell(i + 2, 5)->Range;
	ExportMathString(tstr, spParaRng);

	// ����� ��������� ����������
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

	// ����� �������� �������
	tstr = *(peb->getDescription());
	spParaRng = spTable->Cell(i + 2, 6)->Range;
	ExportMathString(tstr, spParaRng);

	// ����� ��������������� ������ �������, ���� ��������������
	tstring redefined_text = *peb->getRedefinedText(); 
	tstring initial_text = *peb->getInitialText();
	trimWhitespaces(&redefined_text);
	trimWhitespaces(&initial_text);
	if((redefined_text.length() > 0) && (redefined_text.compare(initial_text))) 
	{
		spParaRng = spTable->Cell(i + 2, 7)->Range;
		ExportMathString(initial_text, spParaRng);
	}

	// ����� ��������������� �������� �������
	tstr = *(peb->getAddOns());
	spParaRng = spTable->Cell(i + 2, 8)->Range;
	ExportMathString(tstr, spParaRng);


}


//
//  ����� � ������� ��������� � ������� ����� ������ � �������� ���������, ��� �������, �������������� �������, �� �������� ����������
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
		if ( indexing == LOW_MATHINDEX ) // ���� ��� ��������� ��� ������ ��������
		{
			// ������ ��� ��������� �������� �������� ��� ������� ��������
			spFont->Subscript = true;
		}
		else if ( indexing == HIGH_MATHINDEX ) // ���� ��� ��������� ��� ������ ��������
		{
			// ������ ��� ��������� �������� �������� ��� ������� ��������
			spFont->Superscript = true;
		}
		else
		{
			if ( dsi->symbolics[j] == SYMBOL_TYPEFACE )
			{
				// ���������� ����� Symbol
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
			AfxMessageBox(_T("���������� Word.Application ��������"));
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
//		spTable->OleFunction("Cell", 1, 1)->OlePropertyGet("Range")->OlePropertySet("Text", "������� 1, ������ 1");


		// ��������� ������ ��� ����� � ����������� ��������
		for ( size_t i = 0; i < 8; i++)
		{
			Word::_FontPtr spFont = spTable->Cell(1, i + 1)->Range->Font;
			spFont->Size = 8;
			spFont->Name = L"Times New Roman";
		}

		//  ����������� ������ ���������� � ���������������� ������ �������� ������� Word
		if (CURRENT_LANG_OF == "rus") {

			spTable->Cell(1, 1)->Range->InsertAfter(L"����� �������");
			spTable->Cell(1, 1)->PutPreferredWidth(20);
			spTable->Cell(1, 2)->Range->InsertAfter(L"�������");
			spTable->Cell(1, 2)->PutPreferredWidth(60);
			spTable->Cell(1, 3)->Range->InsertAfter(L"���");
			spTable->Cell(1, 3)->PutPreferredWidth(20);
			spTable->Cell(1, 4)->Range->InsertAfter(L"��������� ����������");
			spTable->Cell(1, 4)->PutPreferredWidth(20);
			spTable->Cell(1, 5)->Range->InsertAfter(L"�����������");
			spTable->Cell(1, 5)->PutPreferredWidth(60);
			spTable->Cell(1, 6)->Range->InsertAfter(L"���������� �����������");
			spTable->Cell(1, 6)->PutPreferredWidth(60);
			spTable->Cell(1, 7)->Range->InsertAfter(L"��������� �����");
			spTable->Cell(1, 7)->PutPreferredWidth(60);
			spTable->Cell(1, 8)->Range->InsertAfter(L"������� �� ������������ ����");
			spTable->Cell(1, 8)->PutPreferredWidth(60);
			//		spTable->Cell(1, 5)->Range->Text(WideString(L"�����������"));
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
			//		spTable->Cell(1, 5)->Range->Text(WideString(L"�����������"));
		}


		for ( size_t i = 0; i < all_entities->size(); i++)  // ������� �� ���� ��������� � ������� ����� ���������
		{
			tstring tstr;
			Word::_FontPtr spFont = spTable->Cell(i + 2, 1)->Range->Font;
			spFont->Size = 8;
			spFont->Name = L"Times New Roman";
			spTable->Cell(i + 2, 1)->Range->InsertAfter(to_tstring((int) (i + 1)).c_str());
			EntityBase * peb = all_entities->at(i);

			// ����� � ������� "���" ������� Word
			tstr.clear();
			if(peb->isFormula())
			{
				Formula * icurr = (Formula *)peb;
				if (icurr->getFeature() == PERFORMED_FEATURE) 
					if (CURRENT_LANG_OF == "rus")
						tstr = _T("����������");
					else
						tstr = _T("workable");

				else if (icurr->getFeature() == TRUTH_FEATURE) 
					if (CURRENT_LANG_OF == "rus")
						tstr = _T("��������");
					else
						tstr = _T("true");
				else if (icurr->getFeature() == FALSE_FEATURE) 
					if (CURRENT_LANG_OF == "rus")
						tstr = _T("������"); 
					else
						tstr = _T("false");
				else if (icurr->getFeature() == ATOMARN_FEATURE)
					if (CURRENT_LANG_OF == "rus")
						tstr = _T("���������");
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

			ExportToWordRow(peb, spTable, i);  // ����� �������� � ��������������� ���������
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
				AfxMessageBox(_T("GetModuleDirectory ������"));
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
			AfxMessageBox(_T("������� ����������"));
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
// ������� �������� ������ � Word
//
void CSemanticsDlg::OnBnClickedExport()
{
	// TODO: �������� ���� ��� ����������� �����������
	// ������ ��� ����������� ������������
	TCHAR docFileName[MAX_PATH];
	m_fileWordExport.GetWindowTextT(docFileName, MAX_PATH-1);

	AutomateWordByImport(&all_entities, docFileName);
}


//
// �������� ���������� ����� � xml-����
//
void CSemanticsDlg::OnBnClickedSavescheme()
{
	CString strExt((LPCSTR)"*.fms");
	CString strTitle;
	if (CURRENT_LANG_OF == "rus")
		strTitle = CString((LPCSTR)"�������� ���� ��� ������ �����");
	else
		strTitle = CString((LPCSTR)"�������� ���� ��� ������ �����");

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
	// ����� ���, ������� � ������ ������ ��� ����������� libxml2, �� �� ����, ������������ ������ ��� ������
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
	//  �������� ������ �������� Formulas � Sets ����� ������� ���� ����������� �� ������ ������ ���������� ������ EntityBase
	for ( size_t i = 0; i < all_entities.size(); i ++)
	{
		EntityBase * base = all_entities.at(i);
//		if ( base->getType() == FORMULA_SET ) // ���� ��������� ��� ��������������� ��������� ���������� � ���������
		EntityBase * preplaced = base->getReplacedBase();
		if (( base->getType() == FORMULA_SET ) || ( (base->getType() == REPLACE_VARIABLE) && (preplaced != nullptr) && preplaced->isSet() )) // ���� ��������� 
		{
			FormulaSet * pfs = (FormulaSet *)base;
			CSetItem * si = new CSetItem(*pfs);	
			si->SetNumber((int)i); // ���������� ���������� ����� � �����
			if ( base->getType() == FORMULA_SET ) // ���� ���������
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
			else if((base->getType() == REPLACE_VARIABLE) && (preplaced != nullptr)) // ���� ��������������� ��������� ���������� � ���������
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
		else  // ���� �������
		{
			Formula * pf = (Formula *)base;
			CFormulaItem * fi = new CFormulaItem(*pf);
			fi->SetNumber((int)i); // ���������� ���������� ����� � �����
			// ��� ��������� �������������� ��������� ���������� ����� ������������� ��������� ����������
			if(pf->isBelongingPredicate() || pf->isSubset())
			{
				int count_of_sets = 0;
				FormulaSet * parent_set = pf->getParentSet();
				for ( size_t i1 = 0; i1 < all_entities.size(); i1 ++)
				{
					EntityBase * base1 = all_entities.at(i1);
					if ( base1->getType() == FORMULA_SET ) // ���� ���������
					{
						if(parent_set == (FormulaSet *)base1)
						{
							fi->SetParentSetNumber((int)count_of_sets); // ���������� ���������� ����� � ����� ��� ������������� ��������� ����������
							break;
						}
						count_of_sets++;
					}
				}
			}
			else if((base->getType() == REPLACE_VARIABLE) && (preplaced != nullptr))  // ���� ��������������� ��������� ���������� � ���������
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
			// ��������� ��� ������ ������� ��� ������������ ���� "�������-����������" � ������ �� ���������� ������ � ParentsLinks
			for ( size_t i1 = 0; i1 < pf->getNumberOfParents(true); i1++)
			{
				ParentLink * ppl = pf->getParentLink(i1, true);
				Formula * parentFormula = get<0>(*ppl);
				int formulaNumber = -1;
				// ��� ���������� ����� ������������ �������
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
				// ��� ���������� ����� ��������� ���������� �� ������������ ����, ���� null_ptr, �� �������� ����� ������ -1
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
			AfxMessageBox(_T("������ ���������� �����"));
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
	// TODO: �������� ���� ��� ����������� �����������
}

//
// �������� ����� ����������� ����� �� ����������� xml-�����
//
void CSemanticsDlg::OnBnClickedLoadscheme()
{
	CString strExt((LPCSTR)"*.fms");
	CString strTitle;
	if (CURRENT_LANG_OF == "rus")
		strTitle = CString((LPCSTR)"�������� ���� ��� �������� �����");
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
			AfxMessageBox(_T("������ �������� �����"));
		else
			AfxMessageBox(_T("Schema loading error"));
	}
	CoUninitialize();
	// ������ ��� ��������� �����
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
	// �������� ����� �� ���������� �� ����������� xml-����� �������� Formulas � Sets
	// ����� ������������� ������� �� Formulas � Sets, ������ �������������� ���������� ������, ��������������� �������� ������ � �����
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
				// ��� ��������� �������������� ��������� ��������� �� ������������ ��������� ����������
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
				if(Sets[i1]->ReplacedNumber != -1) // ���� ��� ������ ���������� ��� ���������
					pfs->setReplacedBase(all_entities.at(Sets[i1]->ReplacedNumber));
				else // ���� ������� ���������
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

	// TODO: �������� ���� ��� ����������� �����������
}


void CSemanticsDlg::OnBnClickedCancel()
{
	// TODO: �������� ���� ��� ����������� �����������
	CDialogEx::OnCancel();
}


void CSemanticsDlg::OnEnChangeMfceditbrowse2()
{
	// TODO:  ���� ��� ������� ���������� RICHEDIT, �� ������� ���������� �� �����
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  �������� ��� �������� ����������
}

// �������� ��������� �������������� �� ��������� ����������
void CSemanticsDlg::OnBnClickedBuildformula7()
{
	FromSetDialog setd;
	setd.setEntities(&all_entities);
	setd.DoModal();

	// TODO: �������� ���� ��� ����������� �����������
}


//�������� �������
void CSemanticsDlg::OnBnClickedBuildtuple()
{
	CTupleDlg * ctd = new CTupleDlg(this);
	ctd->SetEntities(&all_entities);
	if(ctd->DoModal() == IDOK)
	{

	}
	delete ctd;
	// TODO: �������� ���� ��� ����������� �����������
}

// ����� ����� ������ ����������
void CSemanticsDlg::OnBnClickedChangevariable()
{
	ReplaceVariableDialog * rvd = new ReplaceVariableDialog(this);
	rvd->setEntities(&all_entities);
	if(rvd->DoModal() == IDOK)
	{

	}
	delete rvd;
	// TODO: �������� ���� ��� ����������� �����������
}


void CSemanticsDlg::OnBnClickedRus()
{
	// TODO: Add your control notification handler code here
	
	CURRENT_LANG_OF = "rus";
	GetDlgItem(RB_RUS)->SetWindowTextW(L"�������");
	GetDlgItem(RB_ENG)->SetWindowTextW(L"����������");
	m_rbLang = 0;

	GetDlgItem(IDC_ADDAKSIOMA)->SetWindowTextW(L"�������� ��������� �������");
	
	GetDlgItem(IDC_SHOWALLFORMULAS)->SetWindowTextW(L"���������� ��� �������");

	GetDlgItem(IDC_BUILDFORMULA1)->SetWindowTextW(L"���������� ����� ������� Pk:= Pi && Pj");

	GetDlgItem(IDC_BUILDFORMULA2)->SetWindowTextW(L"���������� ����� ������� Pk:= Pi V Pj");

	GetDlgItem(IDC_BUILDFORMULA3)->SetWindowTextW(L"���������� ����� ������� Pk:=not (Pi)");

	GetDlgItem(IDC_BUILDFORMULA4)->SetWindowTextW(L"���������� ����� ������� Pk:= ( K a ) Pi, ��� a - ��������� ����������");
												  //    Building new formula
	GetDlgItem(IDC_BUILDFORMULA5)->SetWindowTextW(L"���������� ����� ������� Pk:= ( K a ) Pj, ��� a - ��������� ����������");

	GetDlgItem(IDC_BUILDFORMULA6)->SetWindowTextW(L"���������� ��������� �� ������ �������");

	GetDlgItem(IDC_CHANGEVARIABLE)->SetWindowTextW(L"������ ����������");



	GetDlgItem(IDEXPORT)->SetWindowTextW(L"������� � WORD");

	GetDlgItem(IDOK)->SetWindowTextW(L"�����");



	GetDlgItem(IDCANCEL)->SetWindowTextW(L"������");

	GetDlgItem(IDSAVESCHEME)->SetWindowTextW(L"���������");

	GetDlgItem(IDLOADSCHEME)->SetWindowTextW(L"���������");

	GetDlgItem(ID_HELP)->SetWindowTextW(L"�������");

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


	//���������� ����� ������� Pk:=not (Pi)

	//IDR_MENU_SYMBOLS -- ���������� ����
	//IDD_SEMANTICS_DIALOG -- ������� ����
	//IDD_REPLACEVARIABLE -- �������� ��������� ����������
	//IDD_CHOOSEDIALOG -- �������� ����� ������

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
