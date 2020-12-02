
// GameSnakeDlg.h: 头文件
//

#pragma once


// CGameSnakeDlg 对话框
class CGameSnakeDlg : public CDialogEx
{
// 构造
public:
	CGameSnakeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMESNAKE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	void DrawGame();

private:
	Graphics* graphics;
	Image* red;
	Image* white;
	Image* green;
	int width;
	int height;

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
	afx_msg void OnEnd();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
