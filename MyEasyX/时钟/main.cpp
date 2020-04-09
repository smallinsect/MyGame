#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#pragma comment(lib, "Winmm.lib")

#define High 20//游戏画面尺寸
#define Width 60

int frame[High][Width];
//int pos[10] = { 0, 4, 8, 12 };// 显示数字的位置
char strTime[64];// 字符串时间
char symbol[20] = "0123456789-: ";

int num[13][7][4] = {
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
	},{
		{0, 0, 0, 0},// ' '
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	},
};

int Idx(char ch) {
	for (int i = 0; symbol[i] != '\0'; i++) {
		if (ch == symbol[i]) {
			return i;
		}
	}
	return -1;
}

//全局变量
void gotoxy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//隐藏光标
void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };//第二个值为0,表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//数据初始化
void startup() {
	srand((unsigned int)time(NULL));//设置随机种子
	HideCursor();//隐藏光标

}
//显示画面
void show() {
	int i, j;
	//system("cls");//清屏
	gotoxy(0, 0);//光标移动到左上角，重画图片

	for (i = 0; i < High; i++) {
		for (j = 0; j < Width; j++) {
			if (frame[i][j] == 1) {
				printf("*");//输出方块
			}
			else {
				printf(" ");//输出
			}
		}
		printf("#\n");//输出右边墙
	}
	// 输出下边墙
	for (j = 0; j < Width; j++) {
		printf("#");
	}
	printf("#\n");
}
//与用户输入无关的更新
void updateWithoutInput() {
	SYSTEMTIME st;
	//获取当前系统时间
	GetLocalTime(&st);
	//sprintf(strTime, "%4d - %02d - %02d %02d : %02d : %02d",
	//	st.wYear, st.wMonth, st.wDay,
	//	st.wHour, st.wMinute, st.wSecond);
	sprintf(strTime, "%02d:%02d:%02d",
		st.wHour, st.wMinute, st.wSecond);

	for (int pos = 0; strTime[pos] != '\0'; pos++) {
		int idx = Idx(strTime[pos]);
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 4; j++) {
				frame[i][j + pos * 4 + 1] = num[idx][i][j];
			}
		}
	}

	Sleep(500);
}
//与用户输入有关的更新
void updateWithInput() {
}

int main() {
	startup();//数据初始化
	while (1) {//游戏循环执行
		show();//显示画面
		updateWithoutInput();//于用户输入无关的更新
		updateWithInput();//与用户输入有关的更新
	}

	return 0;
}