#include <graphics.h>//����EasyXͼ�ο�
#include <conio.h>
#include <stdio.h>
#include <windows.h>

#define WIDTH 40 //���ڿ��
#define HIGH 30 //���ڸ߶�

int main() {
	//С�����꣬��ʼ��
	int ball_x = WIDTH / 2;
	int ball_y = HIGH / 2;
	//С���ٶ�
	int ball_vx = 1;
	int ball_vy = 1;

	int x = 0;
	int y = 0;
	while (1) {
		system("cls");

		for (y = 0; y < ball_y; y++) {
			printf("\n");
		}
		for (x = 0; x < ball_x; x++) {
			printf(" ");
		}
		printf("0\n");


		Sleep(3);
		ball_x += ball_vx;
		ball_y += ball_vy;

		if (ball_x <= 0 || ball_x >= WIDTH) {
			ball_vx = -ball_vx;
		}
		if (ball_y <= 0 || ball_y >= HIGH) {
			ball_vy = -ball_vy;
		}
	}

	return 0;
}