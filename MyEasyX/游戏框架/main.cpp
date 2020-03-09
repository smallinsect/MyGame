#include <stdio.h>

//数据初始化
void startup() {
}
//显示画面
void show() {
}
//于用户输入无关的更新
void updateWithoutInput() {
}
//与用户输入有关的更新
void updateWithInput() {
}

int main() {

	startup();//数据初始化
	while (1) {//游戏循环执行
		show();//显示画面
		updateWithoutInput();//于用户输入无关的更新
		updateWithInput();//与用户输入有关的更新
	}

	return 0;
}