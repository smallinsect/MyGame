
// GameClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "GameClient.h"
#include "GameClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMER_TANK_MOVE 1

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


// CGameClientDlg 对话框



CGameClientDlg::CGameClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAMECLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGameClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_START, &CGameClientDlg::OnStart)
	ON_WM_TIMER()
	ON_COMMAND(ID_STOP, &CGameClientDlg::OnStop)
	ON_COMMAND(ID_END, &CGameClientDlg::OnEnd)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CGameClientDlg 消息处理程序

BOOL CGameClientDlg::OnInitDialog()
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
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	graphics = Graphics::FromHWND(m_hWnd);
	if (graphics->GetLastStatus() != Ok) {
		AfxMessageBox(TEXT("GDI+失败..."));
		return FALSE;
	}
	// 初始化玩家坦克
	player.Init();
	// 初始化背景颜色
	m_bg = Color(0, 0, 0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGameClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGameClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGameClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGameClientDlg::Draw() {
	graphics->Clear(m_bg);
	
	player.Draw(graphics);
}

void CGameClientDlg::OnStart()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(TIMER_TANK_MOVE, 30, NULL);
}

void CGameClientDlg::OnStop()
{
	// TODO: 在此添加命令处理程序代码
	KillTimer(TIMER_TANK_MOVE);
}


void CGameClientDlg::OnEnd()
{
	// TODO: 在此添加命令处理程序代码
}


void CGameClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent) {
	case TIMER_TANK_MOVE:
		player.Move();
		Draw();
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}



void CGameClientDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar) {
	case 'W'://上
		player.SetDire(TANK_UP);
		player.Move();
		break;
	case 'S'://下
		player.SetDire(TANK_DOWN);
		player.Move();
		break;
	case 'A'://左
		player.SetDire(TANK_LEFT);
		player.Move();
		break;
	case 'D'://右
		player.SetDire(TANK_RIGHT);
		player.Move();
		break;
	}
	Draw();
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
