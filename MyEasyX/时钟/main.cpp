
#include "main.h"

//���ݳ�ʼ��
void startup() {
	HideCursor();//���ع��
}
//��ʾ����
void show() {
	int i, j;
	//system("cls");//����
	gotoxy(0, 0);//����ƶ������Ͻǣ��ػ�ͼƬ

	for (i = 0; i < High; i++) {
		for (j = 0; j < Width; j++) {
			if (frame[i][j] == 1) {
				printf("*");//�������
			}
			else {
				printf(" ");//���
			}
		}
		printf("#\n");//����ұ�ǽ
	}
	// ����±�ǽ
	for (j = 0; j < Width; j++) {
		printf("#");
	}
	printf("#\n");
}
//���û������޹صĸ���
void updateWithoutInput() {
	SYSTEMTIME st;
	//��ȡ��ǰϵͳʱ��
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
//���û������йصĸ���
void updateWithInput() {
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