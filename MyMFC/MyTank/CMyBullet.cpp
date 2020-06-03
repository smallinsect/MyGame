#include "pch.h"
#include "CMyBullet.h"


void CMyBullet::Init() {//初始化
	TCHAR name[64];
	HBITMAP hBmp;
	for (int i = 0; i < 4; i++) {
		swprintf(name, TEXT("./res/img/bullet-%d.bmp"), i);
		hBmp = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		if (hBmp == NULL) {
			AfxMessageBox(TEXT("加载位图失败"));
			return;
		}
		m_cbBullet[i].Attach(hBmp);// 绑定位图
		m_cbBullet[i].GetBitmap(&m_bmBullet[i]);// 获取位图大小
	}

	m_iDirect = 0;
	m_bState = false;

	m_iPosX = 0;
	m_iPosY = 0;
}
void CMyBullet::Update() {//更新
	if (m_iDirect == 0) {// 左
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