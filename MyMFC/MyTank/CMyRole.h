#pragma once




class CMyRole{

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
	void SetDirection(CMyDirect iDirection) {
		m_iDirection = iDirection;
	}
	void Init(LPTSTR name, int iPerFrameWidth, int iPerFrameHeight, int iFrameNum, int iPosX = 0, int iPosY = 0);
	void Update();
	void Draw(CDC* pDC, int x, int y);
private:
	CBitmap m_role;//��ɫλͼ
	BITMAP m_bm;//��ȡͼƬ�Ĵ�С
	CDC m_dc;//����DC
	HBITMAP m_hBmp;          //λͼ
	int m_iPerFrameWidth,    //ÿ֡λͼ�Ŀ�
		m_iPerFrameHeight;   //ÿ֡λͼ�ĸ�
	int m_iPosX, m_iPosY;    //λ��
	int m_iSpeedX, m_iSpeedY;//�ٶ�
	int m_iFrameNum;         //֡��
	int m_iCurFrame;         //���Ƶĵ�ǰ֡
	// Down-0 Left-1 Right-2 Up-3
	CMyDirect m_iDirection;        //�ƶ�����
};

