#pragma once


// CSoundChg �Ի���

class CSoundChg : public CDialogEx
{
	DECLARE_DYNAMIC(CSoundChg)

public:
	CSoundChg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSoundChg();

// �Ի�������
	enum { IDD = IDD_SOUND_CHANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
