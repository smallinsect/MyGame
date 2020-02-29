
////创建线程测试
//#include <stdio.h>
//#include <windows.h>
//
//DWORD WINAPI ThreadFunc(LPVOID);
//
//int main() {
//	HANDLE hThread;
//
//	DWORD threadId;
//	for (int i = 0; i < 5; ++i) {
//		hThread = CreateThread(NULL, 0, ThreadFunc, (LPVOID)i, 0, &threadId);
//		if (hThread) {
//			printf("Thread launched %d\n", i);
//			CloseHandle(hThread);
//		}
//	}
//
//	Sleep(3000);
//	printf("end\n");
//	system("pause");
//	return 0;
//}
//
//DWORD WINAPI ThreadFunc(LPVOID lpParam) {
//	DWORD n = (DWORD)lpParam;
//	for (int i = 0; i < 10; ++i) {
//		printf("%d%d%d%d%d%d\n", n, n, n, n, n, n);
//	}
//	return n;
//}