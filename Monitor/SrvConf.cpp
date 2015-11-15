// SrvConf.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "SrvConf.h"
#include "afxdialogex.h"


// CSrvConf 对话框

IMPLEMENT_DYNAMIC(CSrvConf, CDialogEx)

CSrvConf::CSrvConf(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSrvConf::IDD, pParent)
{

}

CSrvConf::~CSrvConf()
{
}

void CSrvConf::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSrvConf, CDialogEx)
END_MESSAGE_MAP()


// CSrvConf 消息处理程序


BOOL CSrvConf::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
