
// 02Tetris5Dlg.h: 头文件
//

#pragma once

#define W 10
#define H 20

// CMy02Tetris5Dlg 对话框
class CMy02Tetris5Dlg : public CDialogEx
{
// 构造
public:
	CMy02Tetris5Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY02TETRIS5_DIALOG };
#endif

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
	afx_msg void OnStartGame();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStopGame();
	afx_msg void OnEndGame();

private:
	CBitmap m_block;
	BITMAP m_bmBlock;

	int m_iSize;// 方块大小
	CPoint a[4];//下落的方块

	int canvas[H][W];
	int dx;// 移动方向
	bool rotate;// 旋转
	int color;// 方块颜色

public:
	bool Check();
};
