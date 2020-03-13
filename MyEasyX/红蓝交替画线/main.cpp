#include <graphics.h>//引用EasyX图形库
#include <conio.h>

int main() {
	initgraph(640, 256);//初始化640*480的画布

	for (int y = 0; y < 200; y += 5) {
		if (y / 5 % 2 == 1) {//判断是否为奇偶行
			setcolor(RGB(255, 0, 0));
		}
		else {
			setcolor(RGB(0, 0, 255));
		}
		line(0, y, 640, y);
	}

	_getch();//按任意键继续
	closegraph();//关闭图形界面
	return 0;
}