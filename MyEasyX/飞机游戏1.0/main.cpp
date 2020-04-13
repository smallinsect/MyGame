
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#pragma comment(lib, "Winmm.lib")

#define High 20//游戏画面尺寸
#define Width 50
#define EnemyNum 5//敌机数量

//全局变量
int canvas[High][Width] = { 0 };
//二维数组记录游戏
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
	srand((unsigned int)time(NULL));//设置随机种子
	HideCursor();//隐藏光标

	position_x = High / 2;//飞机坐标位置
	position_y = Width / 2;

	canvas[position_x][position_y] = 1;

	int i;
	// 初始化，随机敌机位置。
	for (i = 0; i < EnemyNum; i++) {
		enemy_x[i] = rand() % 3;
		enemy_y[i] = rand() % Width;
	}
	// 初始化分数
	score = 0;

	//循环播放音乐
	mciSendString(TEXT("open ./music/bgmusic.mp3 alias bkmusic"), NULL, 0, NULL);//背景音乐
	mciSendString(TEXT("play bkmusic repeat"), NULL, 0, NULL);//循环播放
}
//显示画面
void show() {
	int i, j;
	//system("cls");//清屏
	gotoxy(0, 0);//光标移动到左上角，重画图片

	for (i = 0; i < High; i++) {
		for (j = 0; j < Width; j++) {
			if (canvas[i][j] == 1) {
				printf("*");//输出飞机*
			}
			else if (canvas[i][j] == 2) {
				printf("|");//输出输出子弹|
			}
			else if (canvas[i][j] == 3) {
				printf("@");//输出输出子弹@
			}
			else {
				printf(" ");//输出
			}
		}
		printf("#\n");//输出右边墙
	}
	// 输出下边墙
	for (j = 0; j < Width; j++) {
		printf("#");
	}
	printf("#\n");
	printf("飞机得分 %d\n", score);
}
//与用户输入无关的更新
void updateWithoutInput() {
	int i, j, k;
	//子弹上跑
	for (i = 0; i < High; i++) {
		for (j = 0; j < Width; j++) {
			if (canvas[i][j] == 2) {
				//子弹击中敌机
				for (k = 0; k < EnemyNum; k++) {
					if (i == enemy_x[k] && j == enemy_y[k]) {
						score++;

						canvas[enemy_x[k]][enemy_y[k]] = 0;
						enemy_x[k] = 0;
						enemy_y[k] = rand() % Width;
						canvas[enemy_x[k]][enemy_y[k]] = 3;
					}
				}

				canvas[i][j] = 0;
				if (i > 0) {
					canvas[i - 1][j] = 2;
				}
			}
		}
	}

	for (k = 0; k < EnemyNum; k++) {
		if (enemy_x[k] + 1 >= High) {
			canvas[enemy_x[k]][enemy_y[k]] = 0;
			enemy_x[k] = 0;
			enemy_y[k] = rand() % Width;
			canvas[enemy_x[k]][enemy_y[k]] = 3;
			score--;
		}
	}
	static int speed = 0;
	if (speed < 10) {
		speed++;
	}
	else {
		for (k = 0; k < EnemyNum; k++) {
			//敌机下落
			canvas[enemy_x[k]][enemy_y[k]] = 0;
			enemy_x[k]++;
			canvas[enemy_x[k]][enemy_y[k]] = 3;
			speed = 0;
		}
	}
}
//与用户输入有关的更新
void updateWithInput() {
	if (GetAsyncKeyState(0x41) & 0x8000 && position_y - 1 >= 0) { // a 左移
		canvas[position_x][position_y] = 0;
		position_y--;
		canvas[position_x][position_y] = 1;
	}
	if (GetAsyncKeyState(0x44) & 0x8000 && position_y + 1 < Width) { // d 右移
		canvas[position_x][position_y] = 0;
		position_y++;
		canvas[position_x][position_y] = 1;
	}
	if (GetAsyncKeyState(0x57) & 0x8000 && position_x - 1 >= 0) { // w 上移
		canvas[position_x][position_y] = 0;
		position_x--;
		canvas[position_x][position_y] = 1;
	}
	if (GetAsyncKeyState(0x53) & 0x8000 && position_x + 1 < High) { // s 下移
		canvas[position_x][position_y] = 0;
		position_x++;
		canvas[position_x][position_y] = 1;
	}
	if (GetAsyncKeyState(' ') & 0x8000) { // 空格 发射子弹
		canvas[position_x - 1][position_y] = 2;

		TCHAR szStatus[80];
		//mciSendString(TEXT("status NOWMUSIC position"), szStatus, 80, 0);
		mciSendString(TEXT("status bullet mode"), szStatus, 80, 0);

		if (lstrcmp(szStatus, TEXT("")) == 0 ||
			lstrcmp(szStatus, TEXT("stopped")) == 0
			)
		{
			mciSendString(TEXT("close bullet"), NULL, 0, NULL);//先把之前的音乐关了
			mciSendString(TEXT("open ./music/bullet.mp3 alias bullet"), NULL, 0, NULL);//打开音乐
			mciSendString(TEXT("play bullet"), NULL, 0, NULL);//仅播放一次
		}
		//mciSendString(TEXT("close bullet"), NULL, 0, NULL);//先把之前的音乐关了
		//mciSendString(TEXT("open ./music/bullet.mp3 alias bullet"), NULL, 0, NULL);//打开音乐
		//mciSendString(TEXT("play bullet"), NULL, 0, NULL);//仅播放一次
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