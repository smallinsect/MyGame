#include "pch.h"
#include "CMyRole.h"

void CMyRole::Init(LPTSTR name, int iPerFrameWidth, int iPerFrameHeight, int iFrameNum, int iPosX, int iPosY) {
	HBITMAP hbmp = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if (hbmp == NULL) {
		AfxMessageBox(TEXT("¼ÓÔØÎ»Í¼Ê§°Ü"));
		return;
	}
	m_role.Attach(hbmp);
	m_role.GetBitmap(&m_bm);

	m_iCurFrame = 0;
	m_iDirection = CMyDirect::M_Down;

	m_iFrameNum = iFrameNum;
}
void CMyRole::Update() {
	m_iCurFrame = (m_iCurFrame + 1) % m_iFrameNum;
}
void CMyRole::Draw(CDC* pDC, int x, int y) {
	m_dc.CreateCompatibleDC(pDC);//´´½¨»º´æDC
	m_dc.SelectObject(m_role);//»º´æDC°ó¶¨Ì¹¿ËÍ¼Æ¬

	pDC->StretchBlt(x, y,
		m_bm.bmWidth / m_iFrameNum, m_bm.bmHeight / m_iFrameNum,
		&m_dc,
		m_iCurFrame * 32, m_iDirection * 32,
		m_bm.bmWidth / m_iFrameNum, m_bm.bmHeight / m_iFrameNum,
		SRCCOPY);

	m_dc.DeleteDC();
}