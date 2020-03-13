#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#define High 20//��Ϸ����ߴ�
#define Width 50
#define EnemyNum 5//�л�����

//ȫ�ֱ���
int canvas[High][Width] = { 0 };//��ά�����¼��Ϸ
							//0 ����ո�1����ɻ�
							//2����ӵ�
							//3����л�


int position_x, position_y;//�ɻ�����λ��
int enemy_x[EnemyNum], enemy_y[EnemyNum];//�л�����
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

	int i, j;
	for (i = 0; i < High; i++) {
		canvas[i][0] = -1;
		canvas[i][Width -1 ] = -1;
	}
	for (j = 0; j < Width; j++) {
		canvas[0][j] = -1;
		canvas[High - 1][j] = -1;
	}

	//canvas[High / 2][Width / 2] = 1;
	for (i = 0; i < 4; i++) {
		canvas[High / 2][Width / 2 - i] = i + 1;
	}
	score = 0;
}
//��ʾ����
void show() {
	int i, j;
	//system("cls");//����
	gotoxy(0, 0);//����ƶ������Ͻǣ��ػ�ͼƬ

	for (i = 0; i < High; i++) {
		for (j = 0; j < Width; j++) {
			if (canvas[i][j] == -1) {
				printf("#");//���ǽ#
			}
			else if (canvas[i][j] == 1) {
				printf("@");//�����ͷ@
			}
			else if (canvas[i][j] > 1) {
				printf("*");//�������*
			}
			else {
				printf(" ");//���
			}
		}
		printf("\n");
	}
	printf("�ɻ��÷� %d\n", score);
}
//���û������޹صĸ���
void updateWithoutInput() {
	int i, j, k;
	//�ӵ�����
	//for (i = 0; i < High; i++) {
	//	for (j = 0; j < Width; j++) {
	//		if (canvas[i][j] == 2) {
	//			//�ӵ����ел�
	//			for (k = 0; k < EnemyNum; k++) {
	//				if (i == enemy_x[k] && j == enemy_y[k]) {
	//					score++;

	//					canvas[enemy_x[k]][enemy_y[k]] = 0;
	//					enemy_x[k] = 0;
	//					enemy_y[k] = rand() % Width;
	//					canvas[enemy_x[k]][enemy_y[k]] = 3;
	//				}
	//			}

	//			canvas[i][j] = 0;
	//			if (i > 0) {
	//				canvas[i - 1][j] = 2;
	//			}
	//		}
	//	}
	//}

	//for (k = 0; k < EnemyNum; k++) {
	//	if (enemy_x[k] + 1 >= High) {
	//		canvas[enemy_x[k]][enemy_y[k]] = 0;
	//		enemy_x[k] = 0;
	//		enemy_y[k] = rand() % Width;
	//		canvas[enemy_x[k]][enemy_y[k]] = 3;
	//		score--;
	//	}
	//}
	//static int speed = 0;
	//if (speed < 10) {
	//	speed++;
	//}
	//else {
	//	for (k = 0; k < EnemyNum; k++) {
	//		//�л�����
	//		canvas[enemy_x[k]][enemy_y[k]] = 0;
	//		enemy_x[k]++;
	//		canvas[enemy_x[k]][enemy_y[k]] = 3;
	//		speed = 0;
	//	}
	//}

	//Sleep(30);
}
//���û������йصĸ���
void updateWithInput() {
	char input;
	if (_kbhit()) {//������ִ��
		input = _getch();
		if (input == 'w' && position_x - 1 >= 0) {
			canvas[position_x][position_y] = 0;
			position_x--;
			canvas[position_x][position_y] = 1;
		}
		if (input == 's' && position_x + 1 < High) {
			canvas[position_x][position_y] = 0;
			position_x++;
			canvas[position_x][position_y] = 1;
		}
		if (input == 'a' && position_y - 1 >= 0) {
			canvas[position_x][position_y] = 0;
			position_y--;
			canvas[position_x][position_y] = 1;
		}
		if (input == 'd' && position_y + 1 < Width) {
			canvas[position_x][position_y] = 0;
			position_y++;
			canvas[position_x][position_y] = 1;
		}
		if (input == ' ') {
			canvas[position_x - 1][position_y] = 2;
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