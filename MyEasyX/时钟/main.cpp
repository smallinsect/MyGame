
#include <graphics.h>
#include <conio.h>


#define High 480
#define Width 640

int main() {

	SYSTEMTIME st;

	initgraph(Width, High);

	//��ȡ��ǰϵͳʱ��
	GetLocalTime(&st);


	_getch();
	closegraph();

	return 0;
}