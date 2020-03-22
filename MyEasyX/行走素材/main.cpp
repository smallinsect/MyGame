#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>

#pragma comment(lib, "Winmm.lib")

#define Wight 350
#define High 600

//ȫ�ֱ���
IMAGE img_player;// ����ͼƬ
IMAGE img_h1, img_h2;// Ӣ��ͼƬ
IMAGE img_bullet1, img_bullet2;// �ӵ�ͼƬ
IMAGE img_bar_up1, img_bar_up2;
IMAGE img_bar_down1, img_bar_down2;
int x, y;//���λ��
int left_i, right_i, up_i, down_i;//ͼƬ�ƶ�λ��

//���ݳ�ʼ��
void startup() {
	srand((unsigned int)time(NULL));
	initgraph(Wight, High);

	loadimage(&img_player, _T("./image/player.png"));//��ȡͼƬ��img_bk��
	//putimage(0, 0, &img_player);//������(0, 0)λ����ʾIMAGE����
	//������(0,0)λ����ʾͼƬ
	putimage(0, 0, 32, 32, &img_player, 0, 0);

	x = Wight / 2;
	y = High / 2; 

	left_i = 0;
	right_i = 0;
	up_i = 0;
	down_i = 0;

	BeginBatchDraw();
}
//��ʾ����
void show() {

	Sleep(30);
}
//���û������޹صĸ���
void updateWithoutInput() {
	//if (hero_y < 580) {
	//	hero_y += 3;
	//}
}
//���û������йصĸ���
void updateWithInput() {

	char input;
	if (_kbhit()) {//������ִ��
		input = _getch();
		if (input == 'a') {// ����
			clearrectangle(x, y, x + 32, y + 32);//��ջ���ȫ����������
			left_i++;
			x -= 10;
			putimage(x, y, 32, 32, &img_player, left_i * 32, 1 * 32);
			FlushBatchDraw();
			Sleep(1);
			if (left_i == 3) {
				left_i = 0;
			}
		}
		else if (input == 'd') {// ����
			clearrectangle(x, y, x + 32, y + 32);//��ջ���ȫ����������
			right_i++;
			x += 10;
			putimage(x, y, 32, 32, &img_player, right_i * 32, 2 * 32);
			FlushBatchDraw();
			Sleep(1);
			if (right_i == 3) {
				right_i = 0;
			}
		}
		else if (input == 'w') {// ����
			clearrectangle(x, y, x + 32, y + 32);//��ջ���ȫ����������
			up_i++;
			y -= 10;
			putimage(x, y, 32, 32, &img_player, up_i * 32, 3 * 32);
			FlushBatchDraw();
			Sleep(1);
			if (up_i == 3) {
				up_i = 0;
			}
		}
		else if (input == 's') {// ����
			clearrectangle(x, y, x + 32, y + 32);//��ջ���ȫ����������
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
//��Ϸ��������������
void gameover() {
	EndBatchDraw();
	_getch();
	closegraph();
}

int main() {
	startup();//���ݳ�ʼ��
	while (1) {//��Ϸѭ��ִ��
		show();//��ʾ����
		updateWithoutInput();//���û������޹صĸ���
		updateWithInput();//���û������йصĸ���
	}
	gameover();//��Ϸ��������������
	return 0;
}
