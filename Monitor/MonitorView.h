
// MonitorView.h : CMonitorView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"


class CMonitorView : public CFormView
{
protected: // �������л�����
	CMonitorView();
	DECLARE_DYNCREATE(CMonitorView)

public:
	enum{ IDD = IDD_MONITOR_FORM };

// ����
public:
	CMonitorDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CMonitorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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
	int m_oldWndCx;				//����֮ǰ�Ĵ��ڳ���
	int m_oldWndCy;				//����֮ǰ�Ĵ��ڿ��

	void InitEventLst();			//��ʼ���¼��б�ؼ�
	//void SetMapTreeListItem(CString mapPath, HTREEITEM treectl_root);		//���õ�ͼ�����б���
	//void InitMapTreeList();		//��ʼ����ͼ�б����ؼ�
	//void DisplayCurMap(CString curMapPath);
	
	CTreeCtrl m_mapTreeLst;			//��ͼ�б����ؼ�
	HTREEITEM m_treeCtlRoot;				//TREEMAP���ڵ�
	TV_INSERTSTRUCT m_treeCtlItemInfo;			//���ؼ�ÿһ�����Ϣ�ṹ��
	int m_treeItemId;					//���οؼ��ڵ������
	CString m_treeNodePath[255];		//�������οؼ��ڵ�����ӦͼƬ��·��
	CString m_curMapPath;			//��ǰ��ʾ�ĵ�ͼͼƬ
	CString m_curPrjPath;			//��ǰ��ʾ�ĵ�ͼ�������ļ�
	CString m_curTreeItemPath;		//��ǰѡ�е����ڵ��Ӧ��ͼƬ���������ļ���·��
	CStatic m_mapPicCtl;			//ͼƬ�ؼ������ı���
	CRect m_mapRect;				//��ʾ��ͼ�ľ�������
	CMonitorDoc* pDoc;			//�ĵ�ָ��
	GdiplusStartupInput m_gdiplusStartupInput;	//ʹ��gdiplus����Ҫ�ı���
	ULONG_PTR m_pGdiToken;			//ʹ��gdiplus����Ҫ�ı���

	afx_msg void OnNMClickMapTreeList(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // MonitorView.cpp �еĵ��԰汾
inline CMonitorDoc* CMonitorView::GetDocument() const
   { return reinterpret_cast<CMonitorDoc*>(m_pDocument); }
#endif

