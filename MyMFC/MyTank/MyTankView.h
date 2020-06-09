
// MyTankView.h: CMyTankView 类的接口
//

#pragma once

class CMyTankView : public CView
{
protected: // 仅从序列化创建
	CMyTankView() noexcept;
	DECLARE_DYNCREATE(CMyTankView)

// 特性
public:
	CMyTankDoc* GetDocument() const;

// 操作
public:
	void PaintPlayer(int x, int y);
	void Paint();

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
	virtual ~CMyTankView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CBitmap m_tank;
	BITMAP m_bm;
	CDC m_dc;

	CMyRole m_role;

	CMyTank m_ptank;
	CMyEnemy m_etank;

	CMyBullet m_bullet;

	CMyBlast m_blast;


// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpenBitmap();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnStartWalk();
	afx_msg void OnStopWalk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // MyTankView.cpp 中的调试版本
inline CMyTankDoc* CMyTankView::GetDocument() const
   { return reinterpret_cast<CMyTankDoc*>(m_pDocument); }
#endif

