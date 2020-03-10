#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

//ȫ�ֱ���
int position_x, position_y;//�ɻ�����λ��
int bullet_x, bullet_y;//�ӵ�����
int high, width;//��Ϸ�Ļ���ߴ�
int enemy_x, enemy_y;//�л�������
int score;//��Ϸ�÷�

void gotoxy(int x,int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//���ع��
void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};//�ڶ���ֵΪ0,��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//���ݳ�ʼ��
void startup() {
	srand((unsigned int)time(NULL));
	HideCursor();

	high = 18;
	width = 30;

	position_x = high / 2;
	position_y = width / 2;

	bullet_x = -1;
	bullet_y = position_y;

	enemy_x = 0;
	enemy_y = width / 2;

	score = 0;
}
//��ʾ����
void show() {
	int i, j;
	//system("cls");//����
	gotoxy(0, 0);//����ƶ������Ͻǣ��ػ�ͼƬ

	for (i = 0; i < high; i++) {
		for (j = 0; j < width; j++) {
			if (i == position_x && j == position_y) {
				printf("*");//����ɻ�*
			}
			else if (i == bullet_x && j == bullet_y) {
				printf("|");//����ɻ��ӵ�|
			}
			else if (i == enemy_x && j == enemy_y) {
				printf("@");//����л�@
			}
			else {
				printf(" ");//���
			}
		}
		printf("\n");
	}
	printf("�÷� %d\n", score);
}
//���û������޹صĸ���
void updateWithoutInput() {
	if (bullet_x == enemy_x && bullet_y == enemy_y) {
		score++;
		enemy_x = 0;
		enemy_y = rand() % width;
		bullet_x = -1;
	}

	static int speed = 0;//���ڿ��Ʒɻ�������ٶ�
	if (speed < 10) {
		speed++;
	}
	
	if (bullet_x > -1) {
		bullet_x--;
	}

	if (enemy_x > high) {//�������ɵл�
		enemy_x = 0;
		enemy_y = rand() % width;
	}
	else {
		if (speed == 10) {
			enemy_x++;
			speed = 0;
		}
	}
	//Sleep(150);
}
//���û������йصĸ���
void updateWithInput() {
	char input;
	if (_kbhit()) {//������ִ��
		input = _getch();
		if (input == 'w' && position_x - 1 >= 0) {
			position_x--;
		}
		if (input == 's' && position_x + 1 < high) {
			position_x++;
		}
		if (input == 'a' && position_y - 1 >= 0) {
			position_y--;
		}
		if (input == 'd' && position_y + 1 < width) {
			position_y++;
		}
		if (input == ' ') {
			bullet_x = position_x;
			bullet_y = position_y;
		}
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