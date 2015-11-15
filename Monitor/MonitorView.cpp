
// MonitorView.cpp : CMonitorView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CMonitorView ����/����

CMonitorView::CMonitorView()
	: CFormView(CMonitorView::IDD)
{
	// TODO:  �ڴ˴���ӹ������
	m_curMapPath = "";
	m_curPrjPath = "";
}

CMonitorView::~CMonitorView()
{
	GdiplusShutdown(m_pGdiToken);//ж��gdiplus��
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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CMonitorView::InitEventLst()
{
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_eventLst.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_eventLst.SetExtendedStyle(m_eventLst.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// Ϊ�б���ͼ�ؼ����6��   
	m_eventLst.InsertColumn(0, _T("ʱ��"), LVCFMT_CENTER, rect.Width() / 10, 0);
	m_eventLst.InsertColumn(1, _T("����ID"), LVCFMT_CENTER, rect.Width() / 15, 1);
	m_eventLst.InsertColumn(2, _T("�豸ID"), LVCFMT_CENTER, rect.Width() / 15, 2);
	m_eventLst.InsertColumn(2, _T("�豸��Ϣ"), LVCFMT_CENTER, rect.Width() / 3, 3);
	m_eventLst.InsertColumn(2, _T("�¼���Ϣ"), LVCFMT_CENTER, rect.Width() / 3, 4);
	m_eventLst.InsertColumn(2, _T("�¼�����"), LVCFMT_CENTER, rect.Width() / 10, 5);
}

//void CMonitorView::SetMapTreeListItem(CString mapPath, HTREEITEM treeCtlRoot)
//{
//	CFileFind fileFind;	//�ļ����ҽṹ
//	//CString filepath(map_path);//map�ļ���·����
//	CString fileName;//�����ļ���
//	CString filePath;//�����ļ�·��
//
//	m_treeCtlItemInfo.hParent = treeCtlRoot;//�趨���ڵ�
//	m_treeCtlItemInfo.item.iImage = 0;//�������ڷ�ѡ��״̬��ʱ�������οؼ���ͼ���б������
//	m_treeCtlItemInfo.item.iSelectedImage = 0;//���ѡ��ʱ�������οؼ�ͼ���б��������
//
//	BOOL flag = fileFind.FindFile(mapPath);//��ʼ����map�ļ���
//	while (flag)//���map�ļ��������ļ�
//	{
//		flag = fileFind.FindNextFile();//ָ���¸��ļ�
//		if (fileFind.IsDots())
//		{
//			//ÿ���ļ��ж������������������ļ���:
//			//(1) .   ��ʾ���ļ����Լ���//(2) ..  ��ʾ���ļ��еĸ��ļ����ǵ�ǰĿ¼�����Ǹ�Ŀ¼	
//			continue;
//		}
//		else	
//		{
//			if (fileFind.IsDirectory())//�����ǰ�ļ��������ļ���
//			{
//				filePath = fileFind.GetFilePath();//��ȡ�ļ�·��
//				fileName = fileFind.GetFileName();//��ȡ�ļ���
//				if (fileName.GetLength() > 50)
//				{
//					MessageBox(_T("���ļ������ƹ������������޸����ļ�����!"), _T("��ʾ"), MB_ICONASTERISK | MB_OK);
//					return ;
//				}
//				// gjx-130916 entry001-012B up
//				m_treeCtlItemInfo.item.pszText = (LPWSTR)(LPCWSTR)(fileName);//�ַ���filename��ֵ��pszText��������ʾ
//				//nodeName[num] = treectl_item_info.item.pszText;//����ڵ�����
//				m_treeCtlItemInfo.hParent = treeCtlRoot;//���ڵ�
//				m_treeCtlItemInfo.item.lParam = m_treeItemId;//�ڵ���
//				m_treeNodePath[m_treeItemId] = fileFind.GetFilePath();//�洢�ļ�·��
//				m_treeCtlRoot = m_mapTreeLst.InsertItem(&m_treeCtlItemInfo);//����ڵ�
//				m_treeItemId++;//�ڵ���+1
//				//�ݹ�����ļ����Ӷ��γ����ͽṹͼ
//				SetMapTreeListItem((fileFind.GetFilePath() + _T("\\*.*")), m_treeCtlRoot);
//				//	free(tvinsert.item.pszText);
//			}
//			else
//			{
//				////˵���������ӷ��ļ������͵��ļ�
//
//				//filePath = file_find.GetFilePath();//��ȡ�ļ�·��
//				//fileName = file_find.GetFileName();//��ȡ�ļ�����
//				//int index = fileName.Find(_T("."));//�򵽡�.����λ��
//				//CString picex = fileName.Right(fileName.GetLength() - index - 1);//��ȡ�ļ���չ��
//				//char *pa = (char*)((LPCTSTR)picex);
//
//				//if (strcmp(pa, "prj") == 0)//������ļ�����չ��Ϊ��prj��,���ȡ�����ļ��е����ݣ���ASD���ݱ��浽����AsdToPath
//				//{
//				//	CFileFind mapfind;	//�ļ����ҽṹ
//				//	CString mapname;
//				//	CString mappath;
//				//	int pos = filePath.Find(fileName);
//				//	CString mappos = filePath.Mid(0, pos);
//				//	mappos += "\*.*";
//				//	BOOL mapflag = mapfind.FindFile(mappos);//��ʼ����map�ļ���
//				//	while (mapflag)//���map�ļ��������ļ�,�˴���Ϊ�˲�����.prj�ļ�ͬĿ¼�µĵ�ͼ�ļ�
//				//	{
//				//		mapflag = mapfind.FindNextFile();//ָ���¸��ļ�
//				//		if (mapfind.IsDots())
//				//		{
//				//			//ÿ���ļ��ж������������������ļ���:
//				//			//(1) .   ��ʾ���ļ����Լ���//(2) ..  ��ʾ���ļ��еĸ��ļ����ǵ�ǰĿ¼�����Ǹ�Ŀ¼	
//				//			continue;
//				//		}
//				//		else	
//				//		{
//				//			if (!mapfind.IsDirectory())//�����ǰ�ļ����Ͳ����ļ���	
//				//			{
//				//				mappath = mapfind.GetFilePath();//��ȡ�ļ�·��
//				//				mapname = mapfind.GetFileName();//��ȡ�ļ�����
//				//				int index = mapname.Find(_T("."));//�򵽡�.����λ��
//				//				CString picex = mapname.Right(mapname.GetLength() - index - 1);//��ȡ�ļ���չ��
//				//				char *pa = (char*)((LPCTSTR)picex);
//				//				if (strcmp(pa, "bmp") == 0 || strcmp(pa, "jpg") == 0 || strcmp(pa, "JPG") == 0 || strcmp(pa, "JPEG") == 0 || strcmp(pa, "jpeg") == 0)
//				//				{
//				//					srcMapPath = mappath;//�����ӦͼƬ��·��
//				//					break;
//				//				}
//				//			}
//				//		}
//				//	}
//				//	// gjx-130916 entry001-014B up
//				//	mapfind.Close();
//					
//					//GetDlgItem(IDC_MAP)->GetWindowRect(&rc);//��ȡ��ͼ�ؼ���λ����Ϣ,�������Ļ������Եģ��������Ͻ�������Ǵ�������Ļ�ϵ����Ͻ����꣬���Ĵ�С�����������ڵĴ�С
//					//ScreenToClient(&rc);//����Ļ��ָ�������Ļ����ת���ɿͻ���������
//
//					//CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();//��ȡ�ĵ�ָ��
//					//CMonitorDoc *pDoc = (CMonitorDoc*)pFrame->GetActiveDocument();
//					//ASSERT_VALID(pDoc);
//
//					//CFile file;
//					//if (file.Open(filePath, CStdioFile::modeRead))//���ļ�
//					//	// gjx-130916 entry001-018A down
//					//	// gjx-130916 entry001-018B down
//					//{
//					//	// gjx-130916 entry001-018A up
//					//	file.SeekToBegin();	//Sets the value of the file pointer to the beginning of the file
//					//	CArchive ar(&file, CArchive::load);//����carchive���������ڴ��ļ���ȡ�����ļ�д�����ݵ�CArchive����
//					//	//���л��ļ���ȡ
//					//	pDoc->Serialize(ar);// gjx-130916 entry001-019 down Serialize()
//					//	// gjx-130916 entry001-027 up
//					//	ar.Close();
//					//	file.Close();
//					//}
//					//// gjx-130916 entry001-018B up
//
//					//for (int i = 0; i<pDoc->m_gwlist.GetSize(); i++)//ѭ��ͼԪ�б�
//					//{
//					//	CMapElement* pMap = (CMapElement*)pDoc->m_gwlist.GetAt(i);//��ȡ����ͼ��ָ��
//					//	//�趨ÿ��ͼ���Դ������Ϣ�������ڴ�С�����仯ʱ��Ҫ�õ����ֵ
//					//	pMap->SetSrcRect(rc);// gjx-130916 entry001-028 down SetSrcRect()
//					//	// gjx-130916 entry001-029 up
//					//	//��ȡ����ͼ�������
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
//					//	DebugPrintf("����GW��%s-%s-%d", gs.gwArea, gs.gwID, gs.gwState);
//					//}
//					//for (i = 0; i<pDoc->m_asdlist.GetSize(); i++)//ѭ��ͼԪ�б�
//					//{
//					//	//��Ҫ��ȡ�������ļ�ͬһ·���µ�ͼƬ·��
//					//	CMapElement* pMap = (CMapElement*)pDoc->m_asdlist.GetAt(i);
//					//	pMap->SetSrcRect(rc);// gjx-130916 entry001-032 down SetSrcRect()
//					//	// gjx-130916 entry001-033 up
//					//	CString asdname = pMap->GetName();// gjx-130916 entry001-034 down GetName()
//					//	// gjx-130916 entry001-035 up
//
//					//	char gw[10], asd[10];
//					//	DebugPrintf("����ASD��%s", asdname);
//					//	sscanf(asdname, "%[^-]-%s", gw, asd);
//
//					//	ASD_TO_PATH tempASD;
//					//	tempASD.gw = gw;
//					//	tempASD.asd = asd;
//					//	tempASD.prj_path = filePath;
//					//	tempASD.map_path = srcMapPath;
//					//	AsdToPath.push_back(tempASD);
//					//	DebugPrintf("����ASD��%s-%s-%s", tempASD.gw, tempASD.asd, tempASD.prj_path);
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
//	//TV_INSERTSTRUCT treectl_item_info;			//���ؼ�ÿһ�����Ϣ�ṹ��
//	m_treeCtlItemInfo.hParent = NULL;			//���ڵ���
//	m_treeCtlItemInfo.hInsertAfter = TVI_LAST;	//���б����������
//	m_treeCtlItemInfo.item.mask = TVIF_SELECTEDIMAGE | TVIF_TEXT | LVIF_PARAM;//����ָ��TV_ITEM����Щ��Ա������Ч
//	m_treeCtlItemInfo.item.hItem = NULL;
//	m_treeCtlItemInfo.item.state = 0;			//λ��Ǻ�ͼ���б����������ã�ָ�����״̬
//	m_treeCtlItemInfo.item.stateMask = 0;		//����state��Ա��λ�Ƿ���Ч
//	m_treeCtlItemInfo.item.cchTextMax = 6;		//pszText��Աָ������Ĵ�С,���ַ�Ϊ��λ
//	m_treeCtlItemInfo.item.iSelectedImage = 1;	//���ѡ��ʱ�������οؼ�ͼ���б������
//
//	CString cur_path;
//	GetModuleFileName(NULL, cur_path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);//��ǰӦ�ó��������Ŀ¼
//	//map_file_path.ReleaseBuffer();
//	int pos = cur_path.ReverseFind('\\'); //�ҵ�'\'��λ��
//	cur_path = cur_path.Left(pos);	//�ַ�����ȡ��ȥ����ǰ·��������һ��'\'�ַ�
//
//	CString map_path(cur_path);
//	map_path += _T("\\map");//ָ����Ŀ¼Ϊmap�ļ���
//
//	//HTREEITEM treectl_root;				//TREEMAP���ڵ�
//	m_treeItemId = 0;
//	//��������Ŀ¼��Ϣ
//	SetMapTreeListItem(map_path, m_treeCtlRoot);// gjx-130916 entry001-008 down SetTreeItem()
//}



void CMonitorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	//��ȡ�ĵ�ָ��
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pDoc = (CMonitorDoc*)pFrame->GetActiveDocument();
	ASSERT_VALID(pDoc);

	//��ȡͼƬ�ؼ��ľ�������
	m_mapPicCtl.GetWindowRect(&m_mapRect);//��ȡ�ؼ���λ����Ϣ
	ScreenToClient(m_mapRect);

	InitEventLst();//��ʼ���¼��б�
	
	//���浱ǰ�Ĵ��ڳ��ȺͿ��
	CSize sz = GetTotalSize();
	m_oldWndCx = sz.cx;
	m_oldWndCy = sz.cy;

	//װ��gdiplus��
	GdiplusStartup(&m_pGdiToken, &m_gdiplusStartupInput, NULL);
	InitMapTreeList(FALSE, m_treeItemId, m_treeNodePath, m_mapTreeLst, m_treeCtlItemInfo, m_treeCtlRoot);
}


// CMonitorView ���

#ifdef _DEBUG
void CMonitorView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMonitorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMonitorDoc* CMonitorView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMonitorDoc)));
	return (CMonitorDoc*)m_pDocument;
}
#endif //_DEBUG


