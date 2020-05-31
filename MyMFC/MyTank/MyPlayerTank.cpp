#include "pch.h"
#include "MyPlayerTank.h"


void MyPlayerTank::Init() {
	TCHAR name[64];
	HBITMAP hBmp;
	for (int i = 0; i < 4; i++) {
		swprintf(name, TEXT("./res/img/player0/m0-%d-%d.bmp"), i, 1);
		hBmp = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		if (hBmp == NULL) {
			AfxMessageBox(TEXT("¼ÓÔØÎ»Í¼Ê§°Ü"));
			return;
		}
		swprintf(name, TEXT("./res/img/player0/m0-%d-%d.bmp"), i, 2);
		hBmp = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
		if (hBmp == NULL) {
			AfxMessageBox(TEXT("¼ÓÔØÎ»Í¼Ê§°Ü"));
			return;
		}
	}
}

void MyPlayerTank::Draw(CDC* pDC) {
}