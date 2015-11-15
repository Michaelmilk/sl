// PrjConf.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "PrjConf.h"
#include "afxdialogex.h"
#include "CommonModule.h"
#include "MainFrm.h"
#include "SensorIcon.h"
//#include "MonitorDoc.h"

// CPrjConf 对话框
//extern void SetMapTreeListItem(CString &map_path, HTREEITEM &treectl_root);

IMPLEMENT_DYNAMIC(CPrjConf, CDialogEx)

CPrjConf::CPrjConf(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPrjConf::IDD, pParent)
{
	m_iconType = NO_ICON;
}

CPrjConf::~CPrjConf()
{
}

void CPrjConf::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRJ_TREE_MAPLIST, m_prjMapTreeLst);
	DDX_Control(pDX, IDC_PIC_CTRL, m_prjMapPicCtl);
	DDX_Control(pDX, IDC_BTN_ADDSENSOR, m_addSensorIcon);
	DDX_Control(pDX, IDC_BTN_ADDGW, m_addGWIcon);
	DDX_Control(pDX, IDC_COMBO_GWID, m_comboGWId);
	DDX_Control(pDX, IDC_COMBO_AREA, m_comboArea);
	DDX_Control(pDX, IDC_LISTBOX_SENSOR, m_sensorList);
}


BEGIN_MESSAGE_MAP(CPrjConf, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_PRJ_TREE_MAPLIST, &CPrjConf::OnNMClickPrjTreeMaplist)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_ADDGW, &CPrjConf::OnBnClickedBtnAddGW)
	ON_BN_CLICKED(IDC_BTN_ADDSENSOR, &CPrjConf::OnBnClickedBtnAddSensor)
	ON_CBN_SELCHANGE(IDC_COMBO_GWID, &CPrjConf::OnCbnSelchangeComboGwId)
	ON_BN_CLICKED(ID_BTN_PRJLOAD, &CPrjConf::OnBnClickedBtnPrjLoad)
	ON_BN_CLICKED(IDC_BTN_PRJSAVE, &CPrjConf::OnBnClickedBtnPrjSave)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CPrjConf::OnBnClickedOk)
END_MESSAGE_MAP()


// CPrjConf 消息处理程序


BOOL CPrjConf::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_comboGWId.AddString(_T("2222"));
	m_sensorList.AddString(_T("7777"));
	//获得文档指针
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pDoc = (CMonitorDoc*)pFrame->GetActiveDocument();
	ASSERT_VALID(pDoc);

	m_cursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);//设置光标形状为十字形

	m_prjMapPicCtl.GetWindowRect(&m_mapRect);//获取图片控件的位置信息,相对于屏幕坐标而言的，它的左上角坐标就是窗口在屏幕上的左上角坐标，它的大小就是整个窗口的大小
	ScreenToClient(&m_mapRect);//把屏幕上指定点的屏幕坐标转换成客户区域坐标

	GdiplusStartup(&m_pPrjGdiToken, &m_prjGdiplusStartupInput, NULL);//装载gdiplus库
	InitMapTreeList(TRUE, m_prjTreeItemId, m_prjTreeNodePath, m_prjMapTreeLst, m_prjTreeCtlItemInfo, m_prjTreeCtlRoot);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CPrjConf::OnNMClickPrjTreeMaplist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	m_comboArea.ResetContent();
	CPoint pt = GetCurrentMessage()->pt;
	m_prjMapTreeLst.ScreenToClient(&pt);  //将鼠标的屏幕坐标，转换成树形控件的客户区坐标
	UINT uFlags = 0;
	CFileFind picFileFind;//寻找指定节点下的图片路径
	CString picName;//用于保存指定节点下的图片名称
	CString picPath;//用于保存指定节点下的图片路径
	CString fileName;//用于保存子区域的名称
	HTREEITEM hItem = m_prjMapTreeLst.HitTest(pt, &uFlags);//然后做点击测试 
	m_prjMapPicPath = "";//暂时清空图片路径
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))//如果点击的坐标是在节点位置
	{
		m_prjMapTreeLst.SelectItem(hItem);
		int nDat = m_prjMapTreeLst.GetItemData(hItem);//获取节点的编号
		CString treeItemPath = m_prjTreeNodePath[nDat];//保存图片路径
		//m_curTreeItemPath = treeItemPath;//保存当前节点路径
		treeItemPath += "\\*.*";

		BOOL flag = picFileFind.FindFile(treeItemPath);//开始遍历temp文件夹		
		while (flag)//如果map文件夹下有文件
		{
			flag = picFileFind.FindNextFile();//指向下个文件
			if (picFileFind.IsDots())
			{
				//每个文件夹都有下面两个特殊子文件夹:
				//(1) .   表示本文件夹自己
				//(2) ..  表示本文件夹的父文件夹是当前目录或者是父目录
				continue;
			}
			else
			{
				if (!picFileFind.IsDirectory())//当前文件类型不是文件夹，也就是图片
				{
					// gjx-130921 entry041-003A up
					picPath = picFileFind.GetFilePath();//获取文件路径
					picName = picFileFind.GetFileName();//获取文件名称
					int index = picName.Find(_T("."));//打到“.”的位置
					CString fileExtension = picName.Right(picName.GetLength() - index - 1);//获取文件扩展名
					if (fileExtension == "bmp" || fileExtension == "jpg" || fileExtension == "JPEG" || fileExtension == "jpeg")
						m_prjMapPicPath = picPath;//保存图片路径
				}
				else//当前文件类型如果是文件夹，那么将文件夹的名称添加到子区域的组合框中
				{
					fileName = picFileFind.GetFileName();//获取文件名称
					m_comboArea.AddString(fileName);
				}
			}
		}
		picFileFind.Close();
	}

	this->InvalidateRect(&m_mapRect, FALSE);		//刷新指定区域
}

