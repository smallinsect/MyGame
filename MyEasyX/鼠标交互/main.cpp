
#include <graphics.h>
#include <conio.h>


#define High 480
#define Width 640

int main() {

	initgraph(Width, High);

	
	MOUSEMSG m;//���������Ϣ
	while (1) {
		//��ȡһ�������Ϣ
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE) {
			//����ƶ���ʱ�򻭱�ɫ�ĵ�
			putpixel(m.x, m.y, WHITE);
		}
		else if (m.uMsg == WM_LBUTTONDOWN) {
			//����������ʱ �����λ�û�һ������
			rectangle(m.x - 5, m.y - 5, m.x + 5, m.y + 5);
		}
		else if (m.uMsg == WM_RBUTTONDOWN) {
			//����Ҽ�����ʱ �����λ�û�һ��Բ
			circle(m.x, m.y, 5);
		}
	}

	_getch();
	closegraph();

	return 0;
}