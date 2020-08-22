
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define H 26//游戏画面尺寸
#define W 40

struct Point {
	int x, y;
};

//画布
int canvas[H][W] = { 0 };

char symbol[] = " O@-";//0.空格 1.小球 2.砖块 3.挡板
Point dir;// 小球方向
Point ball, tball;// 小球坐标

// 定时器
int timer = 0, delay = 2;

void gotoxy(SHORT x, SHORT y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
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
//显示画面
void show() {
	gotoxy(0, 0);//光标移动到左上角，重画图片

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			printf("%c", symbol[canvas[i][j]]);//输出
		}
		printf("#\n");//输出右边墙
	}
	// 输出下边墙
	for (int j = 0; j < W; j++) {
		printf("#");
	}
	printf("#\n");
}
//与用户输入无关的更新
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
//与用户输入有关的更新
void updateWithInput() {
	if (GetAsyncKeyState('A') & 0x8000) { // a 左移
	}
	if (GetAsyncKeyState('W') & 0x8000) { // w 上移
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