//////////////////////////////////////////////////////////////////////////
//
// �ͻ��˳���
//
//////////////////////////////////////////////////////////////////////////
//#define WIN32_LEAN_AND_MEAN
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <windows.h>
//#include <winsock2.h>
//
//#pragma comment(lib, "ws2_32.lib")

//int main(int agrc, char *argv[]) {
//	WSADATA wd;
//	WSAStartup(MAKEWORD(2, 2), &wd);
//
//	//�����ͻ����׽���
//	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (clientSocket == INVALID_SOCKET) {
//		puts("[client]:socket error ...");
//		system("pause");
//		return -1;
//	}
//	puts("[client]:socket success ...");
//
//	sockaddr_in caddr;
//	caddr.sin_family = AF_INET;
//	caddr.sin_port = htons(8080);
//	caddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//	int caddrlen = sizeof(sockaddr_in);
//
//	//���ӷ�����
//	if (connect(clientSocket, (const sockaddr *)&caddr, caddrlen) == SOCKET_ERROR) {
//		puts("[client]:connect error ...");
//		system("pause");
//		return -1;
//	}
//	puts("[client]:connect success ...");
//
//	char buf[64] = "";
//	//���ܷ�����������
//	if (recv(clientSocket, buf, sizeof(buf), 0) == SOCKET_ERROR) {
//		puts("[client]:recv error ...");
//		system("pause");
//		return -1;
//	}
//	puts("[client]:recv success ...");
//	printf("%s\n", buf);
//
//	//����֮���������ͨ��
//	while (true) {
//		scanf("%s", buf);
//		//���������������
//		if (send(clientSocket, buf, strlen(buf) + 1, 0) == SOCKET_ERROR) {
//			puts("[client]:send error ...");
//			system("pause");
//			return -1;
//		}
//		puts("[client]:send success ...");
//	}
//
//	closesocket(clientSocket);
//
//	WSACleanup();
//
//	system("pause");
//	return 0;
//}