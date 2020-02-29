
// MainFrm.cpp: CMainFrame 类的实现
//

#include "stdafx.h"
#include "GameTanke.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()

#define GAME_WIN_W (800)
#define GAME_WIN_H (600)

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
#define MY_STYLE (WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|FWS_ADDTOTITLE)
	// TODO: 在此添加成员初始化代码
	//创建窗口
	Create(NULL, _T("坦克大战"), MY_STYLE, CRect(0, 0, GAME_WIN_W, GAME_WIN_H));
	//设置客户区大小
	{
		CRect rcCli;
		GetClientRect(rcCli);//获取客户区大小
		RECT rcFrame = {0, 0,//计算边框的大小，并设置
			m_iWith + m_iWith - rcCli.right,
			m_iHeight + m_iHeight - rcCli.bottom
		};
		MoveWindow(&rcFrame, TRUE);//调整windowsAPI设置窗口位置和大小
	}
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	SetTimer(ETimerIdGameLoop, 0, NULL);
	m_game.SetHandle(GetSafeHwnd());
	return 0;
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent) {
	switch (nIDEvent) {
	case ETimerIdGameLoop:
		static DWORD dwLastUpate = GetTickCount();
		if (GetTickCount() - dwLastUpate >= 20) {
			dwLastUpate = GetTickCount();
			m_game.EnterFrame(GetTickCount());
		}
		break;
	default:
		break;
	}
	CFrameWnd::OnTimer(nIDEvent);
}