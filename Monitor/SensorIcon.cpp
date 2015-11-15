// SensorIcon.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "SensorIcon.h"


// CSensorIcon
IMPLEMENT_SERIAL(CSensorIcon, CObject, 1)

CSensorIcon::CSensorIcon()
{
	m_sensorType = NO_ICON;
	m_locationArea = CRect();
	m_upperLevelName = "";
	m_sensorId = "";
	m_sensorDesc = "";
}

CSensorIcon::~CSensorIcon()
{
}


// CSensorIcon ��Ա����
//���л�
void CSensorIcon::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_sensorType;
		ar << m_locationArea;
		ar << m_upperLevelName;
		ar << m_sensorId;
		ar << m_sensorDesc;
	}
	else
	{
		ar >> m_sensorType;
		ar >> m_locationArea;
		ar >> m_upperLevelName;
		ar >> m_sensorId;
		ar >> m_sensorDesc;
	}
}

//��ʼ����Ա����
void CSensorIcon::InitialMember(IconType iconType, CRect locationArea,
	CString upperLevelName, CString	 sensorId)
{
	m_sensorType = GW_ICON;
	m_locationArea = locationArea;
	m_upperLevelName = upperLevelName;
	m_sensorId = sensorId;
	m_sensorDesc.Format(_T("%s-%s"), upperLevelName, sensorId);
}

//����ͼ��
void CSensorIcon::DrawIcon(CBitmap& iconBmp, CDC*	 pCDC)
{
	CDC compatibleIconDC;
	compatibleIconDC.CreateCompatibleDC(pCDC);
	CBitmap *pOldBmp = compatibleIconDC.SelectObject(&iconBmp);

	pCDC->BitBlt(m_locationArea.left, m_locationArea.top, m_locationArea.Width(),
			m_locationArea.Height(), &compatibleIconDC, 0, 0, SRCCOPY);
	DrawIconDesc(pCDC);
	compatibleIconDC.SelectObject(pOldBmp);
	compatibleIconDC.DeleteDC();
}

//����ͼ�������
void CSensorIcon::DrawIconDesc(CDC*	 pCDC)
{
	pCDC->TextOut(m_locationArea.left, m_locationArea.bottom + 2, m_sensorDesc);
}

//����ͼ�걻ѡ�еı��
void DrawSelectedFlag(CDC*	 pCDC)
{

}