#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#define High 20//游戏画面尺寸
#define Width 50
#define EnemyNum 5//敌机数量

//全局变量
int canvas[High][Width] = { 0 };//二维数组记录游戏
							//0 输出空格，1输出飞机
							//2输出子弹
							//3输出敌机


int position_x, position_y;//飞机坐标位置
int enemy_x[EnemyNum], enemy_y[EnemyNum];//敌机坐标
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

	int i, j;
	for (i = 0; i < High; i++) {
		canvas[i][0] = -1;
		canvas[i][Width -1 ] = -1;
	}
	for (j = 0; j < Width; j++) {
		canvas[0][j] = -1;
		canvas[High - 1][j] = -1;
	}

	//canvas[High / 2][Width / 2] = 1;
	for (i = 0; i < 4; i++) {
		canvas[High / 2][Width / 2 - i] = i + 1;
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
			if (canvas[i][j] == -1) {
				printf("#");//输出墙#
			}
			else if (canvas[i][j] == 1) {
				printf("@");//输出蛇头@
			}
			else if (canvas[i][j] > 1) {
				printf("*");//输出蛇身*
			}
			else {
				printf(" ");//输出
			}
		}
		printf("\n");
	}
	printf("飞机得分 %d\n", score);
}
//于用户输入无关的更新
void updateWithoutInput() {
	int i, j, k;
	//子弹上跑
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

	//Sleep(30);
}
//与用户输入有关的更新
void updateWithInput() {
	char input;
	if (_kbhit()) {//当按键执行
		input = _getch();
		if (input == 'w' && position_x - 1 >= 0) {
			canvas[position_x][position_y] = 0;
			position_x--;
			canvas[position_x][position_y] = 1;
		}
		if (input == 's' && position_x + 1 < High) {
			canvas[position_x][position_y] = 0;
			position_x++;
			canvas[position_x][position_y] = 1;
		}
		if (input == 'a' && position_y - 1 >= 0) {
			canvas[position_x][position_y] = 0;
			position_y--;
			canvas[position_x][position_y] = 1;
		}
		if (input == 'd' && position_y + 1 < Width) {
			canvas[position_x][position_y] = 0;
			position_y++;
			canvas[position_x][position_y] = 1;
		}
		if (input == ' ') {
			canvas[position_x - 1][position_y] = 2;
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