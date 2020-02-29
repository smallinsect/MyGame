#include "stdafx.h"
#include "CGame.h"


CGame::CGame()
{


}


CGame::~CGame()
{
}


void CGame::SetHandle(HWND hWnd) {
	m_hWnd = hWnd;
}
bool CGame::EnterFrame(DWORD dwTime) {
	GameRunDraw();
	return false;
}
void CGame::OnMouseMove(UINT nFlags, CPoint point) {

}
void CGame::OnLButtonUp(UINT nFlags, CPoint point) {

}

void CGame::GameRunDraw() {
	HDC hdc = ::GetDC(m_hWnd);
	CRect rc;
	GetClientRect(m_hWnd, &rc);

	CDC *dc = CClientDC::FromHandle(hdc);

	CDC m_dcMemory;
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
	m_dcMemory.CreateCompatibleDC(dc);

	CBitmap* pOldBitmap = m_dcMemory.SelectObject(&bmp);

	Graphics gh(m_dcMemory.GetSafeHdc());
	gh.Clear(Color::White);
}
void CGame::DrawFps(Graphics &gh) {
}