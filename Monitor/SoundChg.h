#pragma once


// CSoundChg 对话框

class CSoundChg : public CDialogEx
{
	DECLARE_DYNAMIC(CSoundChg)

public:
	CSoundChg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSoundChg();

// 对话框数据
	enum { IDD = IDD_SOUND_CHANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
