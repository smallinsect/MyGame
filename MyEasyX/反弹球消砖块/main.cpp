#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

//全局变量
int ball_x, ball_y;//小球坐标位置
int ball_vx, ball_vy;//小球x方向的速度和y方向的速度
int bullet_x, bullet_y;//子弹坐标
int position_x, position_y;//挡板坐标
int raduis;//挡板半径
int high, width;//游戏的画面尺寸
int enemy_x, enemy_y;//敌机的坐标
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

	ball_x = high / 2;
	ball_y = width / 2;

	ball_vx = 1;
	ball_vy = 1;

	raduis = 5;
	position_x = high - 1;
	position_y = (width - 5) / 2;

	score = 0;
}
//显示画面
void show() {
	int i, j;
	//system("cls");//清屏
	gotoxy(0, 0);//光标移动到左上角，重画图片

	for (i = 0; i < high; i++) {
		for (j = 0; j < width; j++) {
			if (i == ball_x && j == ball_y) {
				printf("O");//输出小球O
			}
			else if (i == position_x && (position_y <= j && j <= position_y + raduis)) {
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
	printf("小球反弹次数 %d\n", score);
}
//于用户输入无关的更新
void updateWithoutInput() {
	if (ball_x + 1 == position_x) {
		if (position_y <= ball_y && ball_y <= position_y+raduis) {
			score ++;
			ball_vy = -ball_vy;
		}
	}

	ball_x += ball_vx;
	ball_y += ball_vy;

	if (ball_x + ball_vx < 0 || high <= ball_x + ball_vx) {
		ball_vx = -ball_vx;
	}
	if (ball_y + ball_vy < 0 || width <= ball_y + ball_vy) {
		ball_vy = -ball_vy;
	}
	Sleep(50);
}
//与用户输入有关的更新
void updateWithInput() {
	char input;
	if (_kbhit()) {//当按键执行
		input = _getch();
		if (input == 'w' && position_x - 1 >= 0) {
			position_x--;
		}
		if (input == 's' && position_x + 1 < high) {
			position_x++;
		}
		if (input == 'a' && position_y - 1 >= 0) {
			position_y--;
		}
		if (input == 'd' && position_y + 1 < width) {
			position_y++;
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