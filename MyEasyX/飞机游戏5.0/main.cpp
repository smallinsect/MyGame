#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>

#pragma comment(lib, "Winmm.lib")

#define Width 640 // 屏幕宽度
#define High 480 // 屏幕高度

#define Player_Width 50 // 飞机宽度
#define Player_High 50 // 飞机高度


//全局变量
IMAGE img_bg;// 背景图片
IMAGE img_player1, img_player2;

int player_x, player_y;

//数据初始化
void startup() {
	srand((unsigned int)time(NULL));
	initgraph(Width, High);

	loadimage(&img_bg, _T("./image/bg.png"), Width, High, true);//读取图片到img_bk中
	putimage(0, 0, &img_bg);//在坐标(0, 0)位置显示IMAGE对象

	loadimage(&img_player1, _T("./image/player01.png"), Player_Width, Player_High, true);
	loadimage(&img_player2, _T("./image/player02.png"), Player_Width, Player_High, true);

	player_x = 50;
	player_y = 200;

	BeginBatchDraw();

	//循环播放音乐
	mciSendString(_T("open ./music/big_spaceship_flying.mp3 alias bkmusic"), NULL, 0, NULL);//背景音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//循环播放
}
//显示画面
void show() {

	//putimage(0, 0, &img_bk);//显示背景

	putimage(player_x, player_y, &img_player1);//显示小鸟
	//putimage(player_x, player_y, &img_player2);

	FlushBatchDraw();
	//Sleep(50);
}
//于用户输入无关的更新
void updateWithoutInput() {
	//if (player_y < 580) {
	//	player_y += 3;
	//}
}
//与用户输入有关的更新
void updateWithInput() {

	MOUSEMSG m;//定义鼠标消息
	//获取一套鼠标消息
	m = GetMouseMsg();
	if (m.uMsg == WM_MOUSEMOVE) {
		player_x = m.x;
		player_y = m.y;
	}
	else if (m.uMsg == WM_LBUTTONDOWN) {
		//鼠标左键按下时 在鼠标位置画一个方块
		rectangle(m.x - 5, m.y - 5, m.x + 5, m.y + 5);
	}
	else if (m.uMsg == WM_RBUTTONDOWN) {
		//鼠标右键按下时 在鼠标位置画一个圆
		circle(m.x, m.y, 5);
	}
	

	//if (GetAsyncKeyState(0x41) & 0x8000 && player_x - 1 >= 0) { // a 左移
	//	player_x--;
	//}
	//if (GetAsyncKeyState(0x44) & 0x8000 && player_x + 1 < Width) { // d 右移
	//	player_x++;
	//}
	//if (GetAsyncKeyState(0x57) & 0x8000 && player_y - 1 >= 0) { // w 上移
	//	player_y--;
	//}
	//if (GetAsyncKeyState(0x53) & 0x8000 && player_y + 1 < High) { // s 下移
	//	player_y++;
	//}
	//if (GetAsyncKeyState(' ') & 0x8000) { // 空格 发射子弹
	//	mciSendString(_T("close bullet"), NULL, 0, NULL);//先把之前的音乐关了
	//	mciSendString(_T("open ./music/bullet.mp3 alias bullet"), NULL, 0, NULL);//打开音乐
	//	mciSendString(_T("play bullet"), NULL, 0, NULL);//仅播放一次
	//}
}

void clean() {
	clearrectangle(player_x, player_y, player_x+Player_Width, player_y+Player_High);
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
		clean();
		updateWithoutInput();//于用户输入无关的更新
		updateWithInput();//与用户输入有关的更新
	}
	gameover();//游戏结束、后续处理
	return 0;
}
