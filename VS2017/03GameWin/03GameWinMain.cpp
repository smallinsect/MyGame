
#include <time.h>
#include <stdlib.h>

#include <Windows.h>

#include "resource.h"

HINSTANCE g_hInstace;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR lpCmdLine, int nCmdShow) {
	g_hInstace = hInstance;
	TCHAR szClassName[] = TEXT("my window");


	MSG msg;
	HWND hWnd;
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = szClassName;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wc)) {
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szClassName, MB_OK);
		return 0;
	}

	hWnd = CreateWindow(szClassName,
		TEXT("Game"),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		640+16, 480+39,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {

	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	HINSTANCE hInstance;
	BITMAP bitmap;
	TCHAR szBuffer[64];
	int len;

	HBITMAP hBitmap;
	static int cxPlane, cyPlane, cxBack, cyBack, cxBullet, cyBullet, cxClient, cyClient;
	static HBRUSH hBrush;
	static HDC hdcPlane, hdcBack, hdcBullet;
	static int planeX;//�ɻ�X��λ��
	static int planeY;//�ɻ�Y��λ��
	static int speed;//�ɻ��ٶ�

	switch (Msg) {
	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;

		hdc = GetDC(hWnd);

		//����������DC���طɻ�
		hdcPlane = CreateCompatibleDC(hdc);
		hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));//���طɻ�ͼƬ
		SelectObject(hdcPlane, hBitmap);//�󶨼�����DC�ͷɻ�ͼƬ

		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		cxPlane = bitmap.bmWidth;
		cyPlane = bitmap.bmHeight;

		//��������ͼƬ������DC
		hdcBack = CreateCompatibleDC(hdc);
		hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP2));//���ر���ͼƬ
		SelectObject(hdcBack, hBitmap);//�󶨼�����DC�ͱ���ͼƬ

		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		cxBack = bitmap.bmWidth;
		cyBack = bitmap.bmHeight;

		//�����ӵ�������DC
		hdcBullet = CreateCompatibleDC(hdc);
		hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP3));//�����ӵ�ͼƬ
		SelectObject(hdcBullet, hBitmap);//�󶨼�����DC���ӵ�ͼƬ
		
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		cxBullet = bitmap.bmWidth;
		cyBullet = bitmap.bmHeight;

		ReleaseDC(hWnd, hdc);

		planeX = planeY = 0;
		speed = 10;

		break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		break;
	case WM_TIMER:
		hdc = GetDC(hWnd);

		//InvalidateRect(hWnd, NULL, TRUE);

		ReleaseDC(hWnd, hdc);
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_UP://��
			if (planeY-speed >= 0) {
				planeY = planeY - speed;
			}
			break;
		case VK_RIGHT://��
			if (planeX+speed < 640-cxPlane) {
				planeX = planeX + speed;
			}
			break;
		case VK_DOWN://��
			if (planeY+speed < 480-cyPlane) {
				planeY = planeY + speed;
			}
			break;
		case VK_LEFT://��
			if (planeX-speed >= 0) {
				planeX = planeX - speed;
			}
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		//GetWindowRect(hWnd, &rect);
		//len = wsprintf(szBuffer, TEXT("left=%d top=%d right=%d bottom=%d"), rect.left, rect.top, rect.right, rect.bottom);
		//TextOut(hdc, 0, 0, szBuffer, len);

		//GetClientRect(hWnd, &rect);
		//len = wsprintf(szBuffer, TEXT("left=%d top=%d right=%d bottom=%d"), rect.left, rect.top, rect.right, rect.bottom);
		//TextOut(hdc, 0, 30, szBuffer, len);

		BitBlt(hdc, 0, 0, cxBack, cyBack, hdcBack, 0, 0, SRCCOPY);
		BitBlt(hdc, planeX, planeY, cxPlane, cyPlane, hdcPlane, 0, 0, SRCCOPY);
		BitBlt(hdc, 0, 0, cxBullet, cyBullet, hdcBullet, 0, 0, SRCCOPY);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);

		DeleteObject(hBrush);

		DeleteDC(hdcPlane);
		DeleteDC(hdcBack); 
		DeleteDC(hdcBullet);
		//KillTimer(hWnd, ID_TIMER1);
		break;
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}