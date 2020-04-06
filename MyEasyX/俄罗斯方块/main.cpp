
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#pragma comment(lib, "Winmm.lib")

#define High 20//��Ϸ����ߴ�
#define Width 10
#define EnemyNum 5//�л�����

//ȫ�ֱ���
int field[High][Width] = { 0 };

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
	srand((unsigned int)time(NULL));//�����������
	HideCursor();//���ع��

	int i, j, n;
	n = rand() % 7;
	for (i = 0; i < 4; i++)
	{
		a[i].x = figures[n][i] % 2;
		a[i].y = figures[n][i] / 2;
	}

	score = 0;
}
//��ʾ����
void show() {
	int i, j;
	//system("cls");//����
	gotoxy(0, 0);//����ƶ������Ͻǣ��ػ�ͼƬ

	for (i = 0; i < High; i++) {
		for (j = 0; j < Width; j++) {
			if (field[i][j] == 1) {
				printf("*");//�������
			}
			else {
				printf(" ");//���
			}
		}
		printf("#\n");//����ұ�ǽ
	}
	// ����±�ǽ
	for (j = 0; j < Width; j++) {
		printf("#");
	}
	printf("#\n");
	printf("�÷֣�%d\n", score);
}
//���û������޹صĸ���
void updateWithoutInput() {
	//int i, j, k;
	////�ӵ�����
	//for (i = 0; i < High; i++) {
	//	for (j = 0; j < Width; j++) {
	//		if (canvas[i][j] == 2) {
	//			//�ӵ����ел�
	//			for (k = 0; k < EnemyNum; k++) {
	//				if (i == enemy_x[k] && j == enemy_y[k]) {
	//					score++;

	//					canvas[enemy_x[k]][enemy_y[k]] = 0;
	//					enemy_x[k] = 0;
	//					enemy_y[k] = rand() % Width;
	//					canvas[enemy_x[k]][enemy_y[k]] = 3;
	//				}
	//			}

	//			canvas[i][j] = 0;
	//			if (i > 0) {
	//				canvas[i - 1][j] = 2;
	//			}
	//		}
	//	}
	//}

	//for (k = 0; k < EnemyNum; k++) {
	//	if (enemy_x[k] + 1 >= High) {
	//		canvas[enemy_x[k]][enemy_y[k]] = 0;
	//		enemy_x[k] = 0;
	//		enemy_y[k] = rand() % Width;
	//		canvas[enemy_x[k]][enemy_y[k]] = 3;
	//		score--;
	//	}
	//}
	//static int speed = 0;
	//if (speed < 10) {
	//	speed++;
	//}
	//else {
	//	for (k = 0; k < EnemyNum; k++) {
	//		//�л�����
	//		canvas[enemy_x[k]][enemy_y[k]] = 0;
	//		enemy_x[k]++;
	//		canvas[enemy_x[k]][enemy_y[k]] = 3;
	//		speed = 0;
	//	}
	//}
}
//���û������йصĸ���
void updateWithInput() {
	//if (GetAsyncKeyState(0x41) & 0x8000 && position_y - 1 >= 0) { // a ����
	//	canvas[position_x][position_y] = 0;
	//	position_y--;
	//	canvas[position_x][position_y] = 1;
	//}
	//if (GetAsyncKeyState(0x44) & 0x8000 && position_y + 1 < Width) { // d ����
	//	canvas[position_x][position_y] = 0;
	//	position_y++;
	//	canvas[position_x][position_y] = 1;
	//}
	//if (GetAsyncKeyState(0x57) & 0x8000 && position_x - 1 >= 0) { // w ����
	//	canvas[position_x][position_y] = 0;
	//	position_x--;
	//	canvas[position_x][position_y] = 1;
	//}
	//if (GetAsyncKeyState(0x53) & 0x8000 && position_x + 1 < High) { // s ����
	//	canvas[position_x][position_y] = 0;
	//	position_x++;
	//	canvas[position_x][position_y] = 1;
	//}
	//if (GetAsyncKeyState(' ') & 0x8000) { // �ո� �����ӵ�
	//	canvas[position_x - 1][position_y] = 2;
	//}
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