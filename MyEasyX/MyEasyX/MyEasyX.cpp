#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>

#pragma comment(lib, "Winmm.lib")



int main() {
	//mciSendString(TEXT("open ./music/bullet.mp3 alias bullet"), NULL, 0, NULL);//������
	//mciSendString(TEXT("play bullet"), NULL, 0, NULL);//������һ��


	while (1) {

		TCHAR szStatus[80];
		mciSendString(TEXT("status bullet mode"), szStatus, 80, 0);


		if (lstrcmp(szStatus, TEXT("")) == 0 ||
			lstrcmp(szStatus, TEXT("stopped")) == 0
			)
		{
			mciSendString(TEXT("close bullet"), NULL, 0, NULL);//�Ȱ�֮ǰ�����ֹ���
			mciSendString(TEXT("open ./music/bullet.mp3 alias bullet"), NULL, 0, NULL);//������
			mciSendString(TEXT("play bullet"), NULL, 0, NULL);//������һ��
			wprintf(TEXT("11111111"));
		}
		wprintf(TEXT("%s\n"), szStatus);
		Sleep(30);
	}
	getchar();
	return 0;
}