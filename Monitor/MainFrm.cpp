
// MainFrm.cpp : CMainFrame 类的实现
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

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO:  在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式;
	cs.x = 225;
	cs.y = 10;//修改默认窗口的位置
	////cs.style &= ~WS_THICKFRAME;   //don 't   let   user   resize
	////cs.style = WS_OVERLAPPEDWINDOW;

	cs.style &= ~FWS_ADDTOTITLE;
	cs.lpszName = _T("监控端");
	return TRUE;
}

// CMainFrame 诊断

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


// CMainFrame 消息处理程序



void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

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
//	// TODO:  在此处添加消息处理程序代码
//}
