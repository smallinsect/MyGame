
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define H 26//��Ϸ����ߴ�
#define W 40

struct Point {
	int x, y;
};

//����
int canvas[H][W] = { 0 };

char symbol[] = " O@-";//0.�ո� 1.С�� 2.ש�� 3.����
Point dir;// С����
Point ball, tball;// С������

// ��ʱ��
int timer = 0, delay = 2;

void gotoxy(SHORT x, SHORT y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(handle, pos);
}

//���ع��
void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };//�ڶ���ֵΪ0,��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//���ݳ�ʼ��
void startup() {
	srand((unsigned int)time(NULL));//�����������
	HideCursor();//���ع��

	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < W - 1; j++) {
			canvas[i][j] = 2;
		}
	}
	dir.x = 2;
	dir.y = -1;
	ball.x = W / 2;
	ball.y = H / 2;
}
//��ʾ����
void show() {
	gotoxy(0, 0);//����ƶ������Ͻǣ��ػ�ͼƬ

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			printf("%c", symbol[canvas[i][j]]);//���
		}
		printf("#\n");//����ұ�ǽ
	}
	// ����±�ǽ
	for (int j = 0; j < W; j++) {
		printf("#");
	}
	printf("#\n");
}
//���û������޹صĸ���
void updateWithoutInput() {

	timer++;
	if (timer > delay) {
		timer = 0;
		tball = ball;
		canvas[ball.y][ball.x] = 0;

		ball.x += dir.x;
		ball.y += dir.y;
		if (ball.x < 0 || W <= ball.x) {
			dir.x = -dir.x;
			ball.x = tball.x + dir.x;
		}
		if (ball.y < 0 || H <= ball.y) {
			dir.y = -dir.y;
			ball.y = tball.y + dir.y;
		}
		canvas[ball.y][ball.x] = 1;
	}
}
//���û������йصĸ���
void updateWithInput() {
	if (GetAsyncKeyState('A') & 0x8000) { // a ����
	}
	if (GetAsyncKeyState('W') & 0x8000) { // w ����
	}
}

int main() {
	startup();//���ݳ�ʼ��
	while (1) {//��Ϸѭ��ִ��
		show();//��ʾ����
		updateWithoutInput();//���û������޹صĸ���
		updateWithInput();//���û������йصĸ���
	}
	return 0;
}