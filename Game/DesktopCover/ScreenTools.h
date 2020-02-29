#pragma once

#include "stdafx.h"

class CScreenTools {
private:
	CScreenTools() {
	}

	~CScreenTools() {
	}

private:
	//计算位图文件每个像素所占字节数
	static int GetBits() {
	}
	//确定是多少位的位图
	static int GetBitCount() {
	}
	static BOOL WriteBmpDataToFile(PCTSTR szFileName,
		PBITMAPINFOHEADER pBitmapInfoHeader,
		DWORD dwPaletterSize, DWORD dwBmBitsSize) {
	}

public:
	//保存到文件
	static int SaveBitmapToFile(HBITMAP hBitmap, LPCSTR lpFileName) {}
	//获取位图句柄
	static HBITMAP CopyScreenToBitmap(LPRECT lpRect) {
		if (IsRectEmpty(lpRect)) {
			return NULL;
		}
		HDC hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
		HDC hMemDC = CreateCompatibleDC(hScrDC);
		//获得选定区域坐标
		int nX1 = lpRect->left;
		int nY1 = lpRect->top;
		int nX2 = lpRect->right;
		int nY2 = lpRect->bottom;
		//获得屏幕分辨率
		int xScrn = GetDeviceCaps(hScrDC, HORZRES);
		int	yScrn = GetDeviceCaps(hScrDC, VERTRES);
		//确保选定区域是可见的
		nX1 = nX1 < 0 ? 0 : nX1;
		nY1 = nY1 < 0 ? 0 : nY1;
		nX2 = nX2 > xScrn ? 0 : nX2;
		nY2 = nY2 > yScrn ? 0 : nY2;
		int nWidth = nX2 - nX1;
		int nHeight= nY2 - nY1;
		//创建一个与屏幕设备秒速表兼容的位图
		HBITMAP hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);
		//把新的位图宣导内存设备描述表中
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
		//把屏幕设备描述表复制到内存设备描述表中
		BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, nX1, nY1, SRCCOPY);
		//得到屏幕位图的句柄
		hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
		//清除
		DeleteDC(hScrDC);
		DeleteDC(hMemDC);
		return hBitmap;
	}
	//全屏截图
	static HBITMAP PrintScreen() {
		CRect rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = GetSystemMetrics(SM_CXSCREEN);
		rect.bottom = GetSystemMetrics(SM_CYSCREEN);
		return CopyScreenToBitmap(rect);
	}
	//截指定窗体
	static HBITMAP PrintWindow(HWND hwnd) {}

	static void DawMouse(POINT pnt) {}
};