// CMonitorView ��Ϣ�������



void CMonitorView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
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
	// TODO:  �ڴ���������������
	CSrvConf srv_conf;
	srv_conf.DoModal();
}


void CMonitorView::OnMenuGwconf()
{
	// TODO:  �ڴ���������������
	CGWConf gw_conf;
	gw_conf.DoModal();
}


void CMonitorView::OnMenuPrjconf()
{
	// TODO:  �ڴ���������������
	CPrjConf prj_conf;
	prj_conf.DoModal();
}


void CMonitorView::OnMenuTmchk()
{
	// TODO:  �ڴ���������������
	CTimeCheck time_chk;
	time_chk.DoModal();
}


void CMonitorView::OnMenuSound()
{
	// TODO:  �ڴ���������������
	CSoundChg sound_chg;
	sound_chg.DoModal();
}


void CMonitorView::OnMenuHistory()
{
	// TODO:  �ڴ���������������
	CHistory ht;
	ht.DoModal();
}


void CMonitorView::OnNMClickMapTreeList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CPoint pt = GetCurrentMessage()->pt;
	m_mapTreeLst.ScreenToClient(&pt);  //��������Ļ���꣬ת�������οؼ��Ŀͻ�������
	UINT uFlags = 0;
	CFileFind picFileFind;//Ѱ��ָ���ڵ��µ�ͼƬ·��
	CString picName;//���ڱ���ָ���ڵ��µ�ͼƬ����
	CString picPath;//���ڱ���ָ���ڵ��µ�ͼƬ·��
	HTREEITEM hItem = m_mapTreeLst.HitTest(pt, &uFlags);//Ȼ����������� 
	//m_curMapPath = "";//��ʱ���ͼƬ·��
	//m_curPrjPath = "";//��ʱ��������ļ�·��
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))//���������������ڽڵ�λ��
	{
		m_mapTreeLst.SelectItem(hItem);
		int nDat = m_mapTreeLst.GetItemData(hItem);//��ȡ�ڵ�ı��
		CString treeItemPath = m_treeNodePath[nDat];//����ͼƬ·��
		m_curTreeItemPath = treeItemPath;//���浱ǰ�ڵ�·��
		treeItemPath += "\\*.*";

		m_curMapPath = "";//��������ݣ��������û������û�б���ͼƬ���ļ���ʱ���м�������ʾ�հ�
		m_curPrjPath = "";
		BOOL flag = picFileFind.FindFile(treeItemPath);//��ʼ����temp�ļ���		
		while (flag)//���map�ļ��������ļ�
		{
			flag = picFileFind.FindNextFile();//ָ���¸��ļ�
			if (picFileFind.IsDots())
			{
				//ÿ���ļ��ж������������������ļ���:
				//(1) .   ��ʾ���ļ����Լ�
				//(2) ..  ��ʾ���ļ��еĸ��ļ����ǵ�ǰĿ¼�����Ǹ�Ŀ¼
				continue;
			}
			else
			{
				if (!picFileFind.IsDirectory())//��ǰ�ļ����Ͳ����ļ��У����й��˲���
				{
					picPath = picFileFind.GetFilePath();//��ȡ�ļ�·��
					picName = picFileFind.GetFileName();//��ȡ�ļ�����
					int pos = picName.Find(_T("."));//�򵽡�.����λ��
					CString fileExtension = picName.Right(picName.GetLength() - pos - 1);//��ȡ�ļ���չ��
					if (fileExtension == "bmp" || fileExtension == "jpg" || fileExtension == "JPEG" || fileExtension == "jpeg")
						m_curMapPath = picPath;//����ͼƬ·��

					if (fileExtension == "prj")//������ļ�����չ��Ϊ��prj��
					{
						m_curPrjPath = picPath;//���������ļ�·��
						CFile file;
						BOOL fileret = file.Open(m_curPrjPath, CStdioFile::modeRead);//��ȡ�����ļ�������
						if (fileret)//���ļ�
						{
							file.SeekToBegin();	//�����ļ�ָ�뵽�ļ��Ŀ�ʼ��
							CArchive ar(&file, CArchive::load);
							pDoc->Serialize(ar);//���л��ļ���ȡ
							ar.Abort();
							file.Close();
						}
					}
				}
			}
		}
		picFileFind.Close();
	}
	
	this->InvalidateRect(&m_mapRect, FALSE);		//ˢ��ָ������
}

