#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "SensorIcon.h"
#include "MonitorDoc.h"
// CPrjConf �Ի���
////ͼ������ͣ������Ҫ���ͼ�꣬���ӱ�������
//enum IconType{NO_ICON, GW_ICON, DHT11_ICON };

class CPrjConf : public CDialogEx
{
	DECLARE_DYNAMIC(CPrjConf)

public:
	CPrjConf(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPrjConf();

// �Ի�������
	enum { IDD = IDD_PRJCONF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//void DisplayCurMap();	//��ʾ��ǰѡ�е����ڵ��Ӧ�ĵ�ͼ
	//void DisplayGWIcon();					//��ʾ��ǰѡ�е����ڵ��Ӧ�ĵ�ͼ�ϵ�����ͼ��
	//void DisplaySensorIcon();				//��ʾ��ǰѡ�е����ڵ��Ӧ�ĵ�ͼ�ϵĴ�����ͼ��


	virtual BOOL OnInitDialog();
	CTreeCtrl m_prjMapTreeLst;
	HTREEITEM m_prjTreeCtlRoot;					//TREEMAP���ڵ�
	TV_INSERTSTRUCT m_prjTreeCtlItemInfo;			//���ؼ�ÿһ�����Ϣ�ṹ��
	int m_prjTreeItemId;							//���οؼ��ڵ������
	CString m_prjTreeNodePath[255];					//�������οؼ��ڵ�����ӦͼƬ��·��
	GdiplusStartupInput m_prjGdiplusStartupInput;	//ʹ��gdiplus����Ҫ�ı���
	ULONG_PTR m_pPrjGdiToken;						//ʹ��gdiplus����Ҫ�ı���
	CString m_prjMapPicPath;						//������ڵ�ʱ����ʾ��ͼƬ��·��
	CStatic m_prjMapPicCtl;						//��ʾ��ͼ��ͼƬ�ؼ���������
	IconType m_iconType;							//ͼ������
	CButton m_addSensorIcon;						//��Ӵ�����ͼ��İ���
	CButton m_addGWIcon;							//������ص�ͼ��İ���
	CComboBox m_comboGWId;							//ѡ�����ر�ŵ���Ͽ�
	CComboBox m_comboArea;							//ѡ���������������Ͽ�
	CString m_curGWId;							//��ǰ���ر��
	CString m_curAreaName;							//��ǰ����������
	CString m_curSensorId;							//��ǰ�����µĴ������ı��
	CListBox m_sensorList;							//��ǰ�����µĴ������б�
	HCURSOR m_cursor;								//��ǰ�����״
	CRect m_mapRect;								//��ͼ����ľ��δ�С
	CMonitorDoc*	pDoc;								//�ĵ���ָ��

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
