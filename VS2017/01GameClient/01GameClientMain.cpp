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

int main() {

	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);

	//�����ͻ����׽���
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		puts("socket error ...");
		system("pause");
		exit(-1);
	}
	puts("socket success ...");

	sockaddr_in caddr;
	caddr.sin_family = AF_INET;
	caddr.sin_port = htons(8080);
	caddr.sin_addr.S_un.S_addr = inet_addr("192.168.3.58");
	int caddrlen = sizeof(sockaddr_in);

	//���ӷ�����
	if (connect(clientSocket, (const sockaddr *)&caddr, caddrlen) == SOCKET_ERROR) {
		puts("connect error ...");
		system("pause");
		exit(-1);
	}
	puts("connect success ...");

	char buf[64];
	//����֮���������ͨ��
	while (true) {
		memset(buf, 0, sizeof(buf));
		//���ܷ�����������
		if (recv(clientSocket, buf, sizeof(buf), 0) == SOCKET_ERROR) {
			puts("recv error ...");
			system("pause");
			exit(-1);
		}
		puts("recv success ...");
		printf("[server]��%s\n", buf);

		memset(buf, 0, sizeof(buf));
		scanf("%s", buf);
		//���������������
		if (send(clientSocket, buf, strlen(buf) + 1, 0) == SOCKET_ERROR) {
			puts("send error ...");
			system("pause");
			exit(-1);
		}
		puts("send success ...");
	}

	closesocket(clientSocket);

	WSACleanup();

	system("pause");
	return 0;
}