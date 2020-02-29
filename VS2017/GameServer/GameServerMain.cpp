////////////////////////////////////////////////////////////////////////////
////
//// 服务器端程序
////
////////////////////////////////////////////////////////////////////////////
//#define WIN32_LEAN_AND_MEAN
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <windows.h>
//#include <winsock2.h>
//
//#pragma comment(lib, "ws2_32.lib")
//
//int main() {
//	puts("hello world");
//
//	WSADATA wd;
//	WSAStartup(MAKEWORD(2, 2), &wd);
//
//	//服务器创建套接字
//	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (serverSocket == SOCKET_ERROR) {
//		puts("socket error ...");
//		system("pause");
//		exit(-1);
//	}
//	puts("socket success ...");
//	//服务器绑定IP和端口
//	sockaddr_in saddr;
//	saddr.sin_family = AF_INET;
//	saddr.sin_port = htons(8080);
//	saddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//	if (bind(serverSocket, (const sockaddr *)&saddr, sizeof(sockaddr_in)) == SOCKET_ERROR) {
//		puts("bind error ...");
//		system("pause");
//		exit(-1);
//	}
//	puts("bind success ...");
//
//	//服务器开始监听
//	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
//		puts("listen error ...");
//		system("pause");
//		exit(-1);
//	}
//	puts("listen success ...");
//
//	//服务等待客户端连接
//	sockaddr_in clientAddr;
//	int clientAddrLen = sizeof(sockaddr_in);
//	SOCKET clientSocket = accept(serverSocket, (sockaddr *)&clientAddr, &clientAddrLen);
//	if (clientSocket == INVALID_SOCKET) {
//		puts("accept error ...");
//		system("pause");
//		exit(-1);
//	}
//	puts("accept success ...");
//	printf("client ip : %s\n", inet_ntoa(clientAddr.sin_addr));
//	printf("client port:%d\n", clientAddr.sin_port);
//
//	//连接之后与客户端通信
//	char buf[64];
//	while (true) {
//		memset(buf, 0, sizeof(buf));
//		scanf("%s", buf);
//		//向客户端发送数据
//		if (send(clientSocket, buf, strlen(buf)+1, 0) == SOCKET_ERROR) {
//			puts("send error ...");
//			system("pause");
//			exit(-1);
//		}
//		puts("send success ...");
//
//		memset(buf, 0, sizeof(buf));
//		//接受客户端数据
//		if (recv(clientSocket, buf, sizeof(buf), 0) == SOCKET_ERROR) {
//			puts("recv error ...");
//			system("pause");
//			exit(-1);
//		}
//		puts("recv success ...");
//		printf("客户端：%s\n", buf);
//	}
//
//	closesocket(clientSocket);
//	closesocket(serverSocket);
//
//	WSACleanup();
//
//	system("pause");
//	return 0;
//}