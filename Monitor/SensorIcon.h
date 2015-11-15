#pragma once

// CSensorIcon ����Ŀ��

#ifndef SENSOR_ICON
#define SENSOR_ICON

#define IconType		int
#define NO_ICON		0	//��ʾ��ǰ�޹���ͼ�꣬�����������ͼ���״̬
#define GW_ICON		1	//��ʾ����ͼ��
#define DHT11_ICON	2	//��ʾDHT11ͼ��

class CSensorIcon : public CObject
{
public:
	DECLARE_SERIAL(CSensorIcon)

	CSensorIcon();
	virtual ~CSensorIcon();
	//���л�
	void Serialize(CArchive& ar);
	//��ʼ����Ա����
	void InitialMember(IconType iconType, CRect locationArea,
		CString upperLevelName, CString	 sensorId);
	//����ͼ��
	void DrawIcon(CBitmap& iconBmp, CDC*	 pCDC);
	//����ͼ�������
	void DrawIconDesc(CDC*	 pCDC);
	//����ͼ�걻ѡ�еı��
	void DrawSelectedFlag(CDC*	 pCDC);
public:
	IconType		m_sensorType;		//ͼ���ʾ�Ĵ���������
	CRect		m_locationArea;	//ͼ�����ڵľ�������
	CString		m_upperLevelName;	//������������������ƣ����ڴ����������ص�id
	CString		m_sensorId;		//��������������id�����ڴ������Ǵ�������id
	CString		m_sensorDesc;		//ͼ������ʾ�Ĵ�����������
};

#endif
