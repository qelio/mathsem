
// SemanticsDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "Semantics.h"
#include "SemanticsDlg.h"
#include "afxdialogex.h"
#include "AtomFormulaDialog.h"
#include "SummaryDialog.h"
#include "common_functions.h"
#include "SchemaDialog.h"
#include "OperationDlg.h"
//#include <afxdisp.h>



#ifdef WITHEXCEL
#import "C:\Program Files\Common Files\Microsoft Shared\OFFICE12\MSO.DLL" no_implementation rename("RGB", "ExclRGB") rename("DocumentProperties", "ExclDocumentProperties") rename("SearchPath", "ExclSearchPath")
//exclude("CalloutFormat")
#import "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB" no_implementation
#import "C:\Program Files\Microsoft Office\OFFICE12\EXCEL.EXE"  auto_rename rename("DialogBox", "ExclDialogBox") rename("RGB", "ExclRGB") rename("CopyFile", "ExclCopyFile") rename("ReplaceText", "ExclReplaceText") 
//	        include("IFont","IPicture") rename("IFont","_IFont") rename("IPicture","_IPicture")
/*
//#include "../Semantics/Debug/excel.tlh"
//using namespace Excel;
//#define USES_MSO97
//#define USES_MSO2000
//#define USES_MSO2002
#define USES_MSO2003

#ifdef USES_MSO97
#import "C:\Program Files\Microsoft Office\Office\Excel8.OLB" auto_search auto_rename
#endif
#ifdef USES_MSO2000
#import "C:\Program Files\Microsoft Office\Office\Excel9.OLB" auto_search auto_rename
#endif
#ifdef USES_MSO2002
#import "progid:Excel.Sheet.8" auto_search auto_rename rename_search_namespace("Office9") \
	       rename("DialogBox","_DialogBox") \
        rename("RGB","_RGB") \
        exclude("IFont","IPicture")
#endif
#ifdef USES_MSO2003

#import "progid:Excel.Sheet.8" auto_search auto_rename rename_search_namespace("Office9") \
	       rename("DialogBox","_DialogBox") \
        rename("RGB","ExclRGB") \
        exclude("IFont","IPicture")

#endif
*/
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef WITHEXCEL
#include <ole2.h> // OLE2 Definitions

// AutoWrap() - Automation helper function...
HRESULT AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs...) {
    // Begin variable-argument list...
    va_list marker;
    va_start(marker, cArgs);

    if(!pDisp) {
        MessageBox(NULL, _T("NULL IDispatch passed to AutoWrap()"), _T("Error"), 0x10010);
        _exit(0);
    }

    // Variables used...
    DISPPARAMS dp = { NULL, NULL, 0, 0 };
    DISPID dispidNamed = DISPID_PROPERTYPUT;
    DISPID dispID;
    HRESULT hr;
    char buf[200];
    char szName[200];

    
    // Convert down to ANSI
    WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL);
    
    // Get DISPID for name passed...
    hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispID);
    if(FAILED(hr)) {
		tstring str_err = _T("IDispatch::GetIDsOfNames(\\");
		//str_err += 
        //sprintf(buf, "IDispatch::GetIDsOfNames(\"%s\") failed w/err 0x%08lx", szName, hr);
        ::MessageBox(NULL, str_err.data() , _T("AutoWrap()"), 0x10010);
        _exit(0);
        return hr;
    }
    
    // Allocate memory for arguments...
    VARIANT *pArgs = new VARIANT[cArgs+1];
    // Extract arguments...
    for(int i=0; i<cArgs; i++) {
        pArgs[i] = va_arg(marker, VARIANT);
    }
    
    // Build DISPPARAMS
    dp.cArgs = cArgs;
    dp.rgvarg = pArgs;
    
    // Handle special-case for property-puts!
    if(autoType & DISPATCH_PROPERTYPUT) {
        dp.cNamedArgs = 1;
        dp.rgdispidNamedArgs = &dispidNamed;
    }
    
    // Make the call!
    hr = pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, autoType, &dp, pvResult, NULL, NULL);
    if(FAILED(hr)) {
//        sprintf(buf, "IDispatch::Invoke(\"%s\"=%08lx) failed w/err 0x%08lx", szName, dispID, hr);
        MessageBox(NULL, _T("IDispatch::Invoke"), _T("AutoWrap()"), 0x10010);
        _exit(0);
        return hr;
    }
    // End variable-argument section...
    va_end(marker);
    
    delete [] pArgs;
    
    return hr;
}

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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

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
END_MESSAGE_MAP()


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

	m_fileFinder.SetWindowTextT(_T("D:\\VUE\\VUE-launcher.exe"));


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

#ifdef WITHEXCEL
void SetTextInBox(Excel::ShapePtr pShape, tstring &res_formula)
{
	IDispatch *pXlTextEffectFormat;
	VARIANT result;
	VariantInit(&result);
	AutoWrap(DISPATCH_PROPERTYGET, &result, pShape, L"TextEffect", 0);
	pXlTextEffectFormat = result.pdispVal;
	VARIANT x;
	x.bstrVal = _bstr_t(res_formula.data());
	x.vt = VT_BSTR;
	AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlTextEffectFormat, L"Text", 1, x);
	pXlTextEffectFormat->Release();
}

