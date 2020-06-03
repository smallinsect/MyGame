#pragma once
class MyPlayerTank{
private:
	int m_iLevel;//̹�˵ȼ�
	int m_iDirect;//̹�˷���
	int m_iCurFrame;//��ǰ֡

	int m_iSpeedX;//̹���ٶ�
	int m_iSpeedY;//̹���ٶ�

	int m_iPosX;// ̹������
	int m_iPosY;

	CBitmap m_tank[4][2];//���̹��λͼ 4������ ÿ������2����ͼ
	BITMAP m_bm[4][2];//��ȡλͼ��С
	CDC m_dc;//�ڴ����DC


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

