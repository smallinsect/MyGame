#include <graphics.h>//����EasyXͼ�ο�
#include <conio.h>

int main() {
	initgraph(640, 256);//��ʼ��640*480�Ļ���

	for (int y = 0; y < 200; y += 5) {
		if (y / 5 % 2 == 1) {//�ж��Ƿ�Ϊ��ż��
			setcolor(RGB(255, 0, 0));
		}
		else {
			setcolor(RGB(0, 0, 255));
		}
		line(0, y, 640, y);
	}

	_getch();//�����������
	closegraph();//�ر�ͼ�ν���
	return 0;
}