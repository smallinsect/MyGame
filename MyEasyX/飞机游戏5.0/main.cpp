#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>

#pragma comment(lib, "Winmm.lib")

#define Width 640 // ��Ļ���
#define High 480 // ��Ļ�߶�

#define Player_Width 50 // �ɻ����
#define Player_High 50 // �ɻ��߶�


//ȫ�ֱ���
IMAGE img_bg;// ����ͼƬ
IMAGE img_player1, img_player2;

int player_x, player_y;

//���ݳ�ʼ��
void startup() {
	srand((unsigned int)time(NULL));
	initgraph(Width, High);

	loadimage(&img_bg, _T("./image/bg.png"), Width, High, true);//��ȡͼƬ��img_bk��
	putimage(0, 0, &img_bg);//������(0, 0)λ����ʾIMAGE����

	loadimage(&img_player1, _T("./image/player01.png"), Player_Width, Player_High, true);
	loadimage(&img_player2, _T("./image/player02.png"), Player_Width, Player_High, true);

	player_x = 50;
	player_y = 200;

	BeginBatchDraw();

	//ѭ����������
	mciSendString(_T("open ./music/big_spaceship_flying.mp3 alias bkmusic"), NULL, 0, NULL);//��������
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);//ѭ������
}
//��ʾ����
void show() {

	//putimage(0, 0, &img_bk);//��ʾ����

	putimage(player_x, player_y, &img_player1);//��ʾС��
	//putimage(player_x, player_y, &img_player2);

	FlushBatchDraw();
	//Sleep(50);
}
//���û������޹صĸ���
void updateWithoutInput() {
	//if (player_y < 580) {
	//	player_y += 3;
	//}
}
//���û������йصĸ���
void updateWithInput() {

	MOUSEMSG m;//���������Ϣ
	//��ȡһ�������Ϣ
	m = GetMouseMsg();
	if (m.uMsg == WM_MOUSEMOVE) {
		player_x = m.x;
		player_y = m.y;
	}
	else if (m.uMsg == WM_LBUTTONDOWN) {
		//����������ʱ �����λ�û�һ������
		rectangle(m.x - 5, m.y - 5, m.x + 5, m.y + 5);
	}
	else if (m.uMsg == WM_RBUTTONDOWN) {
		//����Ҽ�����ʱ �����λ�û�һ��Բ
		circle(m.x, m.y, 5);
	}
	

	//if (GetAsyncKeyState(0x41) & 0x8000 && player_x - 1 >= 0) { // a ����
	//	player_x--;
	//}
	//if (GetAsyncKeyState(0x44) & 0x8000 && player_x + 1 < Width) { // d ����
	//	player_x++;
	//}
	//if (GetAsyncKeyState(0x57) & 0x8000 && player_y - 1 >= 0) { // w ����
	//	player_y--;
	//}
	//if (GetAsyncKeyState(0x53) & 0x8000 && player_y + 1 < High) { // s ����
	//	player_y++;
	//}
	//if (GetAsyncKeyState(' ') & 0x8000) { // �ո� �����ӵ�
	//	mciSendString(_T("close bullet"), NULL, 0, NULL);//�Ȱ�֮ǰ�����ֹ���
	//	mciSendString(_T("open ./music/bullet.mp3 alias bullet"), NULL, 0, NULL);//������
	//	mciSendString(_T("play bullet"), NULL, 0, NULL);//������һ��
	//}
}

void clean() {
	clearrectangle(player_x, player_y, player_x+Player_Width, player_y+Player_High);
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
		clean();
		updateWithoutInput();//���û������޹صĸ���
		updateWithInput();//���û������йصĸ���
	}
	gameover();//��Ϸ��������������
	return 0;
}
