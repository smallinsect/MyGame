#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#pragma comment(lib, "Winmm.lib")

#define High 7//��Ϸ����ߴ�
#define Width 20

int frame[High][Width];
int pos[10] = { 0, 4, 8, 12 };// ��ʾ���ֵ�λ��

int num[12][7][4] = {
	{
		{0, 1, 1, 0}, // 0
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{0, 0, 0, 0},
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{0, 1, 1, 0},
	},{
		{0, 0, 0, 0}, // 1
		{0, 0, 0, 1},
		{0, 0, 0, 1},
		{0, 0, 0, 0},
		{0, 0, 0, 1},
		{0, 0, 0, 1},
		{0, 0, 0, 0},
	},{
		{0, 1, 1, 0},// 2
		{0, 0, 0, 1},
		{0, 0, 0, 1},
		{0, 1, 1, 0},
		{1, 0, 0, 0},
		{1, 0, 0, 0},
		{0, 1, 1, 0},
	},{
		{0, 1, 1, 0},// 3
		{0, 0, 0, 1},
		{0, 0, 0, 1},
		{0, 1, 1, 0},
		{0, 0, 0, 1},
		{0, 0, 0, 1},
		{0, 1, 1, 0},
	},{
		{0, 0, 0, 0},// 4
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{0, 1, 1, 0},
		{0, 0, 0, 1},
		{0, 0, 0, 1},
		{0, 0, 0, 0},
	},{
		{0, 1, 1, 0},// 5
		{1, 0, 0, 0},
		{1, 0, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 1},
		{0, 0, 0, 1},
		{0, 1, 1, 0},
	},{
		{0, 1, 1, 0},// 6
		{1, 0, 0, 0},
		{1, 0, 0, 0},
		{0, 1, 1, 0},
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{0, 1, 1, 0},
	},{
		{0, 1, 1, 0},// 7
		{0, 0, 0, 1},
		{0, 0, 0, 1},
		{0, 0, 0, 0},
		{0, 0, 0, 1},
		{0, 0, 0, 1},
		{0, 0, 0, 0},
	},{
		{0, 1, 1, 0},// 8
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{0, 1, 1, 0},
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{0, 1, 1, 0},
	},{
		{0, 1, 1, 0},// 9
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{0, 1, 1, 0},
		{0, 0, 0, 1},
		{0, 0, 0, 1},
		{0, 1, 1, 0},
	},{
		{0, 0, 0, 0},// -
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	},{
		{0, 0, 0, 0},// :
		{0, 1, 1, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0},
		{0, 1, 1, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0},
	},
};

//ȫ�ֱ���
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

}
//��ʾ����
void show() {
	int i, j;
	//system("cls");//����
	gotoxy(0, 0);//����ƶ������Ͻǣ��ػ�ͼƬ

	for (i = 0; i < High; i++) {
		for (j = 0; j < Width; j++) {
			if (frame[i][j] == 1) {
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
}
//���û������޹صĸ���
void updateWithoutInput() {
	static int k = 0;

	int i, j, p;
	for (p = 0; p < 16; p += 4) {
		for (i = 0; i < 7; i++) {
			for (j = 0; j < 4; j++) {
				frame[i][j + p] = num[k][i][j];
			}
		}
	}

	k++;
	if (k >= 12) {
		k = 0;
	}
	Sleep(500);
}
//���û������йصĸ���
void updateWithInput() {
	SYSTEMTIME st;
	//��ȡ��ǰϵͳʱ��
	GetLocalTime(&st);
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