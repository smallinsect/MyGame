#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>

#pragma comment(lib, "Winmm.lib")

#define Wight 512
#define High 768

//全局变量
IMAGE img_bk;// 背景图片
IMAGE img_h1, img_h2;// 英雄图片
IMAGE img_bullet1, img_bullet2;// 子弹图片
IMAGE img_bar_up1, img_bar_up2;
IMAGE img_bar_down1, img_bar_down2;
int hero_x, hero_y;//英雄坐标
int bullet_x, bullet_y;//子弹坐标

//数据初始化
void startup() {
	srand((unsigned int)time(NULL));
	initgraph(Wight, High);

	loadimage(&img_bk, _T("./images/bg/bg.jpg"));//读取图片到img_bk中
	putimage(0, 0, &img_bk);//在坐标(0, 0)位置显示IMAGE对象

	//loadimage(&img_h1, _T("./flappybird/mbird1.jpg"));
	//loadimage(&img_h2, _T("./flappybird/mbird2.jpg"));
	

	//loadimage(&img_bar_up1, _T("./flappybird/mbird1.jpg"));
	//loadimage(&img_bar_up2, _T("./flappybird/mbird2.jpg"));

	//loadimage(&img_bar_down1, _T("./flappybird/mbird1.jpg"));
	//loadimage(&img_bar_down2, _T("./flappybird/mbird2.jpg"));

	loadimage(&img_h2, _T("./images/hero/hero.png"));

	loadimage(&img_bullet2, _T("./images/bullet/bullet1.png"));

	hero_x = Wight / 2;
	hero_y = High / 2;

	//BeginBatchDraw();

	//循环播放音乐
	mciSendString(_T("open ./music/bgmusic.mp3 alias bkmusic"), NULL, 0, NULL);//背景音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//循环播放
}
//显示画面
void show() {

	//putimage(0, 0, &img_bk);//显示背景

	//putimage(150, -300, &img_bar_up1, NOTSRCERASE);//显示上一班的障碍物
	//putimage(150, -300, &img_bar_up2, SRCINVERT);

	//putimage(150, 400, &img_bar_down1, NOTSRCERASE);//显示下一半的障碍物
	//putimage(150, 400, &img_bar_down2, SRCINVERT);

	//putimage(hero_x, hero_y, &img_h1, NOTSRCERASE);//显示小鸟
	//putimage(hero_x, hero_y, &img_h2, SRCINVERT);

	putimage(hero_x, hero_y, &img_h2);

	putimage(bullet_x, bullet_y, &img_bullet2);

	//FlushBatchDraw();
	//Sleep(50);
}
//于用户输入无关的更新
void updateWithoutInput() {
	//if (hero_y < 580) {
	//	hero_y += 3;
	//}
}
//与用户输入有关的更新
void updateWithInput() {

	MOUSEMSG m;//记录鼠标消息
	while (MouseHit()) {
		m = GetMouseMsg();//获取鼠标事件
		if (m.uMsg == WM_MOUSEMOVE) {//鼠标移动时，飞机坐标等于鼠标位置
			hero_x = m.x;
			hero_y = m.y;
		}
	}

	//char input;
	//if (_kbhit()) {//当按键执行
	//	input = _getch();
	//	if (input == ' ') {
	//		//hero_y -= 60;

	//		mciSendString(_T("close bullet"), NULL, 0, NULL);//先把之前的音乐关了
	//		mciSendString(_T("open ./music/bullet.mp3 alias bullet"), NULL, 0, NULL);//打开音乐
	//		mciSendString(_T("play bullet"), NULL, 0, NULL);//仅播放一次
	//	}
	//}
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
