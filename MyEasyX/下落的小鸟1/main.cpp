#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>

#pragma comment(lib, "Winmm.lib")

//全局变量
IMAGE img_bk;// 背景图片
IMAGE img_bd1, img_bd2;
IMAGE img_bar_up1, img_bar_up2;
IMAGE img_bar_down1, img_bar_down2;
int bird_x, bird_y;

//数据初始化
void startup() {
	srand((unsigned int)time(NULL));
	initgraph(288, 512);

	loadimage(&img_bk, _T("./flappybird/bg_day.png"));//读取图片到img_bk中
	putimage(0, 0, &img_bk);//在坐标(0, 0)位置显示IMAGE对象

	loadimage(&img_bd1, _T("./flappybird/mbird1.jpg"));
	loadimage(&img_bd2, _T("./flappybird/mbird2.jpg"));

	loadimage(&img_bar_up1, _T("./flappybird/mbird1.jpg"));
	loadimage(&img_bar_up2, _T("./flappybird/mbird2.jpg"));

	loadimage(&img_bar_down1, _T("./flappybird/mbird1.jpg"));
	loadimage(&img_bar_down2, _T("./flappybird/mbird2.jpg"));

	bird_x = 50;
	bird_y = 200;

	BeginBatchDraw();

	//循环播放音乐
	mciSendString(_T("open ./music/bk_sound.mp3 alias bkmusic"), NULL, 0, NULL);//背景音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//循环播放
}
//显示画面
void show() {

	putimage(0, 0, &img_bk);//显示背景

	putimage(150, -300, &img_bar_up1, NOTSRCERASE);//显示上一班的障碍物
	putimage(150, -300, &img_bar_up2, SRCINVERT);

	putimage(150, 400, &img_bar_down1, NOTSRCERASE);//显示下一半的障碍物
	putimage(150, 400, &img_bar_down2, SRCINVERT);

	putimage(bird_x, bird_y, &img_bd1, NOTSRCERASE);//显示小鸟
	putimage(bird_x, bird_y, &img_bd2, SRCINVERT);

	FlushBatchDraw();
	Sleep(50);
}
//于用户输入无关的更新
void updateWithoutInput() {
	if (bird_y < 580) {
		bird_y += 3;
	}
}
//与用户输入有关的更新
void updateWithInput() {
	char input;
	if (_kbhit()) {//当按键执行
		input = _getch();
		if (input == ' ' && bird_y > 20) {
			bird_y -= 60;

			mciSendString(_T("close jpmusic"), NULL, 0, NULL);//先把之前的音乐关了
			mciSendString(_T("open ./music/shoot.wav alias jpmusic"), NULL, 0, NULL);//打开音乐
			mciSendString(_T("play jpmusic"), NULL, 0, NULL);//仅播放一次
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
