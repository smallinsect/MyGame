#pragma once
class CMyBullet
{
private:
	bool m_bState;//�ӵ�״̬

	int m_iDirect; // �ӵ�����

	int m_iSpeedX; // �ӵ��ٶ�
	int m_iSpeedY;

	int m_iPosX; // �ӵ�����
	int m_iPosY;

	CBitmap m_cbBullet[4]; // �ӵ�ͼƬ
	BITMAP m_bmBullet[4];  // �ӵ�ͼƬ��С

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
	void Init();//��ʼ��
	void Update();//����
	void Draw(CDC *pDC);
};

