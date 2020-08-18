#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

const int W = 40;// 屏幕宽度
const int H = 20;// 屏幕高度
int canvas[H][W];

// 蛇的方向，蛇的长度
int dir = 2, num = 4;
// 蛇的身体坐标
struct Snake {
	int x, y;
} s[100];

struct Food {
	int x, y;
} f;

void Tick();
void gotoxy(SHORT x, SHORT y);
void HideCursor();// 隐藏光标

int main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));// 时间作为随机种子
	HideCursor();//隐藏光标

	memset(canvas, 0, sizeof(canvas));

	f.x = rand() % W;
	f.y = rand() % H;

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
				else if (canvas[i][j] == 2) {// 食物
					printf("@");
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

		// 检测键盘输入
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 'w') dir = 0;// 上
			if (ch == 'd') dir = 1;// 右
			if (ch == 's') dir = 2;// 下
			if (ch == 'a') dir = 3;// 左
		}

		// 定时器
		clock_t subTime = nowTime - timer;
		if (subTime > delay) {
			timer = nowTime;
			Tick();
		}

		// 重置画布
		memset(canvas, 0, sizeof(canvas));
		// 将蛇贴在画布上
		for (int i = 0; i < num; i++) {
			canvas[s[i].y][s[i].x] = 1;
		}
		// 将食物贴在画布上
		canvas[f.y][f.x] = 2;
	}

	return 0;
}

void Tick() {
	for (int i = num; i > 0; i--) {
		s[i] = s[i - 1];
	}
	if (dir == 0) s[0].y -= 1;// 上
	if (dir == 1) s[0].x += 1;// 右
	if (dir == 2) s[0].y += 1;// 下
	if (dir == 3) s[0].x -= 1;// 左
	// 越界处理
	s[0].x = (s[0].x + W) % W;
	s[0].y = (s[0].y + H) % H;
	// 吃食物
	if (s[0].x == f.x && s[0].y == f.y) {
		// 增加蛇的长度
		num++;
		// 随机新的食物坐标
		f.x = rand() % W;
		f.y = rand() % H;
	}
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
