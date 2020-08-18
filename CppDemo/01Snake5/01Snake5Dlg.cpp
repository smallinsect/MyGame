
// 01Snake5Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "01Snake5.h"
#include "01Snake5Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy01Snake5Dlg 对话框



CMy01Snake5Dlg::CMy01Snake5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY01SNAKE5_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy01Snake5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy01Snake5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_COMMAND(ID_32771, &CMy01Snake5Dlg::OnStartGame)
	ON_COMMAND(ID_32772, &CMy01Snake5Dlg::OnStopGame)
	ON_COMMAND(ID_32773, &CMy01Snake5Dlg::OnEndGame)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CMy01Snake5Dlg 消息处理程序

BOOL CMy01Snake5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_iWidth = 60;
	m_iHeight = 40;

	m_iNum = 4;
	m_snake[0].x = 4; m_snake[0].y = 4;
	m_snake[1].x = 4; m_snake[1].y = 5;
	m_snake[2].x = 4; m_snake[2].y = 6;
	m_snake[3].x = 4; m_snake[3].y = 7;
	m_iDirect = M_Down;

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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy01Snake5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy01Snake5Dlg::OnPaint()
{
	//if (IsIconic())
	//{
	//	CPaintDC dc(this); // 用于绘制的设备上下文

	//	SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

	//	// 使图标在工作区矩形中居中
	//	int cxIcon = GetSystemMetrics(SM_CXICON);
	//	int cyIcon = GetSystemMetrics(SM_CYICON);
	//	CRect rect;
	//	GetClientRect(&rect);
	//	int x = (rect.Width() - cxIcon + 1) / 2;
	//	int y = (rect.Height() - cyIcon + 1) / 2;

	//	// 绘制图标
	//	dc.DrawIcon(x, y, m_hIcon);
	//}
	//else
	//{
	//	CDialogEx::OnPaint();
	//}

	CPaintDC dc(this); // 用于绘制的设备上下文

	CDC* pDC = GetDC();

	CRect rect;
	GetClientRect(&rect);

	CDC mDC;//内存DC
	mDC.CreateCompatibleDC(pDC);

	//创建内存位图
	CBitmap mBmp;
	mBmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	mDC.SelectObject(&mBmp);//内存DC绑定内存位图
	mBmp.DeleteObject();//删除内存位图

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	memDC.SelectObject(m_cbmWhite);
	// 画背景
	for (int x = 0; x < m_iWidth; x++) {
		for (int y = 0; y < m_iHeight; y++) {
			mDC.StretchBlt(x * m_bmWhite.bmWidth, y * m_bmWhite.bmHeight,
				m_bmWhite.bmWidth, m_bmWhite.bmHeight,
				&memDC,
				0, 0, m_bmWhite.bmWidth, m_bmWhite.bmHeight,
				SRCCOPY);
		}
	}

	memDC.SelectObject(m_cbmRed);
	// 画蛇
	for (int i = 0; i < m_iNum; i++) {
		mDC.StretchBlt(m_snake[i].x * m_bmRed.bmWidth, m_snake[i].y * m_bmRed.bmHeight,
			m_bmRed.bmWidth, m_bmRed.bmHeight,
			&memDC,
			0, 0, m_bmRed.bmWidth, m_bmRed.bmHeight,
			SRCCOPY);
	}

	memDC.SelectObject(m_cbmGreen);
	//画食物
	mDC.StretchBlt(m_food.x * m_bmGreen.bmWidth, m_food.y * m_bmGreen.bmHeight,
		m_bmGreen.bmWidth, m_bmGreen.bmHeight,
		&memDC,
		0, 0, m_bmGreen.bmWidth, m_bmGreen.bmHeight,
		SRCCOPY);

	memDC.DeleteDC();

	pDC->StretchBlt(0, 0,
		rect.Width(), rect.Height(),
		&mDC,
		0, 0, rect.Width(), rect.Height(),
		SRCCOPY);

	mDC.DeleteDC();

	ReleaseDC(pDC);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy01Snake5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMy01Snake5Dlg::Tick() {
	for (int i = m_iNum; i > 0; i--) {
		m_snake[i] = m_snake[i - 1];
	}
	if (m_iDirect == M_Up)    m_snake[0].y -= 1;
	if (m_iDirect == M_Right) m_snake[0].x += 1;
	if (m_iDirect == M_Down)  m_snake[0].y += 1;
	if (m_iDirect == M_Left)  m_snake[0].x -= 1;

	m_snake[0].x = (m_snake[0].x + m_iWidth) % m_iWidth;
	m_snake[0].y = (m_snake[0].y + m_iHeight) % m_iHeight;
	// 蛇吃食物
	if (m_food.x == m_snake[0].x && m_food.y == m_snake[0].y) {
		// 增加蛇的长度
		m_iNum++;
		// 重新随机食物位置
		m_food.x = rand() % m_iWidth;
		m_food.y = rand() % m_iHeight;
	}
}

void CMy01Snake5Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
		Tick();
		Invalidate(FALSE);
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}




void CMy01Snake5Dlg::OnStartGame()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(1, 10, NULL);
}


void CMy01Snake5Dlg::OnStopGame()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(1);
}


void CMy01Snake5Dlg::OnEndGame()
{
	// TODO: 在此添加命令处理程序代码
}


void CMy01Snake5Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nChar == 'W') {
		m_iDirect = M_Up;
	}
	if (nChar == 'D') {
		m_iDirect = M_Right;
	}
	if (nChar == 'S') {
		m_iDirect = M_Down;
	}
	if (nChar == 'A') {
		m_iDirect = M_Left;
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
