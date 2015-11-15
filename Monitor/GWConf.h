#pragma once


// CGWConf 对话框

class CGWConf : public CDialogEx
{
	DECLARE_DYNAMIC(CGWConf)

public:
	CGWConf(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGWConf();

// 对话框数据
	enum { IDD = IDD_GWCONF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
