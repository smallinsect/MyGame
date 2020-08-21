
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define H 26//游戏画面尺寸
#define W 40
#define EnemyNum 5//敌机数量

//画布
int canvas[H][W] = { 0 };
//0.输出空格
//1.输出飞机
//2.输出子弹
//3.输出敌机
char symbol[] = " *|@";


int position_x, position_y;//飞机坐标位置
int hero_x[2], hero_y[2];// 飞机的附机
int enemy_x[EnemyNum], enemy_y[EnemyNum];//敌机坐标
int score;//游戏得分

void gotoxy(SHORT x, SHORT y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {x, y};
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

	position_x = H / 2;//飞机坐标位置
	position_y = W / 2;

	hero_x[0] = position_x;// 左附机
	hero_y[0] = position_y - 1;

	canvas[position_x][position_y] = 1;
	canvas[hero_x[0]][hero_y[0]] = 4;
	canvas[hero_x[1]][hero_y[1]] = 4;

	int i;
	// 初始化，随机敌机位置。
	for (i = 0; i < EnemyNum; i++) {
		enemy_x[i] = rand() % 3;
		enemy_y[i] = rand() % W;
	}
	// 初始化分数
	score = 0;
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
	printf("飞机得分 %d\n", score);
}
//与用户输入无关的更新
void updateWithoutInput() {
	int i, j, k;
	//子弹上跑
	for (i = 0; i < H; i++) {
		for (j = 0; j < W; j++) {
			if (canvas[i][j] == 2 || canvas[i][j] == 5) {
				int bullet = canvas[i][j];
				//子弹击中敌机
				for (k = 0; k < EnemyNum; k++) {
					if (i == enemy_x[k] && j == enemy_y[k]) {
						score++;

						canvas[enemy_x[k]][enemy_y[k]] = 0;
						enemy_x[k] = 0;
						enemy_y[k] = rand() % W;
						canvas[enemy_x[k]][enemy_y[k]] = 3;
					}
				}

				canvas[i][j] = 0;
				if (i > 0) {
					canvas[i - 1][j] = bullet;
				}
			}
		}
	}

	for (k = 0; k < EnemyNum; k++) {
		if (enemy_x[k] + 1 >= H) {
			canvas[enemy_x[k]][enemy_y[k]] = 0;
			enemy_x[k] = 0;
			enemy_y[k] = rand() % W;
			canvas[enemy_x[k]][enemy_y[k]] = 3;
			score--;
		}
	}
	static int speed = 0;
	if (speed < 10) {
		speed++;
	}
	else {
		speed = 0;
		for (k = 0; k < EnemyNum; k++) {
			//敌机下落
			canvas[enemy_x[k]][enemy_y[k]] = 0;
			enemy_x[k]++;
			canvas[enemy_x[k]][enemy_y[k]] = 3;
		}
	}
}
//与用户输入有关的更新
void updateWithInput() {
	if (GetAsyncKeyState(0x41) & 0x8000 && position_y - 1 >= 0) { // a 左移
		canvas[hero_x[0]][hero_y[0]] = 0;
		canvas[hero_x[1]][hero_y[1]] = 0;
		canvas[position_x][position_y] = 0;

		position_y--;
		hero_x[0] = position_x;// 左附机
		hero_y[0] = position_y - 1;

		hero_x[1] = position_x;// 右附机
		hero_y[1] = position_y + 1;

		canvas[position_x][position_y] = 1;
		canvas[hero_x[0]][hero_y[0]] = 4;
		canvas[hero_x[1]][hero_y[1]] = 4;
	}
	if (GetAsyncKeyState(0x44) & 0x8000 && position_y + 1 < W) { // d 右移
		canvas[hero_x[0]][hero_y[0]] = 0;
		canvas[hero_x[1]][hero_y[1]] = 0;
		canvas[position_x][position_y] = 0;

		position_y++;
		hero_x[0] = position_x;// 左附机
		hero_y[0] = position_y - 1;

		hero_x[1] = position_x;// 右附机
		hero_y[1] = position_y + 1;

		canvas[position_x][position_y] = 1;
		canvas[hero_x[0]][hero_y[0]] = 4;
		canvas[hero_x[1]][hero_y[1]] = 4;
	}
	if (GetAsyncKeyState(0x57) & 0x8000 && position_x - 1 >= 0) { // w 上移
		canvas[hero_x[0]][hero_y[0]] = 0;
		canvas[hero_x[1]][hero_y[1]] = 0;
		canvas[position_x][position_y] = 0;

		position_x--;
		hero_x[0] = position_x;// 左附
		hero_y[0] = position_y - 1;

		hero_x[1] = position_x;// 右附机
		hero_y[1] = position_y + 1;

		canvas[position_x][position_y] = 1;
		canvas[hero_x[0]][hero_y[0]] = 4;
		canvas[hero_x[1]][hero_y[1]] = 4;
	}
	if (GetAsyncKeyState(0x53) & 0x8000 && position_x + 1 < H) { // s 下移
		canvas[hero_x[0]][hero_y[0]] = 0;
		canvas[hero_x[1]][hero_y[1]] = 0;
		canvas[position_x][position_y] = 0;

		position_x++;
		hero_x[0] = position_x;// 左附机
		hero_y[0] = position_y - 1;

		hero_x[1] = position_x;// 右附机
		hero_y[1] = position_y + 1;

		canvas[position_x][position_y] = 1;
		canvas[hero_x[0]][hero_y[0]] = 4;
		canvas[hero_x[1]][hero_y[1]] = 4;
	}
	if (GetAsyncKeyState(' ') & 0x8000) { // 空格 发射子弹
		canvas[position_x - 1][position_y] = 2;
		canvas[hero_x[0] - 1][hero_y[0]] = 2;
		canvas[hero_x[1] - 1][hero_y[1]] = 2;
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