
// MyTankView.cpp: CMyTankView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyTank.h"
#endif

#include "MyTankDoc.h"
#include "MyTankView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyTankView

IMPLEMENT_DYNCREATE(CMyTankView, CView)

BEGIN_MESSAGE_MAP(CMyTankView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CMyTankView::OnOpenBitmap)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_32772, &CMyTankView::OnStartWalk)
	ON_COMMAND(ID_32773, &CMyTankView::OnStopWalk)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMyTankView 构造/析构

CMyTankView::CMyTankView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMyTankView::~CMyTankView()
{
}

BOOL CMyTankView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	// 加载坦克图片
	//HBITMAP hbmp = (HBITMAP)LoadImage(NULL, TEXT("./res/img/0Player/m0-0-1.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	//HBITMAP hbmp = (HBITMAP)LoadImage(NULL, TEXT("./res/walk.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	//if (hbmp == NULL) {
	//	AfxMessageBox(TEXT("加载位图失败"));
	//	return CView::PreCreateWindow(cs);
	//}
	//m_tank.Attach(hbmp);
	//m_tank.GetBitmap(&m_bm);

	//m_pos.x = 0;
	//m_pos.y = 0;

	m_role.Init(TEXT("./res/walk.bmp"), 0, 0, 4);

	return CView::PreCreateWindow(cs);
}

// CMyTankView 绘图

void CMyTankView::OnDraw(CDC* pDC)
{
	CMyTankDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

}


// CMyTankView 打印

BOOL CMyTankView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyTankView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMyTankView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMyTankView 诊断

#ifdef _DEBUG
void CMyTankView::AssertValid() const
{
	CView::AssertValid();
}

void CMyTankView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyTankDoc* CMyTankView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyTankDoc)));
	return (CMyTankDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyTankView 消息处理程序


void CMyTankView::OnOpenBitmap()
{
	// TODO: 在此添加命令处理程序代码
	//AfxMessageBox(TEXT("加载位图"));
	//CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, TEXT("*.bmp|*.bmp||"), this);
	//if (dlg.DoModal() == IDOK) {
	//	HBITMAP hbmp = (HBITMAP)LoadImage(NULL, dlg.GetPathName(), IMAGE_BITMAP,0, 0, LR_DEFAULTSIZE|LR_LOADFROMFILE);
	//	if (hbmp == NULL) {
	//		AfxMessageBox(TEXT("加载位图失败"));
	//		return;
	//	}
	//	m_tank.Attach(hbmp);

	//	CDC* pDC = GetDC();
	//	m_dc.CreateCompatibleDC(pDC);
	//	ReleaseDC(pDC);

	//	m_dc.SelectObject(&m_tank);
	//	Invalidate(FALSE);
	//}

}


void CMyTankView::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);//获取客户端大小
	::FillRect(dc.GetSafeHdc(), rect, (HBRUSH)GetStockObject(WHITE_BRUSH));//将客户端区域变成白色
	
	//BITMAP bm;
	//m_tank.GetBitmap(&bm);
	//dc.StretchBlt(m_pos.x, m_pos.y,
	//	bm.bmWidth, bm.bmHeight,
	//	&m_dc,
	//	0, 0,
	//	bm.bmWidth, bm.bmHeight,
	//	SRCCOPY);

	
	//m_role.Draw(pDC, m_pos.x, m_pos.y);
	//m_role.Update();

	//m_dc.CreateCompatibleDC(pDC);//创建缓存DC
	//m_dc.SelectObject(m_tank);//缓存DC绑定坦克图片

	//pDC->StretchBlt(m_pos.x, m_pos.y,
	//	m_bm.bmWidth, m_bm.bmHeight,
	//	&m_dc,
	//	0, 0,
	//	m_bm.bmWidth, m_bm.bmHeight,
	//	SRCCOPY);
	//m_dc.DeleteDC();
	HBITMAP hbmp = (HBITMAP)LoadImage(NULL, TEXT("./res/img/player0/m0-0-1.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if (hbmp == NULL) {
		AfxMessageBox(TEXT("加载位图失败"));
		return;
	}

	CBitmap ptank;
	ptank.Attach(hbmp);
	BITMAP bm;
	ptank.GetBitmap(&bm);

	CDC* pDC = GetDC();

	CDC mDC;
	// 创建兼容内存DC
	mDC.CreateCompatibleDC(pDC);
	mDC.SelectObject(ptank);

	pDC->StretchBlt(0, 0,
		bm.bmWidth, bm.bmHeight,
		&mDC,
		0, 0,
		bm.bmWidth, bm.bmHeight,
		SRCCOPY);

	mDC.DeleteDC();

	ReleaseDC(pDC);
}


void CMyTankView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CDC *pDC = GetDC();
	//pDC->Ellipse(point.x - 5, point.y - 5, point.x + 5, point.y + 5);

	//ReleaseDC(pDC);// 释放DC
	PaintPlayer(point.x, point.y);
	CView::OnLButtonDown(nFlags, point);
}


void CMyTankView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CDC* pDC = GetDC();
	//pDC->Rectangle(point.x - 5, point.y - 5, point.x + 5, point.y + 5);

	//ReleaseDC(pDC);// 释放DC
	CView::OnLButtonUp(nFlags, point);
}


void CMyTankView::PaintPlayer(int x, int y) {
	//CDC* pDC = GetDC();
	//m_dc.CreateCompatibleDC(pDC);//创建缓存DC
	//m_dc.SelectObject(m_tank);//缓存DC绑定坦克图片

	//pDC->StretchBlt(x, y,
	//	m_bm.bmWidth, m_bm.bmHeight,
	//	&m_dc,
	//	0, 0,
	//	m_bm.bmWidth, m_bm.bmHeight,
	//	SRCCOPY);
	//m_dc.DeleteDC();

	//ReleaseDC(pDC);
}

void CMyTankView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nChar == VK_UP) {
		m_pos.y -= 10;
		m_role.SetDirection(CMyRole::DIREC::M_Up);
	}
	if (nChar == VK_DOWN) {
		m_pos.y += 10;
		m_role.SetDirection(CMyRole::DIREC::M_Down);
	}
	if (nChar == VK_LEFT) {
		m_pos.x -= 10;
		m_role.SetDirection(CMyRole::DIREC::M_Left);
	}
	if (nChar == VK_RIGHT) {
		m_pos.x += 10;
		m_role.SetDirection(CMyRole::DIREC::M_Right);
	}
	Invalidate(FALSE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

VOID CALLBACK TimerProc(
	HWND hwnd,
	UINT uMsg,
	UINT_PTR ptr,
	DWORD dwTime) {


}

void CMyTankView::OnStartWalk()
{
	// TODO: 在此添加命令处理程序代码
	//::SetTimer(NULL, 0, 1000, TimerProc);
	//关联窗口（常用）
	::SetTimer(this->m_hWnd, 1, 3000, NULL);//开启定时器
}


void CMyTankView::OnStopWalk()
{
	// TODO: 在此添加命令处理程序代码
	::KillTimer(this->m_hWnd, 1);//关闭定时器
}


void CMyTankView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent) {
	case 1:

		break;
	default:
		break;
	}
	CView::OnTimer(nIDEvent);
}
