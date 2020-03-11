#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

//ȫ�ֱ���
int ball_x, ball_y;//С������λ��
int ball_vx, ball_vy;//С��x������ٶȺ�y������ٶ�
int bullet_x, bullet_y;//�ӵ�����
int position_x, position_y;//��������
int raduis;//����뾶
int high, width;//��Ϸ�Ļ���ߴ�
int enemy_x, enemy_y;//�л�������
int score;//��Ϸ�÷�

void gotoxy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//���ع��
void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };//�ڶ���ֵΪ0,��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//���ݳ�ʼ��
void startup() {
	srand((unsigned int)time(NULL));
	HideCursor();

	high = 18;
	width = 30;

	ball_x = high / 2;
	ball_y = width / 2;

	ball_vx = 1;
	ball_vy = 1;

	raduis = 5;
	position_x = high - 1;
	position_y = (width - 5) / 2;

	score = 0;
}
//��ʾ����
void show() {
	int i, j;
	//system("cls");//����
	gotoxy(0, 0);//����ƶ������Ͻǣ��ػ�ͼƬ

	for (i = 0; i < high; i++) {
		for (j = 0; j < width; j++) {
			if (i == ball_x && j == ball_y) {
				printf("O");//���С��O
			}
			else if (i == position_x && (position_y <= j && j <= position_y + raduis)) {
				printf("*");//�������
			}
			//else if (i == enemy_x && j == enemy_y) {
			//	printf("@");//����л�@
			//}
			else {
				printf(" ");//���
			}
		}
		printf("*\n");
	}
	for (j = 0; j < width; j++) {
		printf("*");
	}
	printf("\n");
	printf("С�򷴵����� %d\n", score);
}
//���û������޹صĸ���
void updateWithoutInput() {
	if (ball_x + 1 == position_x) {
		if (position_y <= ball_y && ball_y <= position_y+raduis) {
			score ++;
			ball_vy = -ball_vy;
		}
	}

	ball_x += ball_vx;
	ball_y += ball_vy;

	if (ball_x + ball_vx < 0 || high <= ball_x + ball_vx) {
		ball_vx = -ball_vx;
	}
	if (ball_y + ball_vy < 0 || width <= ball_y + ball_vy) {
		ball_vy = -ball_vy;
	}
	Sleep(50);
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