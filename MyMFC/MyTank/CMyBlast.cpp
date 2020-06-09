#include "pch.h"
#include "CMyBlast.h"


void CMyBlast::Init() {
	m_bState = false;

	m_iCurFrame = 0;
	m_iFrame = 5;
	m_pos.x = m_pos.y = 0;

	TCHAR name[64];
	HBITMAP hBmp;
	for (int i = 0; i < m_iFrame; i++) {
		swprintf(name, TEXT("./res/img/blast/%d.bmp"), i);
		hBmp = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		if (hBmp == NULL) {
			AfxMessageBox(TEXT("¼ÓÔØÎ»Í¼Ê§°Ü"));
			return;
		}
		m_cb[i].Attach(hBmp);
		m_cb[i].GetBitmap(&m_bm[i]);
	}

}
void CMyBlast::Update() {
	m_iCurFrame = (m_iCurFrame + 1) % m_iFrame;
}

void CMyBlast::Draw(CDC* pDC) {
	m_dc.CreateCompatibleDC(pDC);
	m_dc.SelectObject(m_cb[m_iCurFrame]);

	pDC->TransparentBlt(m_pos.x, m_pos.y,
		m_bm[m_iCurFrame].bmWidth, m_bm[m_iCurFrame].bmHeight,
		&m_dc,
		0, 0,
		m_bm[m_iCurFrame].bmWidth, m_bm[m_iCurFrame].bmHeight,
		RGB(0, 0, 0));

	m_dc.DeleteDC();
}