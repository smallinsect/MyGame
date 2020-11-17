#include "pch.h"
#include "MyTank.h"


void MyTank::Init() {
	CString path;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			path.Format(TEXT("./res/image/0Player/m0-%d-%d.gif"), i, j+1);
			m_tank[i][j] = Image::FromFile(path);
			if (m_tank[i][j]->GetLastStatus() != Ok) {
				AfxMessageBox(TEXT("打开图片失败..."));
				return;
			}
		}
	}
	m_widht = m_tank[0][0]->GetWidth();
	m_height = m_tank[0][0]->GetHeight();
	m_dire = TANK_UP;
	m_pos.x = m_pos.y = 0;
	m_frame = 0;
	m_speed = 1;
}
//设置坦克方向
void MyTank::SetDire(int dire) {
	m_dire = dire;
}
//坦克移动
void MyTank::Move() {
	switch (m_dire) {
	case TANK_LEFT:
		m_pos.x -= m_speed;
		break;
	case TANK_UP:
		m_pos.y -= m_speed;
		break;
	case TANK_RIGHT:
		m_pos.x += m_speed;
		break;
	case TANK_DOWN:
		m_pos.y += m_speed;
		break;
	}
	m_frame ^= 1;
}
//画坦克
void MyTank::Draw(Graphics* graphics) {
	graphics->DrawImage(m_tank[m_dire][m_frame], m_pos.x, m_pos.y, m_widht * 2, m_height * 2);
}