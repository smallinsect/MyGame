
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#pragma comment(lib, "Winmm.lib")

#define High 20//游戏画面尺寸
#define Width 10
#define EnemyNum 5//敌机数量

//全局变量
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

int score;//游戏得分

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

	int i, j, n;
	n = rand() % 7;
	for (i = 0; i < 4; i++)
	{
		a[i].x = figures[n][i] % 2;
		a[i].y = figures[n][i] / 2;
	}

	score = 0;
}
//显示画面
void show() {
	int i, j;
	//system("cls");//清屏
	gotoxy(0, 0);//光标移动到左上角，重画图片

	for (i = 0; i < High; i++) {
		for (j = 0; j < Width; j++) {
			if (field[i][j] == 1) {
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
	printf("得分：%d\n", score);
}
//与用户输入无关的更新
void updateWithoutInput() {
	//int i, j, k;
	////子弹上跑
	//for (i = 0; i < High; i++) {
	//	for (j = 0; j < Width; j++) {
	//		if (canvas[i][j] == 2) {
	//			//子弹击中敌机
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
	//		//敌机下落
	//		canvas[enemy_x[k]][enemy_y[k]] = 0;
	//		enemy_x[k]++;
	//		canvas[enemy_x[k]][enemy_y[k]] = 3;
	//		speed = 0;
	//	}
	//}
}
//与用户输入有关的更新
void updateWithInput() {
	//if (GetAsyncKeyState(0x41) & 0x8000 && position_y - 1 >= 0) { // a 左移
	//	canvas[position_x][position_y] = 0;
	//	position_y--;
	//	canvas[position_x][position_y] = 1;
	//}
	//if (GetAsyncKeyState(0x44) & 0x8000 && position_y + 1 < Width) { // d 右移
	//	canvas[position_x][position_y] = 0;
	//	position_y++;
	//	canvas[position_x][position_y] = 1;
	//}
	//if (GetAsyncKeyState(0x57) & 0x8000 && position_x - 1 >= 0) { // w 上移
	//	canvas[position_x][position_y] = 0;
	//	position_x--;
	//	canvas[position_x][position_y] = 1;
	//}
	//if (GetAsyncKeyState(0x53) & 0x8000 && position_x + 1 < High) { // s 下移
	//	canvas[position_x][position_y] = 0;
	//	position_x++;
	//	canvas[position_x][position_y] = 1;
	//}
	//if (GetAsyncKeyState(' ') & 0x8000) { // 空格 发射子弹
	//	canvas[position_x - 1][position_y] = 2;
	//}
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