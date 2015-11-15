#include "stdafx.h"
#include "CommonModule.h"
#include "SensorIcon.h"

//���õ�ͼ�����б���
void SetMapTreeListItem(bool configTag, int& treeItemId, CString treeNodePath[], CString mapPath, 
	CTreeCtrl& mapTreeLst, TV_INSERTSTRUCT& treeCtlItemInfo, HTREEITEM treeCtlRoot)		//���õ�ͼ�����б���
{
	CFileFind fileFind;	//�ļ����ҽṹ
	//CString filepath(map_path);//map�ļ���·����
	CString fileName;//�����ļ���
	CString filePath;//�����ļ�·��

	treeCtlItemInfo.hParent = treeCtlRoot;//�趨���ڵ�
	treeCtlItemInfo.item.iImage = 0;//�������ڷ�ѡ��״̬��ʱ�������οؼ���ͼ���б������
	treeCtlItemInfo.item.iSelectedImage = 0;//���ѡ��ʱ�������οؼ�ͼ���б��������

	BOOL flag = fileFind.FindFile(mapPath);//��ʼ����map�ļ���
	while (flag)//���map�ļ��������ļ�
	{
		flag = fileFind.FindNextFile();//ָ���¸��ļ�
		if (fileFind.IsDots())
		{
			//ÿ���ļ��ж������������������ļ���:
			//(1) .   ��ʾ���ļ����Լ���//(2) ..  ��ʾ���ļ��еĸ��ļ����ǵ�ǰĿ¼�����Ǹ�Ŀ¼	
			continue;
		}
		else
		{
			if (fileFind.IsDirectory())//�����ǰ�ļ��������ļ���
			{
				filePath = fileFind.GetFilePath();//��ȡ�ļ�·��
				fileName = fileFind.GetFileName();//��ȡ�ļ���
				if (fileName.GetLength() > 50)
				{
					//MessageBox(_T("���ļ������ƹ������������޸����ļ�����!"), _T("��ʾ"), MB_ICONASTERISK | MB_OK);
					return;
				}
				treeCtlItemInfo.item.pszText = (LPWSTR)(LPCWSTR)(fileName);//�ַ���filename��ֵ��pszText��������ʾ
				//nodeName[num] = treectl_item_info.item.pszText;//����ڵ�����
				treeCtlItemInfo.hParent = treeCtlRoot;//���ڵ�
				treeCtlItemInfo.item.lParam = treeItemId;//�ڵ���
				treeNodePath[treeItemId] = fileFind.GetFilePath();//�洢�ļ�·��
				HTREEITEM nextTreeCtlRoot = mapTreeLst.InsertItem(&treeCtlItemInfo);//����ڵ�
				treeItemId++;//�ڵ���+1
				//�ݹ�����ļ����Ӷ��γ����ͽṹͼ
				SetMapTreeListItem(configTag, treeItemId, treeNodePath, (fileFind.GetFilePath() + _T("\\*.*")), mapTreeLst, treeCtlItemInfo, nextTreeCtlRoot);
				//	free(tvinsert.item.pszText);
			}
			else if (!configTag)
			{
				////˵���������ӷ��ļ������͵��ļ�

				//filePath = file_find.GetFilePath();//��ȡ�ļ�·��
				//fileName = file_find.GetFileName();//��ȡ�ļ�����
				//int index = fileName.Find(_T("."));//�򵽡�.����λ��
				//CString picex = fileName.Right(fileName.GetLength() - index - 1);//��ȡ�ļ���չ��
				//char *pa = (char*)((LPCTSTR)picex);

				//if (strcmp(pa, "prj") == 0)//������ļ�����չ��Ϊ��prj��,���ȡ�����ļ��е����ݣ���ASD���ݱ��浽����AsdToPath
				//{
				//	CFileFind mapfind;	//�ļ����ҽṹ
				//	CString mapname;
				//	CString mappath;
				//	int pos = filePath.Find(fileName);
				//	CString mappos = filePath.Mid(0, pos);
				//	mappos += "\*.*";
				//	BOOL mapflag = mapfind.FindFile(mappos);//��ʼ����map�ļ���
				//	while (mapflag)//���map�ļ��������ļ�,�˴���Ϊ�˲�����.prj�ļ�ͬĿ¼�µĵ�ͼ�ļ�
				//	{
				//		mapflag = mapfind.FindNextFile();//ָ���¸��ļ�
				//		if (mapfind.IsDots())
				//		{
				//			//ÿ���ļ��ж������������������ļ���:
				//			//(1) .   ��ʾ���ļ����Լ���//(2) ..  ��ʾ���ļ��еĸ��ļ����ǵ�ǰĿ¼�����Ǹ�Ŀ¼	
				//			continue;
				//		}
				//		else	
				//		{
				//			if (!mapfind.IsDirectory())//�����ǰ�ļ����Ͳ����ļ���	
				//			{
				//				mappath = mapfind.GetFilePath();//��ȡ�ļ�·��
				//				mapname = mapfind.GetFileName();//��ȡ�ļ�����
				//				int index = mapname.Find(_T("."));//�򵽡�.����λ��
				//				CString picex = mapname.Right(mapname.GetLength() - index - 1);//��ȡ�ļ���չ��
				//				char *pa = (char*)((LPCTSTR)picex);
				//				if (strcmp(pa, "bmp") == 0 || strcmp(pa, "jpg") == 0 || strcmp(pa, "JPG") == 0 || strcmp(pa, "JPEG") == 0 || strcmp(pa, "jpeg") == 0)
				//				{
				//					srcMapPath = mappath;//�����ӦͼƬ��·��
				//					break;
				//				}
				//			}
				//		}
				//	}
				//	// gjx-130916 entry001-014B up
				//	mapfind.Close();

				//GetDlgItem(IDC_MAP)->GetWindowRect(&rc);//��ȡ��ͼ�ؼ���λ����Ϣ,�������Ļ������Եģ��������Ͻ�������Ǵ�������Ļ�ϵ����Ͻ����꣬���Ĵ�С�����������ڵĴ�С
				//ScreenToClient(&rc);//����Ļ��ָ�������Ļ����ת���ɿͻ���������

				//CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();//��ȡ�ĵ�ָ��
				//CMonitorDoc *pDoc = (CMonitorDoc*)pFrame->GetActiveDocument();
				//ASSERT_VALID(pDoc);

				//CFile file;
				//if (file.Open(filePath, CStdioFile::modeRead))//���ļ�
				//	// gjx-130916 entry001-018A down
				//	// gjx-130916 entry001-018B down
				//{
				//	// gjx-130916 entry001-018A up
				//	file.SeekToBegin();	//Sets the value of the file pointer to the beginning of the file
				//	CArchive ar(&file, CArchive::load);//����carchive���������ڴ��ļ���ȡ�����ļ�д�����ݵ�CArchive����
				//	//���л��ļ���ȡ
				//	pDoc->Serialize(ar);// gjx-130916 entry001-019 down Serialize()
				//	// gjx-130916 entry001-027 up
				//	ar.Close();
				//	file.Close();
				//}
				//// gjx-130916 entry001-018B up

				//for (int i = 0; i<pDoc->m_gwlist.GetSize(); i++)//ѭ��ͼԪ�б�
				//{
				//	CMapElement* pMap = (CMapElement*)pDoc->m_gwlist.GetAt(i);//��ȡ����ͼ��ָ��
				//	//�趨ÿ��ͼ���Դ������Ϣ�������ڴ�С�����仯ʱ��Ҫ�õ����ֵ
				//	pMap->SetSrcRect(rc);// gjx-130916 entry001-028 down SetSrcRect()
				//	// gjx-130916 entry001-029 up
				//	//��ȡ����ͼ�������
				//	CString gwName = pMap->GetName();// gjx-130916 entry001-030 GetName()
				//	// gjx-130916 entry001-031 up
				//	char gwArea[50], gwID[10];
				//	sscanf(gwName, "%[^-]-%s", gwArea, gwID);

				//	GW_STATE gs;
				//	gs.gwID = gwID;
				//	gs.gwArea = gwArea;
				//	gs.gwState = INIT;
				//	gwStateVect.push_back(gs);
				//	DebugPrintf("����GW��%s-%s-%d", gs.gwArea, gs.gwID, gs.gwState);
				//}
				//for (i = 0; i<pDoc->m_asdlist.GetSize(); i++)//ѭ��ͼԪ�б�
				//{
				//	//��Ҫ��ȡ�������ļ�ͬһ·���µ�ͼƬ·��
				//	CMapElement* pMap = (CMapElement*)pDoc->m_asdlist.GetAt(i);
				//	pMap->SetSrcRect(rc);// gjx-130916 entry001-032 down SetSrcRect()
				//	// gjx-130916 entry001-033 up
				//	CString asdname = pMap->GetName();// gjx-130916 entry001-034 down GetName()
				//	// gjx-130916 entry001-035 up

				//	char gw[10], asd[10];
				//	DebugPrintf("����ASD��%s", asdname);
				//	sscanf(asdname, "%[^-]-%s", gw, asd);

				//	ASD_TO_PATH tempASD;
				//	tempASD.gw = gw;
				//	tempASD.asd = asd;
				//	tempASD.prj_path = filePath;
				//	tempASD.map_path = srcMapPath;
				//	AsdToPath.push_back(tempASD);
				//	DebugPrintf("����ASD��%s-%s-%s", tempASD.gw, tempASD.asd, tempASD.prj_path);
				//}
				//}
			}
		}
	}
	fileFind.Close();
}

