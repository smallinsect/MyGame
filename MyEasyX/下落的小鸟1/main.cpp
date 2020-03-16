#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>

#pragma comment(lib, "Winmm.lib")

//ȫ�ֱ���
IMAGE img_bk;// ����ͼƬ
IMAGE img_bd1, img_bd2;
IMAGE img_bar_up1, img_bar_up2;
IMAGE img_bar_down1, img_bar_down2;
int bird_x, bird_y;

//���ݳ�ʼ��
void startup() {
	srand((unsigned int)time(NULL));
	initgraph(288, 512);

	loadimage(&img_bk, _T("./flappybird/bg_day.png"));//��ȡͼƬ��img_bk��
	putimage(0, 0, &img_bk);//������(0, 0)λ����ʾIMAGE����

	loadimage(&img_bd1, _T("./flappybird/mbird1.jpg"));
	loadimage(&img_bd2, _T("./flappybird/mbird2.jpg"));

	loadimage(&img_bar_up1, _T("./flappybird/mbird1.jpg"));
	loadimage(&img_bar_up2, _T("./flappybird/mbird2.jpg"));

	loadimage(&img_bar_down1, _T("./flappybird/mbird1.jpg"));
	loadimage(&img_bar_down2, _T("./flappybird/mbird2.jpg"));

	bird_x = 50;
	bird_y = 200;

	BeginBatchDraw();

	//ѭ����������
	mciSendString(_T("open ./music/bk_sound.mp3 alias bkmusic"), NULL, 0, NULL);//��������
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//ѭ������
}
//��ʾ����
void show() {

	putimage(0, 0, &img_bk);//��ʾ����

	putimage(150, -300, &img_bar_up1, NOTSRCERASE);//��ʾ��һ����ϰ���
	putimage(150, -300, &img_bar_up2, SRCINVERT);

	putimage(150, 400, &img_bar_down1, NOTSRCERASE);//��ʾ��һ����ϰ���
	putimage(150, 400, &img_bar_down2, SRCINVERT);

	putimage(bird_x, bird_y, &img_bd1, NOTSRCERASE);//��ʾС��
	putimage(bird_x, bird_y, &img_bd2, SRCINVERT);

	FlushBatchDraw();
	Sleep(50);
}
//���û������޹صĸ���
void updateWithoutInput() {
	if (bird_y < 580) {
		bird_y += 3;
	}
}
//���û������йصĸ���
void updateWithInput() {
	char input;
	if (_kbhit()) {//������ִ��
		input = _getch();
		if (input == ' ' && bird_y > 20) {
			bird_y -= 60;

			mciSendString(_T("close jpmusic"), NULL, 0, NULL);//�Ȱ�֮ǰ�����ֹ���
			mciSendString(_T("open ./music/shoot.wav alias jpmusic"), NULL, 0, NULL);//������
			mciSendString(_T("play jpmusic"), NULL, 0, NULL);//������һ��
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
