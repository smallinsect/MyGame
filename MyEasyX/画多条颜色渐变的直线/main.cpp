#include <graphics.h>//����EasyXͼ�ο�
#include <conio.h>

int main() {
	initgraph(640, 256);//��ʼ��640*480�Ļ���
	
	for (int y = 0; y < 256; y++) {
		setcolor(RGB(0, 0, y));
		line(0, y, 640, y);
	}

	_getch();//�����������
	closegraph();//�ر�ͼ�ν���
	return 0;
}