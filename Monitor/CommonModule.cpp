#include "stdafx.h"
#include "CommonModule.h"
#include "SensorIcon.h"

//设置地图树形列表项
void SetMapTreeListItem(bool configTag, int& treeItemId, CString treeNodePath[], CString mapPath, 
	CTreeCtrl& mapTreeLst, TV_INSERTSTRUCT& treeCtlItemInfo, HTREEITEM treeCtlRoot)		//设置地图树形列表项
{
	CFileFind fileFind;	//文件查找结构
	//CString filepath(map_path);//map文件夹路径名
	CString fileName;//保存文件名
	CString filePath;//保存文件路径

	treeCtlItemInfo.hParent = treeCtlRoot;//设定父节点
	treeCtlItemInfo.item.iImage = 0;//当项是在非选择状态中时，是树形控件的图像列表的索引
	treeCtlItemInfo.item.iSelectedImage = 0;//当项被选择时，是树形控件图像列表的索引。

	BOOL flag = fileFind.FindFile(mapPath);//开始遍历map文件夹
	while (flag)//如果map文件夹下有文件
	{
		flag = fileFind.FindNextFile();//指向下个文件
		if (fileFind.IsDots())
		{
			//每个文件夹都有下面两个特殊子文件夹:
			//(1) .   表示本文件夹自己；//(2) ..  表示本文件夹的父文件夹是当前目录或者是父目录	
			continue;
		}
		else
		{
			if (fileFind.IsDirectory())//如果当前文件类型是文件夹
			{
				filePath = fileFind.GetFilePath();//获取文件路径
				fileName = fileFind.GetFileName();//获取文件名
				if (fileName.GetLength() > 50)
				{
					//MessageBox(_T("子文件夹名称过长，请重新修改子文件名称!"), _T("提示"), MB_ICONASTERISK | MB_OK);
					return;
				}
				treeCtlItemInfo.item.pszText = (LPWSTR)(LPCWSTR)(fileName);//字符串filename赋值给pszText，用于显示
				//nodeName[num] = treectl_item_info.item.pszText;//保存节点名称
				treeCtlItemInfo.hParent = treeCtlRoot;//父节点
				treeCtlItemInfo.item.lParam = treeItemId;//节点编号
				treeNodePath[treeItemId] = fileFind.GetFilePath();//存储文件路径
				HTREEITEM nextTreeCtlRoot = mapTreeLst.InsertItem(&treeCtlItemInfo);//插入节点
				treeItemId++;//节点编号+1
				//递归查找文件，从而形成树型结构图
				SetMapTreeListItem(configTag, treeItemId, treeNodePath, (fileFind.GetFilePath() + _T("\\*.*")), mapTreeLst, treeCtlItemInfo, nextTreeCtlRoot);
				//	free(tvinsert.item.pszText);
			}
			else if (!configTag)
			{
				////说明遍历到子非文件夹类型的文件

				//filePath = file_find.GetFilePath();//获取文件路径
				//fileName = file_find.GetFileName();//获取文件名称
				//int index = fileName.Find(_T("."));//打到“.”的位置
				//CString picex = fileName.Right(fileName.GetLength() - index - 1);//获取文件扩展名
				//char *pa = (char*)((LPCTSTR)picex);

				//if (strcmp(pa, "prj") == 0)//如果有文件的扩展名为“prj”,则读取配置文件中的内容，将ASD数据保存到数组AsdToPath
				//{
				//	CFileFind mapfind;	//文件查找结构
				//	CString mapname;
				//	CString mappath;
				//	int pos = filePath.Find(fileName);
				//	CString mappos = filePath.Mid(0, pos);
				//	mappos += "\*.*";
				//	BOOL mapflag = mapfind.FindFile(mappos);//开始遍历map文件夹
				//	while (mapflag)//如果map文件夹下有文件,此处是为了查找与.prj文件同目录下的地图文件
				//	{
				//		mapflag = mapfind.FindNextFile();//指向下个文件
				//		if (mapfind.IsDots())
				//		{
				//			//每个文件夹都有下面两个特殊子文件夹:
				//			//(1) .   表示本文件夹自己；//(2) ..  表示本文件夹的父文件夹是当前目录或者是父目录	
				//			continue;
				//		}
				//		else	
				//		{
				//			if (!mapfind.IsDirectory())//如果当前文件类型不是文件夹	
				//			{
				//				mappath = mapfind.GetFilePath();//获取文件路径
				//				mapname = mapfind.GetFileName();//获取文件名称
				//				int index = mapname.Find(_T("."));//打到“.”的位置
				//				CString picex = mapname.Right(mapname.GetLength() - index - 1);//获取文件扩展名
				//				char *pa = (char*)((LPCTSTR)picex);
				//				if (strcmp(pa, "bmp") == 0 || strcmp(pa, "jpg") == 0 || strcmp(pa, "JPG") == 0 || strcmp(pa, "JPEG") == 0 || strcmp(pa, "jpeg") == 0)
				//				{
				//					srcMapPath = mappath;//保存对应图片的路径
				//					break;
				//				}
				//			}
				//		}
				//	}
				//	// gjx-130916 entry001-014B up
				//	mapfind.Close();

				//GetDlgItem(IDC_MAP)->GetWindowRect(&rc);//获取地图控件的位置信息,相对于屏幕坐标而言的，它的左上角坐标就是窗口在屏幕上的左上角坐标，它的大小就是整个窗口的大小
				//ScreenToClient(&rc);//把屏幕上指定点的屏幕坐标转换成客户区域坐标

				//CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();//获取文档指针
				//CMonitorDoc *pDoc = (CMonitorDoc*)pFrame->GetActiveDocument();
				//ASSERT_VALID(pDoc);

				//CFile file;
				//if (file.Open(filePath, CStdioFile::modeRead))//读文件
				//	// gjx-130916 entry001-018A down
				//	// gjx-130916 entry001-018B down
				//{
				//	// gjx-130916 entry001-018A up
				//	file.SeekToBegin();	//Sets the value of the file pointer to the beginning of the file
				//	CArchive ar(&file, CArchive::load);//创建carchive，传递用于从文件读取或向文件写入数据的CArchive对象
				//	//序列化文件读取
				//	pDoc->Serialize(ar);// gjx-130916 entry001-019 down Serialize()
				//	// gjx-130916 entry001-027 up
				//	ar.Close();
				//	file.Close();
				//}
				//// gjx-130916 entry001-018B up

				//for (int i = 0; i<pDoc->m_gwlist.GetSize(); i++)//循环图元列表
				//{
				//	CMapElement* pMap = (CMapElement*)pDoc->m_gwlist.GetAt(i);//获取网关图标指针
				//	//设定每个图标的源区域信息，当窗口大小发生变化时需要用到这个值
				//	pMap->SetSrcRect(rc);// gjx-130916 entry001-028 down SetSrcRect()
				//	// gjx-130916 entry001-029 up
				//	//获取网关图标的名称
				//	CString gwName = pMap->GetName();// gjx-130916 entry001-030 GetName()
				//	// gjx-130916 entry001-031 up
				//	char gwArea[50], gwID[10];
				//	sscanf(gwName, "%[^-]-%s", gwArea, gwID);

				//	GW_STATE gs;
				//	gs.gwID = gwID;
				//	gs.gwArea = gwArea;
				//	gs.gwState = INIT;
				//	gwStateVect.push_back(gs);
				//	DebugPrintf("插入GW：%s-%s-%d", gs.gwArea, gs.gwID, gs.gwState);
				//}
				//for (i = 0; i<pDoc->m_asdlist.GetSize(); i++)//循环图元列表
				//{
				//	//需要获取与配置文件同一路径下的图片路径
				//	CMapElement* pMap = (CMapElement*)pDoc->m_asdlist.GetAt(i);
				//	pMap->SetSrcRect(rc);// gjx-130916 entry001-032 down SetSrcRect()
				//	// gjx-130916 entry001-033 up
				//	CString asdname = pMap->GetName();// gjx-130916 entry001-034 down GetName()
				//	// gjx-130916 entry001-035 up

				//	char gw[10], asd[10];
				//	DebugPrintf("发现ASD：%s", asdname);
				//	sscanf(asdname, "%[^-]-%s", gw, asd);

				//	ASD_TO_PATH tempASD;
				//	tempASD.gw = gw;
				//	tempASD.asd = asd;
				//	tempASD.prj_path = filePath;
				//	tempASD.map_path = srcMapPath;
				//	AsdToPath.push_back(tempASD);
				//	DebugPrintf("插入ASD：%s-%s-%s", tempASD.gw, tempASD.asd, tempASD.prj_path);
				//}
				//}
			}
		}
	}
	fileFind.Close();
}

