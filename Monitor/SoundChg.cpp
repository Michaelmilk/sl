// SoundChg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "SoundChg.h"
#include "afxdialogex.h"


// CSoundChg �Ի���

IMPLEMENT_DYNAMIC(CSoundChg, CDialogEx)

CSoundChg::CSoundChg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSoundChg::IDD, pParent)
{

}

CSoundChg::~CSoundChg()
{
}

void CSoundChg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSoundChg, CDialogEx)
END_MESSAGE_MAP()


// CSoundChg ��Ϣ�������
