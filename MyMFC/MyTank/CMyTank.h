#pragma once

class CMyTank{
private:
	int m_iLevel;//坦克等级
	int m_iCurFrame;//当前帧

	CPoint m_speed;//坦克速度
	CPoint m_pos;//坦克坐标
	CMyDirect m_direct;//坦克方向

	CBitmap m_tank[4][2];//玩家坦克位图 4个方向 每个方向2张贴图
	BITMAP m_bm[4][2];//获取位图大小
	CDC m_dc;//内存兼容DC
public:
	CPoint GetPos() {
		return m_pos;
	}
	void SetPos(CPoint pos) {
		m_pos = pos;
	}

	void SetDirect(CMyDirect direct) {
		m_direct = direct;
	}
	CMyDirect GetDirection() {
		return m_direct;
	}

	void Init();
	void Update();
	void Draw(CDC* pDC);
};


