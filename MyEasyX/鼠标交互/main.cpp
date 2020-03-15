
#include <graphics.h>
#include <conio.h>


#define High 480
#define Width 640

int main() {

	initgraph(Width, High);

	
	MOUSEMSG m;//定义鼠标消息
	while (1) {
		//获取一套鼠标消息
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE) {
			//鼠标移动的时候画标色的点
			putpixel(m.x, m.y, WHITE);
		}
		else if (m.uMsg == WM_LBUTTONDOWN) {
			//鼠标左键按下时 在鼠标位置画一个方块
			rectangle(m.x - 5, m.y - 5, m.x + 5, m.y + 5);
		}
		else if (m.uMsg == WM_RBUTTONDOWN) {
			//鼠标右键按下时 在鼠标位置画一个圆
			circle(m.x, m.y, 5);
		}
	}

	_getch();
	closegraph();

	return 0;
}