
// MySnakeView.cpp: CMySnakeView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MySnake.h"
#endif

#include "MySnakeDoc.h"
#include "MySnakeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMySnakeView

IMPLEMENT_DYNCREATE(CMySnakeView, CView)

BEGIN_MESSAGE_MAP(CMySnakeView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_COMMAND(ID_32771, &CMySnakeView::OnStartGame)
	ON_COMMAND(ID_32772, &CMySnakeView::OnStopGamer)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMySnakeView 构造/析构

CMySnakeView::CMySnakeView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMySnakeView::~CMySnakeView()
{
}

BOOL CMySnakeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	m_iWidth = 30;
	m_iHeight = 20;

	m_iNum = 4;
	m_snake[0].x = 4; m_snake[0].y = 4;
	m_snake[1].x = 4; m_snake[1].y = 5;
	m_snake[2].x = 4; m_snake[2].y = 6;
	m_snake[3].x = 4; m_snake[3].y = 7;
	m_iDirect = M_Up;

	m_food.x = rand() % m_iWidth;
	m_food.y = rand() % m_iHeight;

	// 加载红色位图
	HBITMAP hbmp = (HBITMAP)LoadImage(NULL, TEXT("./res/red.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if (hbmp == NULL) {
		AfxMessageBox(TEXT("加载图片失败"));
	}

	m_cbmRed.Attach(hbmp);
	m_cbmRed.GetBitmap(&m_bmRed);

	// 加载白色位图
	hbmp = (HBITMAP)LoadImage(NULL, TEXT("./res/white.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if (hbmp == NULL) {
		AfxMessageBox(TEXT("加载图片失败"));
	}

	m_cbmWhite.Attach(hbmp);
	m_cbmWhite.GetBitmap(&m_bmWhite);

	// 加载绿色位图
	hbmp = (HBITMAP)LoadImage(NULL, TEXT("./res/green.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if (hbmp == NULL) {
		AfxMessageBox(TEXT("加载图片失败"));
	}

	m_cbmGreen.Attach(hbmp);
	m_cbmGreen.GetBitmap(&m_bmGreen);

	return CView::PreCreateWindow(cs);
}

// CMySnakeView 绘图

void CMySnakeView::OnDraw(CDC* /*pDC*/)
{
	CMySnakeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMySnakeView 打印

BOOL CMySnakeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMySnakeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMySnakeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMySnakeView 诊断

#ifdef _DEBUG
void CMySnakeView::AssertValid() const
{
	CView::AssertValid();
}

void CMySnakeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMySnakeDoc* CMySnakeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMySnakeDoc)));
	return (CMySnakeDoc*)m_pDocument;
}
#endif //_DEBUG


// CMySnakeView 消息处理程序


void CMySnakeView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CView::OnPaint()

	CDC* pDC = GetDC();

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	memDC.SelectObject(m_cbmWhite);
	// 画背景
	for (int x = 0; x < m_iWidth; x++) {
		for (int y = 0; y < m_iHeight; y++) {
			pDC->StretchBlt(x * m_bmWhite.bmWidth, y * m_bmWhite.bmHeight,
				m_bmWhite.bmWidth, m_bmWhite.bmHeight,
				&memDC,
				0, 0,
				m_bmWhite.bmWidth, m_bmWhite.bmHeight,
				SRCCOPY);
		}
	}

	memDC.SelectObject(m_cbmRed);
	// 画蛇
	for (int i = 0; i < m_iNum; i++) {
		pDC->StretchBlt(m_snake[i].x * m_bmRed.bmWidth, m_snake[i].y * m_bmRed.bmHeight,
			m_bmRed.bmWidth, m_bmRed.bmHeight,
			&memDC,
			0, 0,
			m_bmRed.bmWidth, m_bmRed.bmHeight,
			SRCCOPY);
	}

	memDC.SelectObject(m_cbmGreen);
	//画食物
	pDC->StretchBlt(m_food.x * m_bmGreen.bmWidth, m_food.y * m_bmGreen.bmHeight,
		m_bmGreen.bmWidth, m_bmGreen.bmHeight,
		&memDC,
		0, 0,
		m_bmGreen.bmWidth, m_bmGreen.bmHeight, 
		SRCCOPY);

	memDC.DeleteDC();

	ReleaseDC(pDC);
}


void CMySnakeView::OnStartGame()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(1, 60, NULL);
}


void CMySnakeView::OnStopGamer()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(1);
}


void CMySnakeView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent) {
	case 1:
		for (int i = m_iNum; i > 0; i--) {
			m_snake[i] = m_snake[i - 1];
		}
		if (M_Up == m_iDirect) {
			m_snake[0].y -= 1;
		}
		if (M_Down == m_iDirect) {
			m_snake[0].y += 1;
		}
		if (M_Left == m_iDirect) {
			m_snake[0].x -= 1;
		}
		if (M_Right == m_iDirect) {
			m_snake[0].x += 1;
		}

		// 蛇吃掉食物
		if (m_snake[0].x == m_food.x && m_snake[0].y == m_food.y) {
			// 增加蛇的长度
			m_iNum++;
			// 随机食物位置
			m_food.x = rand() % m_iWidth;
			m_food.y = rand() % m_iHeight;
		}

		// 蛇越界
		if (m_snake[0].y < 0) {
			m_snake[0].y = m_iHeight - 1;
		}
		if (m_snake[0].y >= m_iHeight){
			m_snake[0].y = 0;
		}

		if (m_snake[0].x < 0) {
			m_snake[0].x = m_iWidth - 1;
		}
		if (m_snake[0].x >= m_iWidth) {
			m_snake[0].x = 0;
		}


		Invalidate(FALSE);
		break;
	default:
		break;
	}

	CView::OnTimer(nIDEvent);
}


void CMySnakeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nChar == VK_UP) {
		m_iDirect = M_Up;
	}
	if (nChar == VK_DOWN) {
		m_iDirect = M_Down;
	}
	if (nChar == VK_LEFT) {
		m_iDirect = M_Left;
	}
	if (nChar == VK_RIGHT) {
		m_iDirect = M_Right;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
