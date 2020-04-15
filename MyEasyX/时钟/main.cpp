
#include "main.h"

//数据初始化
void startup() {
	HideCursor();//隐藏光标
}
//显示画面
void show() {
	int i, j;
	//system("cls");//清屏
	gotoxy(0, 0);//光标移动到左上角，重画图片

	for (i = 0; i < High; i++) {
		for (j = 0; j < Width; j++) {
			if (frame[i][j] == 1) {
				printf("*");//输出方块
			}
			else {
				printf(" ");//输出
			}
		}
		printf("#\n");//输出右边墙
	}
	// 输出下边墙
	for (j = 0; j < Width; j++) {
		printf("#");
	}
	printf("#\n");
}
//与用户输入无关的更新
void updateWithoutInput() {
	SYSTEMTIME st;
	//获取当前系统时间
	GetLocalTime(&st);
	sprintf(strTime, "%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond);

	for (int pos = 0; strTime[pos] != '\0'; pos++) {
		int idx = Idx(strTime[pos]);
		for (int i = 0; i < Num_High; i++) {
			for (int j = 0; j < Num_Width; j++) {
				frame[i][j + pos * Num_Width + 1] = num[idx][i][j];
			}
		}
	}

	Sleep(100);
}
//与用户输入有关的更新
void updateWithInput() {
}

int main() {
	startup();//数据初始化
	while (1) {//游戏循环执行
		show();//显示画面
		updateWithoutInput();//于用户输入无关的更新
		updateWithInput();//与用户输入有关的更新
	}

	return 0;
}