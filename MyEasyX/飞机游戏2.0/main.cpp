#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>

#pragma comment(lib, "Winmm.lib")

const int W = 1200;
const int H = 800;

float angle, thrust;

IMAGE img_bg;

//���ݳ�ʼ��
void startup() {
	srand((unsigned int)time(NULL));
	initgraph(W, H);

	loadimage(&img_bg, _T("./images/background.jpg"), W, H);

	putimage(0, 0, &img_bg);
	BeginBatchDraw();
}
//��ʾ����
void show() {

	FlushBatchDraw();
}
//���û������޹صĸ���
void updateWithoutInput() {

}
//���û������йصĸ���
void updateWithInput() {
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {//��
		angle += 3;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {//��
		angle -= 3;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) {//��
		thrust = true;
	}
	else {
		thrust = false;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {//��
	}
}

void clean() {


	//FlushBatchDraw();
}

//��Ϸ��������������
void gameover() {
	EndBatchDraw();
	_getch();
	closegraph();
}

int main() {
	startup();//���ݳ�ʼ��
	while (1) {//��Ϸѭ��ִ��
		show();//��ʾ����
		clean();//���
		updateWithInput();//���û������йصĸ���
		updateWithoutInput();//���û������޹صĸ���
	}
	gameover();//��Ϸ��������������
	return 0;
}
