#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>

#pragma comment(lib, "Winmm.lib")

const int M = 20;
const int N = 10;

int field[M][N] = {0};

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

//全局变量
IMAGE tiles;//方块
IMAGE background;//背景
IMAGE frame;//

int dx = 0;
bool rotate = 0;
int colorNum = 1;
float timer = 0, delay = 0.3;

bool check() {
	for (int i = 0; i < 4; i++) {
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) {
			return false;
		}
		else if (field[a[i].y][a[i].x]) {
			return false;
		}
	}

	return true;
}

//数据初始化
void startup() {
	srand((unsigned int)time(NULL));
	initgraph(320, 480);

	loadimage(&tiles, _T("./image/tiles.png"));//读取图片到img_bk中
	//putimage(0, 0, &tiles);//在坐标(0, 0)位置显示IMAGE
	// 坐标(0, 0)，宽度(18, 18)，image中的坐标(0,0)
	//putimage(0, 0, 18, 18, &tiles, 0, 0);

	int n = rand() % 7;
	for (int i = 0; i < 4; i++) {
		a[i].x = figures[n][i] % 2;
		a[i].y = figures[n][i] / 2;
	}
	for (int i = 0; i < 4; i++) {
		putimage(a[i].x * 18, a[i].y * 18, 18, 18, &tiles, 0, 0);
	}

	BeginBatchDraw();
}
//显示画面
void show() {
	for (int i = 0; i < 4; i++) {
		putimage(a[i].x * 18, a[i].y * 18, 18, 18, &tiles, 0, 0);
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (field[i][j] == 0) {
				continue;
			}
			putimage(j * 18, i * 18, 18, 18, &tiles, 0, 0);
		}
	}

	FlushBatchDraw();
}
//于用户输入无关的更新
void updateWithoutInput() {
	static clock_t sstart = 0;
	clock_t cur = clock();
	if (cur - sstart > 300) {
		sstart = cur;
		for (int i = 0; i < 4; i++) {
			b[i] = a[i];
			a[i].y += 1;
		}
		if (!check()) {
			for (int i = 0; i < 4; i++) {
				field[b[i].y][b[i].x] = 1;
			}
			int n = rand() % 7;
			for (int i = 0; i < 4; i++) {
				a[i].x = figures[n][i] % 2;
				a[i].y = figures[n][i] / 2;
			}
		}
	}

	//// <- Move -> ///
	for (int i = 0; i < 4; i++) {
		b[i] = a[i];
		a[i].x += dx;
	}
	if (!check()) {
		for (int i = 0; i < 4; i++) {
			a[i] = b[i];
		}
	}

	//////Rotate//////
	if (rotate){
		Point p = a[1]; //center of rotation
		for (int i = 0; i < 4; i++){
			int x = a[i].y - p.y;
			int y = a[i].x - p.x;
			a[i].x = p.x - x;
			a[i].y = p.y + y;
		}
		if (!check()) {
			for (int i = 0; i < 4; i++) {
				a[i] = b[i];
			}
		}
	}
}
//与用户输入有关的更新
void updateWithInput() {
	if (GetAsyncKeyState(VK_UP) & 0x8000) {//上
		rotate = true;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {//下
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {//左
		dx = -1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {//右
		dx = 1;
	}
}

void clean() {
	for (int i = 0; i < 4; i++) {
		clearrectangle(a[i].x * 18, a[i].y * 18, a[i].x * 18 + 18, a[i].y * 18 + 18);
	}
	//clearrectangle(x, y, x + 32, y + 32);

	//FlushBatchDraw();
	dx = 0;
	rotate = 0;
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
