#pragma once
class CMyEnemy{
private:
	int m_iLevel;//̹�˵ȼ�
	int m_iCurFrame;//̹�˵�ǰ֡

	CPoint m_speed;//̹���ٶ�
	CPoint m_pos;//̹������
	CMyDirect m_direct;//̹�˷���

	CBitmap m_tank[4][2];//����̹��λͼ 4������ ÿ������2��ͼ
	BITMAP m_bm[4][2];//��ȡλͼ��С

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

	void Init();
	void Update();
	void Draw(CDC* pDC);
};

