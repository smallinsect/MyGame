#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

//全局变量
int bird_x, bird_y;//小鸟坐标位置
int bird_vx, bird_vy;//小鸟速度
int high, width;//游戏屏幕大小
int bar1_xTop, bar1_xDown, bar1_y;
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
//显示画面
void show() {
	int i, j;
	//system("cls");//清屏
	gotoxy(0, 0);//光标移动到左上角，重画图片

	for (i = 0; i < high; i++) {
		for (j = 0; j < width; j++) {
			if (i == bird_x && j == bird_y) {
				printf("@");//输出小鸟@
			}
			else if (j == bar1_y && (i <= bar1_xTop || i >= bar1_xDown)) {
				printf("*");//输出挡板
			}
			//else if (i == enemy_x && j == enemy_y) {
			//	printf("@");//输出敌机@
			//}
			else {
				printf(" ");//输出
			}
		}
		printf("*\n");
	}
	for (j = 0; j < width; j++) {
		printf("*");
	}
	printf("\n");
	printf("小鸟反弹次数 %d\n", score);
}
//于用户输入无关的更新
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
//与用户输入有关的更新
void updateWithInput() {
	char input;
	if (_kbhit()) {//当按键执行
		input = _getch();
		if (input == ' ') {
			bird_x += -2*bird_vx;
		}
	}
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