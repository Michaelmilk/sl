#pragma once


// CHistory �Ի���

class CHistory : public CDialogEx
{
	DECLARE_DYNAMIC(CHistory)

public:
	CHistory(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHistory();

// �Ի�������
	enum { IDD = IDD_HISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
