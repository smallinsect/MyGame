#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

const int W = 10;// ��Ļ���
const int H = 20;// ��Ļ�߶�
int canvas[H][W];// ��Ϸ����

struct Point {
	int x, y;
} a[4], b[4];// ����ķ���
int tcanvas[H][W];//����ķ���

int figures[7][4] = {
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

// ���
char symbol[] = " *";

bool check();
void gotoxy(SHORT x, SHORT y);
void HideCursor();// ���ع��

int main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));// ʱ����Ϊ�������
	HideCursor();//���ع��

	memset(canvas, 0, sizeof(canvas));

	int n = rand() % 7;
	for (int i = 0; i < 4; i++) {
		a[i].x = figures[n][i] % 2;
		a[i].y = figures[n][i] / 2;
	}

	int dx = 0;
	bool rotate = false;
	clock_t timer = clock(), delay = 50;
	while (true) {
		clock_t nowTime = clock();

		gotoxy(0, 0);//����ƶ������Ͻǣ��ػ�ͼƬ
		// ��������ӡ�ڿ���̨��
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				printf("%c", symbol[canvas[i][j]]);
			}
			printf("#\n");
		}
		for (int i = 0; i < W; i++) {
			printf("#");
		}
		printf("#\n");

		dx = 0;
		rotate = false;
		delay = 300;
		// ����������
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 'w') rotate = true;// ��
			if (ch == 'd') dx = 1;// ��
			if (ch == 's') delay = 50;// ��
			if (ch == 'a') dx = -1;// ��
		}

		// �ƶ�
		for (int i = 0; i < 4; i++) {
			b[i] = a[i];
			a[i].x += dx;
		}
		if (!check()) {
			for (int i = 0; i < 4; i++) {
				a[i] = b[i];
			}
		}
		// ��ת
		if (rotate) {
			Point p = a[1];
			for (int i = 0; i < 4; i++) {
				b[i] = a[i];
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			if (!check()) {
				for (int i = 0; i < 4; i++) {
					a[i] = b[i];
				}
			}
		}

		// ��ʱ��
		clock_t subTime = nowTime - timer;
		if (subTime > delay) {
			timer = nowTime;
			// ����
			for (int i = 0; i < 4; i++) {
				b[i] = a[i];
				a[i].y += 1;
			}
			// ����������
			if (!check()) {
				for (int i = 0; i < 4; i++) {
					tcanvas[b[i].y][b[i].x] = 1;
				}
				int n = rand() % 7;// ���һ�ַ���
				for (int i = 0; i < 4; i++) {
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}
			}
		}

		// ��ȥ����
		int k = H - 1;
		for (int i = H - 1; i >= 0; i--) {
			int cnt = 0;
			// ͳ��һ�еķ�������
			for (int j = 0; j < W; j++) {
				if (tcanvas[i][j] > 0) {
					cnt++;
				}
				tcanvas[k][j] = tcanvas[i][j];
			}
			if (cnt < W) {
				k--;
			}
		}

		// ���û���
		memset(canvas, 0, sizeof(canvas));
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				canvas[i][j] = tcanvas[i][j];
			}
		}
		for (int i = 0; i < 4; i++) {
			canvas[a[i].y][a[i].x] = 1;
		}
	}

	return 0;
}

bool check() {
	for (int i = 0; i < 4; i++) {
		if (a[i].x < 0 || W <= a[i].x || a[i].y < 0 || H <= a[i].y) {
			return false;
		}
		else if (tcanvas[a[i].y][a[i].x] > 0) {
			return false;
		}
	}
	return true;
}

// ���ù��λ��
void gotoxy(SHORT x, SHORT y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(handle, pos);
}

//���ع��
void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };//�ڶ���ֵΪ0,��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
