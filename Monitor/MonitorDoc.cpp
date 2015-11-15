
// MonitorDoc.cpp : CMonitorDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Monitor.h"
#endif

#include "MonitorDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMonitorDoc

IMPLEMENT_DYNCREATE(CMonitorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMonitorDoc, CDocument)
END_MESSAGE_MAP()


// CMonitorDoc ����/����

CMonitorDoc::CMonitorDoc()
{
	// TODO:  �ڴ����һ���Թ������

}

CMonitorDoc::~CMonitorDoc()
{
}

BOOL CMonitorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}

//���CObarray�е�Ԫ��
void CMonitorDoc::ClearList(CObArray& list)
{
	int size;
	size = list.GetSize();
	for (int i = 0; i < size; i++)
	{
		delete list.GetAt(i);
		//�����д���Ǵ����  
		//      list.RemoveAt(i);  
	}
	list.RemoveAll();
}


// CMonitorDoc ���л�

void CMonitorDoc::Serialize(CArchive& ar)
{
	m_gwList.Serialize(ar);
	m_sensorList.Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO:  �ڴ���Ӵ洢����
	}
	else
	{
		// TODO:  �ڴ���Ӽ��ش���
		//ClearList(m_gwSelectedList);
		//ClearList(m_sensorSelectedList);
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMonitorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CMonitorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CMonitorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMonitorDoc ���

#ifdef _DEBUG
void CMonitorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMonitorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMonitorDoc ����
