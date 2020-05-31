#pragma once
class MyPlayerTank{
private:
	int m_iLevel;//坦克等级
	int m_iDirect;//坦克方向

	int m_iSpeed;//坦克速度

	CBitmap m_tank[4][2];//玩家坦克位图 4个方向 每个方向2张贴图
	BITMAP m_bm[4][2];//获取位图大小
	CDC m_dc;//内存兼容DC


public:
	void Init();
	void Draw(CDC *pDC);
};

