#pragma once

#include "stdafx.h"

class CScreenTools {
private:
	CScreenTools() {
	}

	~CScreenTools() {
	}

private:
	//����λͼ�ļ�ÿ��������ռ�ֽ���
	static int GetBits() {
	}
	//ȷ���Ƕ���λ��λͼ
	static int GetBitCount() {
	}
	static BOOL WriteBmpDataToFile(PCTSTR szFileName,
		PBITMAPINFOHEADER pBitmapInfoHeader,
		DWORD dwPaletterSize, DWORD dwBmBitsSize) {
	}

public:
	//���浽�ļ�
	static int SaveBitmapToFile(HBITMAP hBitmap, LPCSTR lpFileName) {}
	//��ȡλͼ���
	static HBITMAP CopyScreenToBitmap(LPRECT lpRect) {
		if (IsRectEmpty(lpRect)) {
			return NULL;
		}
		HDC hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
		HDC hMemDC = CreateCompatibleDC(hScrDC);
		//���ѡ����������
		int nX1 = lpRect->left;
		int nY1 = lpRect->top;
		int nX2 = lpRect->right;
		int nY2 = lpRect->bottom;
		//�����Ļ�ֱ���
		int xScrn = GetDeviceCaps(hScrDC, HORZRES);
		int	yScrn = GetDeviceCaps(hScrDC, VERTRES);
		//ȷ��ѡ�������ǿɼ���
		nX1 = nX1 < 0 ? 0 : nX1;
		nY1 = nY1 < 0 ? 0 : nY1;
		nX2 = nX2 > xScrn ? 0 : nX2;
		nY2 = nY2 > yScrn ? 0 : nY2;
		int nWidth = nX2 - nX1;
		int nHeight= nY2 - nY1;
		//����һ������Ļ�豸���ٱ���ݵ�λͼ
		HBITMAP hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);
		//���µ�λͼ�����ڴ��豸��������
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
		//����Ļ�豸�������Ƶ��ڴ��豸��������
		BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, nX1, nY1, SRCCOPY);
		//�õ���Ļλͼ�ľ��
		hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
		//���
		DeleteDC(hScrDC);
		DeleteDC(hMemDC);
		return hBitmap;
	}
	//ȫ����ͼ
	static HBITMAP PrintScreen() {
		CRect rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = GetSystemMetrics(SM_CXSCREEN);
		rect.bottom = GetSystemMetrics(SM_CYSCREEN);
		return CopyScreenToBitmap(rect);
	}
	//��ָ������
	static HBITMAP PrintWindow(HWND hwnd) {}

	static void DawMouse(POINT pnt) {}
};