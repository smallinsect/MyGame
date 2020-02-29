//////////////////////////////////////////////////////////////////////////
//
// 服务器端程序
// 通过创建线程，连接多个客户端。
//////////////////////////////////////////////////////////////////////////
//#define WIN32_LEAN_AND_MEAN
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <windows.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//
//#pragma comment(lib, "ws2_32.lib")
//
//#define MAX_REQUEST 4096
//
//DWORD WINAPI CommunicationThread(LPVOID lpParameter);
//
//int main(int agrc, char *argv[]) {
//	WSADATA wd;
//	WSAStartup(MAKEWORD(2, 2), &wd);
//
//	addrinfo hints, *result = NULL;
//	ZeroMemory(&hints, sizeof(hints));
//	hints.ai_family = AF_INET;
//	hints.ai_flags = AI_PASSIVE;
//	hints.ai_protocol = IPPROTO_TCP;
//	hints.ai_socktype = SOCK_STREAM;
//
//	//获取主机地址，保证网络协议可用等。
//	int iResult = getaddrinfo( NULL, "8080", &hints, &result);
//	if (iResult != 0) {
//		puts("[sever]:getaddrinfo error ...");
//		system("pause");
//		return -1;
//	}
//
//	//服务器创建套接字
//	SOCKET serverSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
//	if (serverSocket == SOCKET_ERROR) {
//		puts("[sever]:socket error ...");
//		system("pause");
//		return -1;
//	}
//	puts("[sever]:socket success ...");
//
//	if (bind(serverSocket, result->ai_addr, result->ai_addrlen) == SOCKET_ERROR) {
//		puts("[sever]:bind error ...");
//		system("pause");
//		return -1;
//	}
//	puts("[sever]:bind success ...");
//
//	freeaddrinfo(result);//释放result内存
//
//	//服务器开始监听
//	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
//		puts("[sever]:listen error ...");
//		system("pause");
//		return -1;
//	}
//	puts("[sever]:listen success ...");
//
//
//	while (true) {
//		//服务等待客户端连接
//		sockaddr_in clientAddr;
//		int clientAddrLen = sizeof(sockaddr_in);
//		SOCKET clientSocket = accept(serverSocket, (sockaddr *)&clientAddr, &clientAddrLen);
//		if (clientSocket == INVALID_SOCKET) {
//			puts("[sever]:accept error ...");
//			system("pause");
//			return -1;
//		}
//		puts("[sever]:accept success ...");
//		printf("client ip : %s\n", inet_ntoa(clientAddr.sin_addr));
//		printf("client port:%d\n", clientAddr.sin_port);
//
//		char buf[64];
//		sprintf(buf, "%s", "[server]:accept success ...");
//		//向客户端发送数据
//		if (send(clientSocket, buf, strlen(buf) + 1, 0) == SOCKET_ERROR) {
//			puts("[sever]:send error ...");
//			system("pause");
//			return -1;
//		}
//		puts("[sever]:send success ...");
//
//		if (!CreateThread(NULL, 0, CommunicationThread, (LPVOID)clientSocket, 0, NULL)) {
//			printf("CreateThread error ...\n");
//		}
//	}
//
//	closesocket(serverSocket);
//
//	WSACleanup();
//
//	system("pause");
//	return 0;
//}
//
//
//DWORD WINAPI CommunicationThread(LPVOID lpParameter) {
//	DWORD dwTid = GetCurrentThreadId();
//
//	SOCKET sClient = (SOCKET)lpParameter;
//	char buf[1024] = "";
//
//	while (true) {
//		int iRes = recv(sClient, buf, 1024, 0);
//		if (iRes == SOCKET_ERROR) {
//			printf("[client:%d]:Tid(%d) recv error ...\n", sClient, dwTid);
//			break;
//		}
//		if (iRes == 0) {
//			printf("[client:%d]:Tid(%d) client quit ...\n", sClient, dwTid);
//			break;
//		}
//		printf("[client:%d]:Tid(%d) %s\n", sClient, dwTid, buf);
//	}
//	closesocket(sClient);
//
//	return 0;
//}