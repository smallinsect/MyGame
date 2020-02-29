/*
mciSendCommand播放音乐，调用简单，功能强大，但是它只能同时播放一个
 文件，而有的项目中需要同时播放几个文件，实现混音效果，这时就要使用
DirectSound或者其它库或技术了！
*/
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <MMSystem.h>
#include <map>
#include <iostream>
using namespace std;
//#pragma comment(lib, "WINMM.LIB")
//
//
//void PlayBeep()
//{
//	Beep(3000, 500);
//}
//
//void PlaySysMusic()
//{
//	MessageBeep(MB_OK);
//	Sleep(800);
//	MessageBeep(MB_ICONWARNING);
//	Sleep(800);
//	MessageBeep(MB_ICONSTOP);
//	Sleep(800);
//	MessageBeep(MB_ICONERROR);
//	Sleep(800);
//	MessageBeep(MB_ICONEXCLAMATION);
//}
//
//void PlayWavMusic()
//{
//	PlaySound("GAME_WIN.WAV", NULL/*AfxGetInstanceHandle()*/, SND_FILENAME | SND_ASYNC);
//}
//
//void PlayMp3Music_1()
//{
//	mciSendString("musicback.mp3", NULL, 0, 0);
//	mciSendString("musicback.mp3", NULL, 0, 0);
//}
//
//void PlayMp3Music_2()
//{
//	MCI_OPEN_PARMS MciOpen;
//	MCI_PLAY_PARMS MciPlay;
//	MciOpen.lpstrElementName = "musicback.mp3";
//	MciOpen.lpstrDeviceType = NULL;
//
//	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&MciOpen);
//	UINT wDeviceID = MciOpen.wDeviceID;
//	mciSendCommand(wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& MciPlay);
//}
//
//#define TIMER_MUSIC_STATE 100
//MCI_OPEN_PARMS    gMciOpen;
//MCI_PLAY_PARMS    gMciPlay;
//MCI_STATUS_PARMS  gStatus;
//map<UINT_PTR, int> mapTimer;
//void CheckMusicState()
//{
//	//播放文件长度
//	gStatus.dwItem = MCI_STATUS_LENGTH;
//	mciSendCommand(gMciOpen.wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&gStatus);
//	DWORD dwLen = gStatus.dwReturn;
//
//	//当前播放长度
//	gStatus.dwItem = MCI_STATUS_POSITION;
//	mciSendCommand(gMciOpen.wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&gStatus);
//	DWORD dwCurLen = gStatus.dwReturn;
//
//	cout << "文件长度: " << dwLen << ",当前播放位置: " << dwCurLen << endl;
//
//	//循环播放
//	if (dwLen == dwCurLen)
//	{
//		mciSendCommand(gMciOpen.wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL);
//		mciSendCommand(gMciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& gMciPlay);
//	}
//}
//void CALLBACK TimerProc(HWND, UINT message, UINT_PTR idTimer, DWORD dwTime)
//{
//	if (WM_TIMER == message)
//	{
//		switch (mapTimer[idTimer])
//		{
//		case TIMER_MUSIC_STATE:
//			CheckMusicState();
//			break;
//		default:
//			break;
//		}
//	}
//}
//void PlayMp3Music_3()
//{
//	gMciOpen.lpstrElementName = "musicback.mp3";
//	gMciOpen.lpstrDeviceType = NULL;
//
//
//	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&gMciOpen);
//	mciSendCommand(gMciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)& gMciPlay);
//
//
//	UINT_PTR timer = SetTimer(NULL, TIMER_MUSIC_STATE, 1000, TimerProc);
//	mapTimer.insert(pair<UINT_PTR, int>(timer, TIMER_MUSIC_STATE));
//	MSG msg;
//	while (GetMessage(&msg, NULL, 0, 0))
//	{
//		if (msg.message == WM_TIMER)
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//	}
//}
//
//void func() {
////	播放蜂鸣器
////PlayBeep();
////
////播放系统声音(wav格式)
////PlaySysMusic();
////
////播放自己的wav格式的声音
////PlayWavMusic();
////
////播放MP3(当然wav也能播放)
////PlayMp3Music_1();
////
////播放MP3
////PlayMp3Music_2();
////
////播放MP3(循环播放、当前进度)
////PlayMp3Music_3();
//}
//
//
//typedef long long LL;
//
//LL scan() {
//	char szNum[100];
//	scanf("%s", szNum);
//	LL d = 0;
//	for (int i = 0; szNum[i] != '\0'; ++i) {
//		if (szNum[i] == '.') {
//			continue;
//		}
//		d = d * 10 + (szNum[i] - '0');
//	}
//	return d;
//}
//
//void change(LL n, char num[]) {
//	LL flag = n % 1000000 / 100000;
//	n /= 1000000;
//	if (flag >= 5) {//四舍五入
//		n += 1;
//	}
//	int cnt = 0;
//	while (n > 0) {//数字转字符串
//		num[cnt++] = n % 10 + '0';
//		n /= 10;//去掉整数末尾
//		if (cnt == 2) {
//			num[cnt++] = '.';//添加小数点
//		}
//	}
//	num[cnt] = '\0';//字符串最后一位补'\0'
//}
//
//void print(int lent, char num[]) {
//	int len = strlen(num);
//	//计算打印的空格数量
//	lent = lent - len;
//	while (lent--) {
//		printf(" ");
//	}
//	//打印数字
//	for (len = len - 1; len >= 0; --len) {
//		printf("%c", num[len]);
//	}
//}
//
//
//void test() {
//	//201930.00 4.36
//	//983850.00 6.67
//	LL money = scan() * 100;//扩大10000倍
//	LL rate = scan();//扩大100倍
//
//	LL ra = money * rate;//利息
//	LL total = money * 10000 + ra;//总金
//	char szMoney[30];
//	char szRa[30];
//	char szTotal[30];
//	change(money * 10000, szMoney);//数字转字符串时四舍五入
//	change(ra, szRa);
//	change(total, szTotal);
//	//由于计算，最长的数字一定是总金
//	int lent = strlen(szTotal);
//
//	printf("本金：");
//	print(lent, szMoney);
//	printf("元\n");
//	printf("利息：");
//	print(lent, szRa);
//	printf("元\n");
//	printf("合计：");
//	print(lent, szTotal);
//	printf("元\n");
//}

void test1() {
	cout << "我是test函数..." << endl;
}

class A {
public:
	A() {
		test1();
		cout << "我是构造函数..." << endl;
	}
};

A a;

int main()
{
	cout << "我是主函数main" << endl;

	system("pause");
	return 0;
}
