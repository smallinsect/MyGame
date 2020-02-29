
// DesktopCover.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

// CDesktopCoverApp:
// 有关此类的实现，请参阅 DesktopCover.cpp
//

class CDesktopCoverApp : public CWinApp
{
public:
	CDesktopCoverApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()


private:
	ULONG_PTR m_tokenGdiplus;
	Gdiplus::GdiplusStartupInput m_input;
	Gdiplus::GdiplusStartupOutput m_output;
};

extern CDesktopCoverApp theApp;