//��ʼ����ͼ�б����ؼ�
void InitMapTreeList(bool configTag, int& treeItemId, CString treeNodePath[],
	CTreeCtrl& mapTreeLst, TV_INSERTSTRUCT& treeCtlItemInfo, HTREEITEM& treeCtlRoot)		//��ʼ����ͼ�б����ؼ�
{
	treeCtlItemInfo.hParent = NULL;			//���ڵ���
	treeCtlItemInfo.hInsertAfter = TVI_LAST;	//���б����������
	treeCtlItemInfo.item.mask = TVIF_SELECTEDIMAGE | TVIF_TEXT | LVIF_PARAM;//����ָ��TV_ITEM����Щ��Ա������Ч
	treeCtlItemInfo.item.hItem = NULL;
	treeCtlItemInfo.item.state = 0;			//λ��Ǻ�ͼ���б����������ã�ָ�����״̬
	treeCtlItemInfo.item.stateMask = 0;		//����state��Ա��λ�Ƿ���Ч
	treeCtlItemInfo.item.cchTextMax = 6;		//pszText��Աָ������Ĵ�С,���ַ�Ϊ��λ
	treeCtlItemInfo.item.iSelectedImage = 1;	//���ѡ��ʱ�������οؼ�ͼ���б������

	CString cur_path;
	GetModuleFileName(NULL, cur_path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);//��ǰӦ�ó��������Ŀ¼
	//map_file_path.ReleaseBuffer();
	int pos = cur_path.ReverseFind('\\'); //�ҵ�'\'��λ��
	cur_path = cur_path.Left(pos);	//�ַ�����ȡ��ȥ����ǰ·��������һ��'\'�ַ�

	CString map_path(cur_path);
	map_path += _T("\\map");//ָ����Ŀ¼Ϊmap�ļ���

	//HTREEITEM treectl_root;				//TREEMAP���ڵ�
	treeItemId = 0;
	//��������Ŀ¼��Ϣ
	SetMapTreeListItem(configTag, treeItemId, treeNodePath, map_path, mapTreeLst, treeCtlItemInfo, treeCtlRoot);
}

