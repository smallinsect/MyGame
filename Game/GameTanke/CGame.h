#pragma once
#include "stdafx.h"



class CGame
{
public:
	CGame();
	~CGame();

	void SetHandle(HWND hWnd);
	bool EnterFrame(DWORD dwTime);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);

private:
	HWND m_hWnd;//���ھ��

	void GameRunDraw();
	void DrawFps(Graphics &gh);

	int m_fps{0};
};

