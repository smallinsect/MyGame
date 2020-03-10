#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

//全局变量
int position_x, position_y;//飞机坐标位置
int bullet_x, bullet_y;//子弹坐标
int high, width;//游戏的画面尺寸
int enemy_x, enemy_y;//敌机的坐标
int score;//游戏得分

void gotoxy(int x,int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//隐藏光标
void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};//第二个值为0,表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//数据初始化
void startup() {
	srand((unsigned int)time(NULL));
	HideCursor();

	high = 18;
	width = 30;

	position_x = high / 2;
	position_y = width / 2;

	bullet_x = -1;
	bullet_y = position_y;

	enemy_x = 0;
	enemy_y = width / 2;

	score = 0;
}
//显示画面
void show() {
	int i, j;
	//system("cls");//清屏
	gotoxy(0, 0);//光标移动到左上角，重画图片

	for (i = 0; i < high; i++) {
		for (j = 0; j < width; j++) {
			if (i == position_x && j == position_y) {
				printf("*");//输出飞机*
			}
			else if (i == bullet_x && j == bullet_y) {
				printf("|");//输出飞机子弹|
			}
			else if (i == enemy_x && j == enemy_y) {
				printf("@");//输出敌机@
			}
			else {
				printf(" ");//输出
			}
		}
		printf("\n");
	}
	printf("得分 %d\n", score);
}
//于用户输入无关的更新
void updateWithoutInput() {
	if (bullet_x == enemy_x && bullet_y == enemy_y) {
		score++;
		enemy_x = 0;
		enemy_y = rand() % width;
		bullet_x = -1;
	}

	static int speed = 0;//用于控制飞机下落的速度
	if (speed < 10) {
		speed++;
	}
	
	if (bullet_x > -1) {
		bullet_x--;
	}

	if (enemy_x > high) {//重新生成敌机
		enemy_x = 0;
		enemy_y = rand() % width;
	}
	else {
		if (speed == 10) {
			enemy_x++;
			speed = 0;
		}
	}
	//Sleep(150);
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
		if (input == ' ') {
			bullet_x = position_x;
			bullet_y = position_y;
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