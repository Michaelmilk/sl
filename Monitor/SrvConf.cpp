// SrvConf.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "SrvConf.h"
#include "afxdialogex.h"


// CSrvConf �Ի���

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


// CSrvConf ��Ϣ�������


BOOL CSrvConf::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
