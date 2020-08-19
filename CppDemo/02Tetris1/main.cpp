#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

const int W = 10;// 屏幕宽度
const int H = 20;// 屏幕高度
int canvas[H][W];

struct Point {
	int x, y;
} a[4], b[4];

int figures[7][4] = {
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

void gotoxy(SHORT x, SHORT y);
void HideCursor();// 隐藏光标

int main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));// 时间作为随机种子
	HideCursor();//隐藏光标

	memset(canvas, 0, sizeof(canvas));

	int n = rand() % 7;
	for (int i = 0; i < 4; i++) {
		a[i].x = figures[n][i] % 2;
		a[i].y = figures[n][i] / 2;
	}

	int dx = 0;
	bool rotate = false;
	clock_t timer = clock(), delay = 50;
	while (true) {
		clock_t nowTime = clock();

		gotoxy(0, 0);//光标移动到左上角，重画图片
		// 将画布打印在控制台上
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (canvas[i][j] == 1) {// 蛇
					printf("*");
				}
				else {// 空白
					printf(" ");
				}
			}
			printf("|\n");
		}
		for (int i = 0; i < W; i++) {
			printf("-");
		}
		printf("+\n");

		dx = 0;
		rotate = false;
		delay = 100;
		// 检测键盘输入
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 'w') rotate = true;// 上
			if (ch == 'd') dx = 1;// 右
			if (ch == 's') delay = 50;// 下
			if (ch == 'a') dx = -1;// 左
		}

		// 移动
		for (int i = 0; i < 4; i++) {
			canvas[a[i].y][a[i].x] = 0;// 重置原来位置的值
			b[i] = a[i];
			a[i].x += dx;
		}
		// 旋转
		if (rotate) {
			Point p = a[1];
			for (int i = 0; i < 4; i++) {
				canvas[a[i].y][a[i].x] = 0;// 重置原来位置的值
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
		}

		// 定时器
		clock_t subTime = nowTime - timer;
		if (subTime > delay) {
			timer = nowTime;
			// 下落
			for (int i = 0; i < 4; i++) {
				canvas[a[i].y][a[i].x] = 0;// 重置原来位置的值
				b[i] = a[i];
				a[i].y += 1;
			}
		}

		for (int i = 0; i < 4; i++) {
			canvas[a[i].y][a[i].x] = 1;
		}
	}

	return 0;
}


// 设置光标位置
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
