#include "pch.h"
#include "MyPlayerTank.h"


void MyPlayerTank::Init() {
	TCHAR name[64];
	HBITMAP hBmp;
	for (int i = 0; i < 4; i++) {
		swprintf(name, TEXT("./res/img/player0/m3-%d-%d.bmp"), i, 1);
		hBmp = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		if (hBmp == NULL) {
			AfxMessageBox(TEXT("¼ÓÔØÎ»Í¼Ê§°Ü"));
			return;
		}
		m_tank[i][0].Attach(hBmp);
		m_tank[i][0].GetBitmap(&m_bm[i][0]);

		swprintf(name, TEXT("./res/img/player0/m3-%d-%d.bmp"), i, 2);
		hBmp = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		if (hBmp == NULL) {
			AfxMessageBox(TEXT("¼ÓÔØÎ»Í¼Ê§°Ü"));
			return;
		}

		m_tank[i][1].Attach(hBmp);
		m_tank[i][1].GetBitmap(&m_bm[i][1]);
	}

	m_iLevel = 0;
	m_iDirect = M_Down;
	m_iCurFrame = 0;

	m_iSpeedX = 10;
	m_iSpeedY = 10;

	m_iPosX = 0;
	m_iPosY = 0;
}

void MyPlayerTank::Update() {
	m_iCurFrame++;
	m_iCurFrame %= 2;

	switch (m_iDirect) {
	case M_Down:
		m_iPosY += m_iSpeedY;
		break;
	case M_Left:
		m_iPosX -= m_iSpeedX;
		break;
	case M_Right:
		m_iPosX += m_iSpeedX;
		break;
	case M_Up:
		m_iPosY -= m_iSpeedY;
		break;
	}
}

void MyPlayerTank::Draw(CDC* pDC) {
	m_dc.CreateCompatibleDC(pDC);
	m_dc.SelectObject(m_tank[m_iDirect][m_iCurFrame]);

	BITMAP tbm = m_bm[m_iDirect][m_iCurFrame];
	pDC->TransparentBlt(m_iPosX, m_iPosY,
		tbm.bmWidth, tbm.bmHeight,
		&m_dc,
		0, 0,
		tbm.bmWidth, tbm.bmHeight,
		RGB(0, 0, 0));

	m_dc.DeleteDC();
}