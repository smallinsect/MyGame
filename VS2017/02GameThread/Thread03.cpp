#include <math.h>
#include <stdlib.h>
#include <process.h>
#include <windows.h>

#define WINCHILDSIZE 4
#define TIMES 300

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc1(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc2(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc3(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc4(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

void Thread1(PVOID pvoid);
void Thread2(PVOID pvoid);
void Thread3(PVOID pvoid);
void Thread4(PVOID pvoid);

int CheckBottom(HWND hwnd, int cyClient, int cyChar, int cnt);

typedef struct {
	HWND hwnd;
	int cxClient, cyClient;
	int cyChar;
	BOOL bKill;
} PARAMS, *PPARAMS;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPTSTR lpCmdLine, int nCmdShow) {

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
		TEXT("CLOCK"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
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
	int cxClient, cyClient;
	
	static HWND hwndChild[WINCHILDSIZE];
	static WNDPROC childProc[WINCHILDSIZE] = { WndProc1, WndProc2, WndProc3, WndProc4 };
	static const TCHAR *szChildClass[WINCHILDSIZE] = {TEXT("Child1"), TEXT("Child2"), TEXT("Child3"), TEXT("Child4")};
	WNDCLASS wndclass;
	HINSTANCE hInstance;

	switch (Msg) {
	case WM_CREATE:
		hInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndclass.hInstance = hInstance;
		wndclass.lpszMenuName = NULL;
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		for (int i = 0; i < WINCHILDSIZE; ++i) {
			wndclass.lpfnWndProc = childProc[i];
			wndclass.lpszClassName = szChildClass[i];
			RegisterClass(&wndclass);
			hwndChild[i] = CreateWindow( szChildClass[i], NULL, 
				WS_CHILDWINDOW | WS_BORDER | WS_VISIBLE,
				0, 0, 0, 0,
				hWnd, (HMENU)i, hInstance,NULL);

		}

		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			MessageBox(NULL, TEXT("确定退出程序"), TEXT("小昆虫提示"), MB_OK);
			for (int i = 0; i < WINCHILDSIZE; ++i) {
				DestroyWindow(hwndChild[i]);
			}
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		for (int i = 0; i < WINCHILDSIZE; ++i) {
			MoveWindow(hwndChild[i], 
				(i%2)*cxClient/2, (i/2)*cyClient/2,
				cxClient / 2, cyClient / 2,
				TRUE);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}


LRESULT CALLBACK WndProc1(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	static PARAMS params;
	switch (Msg) {
	case WM_CREATE:
		params.hwnd = hWnd;
		params.cyChar = HIWORD(GetDialogBaseUnits());

		_beginthread(Thread1, 0, (PVOID)&params);
		break;
	case WM_SIZE:
		params.cyClient = HIWORD(lParam);
		break;
	case WM_DESTROY:
		params.bKill = TRUE;
		break;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

LRESULT CALLBACK WndProc2(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	static PARAMS params;
	switch (Msg) {
	case WM_CREATE:
		params.hwnd = hWnd;
		params.cyChar = HIWORD(GetDialogBaseUnits());

		_beginthread(Thread2, 0, (PVOID)&params);
		break;
	case WM_SIZE:
		params.cyClient = HIWORD(lParam);
		break;
	case WM_DESTROY:
		params.bKill = TRUE;
		break;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

LRESULT CALLBACK WndProc3(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	static PARAMS params;
	switch (Msg) {
	case WM_CREATE:
		params.hwnd = hWnd;
		params.cyChar = HIWORD(GetDialogBaseUnits());

		_beginthread(Thread3, 0, (PVOID)&params);
		break;
	case WM_SIZE:
		params.cyClient = HIWORD(lParam);
		break;
	case WM_DESTROY:
		params.bKill = TRUE;
		break;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

LRESULT CALLBACK WndProc4(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	static PARAMS params;
	switch (Msg) {
	case WM_CREATE:
		params.hwnd = hWnd;
		params.cyChar = HIWORD(GetDialogBaseUnits());

		_beginthread(Thread4, 0, (PVOID)&params);
		break;
	case WM_SIZE:
		params.cxClient = LOWORD(lParam);
		params.cyClient = HIWORD(lParam);
		break;
	case WM_DESTROY:
		params.bKill = TRUE;
		break;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

void Thread1(PVOID pvoid) {
	TCHAR szBuf[1024] = "";

	int num = 0;
	int cnt = 0;

	PPARAMS pparams = (PPARAMS)pvoid;
	pparams->bKill = FALSE;
	while (!pparams->bKill) {
		cnt = CheckBottom(pparams->hwnd, pparams->cyClient, pparams->cyChar, cnt);

		HDC hdc = GetDC(pparams->hwnd);

		wsprintf(szBuf, TEXT("%d"), num);
		TextOut(hdc, 0, cnt*pparams->cyChar, szBuf, lstrlen(szBuf));

		ReleaseDC(pparams->hwnd, hdc);

		++num;
		++cnt;
		Sleep(TIMES);
	}
	_endthread();
}
void Thread2(PVOID pvoid) {
	TCHAR szBuf[1024] = "";

	int num = 1;
	int cnt = 0;
	PPARAMS pparams = (PPARAMS)pvoid;
	pparams->bKill = FALSE;
	while (!pparams->bKill) {
		cnt = CheckBottom(pparams->hwnd, pparams->cyClient, pparams->cyChar, cnt);

		HDC hdc = GetDC(pparams->hwnd);

		while (true) {
			++num;
			int iSqrt = (int)sqrt((double)num);
			int i;
			for (i = 2; i <= iSqrt; ++i) {
				if (num % i == 0) {
					break;
				}
			}
			if (i > iSqrt) {
				break;
			}
		}


		wsprintf(szBuf, TEXT("%d"), num);
		TextOut(hdc, 0, cnt*pparams->cyChar, szBuf, lstrlen(szBuf));

		ReleaseDC(pparams->hwnd, hdc);
		++cnt;

		Sleep(TIMES);
	}

	_endthread();
}
void Thread3(PVOID pvoid) {
	TCHAR szBuf[1024] = "";

	int a = 0, b = 1, c;
	int cnt = 0;
	PPARAMS pparams = (PPARAMS)pvoid;
	pparams->bKill = FALSE;
	while (!pparams->bKill) {
		cnt = CheckBottom(pparams->hwnd, pparams->cyClient, pparams->cyChar, cnt);

		HDC hdc = GetDC(pparams->hwnd);

		c = a + b;
		a = b;
		b = c;
		wsprintf(szBuf, TEXT("%d"), c);
		TextOut(hdc, 0, cnt*pparams->cyChar, szBuf, lstrlen(szBuf));

		ReleaseDC(pparams->hwnd, hdc);
		++cnt;

		Sleep(TIMES);
	}

	_endthread();
}
void Thread4(PVOID pvoid) {

	PPARAMS pparams = (PPARAMS)pvoid;
	pparams->bKill = FALSE;
	while (!pparams->bKill) {
		InvalidateRect(pparams->hwnd, NULL, TRUE);
		UpdateWindow(pparams->hwnd);

		int iDiameter = rand() % max(1, min(pparams->cxClient, pparams->cyClient));

		HDC hdc = GetDC(pparams->hwnd);

		Ellipse(hdc, 
			(pparams->cxClient - iDiameter) / 2,
			(pparams->cyClient - iDiameter) / 2,
			(pparams->cxClient + iDiameter) / 2,
			(pparams->cyClient + iDiameter) / 2);

		ReleaseDC(pparams->hwnd, hdc);

		Sleep(TIMES);
	}

	_endthread();
}

int CheckBottom(HWND hwnd, int cyClient, int cyChar, int cnt) {

	if (cyChar * cnt > cyClient) {
		InvalidateRect(hwnd, NULL, TRUE);
		UpdateWindow(hwnd);

		cnt = 0;
	}

	return cnt;
}