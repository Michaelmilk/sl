//#include"stdafx.h"
#ifndef COMMON_MODULE_H
#define COMMON_MODULE_H

//#include "MonitorDoc.h"

//���õ�ͼ�����б���
void SetMapTreeListItem(bool configTag, int& treeItemId, CString treeNodePath[], CString mapPath,
	CTreeCtrl& mapTreeLst, TV_INSERTSTRUCT& treeCtlItemInfo, HTREEITEM treeCtlRoot);	

//��ʼ����ͼ�б����ؼ�
void InitMapTreeList(bool configTag, int& treeItemId, CString treeNodePath[],
	CTreeCtrl& mapTreeLst, TV_INSERTSTRUCT& treeCtlItemInfo, HTREEITEM& treeCtlRoot);

//��ʾͼ��,������Ҫ��ʾm_gwList��COBArray�����е�����ͼ��
void DisplayIcon(CBitmap& iconBmp, CDC* pCDC, CObArray& arrayList);

//��ʾ��ǰ��Ҫ��ʾ�ĵ�ͼ
void DisplayCurMap(HWND wnd, CDC* pCDC, CString curPicPath, CRect& mapRect);

//���CObject����
void ClearList(CObArray& list);
#endif