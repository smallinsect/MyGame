#pragma once
class MyPlayerTank{
private:
	int m_iLevel;//坦克等级
	int m_iDirect;//坦克方向
	int m_iCurFrame;//当前帧

	int m_iSpeedX;//坦克速度
	int m_iSpeedY;//坦克速度

	int m_iPosX;// 坦克坐标
	int m_iPosY;

	CBitmap m_tank[4][2];//玩家坦克位图 4个方向 每个方向2张贴图
	BITMAP m_bm[4][2];//获取位图大小
	CDC m_dc;//内存兼容DC


public:
	enum DIREC {
		M_Down = 3, M_Left = 0, M_Right = 2, M_Up = 1
	};

	int GetPosX() {
		return m_iPosX;
	}
	int GetPosY() {
		return m_iPosY;
	}
	void SetSpeedX(int iSpeedX) {
		m_iSpeedX = iSpeedX;
	}
	void SetSpeedY(int iSpeedY) {
		m_iSpeedY = iSpeedY;
	}
	void SetDirect(DIREC iDirect) {
		m_iDirect = iDirect;
	}
	int GetDirection() {
		return m_iDirect;
	}

	void Init();
	void Update();
	void Draw(CDC *pDC, int x, int y);
};

