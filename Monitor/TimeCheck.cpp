// TimeCheck.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "TimeCheck.h"
#include "afxdialogex.h"


// CTimeCheck 对话框

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


// CTimeCheck 消息处理程序


BOOL CTimeCheck::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
