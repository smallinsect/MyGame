
#include <graphics.h>
#include <conio.h>


#define High 480
#define Width 640

int main() {

	SYSTEMTIME st;

	initgraph(Width, High);

	//获取当前系统时间
	GetLocalTime(&st);


	_getch();
	closegraph();

	return 0;
}