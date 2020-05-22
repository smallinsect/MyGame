#pragma once




class CMyRole{
private:
	CBitmap m_role;//角色位图
	BITMAP m_bm;//获取图片的大小
	HBITMAP m_hBmp;          //位图
	int m_iPerFrameWidth,    //每帧位图的宽
		m_iPerFrameHeight;   //每帧位图的高
	int m_iPosX, m_iPosY;    //位置
	int m_iSpeedX, m_iSpeedY;//速度
	int m_iFrameNum;         //帧数
	int m_iCurFrame;         //绘制的当前帧
	// Up-0 Down-1 Left-2 Right-3
	int m_iDirection;        //移动方向

public:
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
	void SetDirection(int iDirection) {
		m_iDirection = iDirection;
	}
	void Init(LPTSTR name, int iPerFrameWidth, int iPerFrameHeight, int iFrameNum, int iPosX = 0, int iPosY = 0);
	void Update();
	void Draw(HDC hDc, int x, int y);
};

