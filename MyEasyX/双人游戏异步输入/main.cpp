#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h>

#pragma comment(lib, "Winmm.lib")

#define Wight 480
#define High 480

//全局变量
int ball1_x, ball1_y;//玩家1坐标位置
int ball2_x, ball2_y;//玩家2坐标位置
int step;// 步长

//数据初始化
void startup() {
	srand((unsigned int)time(NULL));
	initgraph(Wight, High);

	ball1_x = 100;
	ball1_y = 100;//玩家1坐标位置
	ball2_x = 200;
	ball2_y = 200;//玩家2坐标位置

	step = 5;

	BeginBatchDraw();
}
// 清除画面
void clean() {
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(ball1_x, ball1_y, 10);
	fillcircle(ball2_x, ball2_y, 10);
}
//显示画面
void show() {

	setcolor(GREEN);
	setfillcolor(GREEN);
	fillcircle(ball1_x, ball1_y, 10);

	setcolor(RED);
	setfillcolor(RED);
	fillcircle(ball2_x, ball2_y, 10);

	FlushBatchDraw();
	Sleep(3);
}
//用于用户输入无关的更新
void updateWithoutInput() {
}
//与用户输入有关的更新
void updateWithInput() {

	if (GetAsyncKeyState(0x41) & 0x8000) { // a
		ball1_x -= step;
	}
	if (GetAsyncKeyState(0x44) & 0x8000) { // d
		ball1_x += step;
	}
	if (GetAsyncKeyState(0x57) & 0x8000) { // w
		ball1_y -= step;
	}
	if (GetAsyncKeyState(0x53) & 0x8000) { // s
		ball1_y += step;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // ←
		ball2_x -= step;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { // →
		ball2_x += step;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) { // ↑
		ball2_y -= step;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { // ↓
		ball2_y += step;
	}
}
//游戏结束、后续处理
void gameover() {
	EndBatchDraw();
	closegraph();
}

int main() {
	startup();//数据初始化
	while (1) {//游戏循环执行
		show();//显示画面

		clean();
		updateWithoutInput();//于用户输入无关的更新
		updateWithInput();//与用户输入有关的更新
	}
	gameover();//游戏结束、后续处理
	return 0;
}
