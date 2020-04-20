#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>

#pragma comment(lib, "Winmm.lib")

const int W = 1200;
const int H = 800;

float angle, thrust;

IMAGE img_bg;

//数据初始化
void startup() {
	srand((unsigned int)time(NULL));
	initgraph(W, H);

	loadimage(&img_bg, _T("./images/background.jpg"), W, H);

	putimage(0, 0, &img_bg);
	BeginBatchDraw();
}
//显示画面
void show() {

	FlushBatchDraw();
}
//于用户输入无关的更新
void updateWithoutInput() {

}
//与用户输入有关的更新
void updateWithInput() {
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {//右
		angle += 3;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {//左
		angle -= 3;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) {//上
		thrust = true;
	}
	else {
		thrust = false;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {//下
	}
}

void clean() {


	//FlushBatchDraw();
}

//游戏结束、后续处理
void gameover() {
	EndBatchDraw();
	_getch();
	closegraph();
}

int main() {
	startup();//数据初始化
	while (1) {//游戏循环执行
		show();//显示画面
		clean();//清除
		updateWithInput();//与用户输入有关的更新
		updateWithoutInput();//于用户输入无关的更新
	}
	gameover();//游戏结束、后续处理
	return 0;
}
