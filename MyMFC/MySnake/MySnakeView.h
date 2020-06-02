
// MySnakeView.h: CMySnakeView 类的接口
//

#pragma once


class CMySnakeView : public CView
{
protected: // 仅从序列化创建
	CMySnakeView() noexcept;
	DECLARE_DYNCREATE(CMySnakeView)

// 特性
public:
	CMySnakeDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMySnakeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
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

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnStartGame();
	afx_msg void OnStopGamer();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // MySnakeView.cpp 中的调试版本
inline CMySnakeDoc* CMySnakeView::GetDocument() const
   { return reinterpret_cast<CMySnakeDoc*>(m_pDocument); }
#endif

