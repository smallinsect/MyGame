#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>

#pragma comment(lib, "Winmm.lib")

#define Wight 350
#define High 600

//全局变量
IMAGE img_player;// 背景图片
IMAGE img_h1, img_h2;// 英雄图片
IMAGE img_bullet1, img_bullet2;// 子弹图片
IMAGE img_bar_up1, img_bar_up2;
IMAGE img_bar_down1, img_bar_down2;
int x, y;//玩家位置
int left_i, right_i, up_i, down_i;//图片移动位置

//数据初始化
void startup() {
	srand((unsigned int)time(NULL));
	initgraph(Wight, High);

	loadimage(&img_player, _T("./image/player.png"));//读取图片到img_bk中
	//putimage(0, 0, &img_player);//在坐标(0, 0)位置显示IMAGE对象
	//在坐标(0,0)位置显示图片
	putimage(0, 0, 32, 32, &img_player, 0, 0);

	x = Wight / 2;
	y = High / 2; 

	left_i = 0;
	right_i = 0;
	up_i = 0;
	down_i = 0;

	BeginBatchDraw();
}
//显示画面
void show() {

	Sleep(30);
}
//于用户输入无关的更新
void updateWithoutInput() {
	//if (hero_y < 580) {
	//	hero_y += 3;
	//}
}
//与用户输入有关的更新
void updateWithInput() {

	char input;
	if (_kbhit()) {//当按键执行
		input = _getch();
		if (input == 'a') {// 左移
			clearrectangle(x, y, x + 32, y + 32);//清空画面全部矩形区域
			left_i++;
			x -= 10;
			putimage(x, y, 32, 32, &img_player, left_i * 32, 1 * 32);
			FlushBatchDraw();
			Sleep(1);
			if (left_i == 3) {
				left_i = 0;
			}
		}
		else if (input == 'd') {// 右移
			clearrectangle(x, y, x + 32, y + 32);//清空画面全部矩形区域
			right_i++;
			x += 10;
			putimage(x, y, 32, 32, &img_player, right_i * 32, 2 * 32);
			FlushBatchDraw();
			Sleep(1);
			if (right_i == 3) {
				right_i = 0;
			}
		}
		else if (input == 'w') {// 上移
			clearrectangle(x, y, x + 32, y + 32);//清空画面全部矩形区域
			up_i++;
			y -= 10;
			putimage(x, y, 32, 32, &img_player, up_i * 32, 3 * 32);
			FlushBatchDraw();
			Sleep(1);
			if (up_i == 3) {
				up_i = 0;
			}
		}
		else if (input == 's') {// 下移
			clearrectangle(x, y, x + 32, y + 32);//清空画面全部矩形区域
			down_i++;
			y += 10;
			putimage(x, y, 32, 32, &img_player, down_i * 32, 0 * 32);
			FlushBatchDraw();
			Sleep(1);
			if (down_i == 3) {
				down_i = 0;
			}
		}
	}
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
		updateWithoutInput();//于用户输入无关的更新
		updateWithInput();//与用户输入有关的更新
	}
	gameover();//游戏结束、后续处理
	return 0;
}
