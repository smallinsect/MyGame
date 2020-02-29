﻿
// GameTanke.h: GameTanke 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CGameTankeApp:
// 有关此类的实现，请参阅 GameTanke.cpp
//

class CGameTankeApp : public CWinApp
{
public:
	CGameTankeApp() noexcept;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	ULONG_PTR m_tokenGdiplus;
	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartupOutput output;
};

extern CGameTankeApp theApp;
