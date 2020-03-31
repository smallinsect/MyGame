#include <stdio.h>
#include <conio.h>
#include <graphics.h>

#define Width 480
#define High 480

#define Size 33

IMAGE img;




int main() {
	loadimage(&img, _T("./image/fangkuai.png"));

	initgraph(Width, High);

	putimage(0, 0, &img);

	for (int i = 0; i < 6; i++) {
		putimage(50, 50+Size*i, Size, Size, &img, i*Size, 0);
	}

	_getch();
	closegraph();
	return 0;
}