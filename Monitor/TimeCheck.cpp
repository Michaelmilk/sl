// TimeCheck.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "TimeCheck.h"
#include "afxdialogex.h"


// CTimeCheck �Ի���

IMPLEMENT_DYNAMIC(CTimeCheck, CDialogEx)

CTimeCheck::CTimeCheck(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTimeCheck::IDD, pParent)
{

}

CTimeCheck::~CTimeCheck()
{
}

void CTimeCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTimeCheck, CDialogEx)
END_MESSAGE_MAP()


// CTimeCheck ��Ϣ�������


BOOL CTimeCheck::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