//初始化地图列表树控件
void InitMapTreeList(bool configTag, int& treeItemId, CString treeNodePath[],
	CTreeCtrl& mapTreeLst, TV_INSERTSTRUCT& treeCtlItemInfo, HTREEITEM& treeCtlRoot)		//初始化地图列表树控件
{
	treeCtlItemInfo.hParent = NULL;			//父节点句柄
	treeCtlItemInfo.hInsertAfter = TVI_LAST;	//在列表的最后插入项
	treeCtlItemInfo.item.mask = TVIF_SELECTEDIMAGE | TVIF_TEXT | LVIF_PARAM;//用来指定TV_ITEM的那些成员变量有效
	treeCtlItemInfo.item.hItem = NULL;
	treeCtlItemInfo.item.state = 0;			//位标记和图像列表索引的设置，指出项的状态
	treeCtlItemInfo.item.stateMask = 0;		//设置state成员的位是否有效
	treeCtlItemInfo.item.cchTextMax = 6;		//pszText成员指定缓冲的大小,以字符为单位
	treeCtlItemInfo.item.iSelectedImage = 1;	//当项被选择时，是树形控件图像列表的索引

	CString cur_path;
	GetModuleFileName(NULL, cur_path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);//当前应用程序的运行目录
	//map_file_path.ReleaseBuffer();
	int pos = cur_path.ReverseFind('\\'); //找到'\'的位置
	cur_path = cur_path.Left(pos);	//字符串截取，去掉当前路径名最后的一个'\'字符

	CString map_path(cur_path);
	map_path += _T("\\map");//指定根目录为map文件夹

	//HTREEITEM treectl_root;				//TREEMAP根节点
	treeItemId = 0;
	//设置树型目录信息
	SetMapTreeListItem(configTag, treeItemId, treeNodePath, map_path, mapTreeLst, treeCtlItemInfo, treeCtlRoot);
}

