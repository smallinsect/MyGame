//////////////////////////////////////////////////////////////////////////
//
// 服务器端程序
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
	puts("hello world");

	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);

	//服务器创建套接字
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == SOCKET_ERROR) {
		puts("socket error ...");
		system("pause");
		exit(-1);
	}
	puts("socket success ...");
	//服务器绑定IP和端口
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

	//服务器开始监听
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		puts("listen error ...");
		system("pause");
		exit(-1);
	}
	puts("listen success ...");


	fd_set fdsSockets;
	FD_ZERO(&fdsSockets);
	FD_SET(serverSocket, &fdsSockets);
	timeval timeout;
	timeout.tv_sec = 3;
	timeout.tv_usec = 0;

	char buf[1024];
	while (true) {
		fd_set fdsTempSocket = fdsSockets;
		//接受响应的socket
		int iret = select(0, &fdsTempSocket, NULL, NULL, &timeout);
		//客户端
		if (iret == SOCKET_ERROR) {
			perror("select error...");
			system("pause");
			exit(-1);
		}
		if (iret > 0) {
			for (u_int i = 0; i < fdsTempSocket.fd_count; ++i) {
				SOCKET tempSocket = fdsTempSocket.fd_array[i];
				//有客户端连接
				if (tempSocket == serverSocket) {
					//接受客户端socket
					SOCKET clientSocket = accept( serverSocket, NULL, NULL);
					//无效客户端socket
					if (clientSocket == INVALID_SOCKET) {
						printf("无效客户端socket，错误代码：%d\n", GetLastError());
						continue;
					}
					printf("有新客户端连接\n");
					//添加客户端
					FD_SET(clientSocket, &fdsSockets);
					sprintf(buf, "连接服务器成功");
					int isend = send(clientSocket, buf, strlen(buf)+1, 0);
					if (isend == SOCKET_ERROR) {
						puts("send error ...");
						continue;
					}
					puts("send success ...");
				} else {
					//接受客户端的消息
					int irecv = recv(tempSocket, buf, sizeof(buf), 0);
					if (irecv == SOCKET_ERROR) {
						printf("接受客户端消息错误，错误代码：%d\n", GetLastError());
						FD_CLR(tempSocket, &fdsSockets);
						closesocket(tempSocket);
					} else if (irecv == 0) {
						printf("客户端退出\n");
						FD_CLR(tempSocket, &fdsSockets);
						closesocket(tempSocket);
					} else {
						printf("客户端发送消息：%s\n", buf);
					}
				}
			}
		}
	}

	closesocket(serverSocket);

	WSACleanup();

	system("pause");
	return 0;
}