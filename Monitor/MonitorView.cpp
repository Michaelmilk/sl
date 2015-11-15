
// MonitorView.cpp : CMonitorView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Monitor.h"
#endif

#include "MonitorDoc.h"
#include "MonitorView.h"
#include "SrvConf.h"
#include "GWConf.h"
#include "PrjConf.h"
#include "History.h"
#include "SoundChg.h"
#include "TimeCheck.h"
#include "MainFrm.h"
#include "CommonModule.h"

//extern void InitMapTreeList(int& treeItemId, CString treeNodePath[],
//	CTreeCtrl& mapTreeLst, TV_INSERTSTRUCT& treeCtlItemInfo, HTREEITEM& treeCtlRoot);
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMonitorView

IMPLEMENT_DYNCREATE(CMonitorView, CFormView)

BEGIN_MESSAGE_MAP(CMonitorView, CFormView)
	ON_WM_SIZE()
	ON_COMMAND(ID_MENU_SRVCONF, &CMonitorView::OnMenuSrvconf)
	ON_COMMAND(ID_MENU_GWCONF, &CMonitorView::OnMenuGwconf)
	ON_COMMAND(ID_MENU_PRJCONF, &CMonitorView::OnMenuPrjconf)
	ON_COMMAND(ID_MENU_TMCHK, &CMonitorView::OnMenuTmchk)
	ON_COMMAND(ID_MENU_SOUND, &CMonitorView::OnMenuSound)
	ON_COMMAND(ID_MENU_HISTORY, &CMonitorView::OnMenuHistory)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ADDR, &CMonitorView::OnNMClickMapTreeList)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CMonitorView 构造/析构

CMonitorView::CMonitorView()
	: CFormView(CMonitorView::IDD)
{
	// TODO:  在此处添加构造代码
	m_curMapPath = "";
	m_curPrjPath = "";
}

CMonitorView::~CMonitorView()
{
	GdiplusShutdown(m_pGdiToken);//卸载gdiplus库
}

void CMonitorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTCTRL, m_eventLst);
	DDX_Control(pDX, IDC_TREE_ADDR, m_mapTreeLst);
	DDX_Control(pDX, IDC_PIC_MAP, m_mapPicCtl);
}

