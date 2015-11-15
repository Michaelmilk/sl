#pragma once


// CTimeCheck 对话框

class CTimeCheck : public CDialogEx
{
	DECLARE_DYNAMIC(CTimeCheck)

public:
	CTimeCheck(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTimeCheck();

// 对话框数据
	enum { IDD = IDD_TIME_CHECK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
