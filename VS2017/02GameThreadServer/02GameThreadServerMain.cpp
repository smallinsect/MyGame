//////////////////////////////////////////////////////////////////////////
//
// �������˳���
//
//////////////////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

typedef struct STSOCKET {
	SOCKET mySocket;
	sockaddr_in myAddr;
	int myAddrLen;

	STSOCKET() {
		memset(&myAddr, 0, sizeof(sockaddr_in));
		myAddrLen = sizeof(sockaddr_in);
	}
} STSOCKET, *PSTSOCKET;

DWORD WINAPI ThreadFuncClientSocket(PVOID pvParam);

int main() {
	puts("hello world");

	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);

	//�����������׽���
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == SOCKET_ERROR) {
		puts("socket error ...");
		system("pause");
		exit(-1);
	}
	puts("socket success ...");
	//��������IP�Ͷ˿�
	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (bind(serverSocket, (const sockaddr *)&saddr, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		puts("bind error ...");
		system("pause");
		exit(-1);
	}
	puts("bind success ...");

	//��������ʼ����
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		puts("listen error ...");
		system("pause");
		exit(-1);
	}
	puts("listen success ...");

	PSTSOCKET pStSocket;
	while (true) {
		pStSocket = new STSOCKET();
		pStSocket->mySocket = accept(serverSocket, (sockaddr *)&pStSocket->myAddr, &pStSocket->myAddrLen);
		if (pStSocket->mySocket == SOCKET_ERROR) {
			printf("accept error ...\n");
			break;
		}
		printf("accept success ...\n");
		DWORD threadId;
		HANDLE handle = CreateThread( NULL, 0, ThreadFuncClientSocket, (PVOID)pStSocket, 0, &threadId);
		if (handle) {
			printf("create thread success ...\n");
			CloseHandle(handle);
		}
	}

	closesocket(serverSocket);

	WSACleanup();

	system("pause");
	return 0;
}

DWORD WINAPI ThreadFuncClientSocket(PVOID pvParam) {
	int iRet = 0;

	PSTSOCKET client = (PSTSOCKET)pvParam;

	char buf[1024];
	wsprintf(buf, TEXT("���������ӳɹ�..."));
	if (send(client->mySocket, buf, strlen(buf)+1, 0) == SOCKET_ERROR) {
		printf("send error ...\n");
		printf("client ip : %s\n", inet_ntoa(client->myAddr.sin_addr));
		printf("client port:%hu\n", client->myAddr.sin_port);
		closesocket(client->mySocket);
		return -1;
	}

	printf("send success ...\n");
	printf("client ip : %s\n", inet_ntoa(client->myAddr.sin_addr));
	printf("client port:%hu\n", client->myAddr.sin_port);
	while (true) {
		if (recv(client->mySocket, buf, sizeof(buf), 0) == SOCKET_ERROR) {
			printf("recv error ...");
			printf("client ip : %s\n", inet_ntoa(client->myAddr.sin_addr));
			printf("client port:%hu\n", client->myAddr.sin_port);
			closesocket(client->mySocket);
			return -1;
		}
		printf("recv success ...\n");
		printf("%s\n", buf);
	}
	closesocket(client->mySocket);
	delete client;

	return iRet;
}