//显示图标,这里主要显示m_gwList等COBArray队列中的所有图标
void DisplayIcon(CBitmap& iconBmp, CDC* pCDC, CObArray& arrayList)
{
	for (int i = 0; i < arrayList.GetSize(); i++)
	{
		CSensorIcon* pSensorIcon = (CSensorIcon*)(arrayList.GetAt(i));
		pSensorIcon->DrawIcon(iconBmp, pCDC);
	}
	iconBmp.DeleteObject();
}

//显示当前需要显示的地图
void DisplayCurMap(HWND wnd,CDC* pCDC, CString curPicPath, CRect& mapRect)
{
	if (!curPicPath.IsEmpty())//当前地图路径非空，表明用户点击的节点路径下存有图片
	{
		BSTR str = curPicPath.AllocSysString();//分配字符串空间
		Image image(str);
		Graphics imgraphics(pCDC->m_hDC);
		//5个参数分别表示：(1)图片路径；(2)起点横坐标；(3)起点纵坐标；(4)宽度；(5)高度
		imgraphics.DrawImage(&image, mapRect.left, mapRect.top, mapRect.right - mapRect.left, mapRect.bottom - mapRect.top);
		SysFreeString(str);
		//ReleaseDC(wnd, *pCDC);
	}
}

//清空CObject队列
void ClearList(CObArray& list)
{
	int size = list.GetSize();
	for (int i = 0; i < size; i++)
	{
		delete list.GetAt(i);
		//下面的写法是错误的  
		//      list.RemoveAt(i);  
	}
	list.RemoveAll();
}