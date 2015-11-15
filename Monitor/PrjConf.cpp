// PrjConf.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "PrjConf.h"
#include "afxdialogex.h"
#include "CommonModule.h"
#include "MainFrm.h"
#include "SensorIcon.h"
//#include "MonitorDoc.h"

// CPrjConf �Ի���
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


// CPrjConf ��Ϣ�������


BOOL CPrjConf::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_comboGWId.AddString(_T("2222"));
	m_sensorList.AddString(_T("7777"));
	//����ĵ�ָ��
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pDoc = (CMonitorDoc*)pFrame->GetActiveDocument();
	ASSERT_VALID(pDoc);

	m_cursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);//���ù����״Ϊʮ����

	m_prjMapPicCtl.GetWindowRect(&m_mapRect);//��ȡͼƬ�ؼ���λ����Ϣ,�������Ļ������Եģ��������Ͻ�������Ǵ�������Ļ�ϵ����Ͻ����꣬���Ĵ�С�����������ڵĴ�С
	ScreenToClient(&m_mapRect);//����Ļ��ָ�������Ļ����ת���ɿͻ���������

	GdiplusStartup(&m_pPrjGdiToken, &m_prjGdiplusStartupInput, NULL);//װ��gdiplus��
	InitMapTreeList(TRUE, m_prjTreeItemId, m_prjTreeNodePath, m_prjMapTreeLst, m_prjTreeCtlItemInfo, m_prjTreeCtlRoot);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CPrjConf::OnNMClickPrjTreeMaplist(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	m_comboArea.ResetContent();
	CPoint pt = GetCurrentMessage()->pt;
	m_prjMapTreeLst.ScreenToClient(&pt);  //��������Ļ���꣬ת�������οؼ��Ŀͻ�������
	UINT uFlags = 0;
	CFileFind picFileFind;//Ѱ��ָ���ڵ��µ�ͼƬ·��
	CString picName;//���ڱ���ָ���ڵ��µ�ͼƬ����
	CString picPath;//���ڱ���ָ���ڵ��µ�ͼƬ·��
	CString fileName;//���ڱ��������������
	HTREEITEM hItem = m_prjMapTreeLst.HitTest(pt, &uFlags);//Ȼ����������� 
	m_prjMapPicPath = "";//��ʱ���ͼƬ·��
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))//���������������ڽڵ�λ��
	{
		m_prjMapTreeLst.SelectItem(hItem);
		int nDat = m_prjMapTreeLst.GetItemData(hItem);//��ȡ�ڵ�ı��
		CString treeItemPath = m_prjTreeNodePath[nDat];//����ͼƬ·��
		//m_curTreeItemPath = treeItemPath;//���浱ǰ�ڵ�·��
		treeItemPath += "\\*.*";

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
				if (!picFileFind.IsDirectory())//��ǰ�ļ����Ͳ����ļ��У�Ҳ����ͼƬ
				{
					// gjx-130921 entry041-003A up
					picPath = picFileFind.GetFilePath();//��ȡ�ļ�·��
					picName = picFileFind.GetFileName();//��ȡ�ļ�����
					int index = picName.Find(_T("."));//�򵽡�.����λ��
					CString fileExtension = picName.Right(picName.GetLength() - index - 1);//��ȡ�ļ���չ��
					if (fileExtension == "bmp" || fileExtension == "jpg" || fileExtension == "JPEG" || fileExtension == "jpeg")
						m_prjMapPicPath = picPath;//����ͼƬ·��
				}
				else//��ǰ�ļ�����������ļ��У���ô���ļ��е�������ӵ����������Ͽ���
				{
					fileName = picFileFind.GetFileName();//��ȡ�ļ�����
					m_comboArea.AddString(fileName);
				}
			}
		}
		picFileFind.Close();
	}

	this->InvalidateRect(&m_mapRect, FALSE);		//ˢ��ָ������
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
//	//˫������ƻ��ԭ���ı�����ͼ����
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
//	if (!m_prjMapPicPath.IsEmpty())//��ǰ��ͼ·���ǿգ������û�����Ľڵ�·���´���ͼƬ
//	{
//		BSTR str = m_prjMapPicPath.AllocSysString();//�����ַ����ռ�
//		Image image(str);
//		CDC* hdc = GetDC();
//		Graphics imgraphics(hdc->m_hDC);
//		//5�������ֱ��ʾ��(1)ͼƬ·����(2)�������ꣻ(3)��������ꣻ(4)��ȣ�(5)�߶�
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
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_iconType != NO_ICON)
	{
		if (!m_prjMapPicPath.IsEmpty())
		{
			int gwPos = m_comboGWId.GetCurSel();
			if (-1 == gwPos)
			{
				MessageBox(_T("����ѡ�����ر�ţ�"), _T("��ʾ"));
				return;
			}
			m_comboGWId.GetLBText(gwPos, m_curGWId);//��ȡ��ǰ���صı��

			switch (m_iconType)
			{
				case GW_ICON:
				{
					int areaPos = m_comboArea.GetCurSel();
					if (-1 == areaPos)
					{
						MessageBox(_T("����ѡ��������"), _T("��ʾ"));
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
						MessageBox(_T("����ѡ�񴫸�����ţ�"), _T("��ʾ"));
						return;
					}
					m_sensorList.GetText(sensorPos, m_curSensorId);
					break;
				}
			}
			SetCursor(m_cursor);
			this->SetCapture();//�ı�����״
		}
		
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CPrjConf::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (m_iconType != NO_ICON)
	{
		if (!m_prjMapPicPath.IsEmpty())
		{
			//������ڵ�ͼ�����ڵ����������ʾ
			if (!m_mapRect.PtInRect(point))
			{
				MessageBox(_T("���ڵ�ͼ���������ͼ�꣡"), _T("��ʾ"));
				return;
			}

			m_cursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
			SetCursor(m_cursor);//���������״
			ReleaseCapture();//�ͷ����

			CDC* pCurDC = this->GetDC();

			

			CBitmap  bmpGW, bmpSensor;
			bmpGW.LoadBitmap(IDB_GWBMP);//����ͼ��
			bmpSensor.LoadBitmap(IDB_SENSORBMP);//�豸ͼ��

			BITMAP  bitmapGW, bitmapSensor;
			bmpGW.GetBitmap(&bitmapGW);
			bmpSensor.GetBitmap(&bitmapSensor);
			
			//����ӵ�ͼ����봮�л�����
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
			this->InvalidateRect(&m_mapRect, FALSE);//�ͻ������ָ�����ֽ����ػ�,
			this->ReleaseDC(pCurDC);
		}

	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CPrjConf::OnBnClickedBtnAddGW()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_iconType != GW_ICON)
	{
		if (m_iconType == DHT11_ICON)
			m_addSensorIcon.SetWindowTextW(_T("��Ӵ�����ͼ��"));
		m_iconType = GW_ICON;
		m_addGWIcon.SetWindowTextW(_T("ֹͣ�������ͼ��"));
	}
	else 
	{
		m_iconType = NO_ICON;
		m_addGWIcon.SetWindowTextW(_T("�������ͼ��"));
	}
}

