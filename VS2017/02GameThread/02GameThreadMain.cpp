//
////CreateThread 创建线程测试
//#include <stdio.h>
//#include <conio.h>
//#include <stdlib.h>
//#include <windows.h>
//
//DWORD WINAPI ThreadFunc(LPVOID);
//
//int main() {
//
//	HANDLE hThred1;
//	HANDLE hThred2;
//
//	DWORD exitCode1 = 0;
//	DWORD exitCode2 = 0;
//
//	DWORD threadId;
//	hThred1 = CreateThread(NULL, 0, ThreadFunc, (LPVOID)1, 0, &threadId);
//	if (hThred1) {
//		printf("Thread 1 launched ...\n");
//	}
//	hThred2 = CreateThread(NULL, 0, ThreadFunc, (LPVOID)2, 0, &threadId);
//	if (hThred2) {
//		printf("Thread 2 launched ...\n");
//	}
//
//	while (true) {
//		printf("Press any key to exit ...\n");
//		_getch();
//
//		GetExitCodeThread(hThred1, &exitCode1);
//		GetExitCodeThread(hThred2, &exitCode2);
//
//		if (exitCode1 == STILL_ACTIVE) {
//			puts("Thread 1 is still running !");
//		}
//		if (exitCode2 == STILL_ACTIVE) {
//			puts("Thread 2 is still runnig !");
//		}
//		if (exitCode1 != STILL_ACTIVE && exitCode2 != STILL_ACTIVE) {
//			break;
//		}
//	}
//
//	CloseHandle(hThred1);
//	CloseHandle(hThred2);
//
//	printf("Thread 1 returned %d\n", exitCode1);
//	printf("Thread 2 returned %d\n", exitCode2);
//
//	system("pause");
//	return 0;
//}
//
//DWORD WINAPI ThreadFunc(LPVOID n) {
//	Sleep((DWORD)n*1000*2);
//	return (DWORD)n * 10;
//}