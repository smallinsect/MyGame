#include "pch.h"
#include "CMyRole.h"

void CMyRole::Init(LPTSTR name, int iPerFrameWidth, int iPerFrameHeight, int iFrameNum, int iPosX, int iPosY) {
	HBITMAP hbmp = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if (hbmp == NULL) {
		AfxMessageBox(TEXT("º”‘ÿŒªÕº ß∞‹"));
		return;
	}
	m_role.Attach(hbmp);
	m_role.GetBitmap(&m_bm);
}
void CMyRole::Update() {
}
void CMyRole::Draw(HDC hDc, int x, int y) {

}