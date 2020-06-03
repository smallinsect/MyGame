#pragma once
class CMyBullet
{
private:
	bool m_bState;//子弹状态

	int m_iDirect; // 子弹方向

	int m_iSpeedX; // 子弹速度
	int m_iSpeedY;

	int m_iPosX; // 子弹坐标
	int m_iPosY;

	CBitmap m_cbBullet[4]; // 子弹图片
	BITMAP m_bmBullet[4];  // 子弹图片大小

	CDC m_dc;
public:
	void SetPos(int iPosX, int iPosY) {
		m_iPosX = iPosX;
		m_iPosY = iPosY;
	}
	void SetSpeed(int iSpeedX, int iSpeedY) {
		m_iSpeedX = iSpeedX;
		m_iSpeedY = iSpeedY;
	}
	void SetDirect(int iDirect) {
		m_iDirect = iDirect;
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