//void CPrjConf::DisplayGWIcon()
//{
//	CDC* pPicCtlDC = this->GetDC();//m_prjMapPicCtl.GetDC();
//	CDC compatibleIconDC;
//	compatibleIconDC.CreateCompatibleDC(pPicCtlDC);
//	CBitmap GWBmp;
//	GWBmp.LoadBitmap(IDB_GWBMP);
//	CBitmap *pOldBmp = compatibleIconDC.SelectObject(&GWBmp);
//
//	//双缓存机制会把原来的背景地图覆盖
//	/*CDC memDC;
//	memDC.CreateCompatibleDC(pPicCtlDC);
//	CBitmap memBmp;
//	memBmp.CreateCompatibleBitmap(pPicCtlDC, m_mapRect.right - m_mapRect.left, m_mapRect.bottom - m_mapRect.top);
//	CBitmap* pOldMemBmp = memDC.SelectObject(&memBmp);*/
//
//	for (int i = 0; i < pDoc->m_gwList.GetSize(); i++)
//	{
//		CSensorIcon* pGWIcon = (CSensorIcon*)(pDoc->m_gwList.GetAt(i));
//		//ScreenToClient(&psensorIcon->m_locationArea);
//		pPicCtlDC->BitBlt(pGWIcon->m_locationArea.left, pGWIcon->m_locationArea.top, pGWIcon->m_locationArea.Width(),
//			pGWIcon->m_locationArea.Height(), &compatibleIconDC, 0, 0, SRCCOPY);
//	}
//
//	//pPicCtlDC->StretchBlt(0, 0, m_mapRect.Width(), m_mapRect.Height(), &memDC, 0, 0, m_mapRect.Width(), m_mapRect.Height(), SRCCOPY);
//	//memDC.SelectObject(pOldMemBmp);
//	compatibleIconDC.SelectObject(pOldBmp);
//	//memDC.DeleteDC();
//	compatibleIconDC.DeleteDC();
//	GWBmp.DeleteObject();
//	//memBmp.DeleteObject();
//}
//
//void CPrjConf::DisplaySensorIcon()
//{
//	CDC* pPicCtlDC = this->GetDC();
//	CDC compatibleIconDC;
//	compatibleIconDC.CreateCompatibleDC(pPicCtlDC);
//	CBitmap sensorBmp;
//	sensorBmp.LoadBitmap(IDB_SENSORBMP);
//	CBitmap *pOldBmp = compatibleIconDC.SelectObject(&sensorBmp);
//
//	for (int i = 0; i < pDoc->m_sensorList.GetSize(); i++)
//	{
//		CSensorIcon* pSensorIcon = (CSensorIcon*)(pDoc->m_sensorList.GetAt(i));
//		//ScreenToClient(&psensorIcon->m_locationArea);
//		pPicCtlDC->BitBlt(pSensorIcon->m_locationArea.left, pSensorIcon->m_locationArea.top, pSensorIcon->m_locationArea.Width(),
//			pSensorIcon->m_locationArea.Height(), &compatibleIconDC, 0, 0, SRCCOPY);
//	}
//
//	compatibleIconDC.SelectObject(pOldBmp);
//	compatibleIconDC.DeleteDC();
//	sensorBmp.DeleteObject();
//}
//
//void CPrjConf::DisplayCurMap()
//{
//	if (!m_prjMapPicPath.IsEmpty())//当前地图路径非空，表明用户点击的节点路径下存有图片
//	{
//		BSTR str = m_prjMapPicPath.AllocSysString();//分配字符串空间
//		Image image(str);
//		CDC* hdc = GetDC();
//		Graphics imgraphics(hdc->m_hDC);
//		//5个参数分别表示：(1)图片路径；(2)起点横坐标；(3)起点纵坐标；(4)宽度；(5)高度
//		imgraphics.DrawImage(&image, m_mapRect.left, m_mapRect.top, m_mapRect.right - m_mapRect.left, m_mapRect.bottom - m_mapRect.top);
//		SysFreeString(str);
//		ReleaseDC(hdc);
//
//		DisplayGWIcon();
//		DisplaySensorIcon();
//	}
//}

