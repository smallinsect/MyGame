#include <graphics.h>//����EasyXͼ�ο�
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#define WIDTH 40 //���ڿ��
#define HIGH 30 //���ڸ߶�

int main() {
	
	srand((UINT)time(NULL));

	int x = 20;
	int y = 0;
	int i = 0;
	int j = 0;
	int isFire = 0;
	int weizi = rand() % 30 + 2;

	char input;
	while (1) {
		system("cls");

		for (i = 0; i < weizi; i++) {
			printf(" ");
		}
		printf("+\n");

		if (isFire) {
			for (i = 0; i < x; i++) {
				for (j = 0; j < y; j++) {
					printf(" ");
				}
				printf("  |\n");
			}
			isFire = 0;
			if (y+2 == weizi) {//���ӱ��ӵ�����
				weizi = rand() % 30 + 2;//���ӱ����У���������λ��
			}
		}
		else {
			for (i = 0; i < x; i++) {
				printf("\n");
			}
		}

		//�ɻ��ƶ�
		for (j = 0; j < y; j++) {
			printf(" ");
		}
		printf("  *\n");
		for (j = 0; j < y; j++) {
			printf(" ");
		}
		printf("*****\n");
		for (j = 0; j < y; j++) {
			printf(" ");
		}
		printf(" * *\n");
		Sleep(30);

		input = _getch();
		if (input == 's')
			x++;
		if (input == 'w')
			x--;
		if (input == 'a')
			y--;
		if (input == 'd')
			y++;
		if (input == ' ')
			isFire = 1;
	}

	return 0;
}