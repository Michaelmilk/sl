
// MonitorDoc.h : CMonitorDoc ��Ľӿ�
//


#pragma once


class CMonitorDoc : public CDocument
{
protected: // �������л�����
	CMonitorDoc();
	DECLARE_DYNCREATE(CMonitorDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMonitorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	CObArray m_gwList;
	CObArray m_sensorList;
	CObArray m_gwSelectedList;
	CObArray m_sensorSelectedList;

	void ClearList(CObArray& list);
};