void CPrjConf::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CDC* pCDC = GetDC();
	DisplayCurMap(this->m_hWnd, pCDC, m_prjMapPicPath, m_mapRect);
	CBitmap iconBmp;
	iconBmp.LoadBitmap(IDB_GWBMP);
	DisplayIcon(iconBmp, pCDC, pDoc->m_gwList);
	iconBmp.LoadBitmap(IDB_SENSORBMP);
	DisplayIcon(iconBmp, pCDC, pDoc->m_sensorList);
	ReleaseDC(pCDC);
}


void CPrjConf::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_iconType != NO_ICON)
	{
		if (!m_prjMapPicPath.IsEmpty())
		{
			int gwPos = m_comboGWId.GetCurSel();
			if (-1 == gwPos)
			{
				MessageBox(_T("请先选择网关编号！"), _T("提示"));
				return;
			}
			m_comboGWId.GetLBText(gwPos, m_curGWId);//获取当前网关的编号

			switch (m_iconType)
			{
				case GW_ICON:
				{
					int areaPos = m_comboArea.GetCurSel();
					if (-1 == areaPos)
					{
						MessageBox(_T("请先选择子区域！"), _T("提示"));
						return;
					}
					m_comboArea.GetLBText(areaPos, m_curAreaName);
					break;
				}
				case DHT11_ICON:
				{
					int sensorPos = m_sensorList.GetCurSel();
					if (-1 == sensorPos)
					{
						MessageBox(_T("请先选择传感器编号！"), _T("提示"));
						return;
					}
					m_sensorList.GetText(sensorPos, m_curSensorId);
					break;
				}
			}
			SetCursor(m_cursor);
			this->SetCapture();//改变光标形状
		}
		
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CPrjConf::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	if (m_iconType != NO_ICON)
	{
		if (!m_prjMapPicPath.IsEmpty())
		{
			//如果不在地图区域内点击，弹出提示
			if (!m_mapRect.PtInRect(point))
			{
				MessageBox(_T("请在地图区域内添加图标！"), _T("提示"));
				return;
			}

			m_cursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
			SetCursor(m_cursor);//设置鼠标形状
			ReleaseCapture();//释放鼠标

			CDC* pCurDC = this->GetDC();

			

			CBitmap  bmpGW, bmpSensor;
			bmpGW.LoadBitmap(IDB_GWBMP);//网关图标
			bmpSensor.LoadBitmap(IDB_SENSORBMP);//设备图标

			BITMAP  bitmapGW, bitmapSensor;
			bmpGW.GetBitmap(&bitmapGW);
			bmpSensor.GetBitmap(&bitmapSensor);
			
			//将添加的图标放入串行化队列
			CSensorIcon* p_curIcon = new CSensorIcon();
			switch (m_iconType)
			{
				case	GW_ICON:
				{
					CRect locationRect(point.x - bitmapGW.bmWidth / 2, point.y - bitmapGW.bmHeight / 2, 
						point.x + bitmapGW.bmWidth / 2, point.y + bitmapGW.bmHeight / 2);
					p_curIcon->InitialMember(GW_ICON, locationRect, m_curAreaName, m_curGWId);
					pDoc->m_gwList.Add(p_curIcon);
					break;
				}
				case DHT11_ICON:
				{
					CRect locationRect(point.x - bitmapSensor.bmWidth / 2, point.y - bitmapSensor.bmHeight / 2,
						point.x + bitmapSensor.bmWidth / 2, point.y + bitmapSensor.bmHeight / 2);
					p_curIcon->InitialMember(DHT11_ICON, locationRect, m_curGWId, m_curSensorId);
					pDoc->m_sensorList.Add(p_curIcon);
					break;
				}
			}
			
			
			//If bErase is TRUE, the background is erased when the BeginPaint member function is called; if bErase is FALSE, the background remains unchanged
			this->InvalidateRect(&m_mapRect, FALSE);//客户区域的指定部分将被重绘,
			this->ReleaseDC(pCurDC);
		}

	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CPrjConf::OnBnClickedBtnAddGW()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_iconType != GW_ICON)
	{
		if (m_iconType == DHT11_ICON)
			m_addSensorIcon.SetWindowTextW(_T("添加传感器图标"));
		m_iconType = GW_ICON;
		m_addGWIcon.SetWindowTextW(_T("停止添加网关图标"));
	}
	else 
	{
		m_iconType = NO_ICON;
		m_addGWIcon.SetWindowTextW(_T("添加网关图标"));
	}
}

