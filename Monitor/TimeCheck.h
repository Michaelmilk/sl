#pragma once


// CTimeCheck �Ի���

class CTimeCheck : public CDialogEx
{
	DECLARE_DYNAMIC(CTimeCheck)

public:
	CTimeCheck(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTimeCheck();

// �Ի�������
	enum { IDD = IDD_TIME_CHECK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
