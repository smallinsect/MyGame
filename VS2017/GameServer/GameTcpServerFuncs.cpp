

#include "GameTcpServerFuncs.h"

enum MsgType {
	MSG_TYPE_FOOD,//食物
	MSG_TYPE_SNAKE//蛇
};

struct Point {
	int x, y;
};

struct Message {
	MsgType msgType;
	int size;
	Point points[1024];
};

fd_set fds;
SOCKET serverSocket;

void onInit() {
	WSADATA wd;
	WSAStartup(MAKEWORD(2, 2), &wd);

	//服务器创建套接字
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == SOCKET_ERROR) {
		printf("[server] socket error ...\n");
		exit(-1);
	}
	printf("[server] socket success ...\n");
	//服务器绑定IP和端口
	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8888);
	saddr.sin_addr.s_addr = inet_addr("0.0.0.0");
	if (bind(serverSocket, (const sockaddr *)&saddr, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		printf("[server] bind error ...\n");
		exit(-1);
	}
	printf("[server] bind success ...\n");

	//服务器开始监听
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("[server] listen error ...\n");
		exit(-1);
	}
	printf("[server] listen success ...\n");

	FD_ZERO(&fds);
	FD_SET(serverSocket, &fds);
}

void onRun() {
	onInit();

	timeval tv = { 1, 0 };
	while (true) {
		fd_set fdsTemp = fds;
		//接受响应的socket
		int iRet = select(0, &fdsTemp, NULL, NULL, &tv);
		if (iRet == SOCKET_ERROR) {
			perror("[server] select error ...\n");
			exit(-1);
		}
		if (iRet == 0) {
			continue;
		}
		for (u_int i = 0; i < fdsTemp.fd_count; ++i) {
			SOCKET tempSocket = fdsTemp.fd_array[i];
			//有新客户端连接
			if (tempSocket == serverSocket) {
				onAccept(tempSocket);
			}
			//接受客户端发送来的数据
			else {
				onRead(tempSocket);
			}
		}
	}

	closesocket(serverSocket);
	WSACleanup();
}

void onAccept(SOCKET skt) {
	//接受新客户端socket
	sockaddr_in addr = {0};
	int addrLen = sizeof(addr);
	SOCKET clientSocket = accept(skt, (sockaddr*)&addr, &addrLen);
	if (clientSocket == INVALID_SOCKET) {
		printf("[server] accept error ...\n");
		return ;
	}
	printf("[server] accept success ...\n");
	printf("[%llu:%s:%u] accept success ...\n", clientSocket, inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	//添加新的socket
	FD_SET(clientSocket, &fds);
}

void onRead(SOCKET skt) {
	Message message;
	memset(&message, 0, sizeof(message));
	int iRecv = recv(skt, (char *)&message, sizeof(message), 0);
	if (iRecv == SOCKET_ERROR) {
		printf("[server] recv error ...\n");
	}
	else if (iRecv == 0) {
		printf("[server] client quit ...\n");
		FD_CLR(skt, &fds);
		closesocket(skt);
	}
	else {
		//接收的一个客户端的消息，分发给其他客户端。
		for (u_int i = 0; i < fds.fd_count; ++i) {
			SOCKET tskt = fds.fd_array[i];
			if (tskt != skt && tskt != serverSocket) {
				send(tskt, (const char *)&message, sizeof(message), 0);
			}
		}
	}
}

void onWrite(SOCKET skt) {

}