BOOL CMonitorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CMonitorView::InitEventLst()
{
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_eventLst.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_eventLst.SetExtendedStyle(m_eventLst.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加6列   
	m_eventLst.InsertColumn(0, _T("时间"), LVCFMT_CENTER, rect.Width() / 10, 0);
	m_eventLst.InsertColumn(1, _T("网关ID"), LVCFMT_CENTER, rect.Width() / 15, 1);
	m_eventLst.InsertColumn(2, _T("设备ID"), LVCFMT_CENTER, rect.Width() / 15, 2);
	m_eventLst.InsertColumn(2, _T("设备信息"), LVCFMT_CENTER, rect.Width() / 3, 3);
	m_eventLst.InsertColumn(2, _T("事件信息"), LVCFMT_CENTER, rect.Width() / 3, 4);
	m_eventLst.InsertColumn(2, _T("事件类型"), LVCFMT_CENTER, rect.Width() / 10, 5);
}

//void CMonitorView::SetMapTreeListItem(CString mapPath, HTREEITEM treeCtlRoot)
//{
//	CFileFind fileFind;	//文件查找结构
//	//CString filepath(map_path);//map文件夹路径名
//	CString fileName;//保存文件名
//	CString filePath;//保存文件路径
//
//	m_treeCtlItemInfo.hParent = treeCtlRoot;//设定父节点
//	m_treeCtlItemInfo.item.iImage = 0;//当项是在非选择状态中时，是树形控件的图像列表的索引
//	m_treeCtlItemInfo.item.iSelectedImage = 0;//当项被选择时，是树形控件图像列表的索引。
//
//	BOOL flag = fileFind.FindFile(mapPath);//开始遍历map文件夹
//	while (flag)//如果map文件夹下有文件
//	{
//		flag = fileFind.FindNextFile();//指向下个文件
//		if (fileFind.IsDots())
//		{
//			//每个文件夹都有下面两个特殊子文件夹:
//			//(1) .   表示本文件夹自己；//(2) ..  表示本文件夹的父文件夹是当前目录或者是父目录	
//			continue;
//		}
//		else	
//		{
//			if (fileFind.IsDirectory())//如果当前文件类型是文件夹
//			{
//				filePath = fileFind.GetFilePath();//获取文件路径
//				fileName = fileFind.GetFileName();//获取文件名
//				if (fileName.GetLength() > 50)
//				{
//					MessageBox(_T("子文件夹名称过长，请重新修改子文件名称!"), _T("提示"), MB_ICONASTERISK | MB_OK);
//					return ;
//				}
//				// gjx-130916 entry001-012B up
//				m_treeCtlItemInfo.item.pszText = (LPWSTR)(LPCWSTR)(fileName);//字符串filename赋值给pszText，用于显示
//				//nodeName[num] = treectl_item_info.item.pszText;//保存节点名称
//				m_treeCtlItemInfo.hParent = treeCtlRoot;//父节点
//				m_treeCtlItemInfo.item.lParam = m_treeItemId;//节点编号
//				m_treeNodePath[m_treeItemId] = fileFind.GetFilePath();//存储文件路径
//				m_treeCtlRoot = m_mapTreeLst.InsertItem(&m_treeCtlItemInfo);//插入节点
//				m_treeItemId++;//节点编号+1
//				//递归查找文件，从而形成树型结构图
//				SetMapTreeListItem((fileFind.GetFilePath() + _T("\\*.*")), m_treeCtlRoot);
//				//	free(tvinsert.item.pszText);
//			}
//			else
//			{
//				////说明遍历到子非文件夹类型的文件
//
//				//filePath = file_find.GetFilePath();//获取文件路径
//				//fileName = file_find.GetFileName();//获取文件名称
//				//int index = fileName.Find(_T("."));//打到“.”的位置
//				//CString picex = fileName.Right(fileName.GetLength() - index - 1);//获取文件扩展名
//				//char *pa = (char*)((LPCTSTR)picex);
//
//				//if (strcmp(pa, "prj") == 0)//如果有文件的扩展名为“prj”,则读取配置文件中的内容，将ASD数据保存到数组AsdToPath
//				//{
//				//	CFileFind mapfind;	//文件查找结构
//				//	CString mapname;
//				//	CString mappath;
//				//	int pos = filePath.Find(fileName);
//				//	CString mappos = filePath.Mid(0, pos);
//				//	mappos += "\*.*";
//				//	BOOL mapflag = mapfind.FindFile(mappos);//开始遍历map文件夹
//				//	while (mapflag)//如果map文件夹下有文件,此处是为了查找与.prj文件同目录下的地图文件
//				//	{
//				//		mapflag = mapfind.FindNextFile();//指向下个文件
//				//		if (mapfind.IsDots())
//				//		{
//				//			//每个文件夹都有下面两个特殊子文件夹:
//				//			//(1) .   表示本文件夹自己；//(2) ..  表示本文件夹的父文件夹是当前目录或者是父目录	
//				//			continue;
//				//		}
//				//		else	
//				//		{
//				//			if (!mapfind.IsDirectory())//如果当前文件类型不是文件夹	
//				//			{
//				//				mappath = mapfind.GetFilePath();//获取文件路径
//				//				mapname = mapfind.GetFileName();//获取文件名称
//				//				int index = mapname.Find(_T("."));//打到“.”的位置
//				//				CString picex = mapname.Right(mapname.GetLength() - index - 1);//获取文件扩展名
//				//				char *pa = (char*)((LPCTSTR)picex);
//				//				if (strcmp(pa, "bmp") == 0 || strcmp(pa, "jpg") == 0 || strcmp(pa, "JPG") == 0 || strcmp(pa, "JPEG") == 0 || strcmp(pa, "jpeg") == 0)
//				//				{
//				//					srcMapPath = mappath;//保存对应图片的路径
//				//					break;
//				//				}
//				//			}
//				//		}
//				//	}
//				//	// gjx-130916 entry001-014B up
//				//	mapfind.Close();
//					
//					//GetDlgItem(IDC_MAP)->GetWindowRect(&rc);//获取地图控件的位置信息,相对于屏幕坐标而言的，它的左上角坐标就是窗口在屏幕上的左上角坐标，它的大小就是整个窗口的大小
//					//ScreenToClient(&rc);//把屏幕上指定点的屏幕坐标转换成客户区域坐标
//
//					//CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();//获取文档指针
//					//CMonitorDoc *pDoc = (CMonitorDoc*)pFrame->GetActiveDocument();
//					//ASSERT_VALID(pDoc);
//
//					//CFile file;
//					//if (file.Open(filePath, CStdioFile::modeRead))//读文件
//					//	// gjx-130916 entry001-018A down
//					//	// gjx-130916 entry001-018B down
//					//{
//					//	// gjx-130916 entry001-018A up
//					//	file.SeekToBegin();	//Sets the value of the file pointer to the beginning of the file
//					//	CArchive ar(&file, CArchive::load);//创建carchive，传递用于从文件读取或向文件写入数据的CArchive对象
//					//	//序列化文件读取
//					//	pDoc->Serialize(ar);// gjx-130916 entry001-019 down Serialize()
//					//	// gjx-130916 entry001-027 up
//					//	ar.Close();
//					//	file.Close();
//					//}
//					//// gjx-130916 entry001-018B up
//
//					//for (int i = 0; i<pDoc->m_gwlist.GetSize(); i++)//循环图元列表
//					//{
//					//	CMapElement* pMap = (CMapElement*)pDoc->m_gwlist.GetAt(i);//获取网关图标指针
//					//	//设定每个图标的源区域信息，当窗口大小发生变化时需要用到这个值
//					//	pMap->SetSrcRect(rc);// gjx-130916 entry001-028 down SetSrcRect()
//					//	// gjx-130916 entry001-029 up
//					//	//获取网关图标的名称
//					//	CString gwName = pMap->GetName();// gjx-130916 entry001-030 GetName()
//					//	// gjx-130916 entry001-031 up
//					//	char gwArea[50], gwID[10];
//					//	sscanf(gwName, "%[^-]-%s", gwArea, gwID);
//
//					//	GW_STATE gs;
//					//	gs.gwID = gwID;
//					//	gs.gwArea = gwArea;
//					//	gs.gwState = INIT;
//					//	gwStateVect.push_back(gs);
//					//	DebugPrintf("插入GW：%s-%s-%d", gs.gwArea, gs.gwID, gs.gwState);
//					//}
//					//for (i = 0; i<pDoc->m_asdlist.GetSize(); i++)//循环图元列表
//					//{
//					//	//需要获取与配置文件同一路径下的图片路径
//					//	CMapElement* pMap = (CMapElement*)pDoc->m_asdlist.GetAt(i);
//					//	pMap->SetSrcRect(rc);// gjx-130916 entry001-032 down SetSrcRect()
//					//	// gjx-130916 entry001-033 up
//					//	CString asdname = pMap->GetName();// gjx-130916 entry001-034 down GetName()
//					//	// gjx-130916 entry001-035 up
//
//					//	char gw[10], asd[10];
//					//	DebugPrintf("发现ASD：%s", asdname);
//					//	sscanf(asdname, "%[^-]-%s", gw, asd);
//
//					//	ASD_TO_PATH tempASD;
//					//	tempASD.gw = gw;
//					//	tempASD.asd = asd;
//					//	tempASD.prj_path = filePath;
//					//	tempASD.map_path = srcMapPath;
//					//	AsdToPath.push_back(tempASD);
//					//	DebugPrintf("插入ASD：%s-%s-%s", tempASD.gw, tempASD.asd, tempASD.prj_path);
//					//}
//				//}
//			}
//		}
//	}
//	// gjx-130916 entry001-009B up
//	fileFind.Close();
//}

//void CMonitorView::InitMapTreeList()
//{
//	//TV_INSERTSTRUCT treectl_item_info;			//树控件每一项的信息结构体
//	m_treeCtlItemInfo.hParent = NULL;			//父节点句柄
//	m_treeCtlItemInfo.hInsertAfter = TVI_LAST;	//在列表的最后插入项
//	m_treeCtlItemInfo.item.mask = TVIF_SELECTEDIMAGE | TVIF_TEXT | LVIF_PARAM;//用来指定TV_ITEM的那些成员变量有效
//	m_treeCtlItemInfo.item.hItem = NULL;
//	m_treeCtlItemInfo.item.state = 0;			//位标记和图像列表索引的设置，指出项的状态
//	m_treeCtlItemInfo.item.stateMask = 0;		//设置state成员的位是否有效
//	m_treeCtlItemInfo.item.cchTextMax = 6;		//pszText成员指定缓冲的大小,以字符为单位
//	m_treeCtlItemInfo.item.iSelectedImage = 1;	//当项被选择时，是树形控件图像列表的索引
//
//	CString cur_path;
//	GetModuleFileName(NULL, cur_path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);//当前应用程序的运行目录
//	//map_file_path.ReleaseBuffer();
//	int pos = cur_path.ReverseFind('\\'); //找到'\'的位置
//	cur_path = cur_path.Left(pos);	//字符串截取，去掉当前路径名最后的一个'\'字符
//
//	CString map_path(cur_path);
//	map_path += _T("\\map");//指定根目录为map文件夹
//
//	//HTREEITEM treectl_root;				//TREEMAP根节点
//	m_treeItemId = 0;
//	//设置树型目录信息
//	SetMapTreeListItem(map_path, m_treeCtlRoot);// gjx-130916 entry001-008 down SetTreeItem()
//}



void CMonitorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	//获取文档指针
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pDoc = (CMonitorDoc*)pFrame->GetActiveDocument();
	ASSERT_VALID(pDoc);

	//获取图片控件的矩形区域
	m_mapPicCtl.GetWindowRect(&m_mapRect);//获取控件的位置信息
	ScreenToClient(m_mapRect);

	InitEventLst();//初始化事件列表
	
	//保存当前的窗口长度和宽度
	CSize sz = GetTotalSize();
	m_oldWndCx = sz.cx;
	m_oldWndCy = sz.cy;

	//装载gdiplus库
	GdiplusStartup(&m_pGdiToken, &m_gdiplusStartupInput, NULL);
	InitMapTreeList(FALSE, m_treeItemId, m_treeNodePath, m_mapTreeLst, m_treeCtlItemInfo, m_treeCtlRoot);
}


