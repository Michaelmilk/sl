#pragma once


// CSrvConf �Ի���

class CSrvConf : public CDialogEx
{
	DECLARE_DYNAMIC(CSrvConf)

public:
	CSrvConf(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSrvConf();

// �Ի�������
	enum { IDD = IDD_DSCONF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
