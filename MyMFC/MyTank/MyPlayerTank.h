#pragma once
class MyPlayerTank{
private:
	int m_iLevel;//̹�˵ȼ�
	int m_iDirect;//̹�˷���

	int m_iSpeed;//̹���ٶ�

	CBitmap m_tank[4][2];//���̹��λͼ 4������ ÿ������2����ͼ
	BITMAP m_bm[4][2];//��ȡλͼ��С
	CDC m_dc;//�ڴ����DC


public:
	void Init();
	void Draw(CDC *pDC);
};

