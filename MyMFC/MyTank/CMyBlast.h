#pragma once
class CMyBlast{
private:
	CPoint m_pos;// ��ը����

	int m_iCurFrame;// ��ǰ֡��
	int m_iFrame; // �ܹ�֡��

	CBitmap m_cb[5];//��ըλͼ
	BITMAP m_bm[5];//ͼƬ��С

	CDC m_dc;//�ڴ����DC
public:
	CPoint GetPos() {
		return m_pos;
	}
	void SetPos(CPoint pos) {
		m_pos = pos;
	}

	void Init();
	void Update();
	void Draw(CDC *pDC);
};