void SetDashLineOfBox(Excel::ShapePtr pShape, int style)
{
	IDispatch *pXlLineFormat;
	VARIANT result;
	VariantInit(&result);
	AutoWrap(DISPATCH_PROPERTYGET, &result, pShape, L"Line", 0);
	pXlLineFormat = result.pdispVal;
	VARIANT x;
	x.vt = VT_INT;
	switch (style)
	{
		case 1:
		{
			x.intVal = style;
			AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlLineFormat, L"Style", 1, x);
			break;
		}
		case 2:
		{
			x.intVal = style;
			AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlLineFormat, L"Style", 1, x);
			break;
		}
		case 3:
		default:
		{
			x.intVal = 4;
			AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlLineFormat, L"DashStyle", 1, x);
			break;
		}
	}
	pXlLineFormat->Release();
}

void ArrowedLine(Excel::ShapesPtr pShapes, RECT * rectBegin, RECT * rectFinish)
{
	Excel::ShapePtr pLine = pShapes->AddLine( (rectBegin->left + rectBegin->right)/2 , rectBegin->bottom, (rectFinish->left + rectFinish->right)/2 , rectFinish->bottom );
	IDispatch *pXlLineFormat;
	VARIANT result;
	VariantInit(&result);
	AutoWrap(DISPATCH_PROPERTYGET, &result, pLine, L"Line", 0);
	pXlLineFormat = result.pdispVal;
	VARIANT x;
	x.vt = VT_INT;
	x.intVal = 2;
	AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlLineFormat, L"EndArrowheadStyle", 1, x);
//	pXlTextEffectFormat->Release();	
//	pLine->Line->PutEndArrowheadStyle(Office::MsoArrowheadStyle::msoArrowheadTriangle);
}
#endif

