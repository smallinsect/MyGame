#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

//ȫ�ֱ���
int bird_x, bird_y;//С������λ��
int bird_vx, bird_vy;//С���ٶ�
int high, width;//��Ϸ��Ļ��С
int bar1_xTop, bar1_xDown, bar1_y;
int score;//��Ϸ�÷�

void gotoxy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//���ع��
void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };//�ڶ���ֵΪ0,��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//���ݳ�ʼ��
void startup() {
	srand((unsigned int)time(NULL));
	HideCursor();

	high = 18;
	width = 30;

	bird_x = high / 2;
	bird_y = 3;

	bird_vx = 1;
	bird_vy = 0;

	bar1_xTop = rand() % high;
	bar1_xDown = rand() % high;
	bar1_y = width / 2;

	score = 0;
}
//��ʾ����
void show() {
	int i, j;
	//system("cls");//����
	gotoxy(0, 0);//����ƶ������Ͻǣ��ػ�ͼƬ

	for (i = 0; i < high; i++) {
		for (j = 0; j < width; j++) {
			if (i == bird_x && j == bird_y) {
				printf("@");//���С��@
			}
			else if (j == bar1_y && (i <= bar1_xTop || i >= bar1_xDown)) {
				printf("*");//�������
			}
			//else if (i == enemy_x && j == enemy_y) {
			//	printf("@");//����л�@
			//}
			else {
				printf(" ");//���
			}
		}
		printf("*\n");
	}
	for (j = 0; j < width; j++) {
		printf("*");
	}
	printf("\n");
	printf("С�񷴵����� %d\n", score);
}
//���û������޹صĸ���
void updateWithoutInput() {

	bird_x += bird_vx;
	bird_y += bird_vy;

	bar1_y--;
	if (bar1_y < 0) {
		bar1_xTop = rand() % (high / 4);
		bar1_xDown = rand() % (high / 2) + (high / 2);
		bar1_y = width / 2;
	}

	Sleep(100);
}
//���û������йصĸ���
void updateWithInput() {
	char input;
	if (_kbhit()) {//������ִ��
		input = _getch();
		if (input == ' ') {
			bird_x += -2*bird_vx;
		}
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