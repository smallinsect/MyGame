#include "pch.h"
#include "CMyBullet.h"


void CMyBullet::Init() {//��ʼ��
	TCHAR name[64];
	HBITMAP hBmp;
	for (int i = 0; i < 4; i++) {
		swprintf(name, TEXT("./res/img/bullet/bullet-%d.bmp"), i);
		hBmp = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		if (hBmp == NULL) {
			AfxMessageBox(TEXT("����λͼʧ��"));
			return;
		}
		m_cbBullet[i].Attach(hBmp);// ��λͼ
		m_cbBullet[i].GetBitmap(&m_bmBullet[i]);// ��ȡλͼ��С
	}

	m_bState = false;

	m_direct = CMyDirect::M_Down;
	m_speed.x = m_speed.y = 10;
	m_pos.x = m_pos.y = 0;
}
void CMyBullet::Update() {//����
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
void CMyBullet::Draw(CDC* pDC) {
	m_dc.CreateCompatibleDC(pDC);
	m_dc.SelectObject(m_cbBullet[m_direct]);

	pDC->StretchBlt(m_pos.x, m_pos.y,
		m_bmBullet[m_direct].bmWidth, m_bmBullet[m_direct].bmHeight,
		&m_dc,
		0, 0,
		m_bmBullet[m_direct].bmWidth, m_bmBullet[m_direct].bmHeight,
		SRCCOPY);

	m_dc.DeleteDC();
}