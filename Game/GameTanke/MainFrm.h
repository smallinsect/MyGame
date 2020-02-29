
// MainFrm.h: CMainFrame 类的接口
//

#pragma once

#include "CGame.h"

class CMainFrame : public CFrameWnd
{
	
public: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:

// 实现
public:
	virtual ~CMainFrame();

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

	int m_iWith{ 800 };
	int m_iHeight{ 600 };

	enum ETitmerId {ETimerIdGameLoop = 1};
	CGame m_game;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


