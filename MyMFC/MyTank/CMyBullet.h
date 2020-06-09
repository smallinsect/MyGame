#pragma once
class CMyBullet
{
private:
	bool m_bState;//�ӵ�״̬

	CPoint m_speed;//̹���ٶ�
	CPoint m_pos;//̹������
	CMyDirect m_direct;//̹�˷���

	CBitmap m_cbBullet[4]; // �ӵ�ͼƬ
	BITMAP m_bmBullet[4];  // �ӵ�ͼƬ��С

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
	void Init();//��ʼ��
	void Update();//����
	void Draw(CDC *pDC);
};

