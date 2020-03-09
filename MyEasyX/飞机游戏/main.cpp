#include <graphics.h>//引用EasyX图形库
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#define WIDTH 40 //窗口宽度
#define HIGH 30 //窗口高度

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
			if (y+2 == weizi) {//靶子被子弹击中
				weizi = rand() % 30 + 2;//靶子被击中，重新生成位置
			}
		}
		else {
			for (i = 0; i < x; i++) {
				printf("\n");
			}
		}

		//飞机移动
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