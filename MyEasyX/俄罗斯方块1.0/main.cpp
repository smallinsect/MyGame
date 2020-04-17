#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>

#pragma comment(lib, "Winmm.lib")

const int M = 20;
const int N = 10;

int field[M][N] = {0};

struct Point
{
	int x, y;
} a[4], b[4];

int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

//ȫ�ֱ���
IMAGE tiles;//����
IMAGE background;//����
IMAGE frame;//

int dx = 0;
bool rotate = 0;
int colorNum = 1;

//���ݳ�ʼ��
void startup() {
	srand((unsigned int)time(NULL));
	initgraph(320, 480);

	loadimage(&tiles, _T("./image/tiles.png"));//��ȡͼƬ��img_bk��
	//putimage(0, 0, &tiles);//������(0, 0)λ����ʾIMAGE
	// ����(0, 0)�����(18, 18)��image�е�����(0,0)
	//putimage(0, 0, 18, 18, &tiles, 0, 0);

	int n = 2;
	for (int i = 0; i < 4; i++) {
		a[i].x = figures[n][i] % 2;
		a[i].y = figures[n][i] / 2;
	}
	for (int i = 0; i < 4; i++) {
		putimage(a[i].x * 18, a[i].y * 18, 18, 18, &tiles, 0, 0);
	}

	BeginBatchDraw();
}
//��ʾ����
void show() {
	for (int i = 0; i < 4; i++) {
		putimage(a[i].x * 18, a[i].y * 18, 18, 18, &tiles, 0, 0);
	}


	FlushBatchDraw();
	Sleep(50);
}
//���û������޹صĸ���
void updateWithoutInput() {
	//// <- Move -> ///
	for (int i = 0; i < 4; i++) {
		a[i].x += dx;
	}

	//////Rotate//////
	if (rotate){
		Point p = a[1]; //center of rotation
		for (int i = 0; i < 4; i++){
			int x = a[i].y - p.y;
			int y = a[i].x - p.x;
			a[i].x = p.x - x;
			a[i].y = p.y + y;
		}
	}
}
//���û������йصĸ���
void updateWithInput() {
	if (GetAsyncKeyState(VK_UP) & 0x8000) {//��
		rotate = true;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {//��
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {//��
		dx = -1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {//��
		dx = 1;
	}
}

void clean() {

	dx = 0;
	rotate = 0;
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
