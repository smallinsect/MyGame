#include <graphics.h>//����EasyXͼ�ο�
#include <conio.h>

int main() {
	initgraph(640, 480);//��ʼ��640*480�Ļ���
	setcolor(YELLOW);//Բ������Ϊ��ɫ
	setfillcolor(GREEN);//Բ�ڲ�Ϊ��ɫ���
	fillcircle(100, 100, 20);//��Բ��Բ�ģ�100,100�����뾶20

	line(0, 0, 300, 300);//��һ����

	circle(111, 222, 30);//��һ��Բ��

	_getch();//�����������
	closegraph();//�ر�ͼ�ν���
	return 0;
}