
// GameAsteroidsDlg.h: 头文件
//

#pragma once


// CGameAsteroidsDlg 对话框
class CGameAsteroidsDlg : public CDialogEx
{
// 构造
public:
	CGameAsteroidsDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEASTEROIDS_DIALOG };
#endif

private:
	int m_xA;
	int m_xB;
	int m_xC;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
