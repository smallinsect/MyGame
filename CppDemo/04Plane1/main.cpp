
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define H 26//��Ϸ����ߴ�
#define W 40
#define EnemyNum 15//�л�����

//����
int canvas[H][W] = { 0 };
//0.����ո�
//1.����ɻ�
//2.����ӵ�
//3.����л�
char symbol[] = " *|@";

struct Point {
	int x, y;
};

Point player;//�ɻ�����λ��
Point enemy[EnemyNum];//�л�����
int score = 0;//��Ϸ�÷�
// ��ʱ�����л������ٶ�
int timer = 0, delay = 10;

void gotoxy(SHORT x, SHORT y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {x, y};
	SetConsoleCursorPosition(handle, pos);
}

//���ع��
void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };//�ڶ���ֵΪ0,��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//���ݳ�ʼ��
void startup() {
	srand((unsigned int)time(NULL));//�����������
	HideCursor();//���ع��

	player.x = H / 2;//�ɻ�����λ��
	player.y = W / 2;
	canvas[player.x][player.y] = 1;

	// ��ʼ��������л�λ�á�
	for (int i = 0; i < EnemyNum; i++) {
		enemy[i].x = rand() % 3;
		enemy[i].y = rand() % W;
	}
}
//��ʾ����
void show() {
	gotoxy(0, 0);//����ƶ������Ͻǣ��ػ�ͼƬ

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			printf("%c", symbol[canvas[i][j]]);//���
		}
		printf("#\n");//����ұ�ǽ
	}
	// ����±�ǽ
	for (int j = 0; j < W; j++) {
		printf("#");
	}
	printf("#\n");
	printf("�ɻ��÷� %d\n", score);
}
//���û������޹صĸ���
void updateWithoutInput() {
	int i, j, k;
	//�ӵ�����
	for (i = 0; i < H; i++) {
		for (j = 0; j < W; j++) {
			if (canvas[i][j] == 2) {
				canvas[i][j] = 0;
				if (i == 0) {
					continue;
				}
				bool flag = true;
				//�ӵ����ел�
				for (k = 0; k < EnemyNum; k++) {
					if (i-1 == enemy[k].x && j == enemy[k].y) {// �ӵ����ел�
						score++;// �ӷ�
						canvas[enemy[k].x][enemy[k].y] = 0;// ɾ���л�
						enemy[k].x = 0;
						enemy[k].y = rand() % W;
						canvas[enemy[k].x][enemy[k].y] = 3;
						flag = false;// �ӵ����ел��������ӵ���
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
		//�л�����
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
//���û������йصĸ���
void updateWithInput() {
	if (GetAsyncKeyState('A') & 0x8000 && player.y - 1 >= 0) { // a ����
		canvas[player.x][player.y] = 0;
		player.y--;
		canvas[player.x][player.y] = 1;
	}
	if (GetAsyncKeyState('D') & 0x8000 && player.y + 1 < W) { // d ����
		canvas[player.x][player.y] = 0;
		player.y++;
		canvas[player.x][player.y] = 1;
	}
	if (GetAsyncKeyState('W') & 0x8000 && player.x - 1 >= 0) { // w ����
		canvas[player.x][player.y] = 0;
		player.x--;
		canvas[player.x][player.y] = 1;
	}
	if (GetAsyncKeyState('S') & 0x8000 && player.x + 1 < H) { // s ����
		canvas[player.x][player.y] = 0;
		player.x++;
		canvas[player.x][player.y] = 1;
	}
	if (GetAsyncKeyState(' ') & 0x8000) { // �ո� �����ӵ�
		canvas[player.x - 1][player.y] = 2;
	}
}

int main() {
	startup();//���ݳ�ʼ��
	while (1) {//��Ϸѭ��ִ��
		show();//��ʾ����
		updateWithoutInput();//���û������޹صĸ���
		updateWithInput();//���û������йصĸ���
	}
	return 0;
}