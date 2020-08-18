#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

const int W = 40;// ��Ļ���
const int H = 20;// ��Ļ�߶�
int canvas[H][W];

// �ߵķ����ߵĳ���
int dir = 2, num = 4;
// �ߵ���������
struct Snake {
	int x, y;
} s[100];

struct Food {
	int x, y;
} f;

void Tick();
void gotoxy(SHORT x, SHORT y);
void HideCursor();// ���ع��

int main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));// ʱ����Ϊ�������
	HideCursor();//���ع��

	memset(canvas, 0, sizeof(canvas));

	f.x = rand() % W;
	f.y = rand() % H;

	clock_t timer = clock(), delay = 50;
	while (true) {
		clock_t nowTime = clock();

		gotoxy(0, 0);//����ƶ������Ͻǣ��ػ�ͼƬ
		// ��������ӡ�ڿ���̨��
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (canvas[i][j] == 1) {// ��
					printf("*");
				}
				else if (canvas[i][j] == 2) {// ʳ��
					printf("@");
				}
				else {// �հ�
					printf(" ");
				}
			}
			printf("|\n");
		}
		for (int i = 0; i < W; i++) {
			printf("-");
		}
		printf("+\n");

		// ����������
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 'w') dir = 0;// ��
			if (ch == 'd') dir = 1;// ��
			if (ch == 's') dir = 2;// ��
			if (ch == 'a') dir = 3;// ��
		}

		// ��ʱ��
		clock_t subTime = nowTime - timer;
		if (subTime > delay) {
			timer = nowTime;
			Tick();
		}

		// ���û���
		memset(canvas, 0, sizeof(canvas));
		// �������ڻ�����
		for (int i = 0; i < num; i++) {
			canvas[s[i].y][s[i].x] = 1;
		}
		// ��ʳ�����ڻ�����
		canvas[f.y][f.x] = 2;
	}

	return 0;
}

void Tick() {
	for (int i = num; i > 0; i--) {
		s[i] = s[i - 1];
	}
	if (dir == 0) s[0].y -= 1;// ��
	if (dir == 1) s[0].x += 1;// ��
	if (dir == 2) s[0].y += 1;// ��
	if (dir == 3) s[0].x -= 1;// ��
	// Խ�紦��
	s[0].x = (s[0].x + W) % W;
	s[0].y = (s[0].y + H) % H;
	// ��ʳ��
	if (s[0].x == f.x && s[0].y == f.y) {
		// �����ߵĳ���
		num++;
		// ����µ�ʳ������
		f.x = rand() % W;
		f.y = rand() % H;
	}
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
