#pragma once
class CMyBullet
{
private:
	bool m_bState;//子弹状态

	CPoint m_speed;//坦克速度
	CPoint m_pos;//坦克坐标
	CMyDirect m_direct;//坦克方向

	CBitmap m_cbBullet[4]; // 子弹图片
	BITMAP m_bmBullet[4];  // 子弹图片大小

	CDC m_dc;
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
	void SetState(bool bState) {
		m_bState = bState;
	}
	bool GetState() {
		return m_bState;
	}
	void Init();//初始化
	void Update();//更新
	void Draw(CDC *pDC);
};

