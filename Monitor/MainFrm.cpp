
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "Monitor.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_GETMINMAXINFO()
//	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ;
	cs.x = 225;
	cs.y = 10;//�޸�Ĭ�ϴ��ڵ�λ��
	////cs.style &= ~WS_THICKFRAME;   //don 't   let   user   resize
	////cs.style = WS_OVERLAPPEDWINDOW;

	cs.style &= ~FWS_ADDTOTITLE;
	cs.lpszName = _T("��ض�");
	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������



void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CFrameWnd::OnGetMinMaxInfo(lpMMI);

	lpMMI->ptMinTrackSize.x = 1015;

	//lpMMI->ptMaxTrackSize.x = cx;

	//lpMMI->ptMaxTrackSize.y = cy;

	lpMMI->ptMinTrackSize.y = 725;
}


//void CMainFrame::OnSize(UINT nType, int cx, int cy)
//{
//	CFrameWnd::OnSize(nType, cx, cy);
//
//	// TODO:  �ڴ˴������Ϣ����������
//}
