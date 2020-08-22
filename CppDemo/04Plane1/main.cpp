
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define H 26//游戏画面尺寸
#define W 40
#define EnemyNum 15//敌机数量

//画布
int canvas[H][W] = { 0 };
//0.输出空格
//1.输出飞机
//2.输出子弹
//3.输出敌机
char symbol[] = " *|@";

struct Point {
	int x, y;
};

Point player;//飞机坐标位置
Point enemy[EnemyNum];//敌机坐标
int score = 0;//游戏得分
// 定时器，敌机下落速度
int timer = 0, delay = 10;

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

	player.x = H / 2;//飞机坐标位置
	player.y = W / 2;
	canvas[player.x][player.y] = 1;

	// 初始化，随机敌机位置。
	for (int i = 0; i < EnemyNum; i++) {
		enemy[i].x = rand() % 3;
		enemy[i].y = rand() % W;
	}
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
			if (canvas[i][j] == 2) {
				canvas[i][j] = 0;
				if (i == 0) {
					continue;
				}
				bool flag = true;
				//子弹击中敌机
				for (k = 0; k < EnemyNum; k++) {
					if (i-1 == enemy[k].x && j == enemy[k].y) {// 子弹命中敌机
						score++;// 加分
						canvas[enemy[k].x][enemy[k].y] = 0;// 删除敌机
						enemy[k].x = 0;
						enemy[k].y = rand() % W;
						canvas[enemy[k].x][enemy[k].y] = 3;
						flag = false;// 子弹击中敌机，消除子弹。
					}
				}
				if (flag) {
					canvas[i - 1][j] = 2;
				}
			}
		}
	}

	timer++;
	if(timer > delay){
		timer = 0;
		//敌机下落
		for (k = 0; k < EnemyNum; k++) {
			canvas[enemy[k].x][enemy[k].y] = 0;
			enemy[k].x++;
			if (enemy[k].x >= H) {
				enemy[k].x = 0;
				enemy[k].y = rand() % W;
				score--;
			}
			canvas[enemy[k].x][enemy[k].y] = 3;
		}
	}
}
//与用户输入有关的更新
void updateWithInput() {
	if (GetAsyncKeyState('A') & 0x8000 && player.y - 1 >= 0) { // a 左移
		canvas[player.x][player.y] = 0;
		player.y--;
		canvas[player.x][player.y] = 1;
	}
	if (GetAsyncKeyState('D') & 0x8000 && player.y + 1 < W) { // d 右移
		canvas[player.x][player.y] = 0;
		player.y++;
		canvas[player.x][player.y] = 1;
	}
	if (GetAsyncKeyState('W') & 0x8000 && player.x - 1 >= 0) { // w 上移
		canvas[player.x][player.y] = 0;
		player.x--;
		canvas[player.x][player.y] = 1;
	}
	if (GetAsyncKeyState('S') & 0x8000 && player.x + 1 < H) { // s 下移
		canvas[player.x][player.y] = 0;
		player.x++;
		canvas[player.x][player.y] = 1;
	}
	if (GetAsyncKeyState(' ') & 0x8000) { // 空格 发射子弹
		canvas[player.x - 1][player.y] = 2;
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