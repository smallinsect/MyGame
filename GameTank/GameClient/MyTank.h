#pragma once
class MyTank
{
public:
	void Init();
	void SetDire(int dire);//����̹�˷���
	void Move();//̹���ƶ�
	void Draw(Graphics* graphics);//��̹��
private:
	int m_dire; // ̹�˷���
	int m_frame; // ̹��֡��
	int m_widht; // ̹��ÿ��ͼƬ���
	int m_height;// ̹��ÿ��ͼƬ�߶�
	int m_speed; //̹���ƶ��ٶ�
	CPoint m_pos; // ̹������
	Image* m_tank[4][2];//̹��ͼƬ
};

