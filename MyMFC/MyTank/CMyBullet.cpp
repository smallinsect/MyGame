#include "pch.h"
#include "CMyBullet.h"


void CMyBullet::Init() {//��ʼ��
	TCHAR name[64];
	HBITMAP hBmp;
	for (int i = 0; i < 4; i++) {
		swprintf(name, TEXT("./res/img/bullet-%d.bmp"), i);
		hBmp = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		if (hBmp == NULL) {
			AfxMessageBox(TEXT("����λͼʧ��"));
			return;
		}
		m_cbBullet[i].Attach(hBmp);// ��λͼ
		m_cbBullet[i].GetBitmap(&m_bmBullet[i]);// ��ȡλͼ��С
	}

	m_iDirect = 0;
	m_bState = false;

	m_iPosX = 0;
	m_iPosY = 0;
}
void CMyBullet::Update() {//����
	if (m_iDirect == 0) {// ��
		m_iPosX -= m_iSpeedX;
	}
	if (m_iDirect == 1) {
		m_iPosY -= m_iSpeedY;
	}
	if (m_iDirect == 2) {
		m_iPosX += m_iSpeedX;
	}
	if (m_iDirect == 3) {
		m_iPosY += m_iSpeedY;
	}
}
void CMyBullet::Draw(CDC* pDC) {
	m_dc.CreateCompatibleDC(pDC);
	m_dc.SelectObject(m_cbBullet[m_iDirect]);

	pDC->StretchBlt(m_iPosX, m_iPosY,
		m_bmBullet[m_iDirect].bmWidth, m_bmBullet[m_iDirect].bmHeight,
		&m_dc,
		0, 0,
		m_bmBullet[m_iDirect].bmWidth, m_bmBullet[m_iDirect].bmHeight,
		SRCCOPY);

	m_dc.DeleteDC();
}