void CPrjConf::OnBnClickedBtnAddSensor()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_iconType != DHT11_ICON)
	{
		if (m_iconType == GW_ICON)
			m_addGWIcon.SetWindowTextW(_T("添加网关图标"));
		m_iconType = DHT11_ICON;
		m_addSensorIcon.SetWindowTextW(_T("停止添加传感器图标"));
	}
	else
	{
		m_iconType = NO_ICON;
		m_addSensorIcon.SetWindowTextW(_T("添加传感器图标"));
	}
	
}

//网关编号组合框中选择的网关变化的时候，下面的列表框中的传感器的编号也随着变化
void CPrjConf::OnCbnSelchangeComboGwId()
{
	// TODO:  在此添加控件通知处理程序代码

}


void CPrjConf::OnBnClickedBtnPrjLoad()
{
	// TODO:  在此添加控件通知处理程序代码
	pDoc->m_gwList.RemoveAll();//移除现有的网关列表
	pDoc->m_sensorList.RemoveAll();//移除现在的设备列表
	//OFN_NOCHANGEDIR标志非常重要，如果不用此标志每次CFileDialog后会修改当前路径,需要重启本软件才能恢复正常
	CFileDialog dlg(TRUE,_T("prj"),_T(""),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,_T( "项目文件(.prj)|*||" ),NULL);//创建文件读取对话框

	if (IDOK != dlg.DoModal())
	{
		return;
	}
	CString fileName = dlg.GetPathName();//获取文件路径名
	CFile file;
	if (file.Open(fileName, CStdioFile::modeRead))//读文件
	{
		file.SeekToBegin();	//Sets the value of the file pointer to the beginning of the file
		CArchive ar(&file, CArchive::load);//创建carchive，传递用于从文件读取或向文件写入数据的CArchive对象
		pDoc->Serialize(ar);//序列化文件读取
		ar.Abort();
		file.Close();
	}

	this->InvalidateRect(&m_mapRect, FALSE);		//刷新指定区域
}


void CPrjConf::OnBnClickedBtnPrjSave()
{
	// TODO:  在此添加控件通知处理程序代码
	//OFN_NOCHANGEDIR标志非常重要，如果不用此标志每次CFileDialog后会修改当前路径,需要重启本软件才能恢复正常
	CFileDialog dlg(FALSE, _T("prj"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR, _T("项目文件(.prj)|*||"), this);//创建文件保存对话框

	if (IDOK == dlg.DoModal())
	{
		CString pFileName = dlg.GetPathName();//获取文件路径名
		CFile file;
		char buf[4096];
		if (!file.Open(pFileName, CFile::modeCreate | CFile::modeWrite))//生成文件
		{
			MessageBox(_T("配置文件生成失败"), _T("提示"), MB_OK | MB_ICONASTERISK);
			return;
		}
		CArchive ar(&file, CArchive::store, 4096, buf);//创建carchive结构体，传递用于从文件读取或向文件写入数据的CArchive对象
		pDoc->Serialize(ar);//序列化数据存储，保存位置信息

		this->InvalidateRect(&m_mapRect, FALSE);		//刷新指定区域
	}
}


void CPrjConf::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	pDoc->m_gwList.RemoveAll();
	pDoc->m_sensorList.RemoveAll();
	CDialogEx::OnClose();
}


void CPrjConf::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	pDoc->m_gwList.RemoveAll();
	pDoc->m_sensorList.RemoveAll();
	CDialogEx::OnOK();
}
