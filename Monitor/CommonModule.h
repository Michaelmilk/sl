//#include"stdafx.h"
#ifndef COMMON_MODULE_H
#define COMMON_MODULE_H

//#include "MonitorDoc.h"

//设置地图树形列表项
void SetMapTreeListItem(bool configTag, int& treeItemId, CString treeNodePath[], CString mapPath,
	CTreeCtrl& mapTreeLst, TV_INSERTSTRUCT& treeCtlItemInfo, HTREEITEM treeCtlRoot);	

//初始化地图列表树控件
void InitMapTreeList(bool configTag, int& treeItemId, CString treeNodePath[],
	CTreeCtrl& mapTreeLst, TV_INSERTSTRUCT& treeCtlItemInfo, HTREEITEM& treeCtlRoot);

//显示图标,这里主要显示m_gwList等COBArray队列中的所有图标
void DisplayIcon(CBitmap& iconBmp, CDC* pCDC, CObArray& arrayList);

//显示当前需要显示的地图
void DisplayCurMap(HWND wnd, CDC* pCDC, CString curPicPath, CRect& mapRect);

//清空CObject队列
void ClearList(CObArray& list);
#endif