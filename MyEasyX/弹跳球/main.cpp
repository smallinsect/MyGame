#include <graphics.h>//����EasyXͼ�ο�
#include <conio.h>

#define WIDTH 640 //���ڿ��
#define HIGH 480 //���ڸ߶�

int main() {
	//С��뾶
	float radius = 20;
	//С�����꣬��ʼ��
	float ball_x = WIDTH / 2;
	float ball_y = HIGH / 2;
	//С���ٶ�
	float ball_vx = 1;
	float ball_vy = 1;

	initgraph(WIDTH, HIGH);//��ʼ��640*480�Ļ���

	BeginBatchDraw();//��ʼ��������
	while (1) {
		//�ڴ����ϻ�һ��Բ
		setcolor(YELLOW);//Բ������Ϊ��ɫ
		setfillcolor(GREEN);//Բ�ڲ�Ϊ��ɫ���
		fillcircle(ball_x, ball_y, radius);//��Բ��Բ�ģ�100,100�����뾶20

		FlushBatchDraw();//ˢ����������

		Sleep(3);
		//�Ѵ����ϵ�Բ����
		setcolor(BLACK);//Բ������Ϊ��ɫ
		setfillcolor(BLACK);//Բ�ڲ�Ϊ��ɫ���
		fillcircle(ball_x, ball_y, radius);//��Բ��Բ�ģ�100,100�����뾶20

		ball_x += ball_vx;
		ball_y += ball_vy;

		if (ball_x <= radius || ball_x >= WIDTH - radius) {
			ball_vx = -ball_vx;
		}
		if (ball_y <= radius || ball_y >= HIGH - radius) {
			ball_vy = -ball_vy;
		}
	}

	EndBatchDraw();//������������

	_getch();//�����������
	closegraph();//�ر�ͼ�ν���
	return 0;
}