// CMonitorView 诊断

#ifdef _DEBUG
void CMonitorView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMonitorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMonitorDoc* CMonitorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMonitorDoc)));
	return (CMonitorDoc*)m_pDocument;
}
#endif //_DEBUG


// CMonitorView 消息处理程序



void CMonitorView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (cx < 800 || cy < 600){
		cx = 800;
		cy = 600;
	}

	float dx_percent = (m_oldWndCx == 0) ? 1 : (float)((float)cx / (float)m_oldWndCx);
	float dy_percent = (m_oldWndCy == 0) ? 1 : (float)((float)cy / (float)m_oldWndCy);

	if (m_oldWndCx){
		CRect WndRect;
		CWnd * pWnd = GetWindow(GW_CHILD);;
		while (pWnd){
			pWnd->GetWindowRect(&WndRect);
			ScreenToClient(&WndRect);
			WndRect.left = (int)(WndRect.left*dx_percent);
			WndRect.right = (int)(WndRect.right*dx_percent);
			WndRect.top = (int)(WndRect.top*dy_percent);
			WndRect.bottom = (int)(WndRect.bottom*dy_percent);
			pWnd->MoveWindow(&WndRect);
			pWnd = pWnd->GetWindow(GW_HWNDNEXT);
		}
	}

	m_oldWndCx = cx;
	m_oldWndCy = cy;
}


