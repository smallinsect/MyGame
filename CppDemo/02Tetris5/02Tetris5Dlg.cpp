
// 02Tetris5Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "02Tetris5.h"
#include "02Tetris5Dlg.h"
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


// CMy02Tetris5Dlg 对话框

int figures[7][4] = {
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};



CMy02Tetris5Dlg::CMy02Tetris5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY02TETRIS5_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy02Tetris5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy02Tetris5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32771, &CMy02Tetris5Dlg::OnStartGame)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_32772, &CMy02Tetris5Dlg::OnStopGame)
	ON_COMMAND(ID_32773, &CMy02Tetris5Dlg::OnEndGame)
END_MESSAGE_MAP()


// CMy02Tetris5Dlg 消息处理程序

BOOL CMy02Tetris5Dlg::OnInitDialog()
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
	HBITMAP hbmp = (HBITMAP)LoadImage(NULL, TEXT("./res/tiles.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if (hbmp == NULL) {
		MessageBox(TEXT("加载图片失败"));
	}
	m_block.Attach(hbmp);
	m_block.GetBitmap(&m_bmBlock);

	m_iSize = 9;// 方块大小
	// 设置随机种子
	srand((unsigned int)time(NULL));

	color = rand() % 8;// 随机一种方块颜色
	int n = rand() % 7;// 随机7中方块种的一种
	for (int i = 0; i < 4; i++) {
		a[i].x = figures[n][i] % 2;
		a[i].y = figures[n][i] / 2;
	}
	// 初始化画布
	memset(canvas, 0, sizeof(canvas));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy02Tetris5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy02Tetris5Dlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CDC* pDC = GetDC();

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	memDC.SelectObject(m_block);

	for (int i = 0; i < 4; i++) {
		pDC->StretchBlt(
			a[i].x * m_iSize, a[i].y * m_iSize, m_iSize, m_iSize,
			&memDC,
			color * m_iSize, 0, m_iSize, m_iSize,
			SRCCOPY);
	}
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			int k = canvas[i][j];
			if (k > 0) {
				pDC->StretchBlt(
					j * m_iSize, i * m_iSize, m_iSize, m_iSize,
					&memDC,
					k * m_iSize, 0, m_iSize, m_iSize,
					SRCCOPY);
			}
		}
	}

	memDC.DeleteDC();

	ReleaseDC(pDC);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy02Tetris5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMy02Tetris5Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint b[4];
	dx = 0;
	rotate = false;
	if (nChar == 'W') {// 上 旋转
		rotate = true;
	}
	if (nChar == 'D') {// 右
		dx = 1;
	}
	if (nChar == 'S') {// 下
	}
	if (nChar == 'A') {// 左
		dx = -1;
	}
	for (int i = 0; i < 4; i++) {
		b[i] = a[i];
		a[i].x += dx;
	}
	if (!Check()) {
		for (int i = 0; i < 4; i++) {
			a[i] = b[i];
		}
	}
	if (rotate) {
		CPoint p = a[1];
		for (int i = 0; i < 4; i++) {
			b[i] = a[i];
			int x = a[i].y - p.y;
			int y = a[i].x - p.x;
			a[i].x = p.x - x;
			a[i].y = p.y + y;
		}
		if (!Check()) {
			for (int i = 0; i < 4; i++) {
				a[i] = b[i];
			}
		}
	}
	Invalidate(TRUE);
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMy02Tetris5Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint b[4];
	switch (nIDEvent) {
	case 1:
	{
		// 下落
		for (int i = 0; i < 4; i++) {
			b[i] = a[i];
			a[i].y += 1;
		}
		if (!Check()) {
			for (int i = 0; i < 4; i++) {
				canvas[b[i].y][b[i].x] = color;
			}
			// 重新随机方块颜色
			color = rand() % 8;
			// 重新随机方块种类
			int n = rand() % 7;
			for (int i = 0; i < 4; i++) {
				a[i].x = figures[n][i] % 2;
				a[i].y = figures[n][i] / 2;
			}
		}
		Invalidate(TRUE);
		// 消去满行
		int k = H - 1;
		for (int i = H - 1; i >= 0; i--) {
			int cnt = 0;
			// 统计一行的方块数量
			for (int j = 0; j < W; j++) {
				if (canvas[i][j] > 0) {
					cnt++;
				}
				canvas[k][j] = canvas[i][j];
			}
			if (cnt < W) {
				k--;
			}
		}
		Invalidate(TRUE);
		break;
	}
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CMy02Tetris5Dlg::OnStartGame()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(1, 300, NULL);
}


void CMy02Tetris5Dlg::OnStopGame()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(1);
}


void CMy02Tetris5Dlg::OnEndGame()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(1);
}

bool CMy02Tetris5Dlg::Check() {
	for (int i = 0; i < 4; i++) {
		if (a[i].x < 0 || W <= a[i].x || a[i].y < 0 || H <= a[i].y) {
			return false;
		}
		if (canvas[a[i].y][a[i].x] > 0) {
			return false;
		}
	}
	return true;
}