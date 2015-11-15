// GWConf.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "GWConf.h"
#include "afxdialogex.h"


// CGWConf 对话框

IMPLEMENT_DYNAMIC(CGWConf, CDialogEx)

CGWConf::CGWConf(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGWConf::IDD, pParent)
{

}

CGWConf::~CGWConf()
{
}

void CGWConf::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGWConf, CDialogEx)
END_MESSAGE_MAP()


// CGWConf 消息处理程序