void CMonitorView::OnMenuSrvconf()
{
	// TODO:  在此添加命令处理程序代码
	CSrvConf srv_conf;
	srv_conf.DoModal();
}


void CMonitorView::OnMenuGwconf()
{
	// TODO:  在此添加命令处理程序代码
	CGWConf gw_conf;
	gw_conf.DoModal();
}


void CMonitorView::OnMenuPrjconf()
{
	// TODO:  在此添加命令处理程序代码
	CPrjConf prj_conf;
	prj_conf.DoModal();
}


void CMonitorView::OnMenuTmchk()
{
	// TODO:  在此添加命令处理程序代码
	CTimeCheck time_chk;
	time_chk.DoModal();
}


void CMonitorView::OnMenuSound()
{
	// TODO:  在此添加命令处理程序代码
	CSoundChg sound_chg;
	sound_chg.DoModal();
}


void CMonitorView::OnMenuHistory()
{
	// TODO:  在此添加命令处理程序代码
	CHistory ht;
	ht.DoModal();
}


void CMonitorView::OnNMClickMapTreeList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	CPoint pt = GetCurrentMessage()->pt;
	m_mapTreeLst.ScreenToClient(&pt);  //将鼠标的屏幕坐标，转换成树形控件的客户区坐标
	UINT uFlags = 0;
	CFileFind picFileFind;//寻找指定节点下的图片路径
	CString picName;//用于保存指定节点下的图片名称
	CString picPath;//用于保存指定节点下的图片路径
	HTREEITEM hItem = m_mapTreeLst.HitTest(pt, &uFlags);//然后做点击测试 
	//m_curMapPath = "";//暂时清空图片路径
	//m_curPrjPath = "";//暂时清空配置文件路径
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))//如果点击的坐标是在节点位置
	{
		m_mapTreeLst.SelectItem(hItem);
		int nDat = m_mapTreeLst.GetItemData(hItem);//获取节点的编号
		CString treeItemPath = m_treeNodePath[nDat];//保存图片路径
		m_curTreeItemPath = treeItemPath;//保存当前节点路径
		treeItemPath += "\\*.*";

		m_curMapPath = "";//先清空数据，这样当用户点击到没有保存图片的文件夹时，中间区域显示空白
		m_curPrjPath = "";
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
				if (!picFileFind.IsDirectory())//当前文件类型不是文件夹，进行过滤操作
				{
					picPath = picFileFind.GetFilePath();//获取文件路径
					picName = picFileFind.GetFileName();//获取文件名称
					int pos = picName.Find(_T("."));//打到“.”的位置
					CString fileExtension = picName.Right(picName.GetLength() - pos - 1);//获取文件扩展名
					if (fileExtension == "bmp" || fileExtension == "jpg" || fileExtension == "JPEG" || fileExtension == "jpeg")
						m_curMapPath = picPath;//保存图片路径

					if (fileExtension == "prj")//如果有文件的扩展名为“prj”
					{
						m_curPrjPath = picPath;//保存配置文件路径
						CFile file;
						BOOL fileret = file.Open(m_curPrjPath, CStdioFile::modeRead);//读取配置文件的内容
						if (fileret)//读文件
						{
							file.SeekToBegin();	//设置文件指针到文件的开始处
							CArchive ar(&file, CArchive::load);
							pDoc->Serialize(ar);//序列化文件读取
							ar.Abort();
							file.Close();
						}
					}
				}
			}
		}
		picFileFind.Close();
	}
	
	this->InvalidateRect(&m_mapRect, FALSE);		//刷新指定区域
}

