#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>

#pragma comment(lib, "Winmm.lib")

#define Wight 512
#define High 768

//ȫ�ֱ���
IMAGE img_bk;// ����ͼƬ
IMAGE img_h1, img_h2;// Ӣ��ͼƬ
IMAGE img_bullet1, img_bullet2;// �ӵ�ͼƬ
IMAGE img_bar_up1, img_bar_up2;
IMAGE img_bar_down1, img_bar_down2;
int hero_x, hero_y;//Ӣ������
int bullet_x, bullet_y;//�ӵ�����

//���ݳ�ʼ��
void startup() {
	srand((unsigned int)time(NULL));
	initgraph(Wight, High);

	loadimage(&img_bk, _T("./images/bg/bg.jpg"));//��ȡͼƬ��img_bk��
	putimage(0, 0, &img_bk);//������(0, 0)λ����ʾIMAGE����

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

	//ѭ����������
	mciSendString(_T("open ./music/bgmusic.mp3 alias bkmusic"), NULL, 0, NULL);//��������
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//ѭ������
}
//��ʾ����
void show() {

	//putimage(0, 0, &img_bk);//��ʾ����

	//putimage(150, -300, &img_bar_up1, NOTSRCERASE);//��ʾ��һ����ϰ���
	//putimage(150, -300, &img_bar_up2, SRCINVERT);

	//putimage(150, 400, &img_bar_down1, NOTSRCERASE);//��ʾ��һ����ϰ���
	//putimage(150, 400, &img_bar_down2, SRCINVERT);

	//putimage(hero_x, hero_y, &img_h1, NOTSRCERASE);//��ʾС��
	//putimage(hero_x, hero_y, &img_h2, SRCINVERT);

	putimage(hero_x, hero_y, &img_h2);

	putimage(bullet_x, bullet_y, &img_bullet2);

	//FlushBatchDraw();
	//Sleep(50);
}
//���û������޹صĸ���
void updateWithoutInput() {
	//if (hero_y < 580) {
	//	hero_y += 3;
	//}
}
//���û������йصĸ���
void updateWithInput() {

	MOUSEMSG m;//��¼�����Ϣ
	while (MouseHit()) {
		m = GetMouseMsg();//��ȡ����¼�
		if (m.uMsg == WM_MOUSEMOVE) {//����ƶ�ʱ���ɻ�����������λ��
			hero_x = m.x;
			hero_y = m.y;
		}
	}

	//char input;
	//if (_kbhit()) {//������ִ��
	//	input = _getch();
	//	if (input == ' ') {
	//		//hero_y -= 60;

	//		mciSendString(_T("close bullet"), NULL, 0, NULL);//�Ȱ�֮ǰ�����ֹ���
	//		mciSendString(_T("open ./music/bullet.mp3 alias bullet"), NULL, 0, NULL);//������
	//		mciSendString(_T("play bullet"), NULL, 0, NULL);//������һ��
	//	}
	//}
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
