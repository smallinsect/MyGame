#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h>

#pragma comment(lib, "Winmm.lib")

#define Wight 480
#define High 480

//ȫ�ֱ���
int ball1_x, ball1_y;//���1����λ��
int ball2_x, ball2_y;//���2����λ��
int step;// ����

//���ݳ�ʼ��
void startup() {
	srand((unsigned int)time(NULL));
	initgraph(Wight, High);

	ball1_x = 100;
	ball1_y = 100;//���1����λ��
	ball2_x = 200;
	ball2_y = 200;//���2����λ��

	step = 5;

	BeginBatchDraw();
}
// �������
void clean() {
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(ball1_x, ball1_y, 10);
	fillcircle(ball2_x, ball2_y, 10);
}
//��ʾ����
void show() {

	setcolor(GREEN);
	setfillcolor(GREEN);
	fillcircle(ball1_x, ball1_y, 10);

	setcolor(RED);
	setfillcolor(RED);
	fillcircle(ball2_x, ball2_y, 10);

	FlushBatchDraw();
	Sleep(3);
}
//�����û������޹صĸ���
void updateWithoutInput() {
}
//���û������йصĸ���
void updateWithInput() {

	if (GetAsyncKeyState(0x41) & 0x8000) { // a
		ball1_x -= step;
	}
	if (GetAsyncKeyState(0x44) & 0x8000) { // d
		ball1_x += step;
	}
	if (GetAsyncKeyState(0x57) & 0x8000) { // w
		ball1_y -= step;
	}
	if (GetAsyncKeyState(0x53) & 0x8000) { // s
		ball1_y += step;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // ��
		ball2_x -= step;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { // ��
		ball2_x += step;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) { // ��
		ball2_y -= step;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { // ��
		ball2_y += step;
	}
}
//��Ϸ��������������
void gameover() {
	EndBatchDraw();
	closegraph();
}

int main() {
	startup();//���ݳ�ʼ��
	while (1) {//��Ϸѭ��ִ��
		show();//��ʾ����

		clean();
		updateWithoutInput();//���û������޹صĸ���
		updateWithInput();//���û������йصĸ���
	}
	gameover();//��Ϸ��������������
	return 0;
}
