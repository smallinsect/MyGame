#include <graphics.h>//引用EasyX图形库
#include <conio.h>

int main() {
 	initgraph(640, 480);//初始化640*480的画布
	setcolor(YELLOW);//圆的线条为黄色
	setfillcolor(GREEN);//圆内部为绿色填充
	fillcircle(100, 100, 20);//画圆，圆心（100,100），半径20

	line(0, 0, 300, 300);//画一条线

	circle(111, 222, 30);//画一个圆环

	_getch();//按任意键继续
	closegraph();//关闭图形界面
	return 0;
}