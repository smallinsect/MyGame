#include <stdio.h>

//���ݳ�ʼ��
void startup() {
}
//��ʾ����
void show() {
}
//���û������޹صĸ���
void updateWithoutInput() {
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