//��ʾͼ��,������Ҫ��ʾm_gwList��COBArray�����е�����ͼ��
void DisplayIcon(CBitmap& iconBmp, CDC* pCDC, CObArray& arrayList)
{
	for (int i = 0; i < arrayList.GetSize(); i++)
	{
		CSensorIcon* pSensorIcon = (CSensorIcon*)(arrayList.GetAt(i));
		pSensorIcon->DrawIcon(iconBmp, pCDC);
	}
	iconBmp.DeleteObject();
}

//��ʾ��ǰ��Ҫ��ʾ�ĵ�ͼ
void DisplayCurMap(HWND wnd,CDC* pCDC, CString curPicPath, CRect& mapRect)
{
	if (!curPicPath.IsEmpty())//��ǰ��ͼ·���ǿգ������û�����Ľڵ�·���´���ͼƬ
	{
		BSTR str = curPicPath.AllocSysString();//�����ַ����ռ�
		Image image(str);
		Graphics imgraphics(pCDC->m_hDC);
		//5�������ֱ��ʾ��(1)ͼƬ·����(2)�������ꣻ(3)��������ꣻ(4)��ȣ�(5)�߶�
		imgraphics.DrawImage(&image, mapRect.left, mapRect.top, mapRect.right - mapRect.left, mapRect.bottom - mapRect.top);
		SysFreeString(str);
		//ReleaseDC(wnd, *pCDC);
	}
}

//���CObject����
void ClearList(CObArray& list)
{
	int size = list.GetSize();
	for (int i = 0; i < size; i++)
	{
		delete list.GetAt(i);
		//�����д���Ǵ����  
		//      list.RemoveAt(i);  
	}
	list.RemoveAll();
}