//void CMonitorView::DisplayCurMap(CString curMapPath)
//{
//	if (!curMapPath.IsEmpty())//��ǰ��ͼ·���ǿգ������û�����Ľڵ�·���´���ͼƬ
//	{
//		CRect pic;
//		m_mapPicCtl.GetWindowRect(&pic);//��ȡIDC_MAP�ؼ���������
//		ScreenToClient(&pic);//���������껻Ϊ�ͻ�������
//
//		BSTR str = curMapPath.AllocSysString();//�����ַ����ռ�
//		Image image(str);
//		CDC* hdc = GetDC();
//		Graphics imgraphics(hdc->m_hDC);
//		//5�������ֱ��ʾ��(1)ͼƬ·����(2)�������ꣻ(3)��������ꣻ(4)��ȣ�(5)�߶�
//		imgraphics.DrawImage(&image, pic.left, pic.top, pic.right - pic.left, pic.bottom - pic.top);
//		SysFreeString(str);
//		ReleaseDC(hdc);
//	}
//}

void CMonitorView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CFormView::OnPaint()
	CDC* pCDC = GetDC();
	DisplayCurMap(this->m_hWnd, pCDC, m_curMapPath, m_mapRect);
	CBitmap iconBmp;
	iconBmp.LoadBitmap(IDB_GWBMP);
	DisplayIcon(iconBmp, pCDC, pDoc->m_gwList);
	iconBmp.LoadBitmap(IDB_SENSORBMP);
	DisplayIcon(iconBmp, pCDC, pDoc->m_sensorList);
	ReleaseDC(pCDC);
}