void CSemanticsDlg::OnBnClickedOk()
{
//	SchemaDialog sd;
//	sd.DoModal();
	if(all_formulas.size() < 1)
	{
		MessageBox(_T("Не определено ни одной формулы. Схема не будет построена"), _T("Замечание"), MB_OK);
		return;
	}
	int n = 1;
	setlocale(LC_ALL, "rus");
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
	if(!tof.bad())
	{
	tof << "<!-- Tufts VUE 3.2.2 concept-map (";
	tof << filename;
	tof << ") 2013-09-10 -->" << endl;
	tof << "<!-- Tufts VUE: http://vue.tufts.edu/ -->" << endl;
	tof << "<!-- Do Not Remove: VUE mapping @version(1.1) jar:file:/D:/VUE/VUE.jar!/tufts/vue/resources/lw_mapping_1_1.xml -->" << endl;
	tof << "<!-- Do Not Remove: Saved date Tue Sep 10 14:15:28 YEKT 2013 by user on platform Windows XP 5.1 in JVM 1.7.0_21-b11 -->" << endl;
	tof << "<!-- Do Not Remove: Saving version @(#)VUE: built May 23 2013 at 2146 by tomadm on Linux 2.6.18-348.2.1.el5 i386 JVM 1.7.0_21-b11(bits=32) -->" << endl;
	tof << "<?xml version=\"1.0\" encoding=\"US-ASCII\"?>" << endl;
	tof << "<LW-MAP xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << endl;
	tof << "    xsi:noNamespaceSchemaLocation=\"none\" ID=\"0\"" << endl;
	tof << "    label=\"";
	tof << filename;
	tof << "\"" << endl;
	tof << "    created=\"1378800153093\" x=\"0.0\" y=\"0.0\" width=\"1.4E-45\"" << endl;
	tof << "    height=\"1.4E-45\" strokeWidth=\"0.0\" autoSized=\"false\">" << endl;
	tof << "    <resource referenceCreated=\"1378800928968\"" << endl;
	tof << "        spec=\"";

	tof << currentDir;
	tof << filename;
	tof << "\"" << endl;
	tof << "        type=\"1\" xsi:type=\"URLResource\">" << endl;
	tof << "        <title>";
	tof << filename;
	tof << "</title>" << endl;
	tof << "        <property key=\"File\" value=\"";
	tof << currentDir;
	tof << filename;
	tof << "\"/>" << endl;
	tof << "    </resource>" << endl;
	tof << "    <fillColor>#FFFFFF</fillColor>" << endl;
	tof << "    <strokeColor>#404040</strokeColor>" << endl;
	tof << "    <textColor>#000000</textColor>" << endl;
	tof << "    <font>SansSerif-plain-14</font>" << endl;
	tof << "    <URIString>http://vue.tufts.edu/rdf/resource/06e8c0d7c0a8000b00f95b1e7c5003d1</URIString>" << endl;

	// выводим легенду (фигурки с расшифровкой что кто обзоначает)
	tof << "    <child ID=\"6\" layerID=\"1\" created=\"1373631072250\" x=\"-695.0\"" << endl;
	tof << "        y=\"-200.0\" width=\"295.0\" height=\"270.05835\" strokeWidth=\"2.0\"" << endl;
	tof << "        strokeStyle=\"2\" autoSized=\"true\" xsi:type=\"node\">" << endl;
	tof << "        <resource referenceCreated=\"0\" accessAttempted=\"1373631233515\"" << endl;
	tof << "            accessSuccessful=\"1373631233609\" size=\"9688\"" << endl;
	tof << "            spec=\"" << legend;
	tof << "legend.JPG\" type=\"1\" xsi:type=\"URLResource\">" << endl;
	tof << "            <title>legend.JPG</title>" << endl;
	tof << "            <property key=\"Content.size\" value=\"9688\"/>" << endl;
	tof << "            <property key=\"Content.modified\" value=\"Fri Jul 12 18:10:16 YEKT 2013\"/>" << endl;
	tof << "            <property key=\"image.width\" value=\"257\"/>" << endl;
	tof << "            <property key=\"image.height\" value=\"242\"/>" << endl;
	tof << "            <property key=\"image.format\" value=\"JPEG\"/>" << endl;
	tof << "            <property key=\"@file.relative\" value=\"legend.JPG\"/>" << endl;
	tof << "            <property key=\"File\" value=\"legend.JPG\"/>" << endl;
	tof << "        </resource>" << endl;
	tof << "        <fillColor>#0AAD1D</fillColor>" << endl;
	tof << "        <strokeColor>#000000</strokeColor>" << endl;
	tof << "        <textColor>#000000</textColor>" << endl;
	tof << "        <font>Arial-bold-12</font>" << endl;
	tof << "        <URIString>http://vue.tufts.edu/rdf/resource/d2cdd634c0a8000b01592170d07ead80</URIString>" << endl;
	tof << "        <child ID=\"7\" created=\"1373631127984\" x=\"34.0\" y=\"23.0\"" << endl;
	tof << "            width=\"256.0\" height=\"241.05836\" strokeWidth=\"0.0\"" << endl;
	tof << "            autoSized=\"false\" xsi:type=\"image\">" << endl;
	tof << "            <resource referenceCreated=\"0\"" << endl;
	tof << "                accessAttempted=\"1373631233515\"" << endl;
	tof << "                accessSuccessful=\"1373631233609\" size=\"9688\"" << endl;
	tof << "            spec=\"" << legend;
	tof << "legend.JPG\"" << endl;
//	tof << "                spec=\"D:\\project2010\\Semantics\\Release\\legend.JPG\"" << endl;
	tof << "                type=\"1\" xsi:type=\"URLResource\">" << endl;
	tof << "                <title>legend.JPG</title>" << endl;
	tof << "                <property key=\"Content.size\" value=\"9688\"/>" << endl;
	tof << "                <property key=\"Content.modified\" value=\"Fri Jul 12 18:10:16 YEKT 2013\"/>" << endl;
	tof << "                <property key=\"image.width\" value=\"257\"/>" << endl;
	tof << "                <property key=\"image.height\" value=\"242\"/>" << endl;
	tof << "                <property key=\"image.format\" value=\"JPEG\"/>" << endl;
	tof << "                <property key=\"@file.relative\" value=\"legend.JPG\"/>" << endl;
	tof << "                <property key=\"File\" value=\"legend.JPG\"/>" << endl;
	tof << "            </resource>" << endl;
	tof << "            <strokeColor>#404040</strokeColor>" << endl;
	tof << "            <textColor>#000000</textColor>" << endl;
	tof << "            <font>SansSerif-plain-14</font>" << endl;
	tof << "            <URIString>http://vue.tufts.edu/rdf/resource/d2cdd643c0a8000b01592170df367645</URIString>" << endl;
	tof << "        </child>" << endl;
	tof << "        <shape xsi:type=\"rectangle\"/>" << endl;
	tof << "    </child>" << endl;




	// сейчас запись узлов и связи, пока один узел
	double x= -354.0;
	double y = -199.0;
	double width = 120.0;
	double height = 160.0;
	double interval = 200.0;
	double height_interval = 30.;
	double height_offset_atom = (1.5 *height) + (1.5 * height_interval);
	double offsetOfGroup = (height + height_interval) * 4;
//	int groupAtom = 0;
	int numberTotal = 0;
	vector <VUENode *> nodes;
	vector <VUENode *> atomics;
	vector <VUENode *> loose;
	vector <VUELink *> links;
	for(size_t i = 0; i < all_formulas.size(); i++)
	{
		VUENode * node = new VUENode(8 + numberTotal, 1 + numberTotal);
		numberTotal++;
		node->formula = all_formulas.at(i);
		if(!node->formula->isAtom())
		{
			Formula * curr = node->formula;
			while( curr->parents.size() > 0)
			{
				curr = curr->parents.at(0);
			}
			bool existAtomicLink = false;
			for(size_t j = 0; j < atomics.size(); j++)
			{
				VUENode * centerNode = atomics.at(j);
				if ( atomics.at(j)->formula == curr )
				{
					existAtomicLink = true;
					centerNode->numberInGroup++;
					node->groupAtom = centerNode->groupAtom;
					node->childProperties();
					node->SetPosition(x + (interval * ((centerNode->numberInGroup/4) + 1)), 
						y + (offsetOfGroup * (node->groupAtom - 1)) + (height + height_interval) * ((centerNode->numberInGroup%4) - 1), 
						width, 
						height);
					break;
				}
			}
			if( !existAtomicLink )
				loose.push_back(node);
		}
		else
		{
			// атомарная формула
			atomics.push_back(node);
			node->groupAtom = atomics.size();
			node->SetPosition(x , 
				y + (offsetOfGroup * (node->groupAtom - 1)) + height_offset_atom , 
						width, 
						height);
		}
		nodes.push_back(node);
//		node->SetPosition(x + (width + 30.0)* i, y + (height + 30.0) * i, 133.0, 167.0);
//		tof << node << endl;
//		node.print(tof);
	}
	for(size_t j = 0; j < nodes.size(); j++)
	{
		nodes.at(j)->print(tof);
	}

	for(size_t j = 0; j < nodes.size(); j++)
	{
		Formula * curr = nodes.at(j)->formula;
		for ( size_t j1 = 0 ; j1 < curr->parents.size(); j1++)
		{
			Formula * parent = curr->parents.at(j1);
			for(size_t j2 = 0; j2 < nodes.size(); j2++)
			{
				if(nodes.at(j2)->formula == parent)
				{
					VUELink * link = new VUELink(8 + numberTotal, 1 + numberTotal);
					numberTotal++;
					links.push_back(link);
					link->setLink(nodes.at(j2), nodes.at(j));
					break;
				}
			}
		}
	}
	for(size_t j = 0; j < links.size(); j++)
	{
		links.at(j)->print(tof);
	}
	for(size_t j = 0; j < nodes.size(); j++)
	{
		delete nodes.at(j);
	}
	for(size_t j = 0; j < loose.size(); j++)
	{
		delete loose.at(j);
	}
	for(size_t j = 0; j < links.size(); j++)
	{
		delete links.at(j);
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

	//  запись уровня
	tof << "    <layer ID=\"1\" label=\"Layer 1\" created=\"1378800153093\" x=\"0.0\"" << endl;
	tof << "        y=\"0.0\" width=\"1.4E-45\" height=\"1.4E-45\" strokeWidth=\"0.0\" autoSized=\"false\">" << endl;
	tof << "        <URIString>http://vue.tufts.edu/rdf/resource/06e8c0f6c0a8000b00f95b1e0b908b0f</URIString>" << endl;
	tof << "    </layer>" << endl;


	tof << "    <userZoom>1.0</userZoom>" << endl;
	tof << "    <userOrigin x=\"-14.0\" y=\"-14.0\"/>" << endl;
	tof << "    <presentationBackground>#202020</presentationBackground>" << endl;
	tof << "    <PathwayList currentPathway=\"0\" revealerIndex=\"-1\">" << endl;
	tof << "        <pathway ID=\"0\"" << endl;
	tof << "            label=\"&#x41c;&#x430;&#x440;&#x448;&#x440;&#x443;&#x442; &#x431;&#x435;&#x437; &#x438;&#x43c;&#x435;&#x43d;&#x438;\"" << endl;
	tof << "            created=\"1378800153078\" x=\"0.0\" y=\"0.0\" width=\"1.4E-45\"";
	tof << "            height=\"1.4E-45\" strokeWidth=\"0.0\" autoSized=\"false\"" << endl;
	tof << "            currentIndex=\"-1\" open=\"true\">" << endl;
	tof << "            <strokeColor>#B3CC33CC</strokeColor>" << endl;
	tof << "            <textColor>#000000</textColor>" << endl;
	tof << "            <font>SansSerif-plain-14</font>" << endl;
	tof << "            <URIString>http://vue.tufts.edu/rdf/resource/06e8c0f6c0a8000b00f95b1e5052945b</URIString>" << endl;
	tof << "            <masterSlide ID=\"2\" created=\"1378800153125\" x=\"0.0\" y=\"0.0\"" << endl;
	tof << "                width=\"800.0\" height=\"600.0\" locked=\"true\"" << endl;
	tof << "                strokeWidth=\"0.0\" autoSized=\"false\">" << endl;
	tof << "                <fillColor>#000000</fillColor>" << endl;
	tof << "                <strokeColor>#404040</strokeColor>" << endl;
	tof << "                <textColor>#000000</textColor>" << endl;
	tof << "                <font>SansSerif-plain-14</font>" << endl;
	tof << "                <URIString>http://vue.tufts.edu/rdf/resource/06e8c0f6c0a8000b00f95b1ea03139ac</URIString>" << endl;
	tof << "                <titleStyle ID=\"3\" label=\"Header\"" << endl;
	tof << "                    created=\"1378800153156\" x=\"335.5\" y=\"172.5\"" << endl;
	tof << "                    width=\"129.0\" height=\"55.0\" strokeWidth=\"0.0\"" << endl;
	tof << "                    autoSized=\"true\" isStyle=\"true\" xsi:type=\"node\">" << endl;
	tof << "                    <strokeColor>#404040</strokeColor>" << endl;
	tof << "                    <textColor>#FFFFFF</textColor>" << endl;
	tof << "                    <font>Gill Sans-plain-36</font>" << endl;
	tof << "                    <URIString>http://vue.tufts.edu/rdf/resource/06e8c0f6c0a8000b00f95b1e7c83bf85</URIString>" << endl;
	tof << "                    <shape xsi:type=\"rectangle\"/>" << endl;
	tof << "                </titleStyle>" << endl;
	tof << "                <textStyle ID=\"4\" label=\"Slide Text\"" << endl;
	tof << "                    created=\"1378800153156\" x=\"346.5\" y=\"281.5\"" << endl;
	tof << "                    width=\"107.0\" height=\"37.0\" strokeWidth=\"0.0\"" << endl;
	tof << "                    autoSized=\"true\" isStyle=\"true\" xsi:type=\"node\">" << endl;
	tof << "                    <strokeColor>#404040</strokeColor>" << endl;
	tof << "                    <textColor>#FFFFFF</textColor>" << endl;
	tof << "                    <font>Gill Sans-plain-22</font>" << endl;
	tof << "                    <URIString>http://vue.tufts.edu/rdf/resource/06e8c106c0a8000b00f95b1e33dc73d4</URIString>" << endl;
	tof << "                    <shape xsi:type=\"rectangle\"/>" << endl;
	tof << "                </textStyle>" << endl;
	tof << "                <linkStyle ID=\"5\" label=\"Links\" created=\"1378800153171\"" << endl;
	tof << "                    x=\"373.5\" y=\"384.0\" width=\"53.0\" height=\"32.0\"" << endl;
	tof << "                    strokeWidth=\"0.0\" autoSized=\"true\" isStyle=\"true\" xsi:type=\"node\">" << endl;
	tof << "                    <strokeColor>#404040</strokeColor>" << endl;
	tof << "                    <textColor>#B3BFE3</textColor>" << endl;
	tof << "                    <font>Gill Sans-plain-18</font>" << endl;
	tof << "                    <URIString>http://vue.tufts.edu/rdf/resource/06e8c106c0a8000b00f95b1ea93b8699</URIString>" << endl;
	tof << "                    <shape xsi:type=\"rectangle\"/>" << endl;
	tof << "                </linkStyle>" << endl;
	tof << "            </masterSlide>" << endl;
	tof << "        </pathway>" << endl;
	tof << "    </PathwayList>" << endl;
	tof << "    <date>2013-09-10</date>" << endl;
	tof << "    <modelVersion>6</modelVersion>" << endl;
	
	tof << "    <saveLocation>";
	tof << currentDir;
	tof << "</saveLocation>" << endl;
	tof << "    <saveFile>";
	tof << currentDir;
	tof << filename;
	tof << "</saveFile>" << endl;
	tof << "</LW-MAP>";
	
	tof.close();

	// диалог для определения просмотрщика
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

/*
	tof << ("<!-- Tufts VUE 3.2.2 concept-map (";
	tof << filename;
	tof << ") 2013-09-10 -->" << endl;
	tof << "<!-- Tufts VUE: http://vue.tufts.edu/ -->" << endl;
	tof << _T("<!-- Do Not Remove: VUE mapping @version(1.1) jar:file:/D:/VUE/VUE.jar!/tufts/vue/resources/lw_mapping_1_1.xml -->") << endl;
	tof << _T("<!-- Do Not Remove: Saved date Tue Sep 10 14:15:28 YEKT 2013 by user on platform Windows XP 5.1 in JVM 1.7.0_21-b11 -->") << endl;
	tof << _T("<!-- Do Not Remove: Saving version @(#)VUE: built May 23 2013 at 2146 by tomadm on Linux 2.6.18-348.2.1.el5 i386 JVM 1.7.0_21-b11(bits=32) -->") << endl;
	tof << _T("<?xml version=\"1.0\" encoding=\"US-ASCII\"?>") << endl;
	tof << _T("<LW-MAP xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"") << endl;
	tof << _T("    xsi:noNamespaceSchemaLocation=\"none\" ID=\"0\"") << endl;
	tof << _T("    label=\"");
	tof << filename;
	tof << _T("\"") << endl;
	tof << _T("    created=\"1378800153093\" x=\"0.0\" y=\"0.0\" width=\"1.4E-45\"") << endl;
	tof << _T("    height=\"1.4E-45\" strokeWidth=\"0.0\" autoSized=\"false\">") << endl;
	tof << _T("    <resource referenceCreated=\"1378800928968\"") << endl;
	tof << _T("        spec=\"");

	tof << currentDir;
	tof << filename;
	tof << _T("\"") << endl;
	tof << _T("        type=\"1\" xsi:type=\"URLResource\">") << endl;
	tof << _T("        <title>");
	tof << filename;
	tof << _T("</title>") << endl;
	tof << _T("        <property key=\"File\" value=\"");
	tof << currentDir;
	tof << filename;
	tof << _T("\"/>") << endl;
	tof << _T("    </resource>") << endl;
	tof << _T("    <fillColor>#FFFFFF</fillColor>") << endl;
	tof << _T("    <strokeColor>#404040</strokeColor>") << endl;
	tof << _T("    <textColor>#000000</textColor>") << endl;
	tof << _T("    <font>SansSerif-plain-14</font>") << endl;
	tof << _T("    <URIString>http://vue.tufts.edu/rdf/resource/06e8c0d7c0a8000b00f95b1e7c5003d1</URIString>") << endl;


	// сейчас запись узлов и связи, пока один узел
	tof << _T("    <child ID=\"6\"") << endl;
	tof << _T("        label=\"");
	tof << _T("Узел 1");
	tof << _T("\"") << endl;
	tof << _T("        layerID=\"1\" created=\"1378800156937\" x=\"107.0\" y=\"78.0\"") << endl;
	tof << _T("        width=\"133.0\" height=\"167.0\" strokeWidth=\"2.0\" strokeStyle=\"2\"") << endl;
	tof << _T("        autoSized=\"false\" xsi:type=\"node\">") << endl;
	tof << _T("        <fillColor>#0AAD1D</fillColor>") << endl;
	tof << _T("        <strokeColor>#000000</strokeColor>") << endl;
	tof << _T("        <textColor>#000000</textColor>") << endl;
	tof << _T("        <font>Arial-bold-12</font>") << endl;
	tof << _T("        <URIString>http://vue.tufts.edu/rdf/resource/06e8c0d7c0a8000b00f95b1eac61c244</URIString>") << endl;
	tof << _T("        <shape xsi:type=\"rectangle\"/>") << endl;
	tof << _T("    </child>") << endl;

	//  запись уровня
	tof << _T("    <layer ID=\"1\" label=\"Layer 1\" created=\"1378800153093\" x=\"0.0\"") << endl;
	tof << _T("        y=\"0.0\" width=\"1.4E-45\" height=\"1.4E-45\" strokeWidth=\"0.0\" autoSized=\"false\">") << endl;
	tof << _T("        <URIString>http://vue.tufts.edu/rdf/resource/06e8c0f6c0a8000b00f95b1e0b908b0f</URIString>") << endl;
	tof << _T("    </layer>") << endl;


	tof << _T("    <userZoom>1.0</userZoom>") << endl;
	tof << _T("    <userOrigin x=\"-14.0\" y=\"-14.0\"/>") << endl;
	tof << _T("    <presentationBackground>#202020</presentationBackground>") << endl;
	tof << _T("    <PathwayList currentPathway=\"0\" revealerIndex=\"-1\">") << endl;
	tof << _T("        <pathway ID=\"0\"") << endl;
	tof << _T("            label=\"&#x41c;&#x430;&#x440;&#x448;&#x440;&#x443;&#x442; &#x431;&#x435;&#x437; &#x438;&#x43c;&#x435;&#x43d;&#x438;\"") << endl;
	tof << _T("            created=\"1378800153078\" x=\"0.0\" y=\"0.0\" width=\"1.4E-45\"");
	tof << _T("            height=\"1.4E-45\" strokeWidth=\"0.0\" autoSized=\"false\"") << endl;
	tof << _T("            currentIndex=\"-1\" open=\"true\">") << endl;
	tof << _T("            <strokeColor>#B3CC33CC</strokeColor>") << endl;
	tof << _T("            <textColor>#000000</textColor>") << endl;
	tof << _T("            <font>SansSerif-plain-14</font>") << endl;
	tof << _T("            <URIString>http://vue.tufts.edu/rdf/resource/06e8c0f6c0a8000b00f95b1e5052945b</URIString>") << endl;
	tof << _T("            <masterSlide ID=\"2\" created=\"1378800153125\" x=\"0.0\" y=\"0.0\"") << endl;
	tof << _T("                width=\"800.0\" height=\"600.0\" locked=\"true\"") << endl;
	tof << _T("                strokeWidth=\"0.0\" autoSized=\"false\">") << endl;
	tof << _T("                <fillColor>#000000</fillColor>") << endl;
	tof << _T("                <strokeColor>#404040</strokeColor>") << endl;
	tof << _T("                <textColor>#000000</textColor>") << endl;
	tof << _T("                <font>SansSerif-plain-14</font>") << endl;
	tof << _T("                <URIString>http://vue.tufts.edu/rdf/resource/06e8c0f6c0a8000b00f95b1ea03139ac</URIString>") << endl;
	tof << _T("                <titleStyle ID=\"3\" label=\"Header\"") << endl;
	tof << _T("                    created=\"1378800153156\" x=\"335.5\" y=\"172.5\"") << endl;
	tof << _T("                    width=\"129.0\" height=\"55.0\" strokeWidth=\"0.0\"") << endl;
	tof << _T("                    autoSized=\"true\" isStyle=\"true\" xsi:type=\"node\">") << endl;
	tof << _T("                    <strokeColor>#404040</strokeColor>") << endl;
	tof << _T("                    <textColor>#FFFFFF</textColor>") << endl;
	tof << _T("                    <font>Gill Sans-plain-36</font>") << endl;
	tof << _T("                    <URIString>http://vue.tufts.edu/rdf/resource/06e8c0f6c0a8000b00f95b1e7c83bf85</URIString>") << endl;
	tof << _T("                    <shape xsi:type=\"rectangle\"/>") << endl;
	tof << _T("                </titleStyle>") << endl;
	tof << _T("                <textStyle ID=\"4\" label=\"Slide Text\"") << endl;
	tof << _T("                    created=\"1378800153156\" x=\"346.5\" y=\"281.5\"") << endl;
	tof << _T("                    width=\"107.0\" height=\"37.0\" strokeWidth=\"0.0\"") << endl;
	tof << _T("                    autoSized=\"true\" isStyle=\"true\" xsi:type=\"node\">") << endl;
	tof << _T("                    <strokeColor>#404040</strokeColor>") << endl;
	tof << _T("                    <textColor>#FFFFFF</textColor>") << endl;
	tof << _T("                    <font>Gill Sans-plain-22</font>") << endl;
	tof << _T("                    <URIString>http://vue.tufts.edu/rdf/resource/06e8c106c0a8000b00f95b1e33dc73d4</URIString>") << endl;
	tof << _T("                    <shape xsi:type=\"rectangle\"/>") << endl;
	tof << _T("                </textStyle>") << endl;
	tof << _T("                <linkStyle ID=\"5\" label=\"Links\" created=\"1378800153171\"") << endl;
	tof << _T("                    x=\"373.5\" y=\"384.0\" width=\"53.0\" height=\"32.0\"") << endl;
	tof << _T("                    strokeWidth=\"0.0\" autoSized=\"true\" isStyle=\"true\" xsi:type=\"node\">") << endl;
	tof << _T("                    <strokeColor>#404040</strokeColor>") << endl;
	tof << _T("                    <textColor>#B3BFE3</textColor>") << endl;
	tof << _T("                    <font>Gill Sans-plain-18</font>") << endl;
	tof << _T("                    <URIString>http://vue.tufts.edu/rdf/resource/06e8c106c0a8000b00f95b1ea93b8699</URIString>") << endl;
	tof << _T("                    <shape xsi:type=\"rectangle\"/>") << endl;
	tof << _T("                </linkStyle>") << endl;
	tof << _T("            </masterSlide>") << endl;
	tof << _T("        </pathway>") << endl;
	tof << _T("    </PathwayList>") << endl;
	tof << _T("    <date>2013-09-10</date>") << endl;
	tof << _T("    <modelVersion>6</modelVersion>") << endl;
	
	tof << _T("    <saveLocation>");
	tof << currentDir;
	tof << _T("</saveLocation>") << endl;
	tof << _T("    <saveFile>");
	tof << currentDir;
	tof << filename;
	tof << _T("</saveFile>") << endl;
	tof << _T("</LW-MAP>");
	
	tof.close();
	*/



#ifdef WITHEXCEL
	// это вставка дляподключения Эксела
	/*
	if(!AfxOleInit())  // Your addition starts here
	{
		AfxMessageBox(_T("Could not initialize COM dll"));
		return FALSE;
	}                 // End of your addition

	AfxEnableControlContainer();	// InitCommonControlsEx() требуется для Windows XP, если манифест
	*/
	  // Иницилизация COM объекта
	if(all_formulas.size() == 0)
	{
		::MessageBox(NULL, _T("Не создано ни одной формулы. Схема сохдана не будет"), _T("Ошибка"),  MB_SETFOREGROUND | MB_OK);
		return;
	}

	CoInitialize(NULL);
	// Использовать именное пространство Excel
	using namespace Excel;
	// Соединение с MS Excel
	_ApplicationPtr pXL;

	try
	{

		pXL.CreateInstance(L"Excel.Application");
		// Показать приложение VARIANT_TRUE или не показывать VARIANT_FALSE
		pXL->Visible[0] = VARIANT_TRUE;
		// Подключение книги
		WorkbooksPtr pBooks = pXL->Workbooks;
		// Создание новой книги
		_WorkbookPtr pBook  = pBooks->Add((long)xlWorksheet);
		// Указатель на N книгу  
		//WorkbookPtr book = pXL->Workbooks->Item[N];

		// Указатель на активную страницу
		_WorksheetPtr pSheet = pXL->ActiveSheet;
  
		// Указатель на N страницу  
		//_WorksheetPtr pSheet = pXL->Worksheets->Item[N];
		// Изменение имени страницы
		pSheet->Name = "Semantic schema";
		// Доступ ко всем ячейкам
		RangePtr pRange = pSheet->Cells;

		RangePtr pCell;
		pCell = pSheet->GetRange( _bstr_t( _T("A1") ));

		ShapesPtr pShapes = pSheet->Shapes;
		LinesPtr pLines = pSheet->Lines();


		int numberOfAtomFunction = 0;
		int numberOfTheorem = 0;
		int numberOfSet = 0;
		vector <RECT *> rects;
		for( size_t i = 0; i < all_formulas.size(); i++)
		{
			int count = i;
			int row = 0;
			Formula * icurr = all_formulas.at(i);
			TCHAR a = icurr->getTip();
			if( a == TCHAR('A'))
			{
				row = 0;
				count = numberOfAtomFunction;
				numberOfAtomFunction++;
			}
			else
			{
				row = numberOfTheorem/10;
				count = numberOfTheorem - row * 10;
				numberOfTheorem++;
				row++;
			}
			_variant_t index = i;
//			int row = i/10;
			int numberInRow = count;
			int width = 100;
			int height = 100;
			int x = 20 + (width + 20) * numberInRow;
			int y = 20 + (20 + height)* row;
			RECT * rect = new RECT();
			rects.push_back(rect);
			rect->left = x;
			rect->top = y;
			rect->right = x + width;
			rect->bottom = y + height;
			ShapePtr pShape = pShapes->AddTextbox(Office::msoTextOrientationHorizontal, x , y , width, height); 
			ShapePtr pShape1(pShape);
//			pShape1->PutShapeStyle(Office::msoShapeStylePreset25);
			pShape1->PutShapeStyle(Office::msoShapeStylePreset1);
			if( a == TCHAR('A'))
			{
				SetDashLineOfBox(pShape, 1);
			}
			else if (a == TCHAR('T'))
			{
				SetDashLineOfBox(pShape, 3);
			}
			else
				SetDashLineOfBox(pShape, 2);





			tstring str_number;
			tstring res, res_formula;
			res.clear();
			res_formula.clear();
			str_number = to_tstring((long long)(i + 1));
			res.clear();
			if (icurr->getIstinost() == 'v') 
				res = _T("выполнима");
			if (icurr->getIstinost() == 'i') 
				res = _T("истина");
			if (icurr->getIstinost() == 'l') 
				res = _T("ложь"); 
			if(!res.empty())
			{
			}
			res.clear();
			res_formula = *(icurr->getDobavka());
			res_formula += _T(" [ ");
			if(!res.empty())
			{
				pShape1->PutAlternativeText(_bstr_t(res_formula.data()));

				SetTextInBox(pShape, res_formula);

			}

			proccessOneDetail(&all_formulas, &res_formula, i+1, i);
			res.clear();
			res = _T(" ");
			vector <tstring *> * svo_per = icurr->getSvo_per();
			for (size_t j = 0; j < svo_per->size(); j++)
				res += *svo_per->at(j) + _T(" ");
			if(!res.empty())
			{
			}
 
			res_formula += _T(" ]");
			pShape1->PutAlternativeText(_bstr_t(res_formula.data()));
			SetTextInBox(pShape, res_formula);
			if( i > 0)
			{
				RECT * rectBegin = rects.at(i-1);
				RECT * rectFinish = rects.at(i);
				ArrowedLine(pShapes, rectBegin, rectFinish);
			}

		}
		for( size_t i = 0; i < rects.size(); i++)
			delete rects.at(i);

		pBook->Saved[0] = VARIANT_TRUE;
		// Запись книги в файл Excel
		_variant_t vname, vnull, vformat, vamode, vconflict;
		// Задание имени файла Excel
		vname.SetString("C:\\test2.xls");
		pBook->SaveAs(vname,xlWorkbookNormal,vnull,vnull,vnull,vnull,xlNoChange,xlLocalSessionChanges);
		// Закрытие книги
		pBook->Close( VARIANT_FALSE );
		// Выход из Excel
		pXL->Quit();
		// Закрытие COM 
		//CoUninitialize(); 

	}
	catch (_com_error& er)
	{
		tstring err_str;
		err_str = _T("_com_error:\nError       :");
		err_str += er.Error();
		err_str += _T("\nErrorMessage: ");
		err_str += (LPCTSTR)_bstr_t(er.ErrorMessage());
		::MessageBox(NULL, (LPCTSTR)err_str.data(), _T("Error"), MB_SETFOREGROUND | MB_OK);
	}
	catch(...)
	{
	}

#endif
	// TODO: добавьте свой код обработчика уведомлений
//	CDialogEx::OnOK();
//	cad->ShowWindow(SW_SHOW);
//	cad->DoModal();

}


void CSemanticsDlg::OnBnClickedShowallformulas3()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CSemanticsDlg::OnBnClickedAddatomformula()
{
	CAtomFormulaDialog * cad = new CAtomFormulaDialog(this);//	cad->SetStrings( _T("a1") , _T("A") );
	if(cad->DoModal() == IDOK)
	{
		Formula * formula1 = new Formula;
		formula1->setAtomFormula(&all_formulas, cad->tbuf1, cad->tbuf2);
//		all_formulas.push_back(formula1);
	}
	delete cad;
	// TODO: добавьте свой код обработчика уведомлений
}


CSemanticsDlg::~CSemanticsDlg()
{
	for ( size_t i = 0; i < all_formulas.size(); i++)
		delete all_formulas.at(i);
}

void CSemanticsDlg::OnBnClickedBuildformula1()
{
	if(all_formulas.size() > 1)
	{
		Formula * formula1 = new Formula;
		all_formulas.push_back(formula1);
#ifdef OLD_STYLE
		formula1->joinFormula(&all_formulas, TCHAR('1'));
#else
		formula1->joinFormula(&all_formulas, AND_OPERATION);
#endif
	}
//	  objedinjem('1');   // & - 1
	// TODO: добавьте свой код обработчика уведомлений
}


void CSemanticsDlg::OnBnClickedBuildformula2()
{
	if(all_formulas.size() > 1)
	{
		Formula * formula1 = new Formula;
		all_formulas.push_back(formula1);
#ifdef OLD_STYLE
		formula1->joinFormula(&all_formulas, TCHAR('2'));
#else
		formula1->joinFormula(&all_formulas, OR_OPERATION);
#endif
	}
//	objedinjem('2');    // v -2
	// TODO: добавьте свой код обработчика уведомлений
}


void CSemanticsDlg::OnBnClickedBuildformula3()
{
	OperationDlg operationDlg;
	operationDlg.SetOperation(OPERATION_NOT);
	operationDlg.setFormulas(&all_formulas);
	
	if(operationDlg.DoModal() == IDOK)
	{
	}

	// TODO: добавьте свой код обработчика уведомлений
}


void CSemanticsDlg::OnBnClickedBuildformula4()
{
	OperationDlg operationDlg;
	operationDlg.SetOperation(OPERATION_QWANTOR_ONE);
	operationDlg.setFormulas(&all_formulas);
	
	if(operationDlg.DoModal() == IDOK)
	{
	}
	// TODO: добавьте свой код обработчика уведомлений
}


void CSemanticsDlg::OnBnClickedBuildformula5()
{
	OperationDlg operationDlg;
	operationDlg.SetOperation(OPERATION_QWANTOR_TWO);
	operationDlg.setFormulas(&all_formulas);
	
	if(operationDlg.DoModal() == IDOK)
	{
	}
	// TODO: добавьте свой код обработчика уведомлений
}


void CSemanticsDlg::OnBnClickedShowallformulas()
{
	SummaryDialog sd;
	sd.setFormulas(&all_formulas);
	sd.DoModal();
	// TODO: добавьте свой код обработчика уведомлений
}