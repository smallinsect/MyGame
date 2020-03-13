#include <graphics.h>//引用EasyX图形库
#include <conio.h>

#define WIDTH 640 //窗口宽度
#define HIGH 480 //窗口高度

int main() {
	//小球半径
	float radius = 20;
	//小球坐标，初始化
	float ball_x = WIDTH / 2;
	float ball_y = HIGH / 2;
	//小球速度
	float ball_vx = 1;
	float ball_vy = 1;

	initgraph(WIDTH, HIGH);//初始化640*480的画布

	BeginBatchDraw();//开始批量绘制
	while (1) {
		//在窗口上画一个圆
		setcolor(YELLOW);//圆的线条为黄色
		setfillcolor(GREEN);//圆内部为绿色填充
		fillcircle(ball_x, ball_y, radius);//画圆，圆心（100,100），半径20

		FlushBatchDraw();//刷新批量绘制

		Sleep(3);
		//把窗口上的圆擦掉
		setcolor(BLACK);//圆的线条为黑色
		setfillcolor(BLACK);//圆内部为黑色填充
		fillcircle(ball_x, ball_y, radius);//画圆，圆心（100,100），半径20

		ball_x += ball_vx;
		ball_y += ball_vy;

		if (ball_x <= radius || ball_x >= WIDTH - radius) {
			ball_vx = -ball_vx;
		}
		if (ball_y <= radius || ball_y >= HIGH - radius) {
			ball_vy = -ball_vy;
		}
	}

	EndBatchDraw();//结束批量绘制

	_getch();//按任意键继续
	closegraph();//关闭图形界面
	return 0;
}