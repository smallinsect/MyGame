/*
mciSendCommand�������֣����ü򵥣�����ǿ�󣬵�����ֻ��ͬʱ����һ��
 �ļ������е���Ŀ����Ҫͬʱ���ż����ļ���ʵ�ֻ���Ч������ʱ��Ҫʹ��
DirectSound��������������ˣ�
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
//	//�����ļ�����
//	gStatus.dwItem = MCI_STATUS_LENGTH;
//	mciSendCommand(gMciOpen.wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&gStatus);
//	DWORD dwLen = gStatus.dwReturn;
//
//	//��ǰ���ų���
//	gStatus.dwItem = MCI_STATUS_POSITION;
//	mciSendCommand(gMciOpen.wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&gStatus);
//	DWORD dwCurLen = gStatus.dwReturn;
//
//	cout << "�ļ�����: " << dwLen << ",��ǰ����λ��: " << dwCurLen << endl;
//
//	//ѭ������
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
////	���ŷ�����
////PlayBeep();
////
////����ϵͳ����(wav��ʽ)
////PlaySysMusic();
////
////�����Լ���wav��ʽ������
////PlayWavMusic();
////
////����MP3(��ȻwavҲ�ܲ���)
////PlayMp3Music_1();
////
////����MP3
////PlayMp3Music_2();
////
////����MP3(ѭ�����š���ǰ����)
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
//	if (flag >= 5) {//��������
//		n += 1;
//	}
//	int cnt = 0;
//	while (n > 0) {//����ת�ַ���
//		num[cnt++] = n % 10 + '0';
//		n /= 10;//ȥ������ĩβ
//		if (cnt == 2) {
//			num[cnt++] = '.';//���С����
//		}
//	}
//	num[cnt] = '\0';//�ַ������һλ��'\0'
//}
//
//void print(int lent, char num[]) {
//	int len = strlen(num);
//	//�����ӡ�Ŀո�����
//	lent = lent - len;
//	while (lent--) {
//		printf(" ");
//	}
//	//��ӡ����
//	for (len = len - 1; len >= 0; --len) {
//		printf("%c", num[len]);
//	}
//}
//
//
//void test() {
//	//201930.00 4.36
//	//983850.00 6.67
//	LL money = scan() * 100;//����10000��
//	LL rate = scan();//����100��
//
//	LL ra = money * rate;//��Ϣ
//	LL total = money * 10000 + ra;//�ܽ�
//	char szMoney[30];
//	char szRa[30];
//	char szTotal[30];
//	change(money * 10000, szMoney);//����ת�ַ���ʱ��������
//	change(ra, szRa);
//	change(total, szTotal);
//	//���ڼ��㣬�������һ�����ܽ�
//	int lent = strlen(szTotal);
//
//	printf("����");
//	print(lent, szMoney);
//	printf("Ԫ\n");
//	printf("��Ϣ��");
//	print(lent, szRa);
//	printf("Ԫ\n");
//	printf("�ϼƣ�");
//	print(lent, szTotal);
//	printf("Ԫ\n");
//}

void test1() {
	cout << "����test����..." << endl;
}

class A {
public:
	A() {
		test1();
		cout << "���ǹ��캯��..." << endl;
	}
};

A a;

int main()
{
	cout << "����������main" << endl;

	system("pause");
	return 0;
}
