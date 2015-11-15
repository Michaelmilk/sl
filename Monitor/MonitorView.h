
// MonitorView.h : CMonitorView 类的接口
//

#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"


class CMonitorView : public CFormView
{
protected: // 仅从序列化创建
	CMonitorView();
	DECLARE_DYNCREATE(CMonitorView)

public:
	enum{ IDD = IDD_MONITOR_FORM };

// 特性
public:
	CMonitorDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CMonitorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_eventLst;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMenuSrvconf();
	afx_msg void OnMenuGwconf();
	afx_msg void OnMenuPrjconf();
	afx_msg void OnMenuTmchk();
	afx_msg void OnMenuSound();
	afx_msg void OnMenuHistory();

public:
	int m_oldWndCx;				//保存之前的窗口长度
	int m_oldWndCy;				//保存之前的窗口宽度

	void InitEventLst();			//初始化事件列表控件
	//void SetMapTreeListItem(CString mapPath, HTREEITEM treectl_root);		//设置地图树形列表项
	//void InitMapTreeList();		//初始化地图列表树控件
	//void DisplayCurMap(CString curMapPath);
	
	CTreeCtrl m_mapTreeLst;			//地图列表树控件
	HTREEITEM m_treeCtlRoot;				//TREEMAP根节点
	TV_INSERTSTRUCT m_treeCtlItemInfo;			//树控件每一项的信息结构体
	int m_treeItemId;					//树形控件节点项序号
	CString m_treeNodePath[255];		//保存树形控件节点所对应图片的路径
	CString m_curMapPath;			//当前显示的地图图片
	CString m_curPrjPath;			//当前显示的地图的配置文件
	CString m_curTreeItemPath;		//当前选中的树节点对应的图片或者配置文件的路径
	CStatic m_mapPicCtl;			//图片控件关联的变量
	CRect m_mapRect;				//显示地图的矩形区域
	CMonitorDoc* pDoc;			//文档指针
	GdiplusStartupInput m_gdiplusStartupInput;	//使用gdiplus库需要的变量
	ULONG_PTR m_pGdiToken;			//使用gdiplus库需要的变量

	afx_msg void OnNMClickMapTreeList(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // MonitorView.cpp 中的调试版本
inline CMonitorDoc* CMonitorView::GetDocument() const
   { return reinterpret_cast<CMonitorDoc*>(m_pDocument); }
#endif