//void CMonitorView::DisplayCurMap(CString curMapPath)
//{
//	if (!curMapPath.IsEmpty())//当前地图路径非空，表明用户点击的节点路径下存有图片
//	{
//		CRect pic;
//		m_mapPicCtl.GetWindowRect(&pic);//获取IDC_MAP控件窗口坐标
//		ScreenToClient(&pic);//将窗口坐标换为客户区坐标
//
//		BSTR str = curMapPath.AllocSysString();//分配字符串空间
//		Image image(str);
//		CDC* hdc = GetDC();
//		Graphics imgraphics(hdc->m_hDC);
//		//5个参数分别表示：(1)图片路径；(2)起点横坐标；(3)起点纵坐标；(4)宽度；(5)高度
//		imgraphics.DrawImage(&image, pic.left, pic.top, pic.right - pic.left, pic.bottom - pic.top);
//		SysFreeString(str);
//		ReleaseDC(hdc);
//	}
//}

void CMonitorView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CFormView::OnPaint()
	CDC* pCDC = GetDC();
	DisplayCurMap(this->m_hWnd, pCDC, m_curMapPath, m_mapRect);
	CBitmap iconBmp;
	iconBmp.LoadBitmap(IDB_GWBMP);
	DisplayIcon(iconBmp, pCDC, pDoc->m_gwList);
	iconBmp.LoadBitmap(IDB_SENSORBMP);
	DisplayIcon(iconBmp, pCDC, pDoc->m_sensorList);
	ReleaseDC(pCDC);
}
