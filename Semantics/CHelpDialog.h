#pragma once
#include "afxdialogex.h"
#include "resource.h"

class CHelpDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CHelpDialog)

public:
    CHelpDialog(CWnd* pParent = nullptr); // ����������� �����������
    enum { IDD = IDD_DIALOG4 }; // ���������, ��� ��� ��������� � ��������������� �������

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // ��������� DDX/DDV

    DECLARE_MESSAGE_MAP()
};