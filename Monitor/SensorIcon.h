#pragma once

// CSensorIcon 命令目标

#ifndef SENSOR_ICON
#define SENSOR_ICON

#define IconType		int
#define NO_ICON		0	//表示当前无关联图标，即不处于添加图标的状态
#define GW_ICON		1	//表示网关图标
#define DHT11_ICON	2	//表示DHT11图标

class CSensorIcon : public CObject
{
public:
	DECLARE_SERIAL(CSensorIcon)

	CSensorIcon();
	virtual ~CSensorIcon();
	//串行化
	void Serialize(CArchive& ar);
	//初始化成员变量
	void InitialMember(IconType iconType, CRect locationArea,
		CString upperLevelName, CString	 sensorId);
	//绘制图标
	void DrawIcon(CBitmap& iconBmp, CDC*	 pCDC);
	//绘制图标的描述
	void DrawIconDesc(CDC*	 pCDC);
	//绘制图标被选中的标记
	void DrawSelectedFlag(CDC*	 pCDC);
public:
	IconType		m_sensorType;		//图标表示的传感器类型
	CRect		m_locationArea;	//图标所在的矩形区域
	CString		m_upperLevelName;	//对于网关是区域的名称，对于传感器是网关的id
	CString		m_sensorId;		//对于网关是网关id，对于传感器是传感器的id
	CString		m_sensorDesc;		//图标所表示的传感器的描述
};

#endif
