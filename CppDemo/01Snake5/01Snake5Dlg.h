
// 01Snake5Dlg.h: 头文件
//

#pragma once


// CMy01Snake5Dlg 对话框
class CMy01Snake5Dlg : public CDialogEx
{
// 构造
public:
	CMy01Snake5Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY01SNAKE5_DIALOG };
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
	void Tick();

private:
	enum DRICT {
		M_Up = 0, M_Down, M_Left, M_Right
	};
	int m_iWidth;
	int m_iHeight;

	CBitmap m_cbmRed;
	CBitmap m_cbmWhite;
	CBitmap m_cbmGreen;

	BITMAP m_bmRed;
	BITMAP m_bmWhite;
	BITMAP m_bmGreen;

	int m_iNum;// 蛇的长度
	int m_iDirect;// 蛇的方向
	CPoint m_snake[100];

	CPoint m_food;//食物的坐标
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStartGame();
	afx_msg void OnStopGame();
	afx_msg void OnEndGame();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
