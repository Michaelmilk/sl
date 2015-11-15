#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "SensorIcon.h"
#include "MonitorDoc.h"
// CPrjConf 对话框
////图标的类型，如果需要添加图标，增加变量即可
//enum IconType{NO_ICON, GW_ICON, DHT11_ICON };

class CPrjConf : public CDialogEx
{
	DECLARE_DYNAMIC(CPrjConf)

public:
	CPrjConf(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPrjConf();

// 对话框数据
	enum { IDD = IDD_PRJCONF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//void DisplayCurMap();	//显示当前选中的树节点对应的地图
	//void DisplayGWIcon();					//显示当前选中的树节点对应的地图上的网关图标
	//void DisplaySensorIcon();				//显示当前选中的树节点对应的地图上的传感器图标


	virtual BOOL OnInitDialog();
	CTreeCtrl m_prjMapTreeLst;
	HTREEITEM m_prjTreeCtlRoot;					//TREEMAP根节点
	TV_INSERTSTRUCT m_prjTreeCtlItemInfo;			//树控件每一项的信息结构体
	int m_prjTreeItemId;							//树形控件节点项序号
	CString m_prjTreeNodePath[255];					//保存树形控件节点所对应图片的路径
	GdiplusStartupInput m_prjGdiplusStartupInput;	//使用gdiplus库需要的变量
	ULONG_PTR m_pPrjGdiToken;						//使用gdiplus库需要的变量
	CString m_prjMapPicPath;						//点击树节点时，显示的图片的路径
	CStatic m_prjMapPicCtl;						//显示地图的图片控件关联变量
	IconType m_iconType;							//图标类型
	CButton m_addSensorIcon;						//添加传感器图标的按键
	CButton m_addGWIcon;							//添加网关的图标的按键
	CComboBox m_comboGWId;							//选择网关编号的组合框
	CComboBox m_comboArea;							//选择网关子区域的组合框
	CString m_curGWId;							//当前网关编号
	CString m_curAreaName;							//当前子区域名称
	CString m_curSensorId;							//当前网关下的传感器的编号
	CListBox m_sensorList;							//当前网关下的传感器列表
	HCURSOR m_cursor;								//当前鼠标形状
	CRect m_mapRect;								//地图区域的矩形大小
	CMonitorDoc*	pDoc;								//文档的指针

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnAddGW();
	afx_msg void OnBnClickedBtnAddSensor();
	afx_msg void OnNMClickPrjTreeMaplist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPaint();
	afx_msg void OnCbnSelchangeComboGwId();
	
	afx_msg void OnBnClickedBtnPrjLoad();
	afx_msg void OnBnClickedBtnPrjSave();
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
};
