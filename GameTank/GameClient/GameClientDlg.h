
// GameClientDlg.h: 头文件
//

#pragma once


// CGameClientDlg 对话框
class CGameClientDlg : public CDialogEx
{
// 构造
public:
	CGameClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMECLIENT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	void Draw();

private:
	MyTank player;
	Graphics* graphics;
	Color m_bg;
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStop();
	afx_msg void OnEnd();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
