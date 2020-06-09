#include "pch.h"
#include "CMyEnemy.h"


void CMyEnemy::Init() {
	TCHAR name[64];
	HBITMAP hBmp;
	for (int i = 0; i < 4; i++) {
		swprintf(name, TEXT("./res/img/gray-tank/1-%d-%d.bmp"), i+1, 1);
		hBmp = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		if (hBmp == NULL) {
			AfxMessageBox(TEXT("¼ÓÔØÎ»Í¼Ê§°Ü"));
			return;
		}
		m_tank[i][0].Attach(hBmp);
		m_tank[i][0].GetBitmap(&m_bm[i][0]);

		swprintf(name, TEXT("./res/img/gray-tank/1-%d-%d.bmp"), i+1, 2);
		hBmp = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		if (hBmp == NULL) {
			AfxMessageBox(TEXT("¼ÓÔØÎ»Í¼Ê§°Ü"));
			return;
		}

		m_tank[i][1].Attach(hBmp);
		m_tank[i][1].GetBitmap(&m_bm[i][1]);
	}

	m_iLevel = 0;
	m_iCurFrame = 0;

	m_direct = CMyDirect::M_Down;
	m_speed.x = m_speed.y = 10;
	m_pos.x = m_pos.y = 0;
}
void CMyEnemy::Update() {
	m_iCurFrame = (m_iCurFrame + 1) % 2;

	switch (m_direct) {
	case CMyDirect::M_Down:
		m_pos.y += m_speed.y;
		break;
	case CMyDirect::M_Left:
		m_pos.x -= m_speed.x;
		break;
	case CMyDirect::M_Right:
		m_pos.x += m_speed.x;
		break;
	case CMyDirect::M_Up:
		m_pos.y -= m_speed.y;
		break;
	}
}
void CMyEnemy::Draw(CDC* pDC) {
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	memDC.SelectObject(m_tank[m_direct][m_iCurFrame]);

	BITMAP tbm = m_bm[m_direct][m_iCurFrame];
	pDC->TransparentBlt(m_pos.x, m_pos.y,
		tbm.bmWidth, tbm.bmHeight,
		&memDC,
		0, 0,
		tbm.bmWidth, tbm.bmHeight, 
		RGB(0, 0, 0));

	memDC.DeleteDC();
}