void CPrjConf::OnBnClickedBtnAddSensor()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_iconType != DHT11_ICON)
	{
		if (m_iconType == GW_ICON)
			m_addGWIcon.SetWindowTextW(_T("�������ͼ��"));
		m_iconType = DHT11_ICON;
		m_addSensorIcon.SetWindowTextW(_T("ֹͣ��Ӵ�����ͼ��"));
	}
	else
	{
		m_iconType = NO_ICON;
		m_addSensorIcon.SetWindowTextW(_T("��Ӵ�����ͼ��"));
	}
	
}

//���ر����Ͽ���ѡ������ر仯��ʱ��������б���еĴ������ı��Ҳ���ű仯
void CPrjConf::OnCbnSelchangeComboGwId()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

}


void CPrjConf::OnBnClickedBtnPrjLoad()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	pDoc->m_gwList.RemoveAll();//�Ƴ����е������б�
	pDoc->m_sensorList.RemoveAll();//�Ƴ����ڵ��豸�б�
	//OFN_NOCHANGEDIR��־�ǳ���Ҫ��������ô˱�־ÿ��CFileDialog����޸ĵ�ǰ·��,��Ҫ������������ָܻ�����
	CFileDialog dlg(TRUE,_T("prj"),_T(""),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,_T( "��Ŀ�ļ�(.prj)|*||" ),NULL);//�����ļ���ȡ�Ի���

	if (IDOK != dlg.DoModal())
	{
		return;
	}
	CString fileName = dlg.GetPathName();//��ȡ�ļ�·����
	CFile file;
	if (file.Open(fileName, CStdioFile::modeRead))//���ļ�
	{
		file.SeekToBegin();	//Sets the value of the file pointer to the beginning of the file
		CArchive ar(&file, CArchive::load);//����carchive���������ڴ��ļ���ȡ�����ļ�д�����ݵ�CArchive����
		pDoc->Serialize(ar);//���л��ļ���ȡ
		ar.Abort();
		file.Close();
	}

	this->InvalidateRect(&m_mapRect, FALSE);		//ˢ��ָ������
}


void CPrjConf::OnBnClickedBtnPrjSave()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//OFN_NOCHANGEDIR��־�ǳ���Ҫ��������ô˱�־ÿ��CFileDialog����޸ĵ�ǰ·��,��Ҫ������������ָܻ�����
	CFileDialog dlg(FALSE, _T("prj"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR, _T("��Ŀ�ļ�(.prj)|*||"), this);//�����ļ�����Ի���

	if (IDOK == dlg.DoModal())
	{
		CString pFileName = dlg.GetPathName();//��ȡ�ļ�·����
		CFile file;
		char buf[4096];
		if (!file.Open(pFileName, CFile::modeCreate | CFile::modeWrite))//�����ļ�
		{
			MessageBox(_T("�����ļ�����ʧ��"), _T("��ʾ"), MB_OK | MB_ICONASTERISK);
			return;
		}
		CArchive ar(&file, CArchive::store, 4096, buf);//����carchive�ṹ�壬�������ڴ��ļ���ȡ�����ļ�д�����ݵ�CArchive����
		pDoc->Serialize(ar);//���л����ݴ洢������λ����Ϣ

		this->InvalidateRect(&m_mapRect, FALSE);		//ˢ��ָ������
	}
}


void CPrjConf::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	pDoc->m_gwList.RemoveAll();
	pDoc->m_sensorList.RemoveAll();
	CDialogEx::OnClose();
}


void CPrjConf::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	pDoc->m_gwList.RemoveAll();
	pDoc->m_sensorList.RemoveAll();
	CDialogEx::OnOK();
}
