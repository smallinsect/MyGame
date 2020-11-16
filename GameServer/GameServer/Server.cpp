#include "Server.h"



void Server::Init(u_short port) {
	this->m_port = port;

	WSADATA wd;
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0) {
		printf("[server] WSAStartup error ...%d\n", GetLastError());
		return;
	}
	puts("[server] WSAStartup success ...");

	//创建一个套接字 IPV4 流类型 TCP协议
	SOCKET m_skt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_skt == INVALID_SOCKET) {
		printf("[server] socket error ...%d\n", GetLastError());
		return;
	}
	puts("[server] socket success ...");

	//IPV4协议 ip 端口
	sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;//IPV4
	addr.sin_addr.s_addr = inet_addr("0.0.0.0");//自动绑定本机IP地址
	addr.sin_port = htons(port);//端口8000

	//绑定套接字
	if (bind(m_skt, (const sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
		printf("[server] bind error ...%d\n", GetLastError());
		return;
	}
	puts("[server] bind success ...");

	//监听套接字
	if (listen(m_skt, SOMAXCONN) == SOCKET_ERROR) {
		printf("[server] listen error ...%d\n", GetLastError());
		return;
	}
	puts("[server] listen success ...");

	_beginthread(Run, 0, (void*)this);
	return;
}

void Server::Run(void* lpParam) {
	Server* pserver = (Server*)lpParam;

	fd_set m_fds;
	FD_ZERO(&m_fds);//初始化
	FD_SET(pserver->m_skt, &m_fds);//服务socket放入集合

	timeval tv = { 0, 30 };

	char buf[MAX_SIZE_BUF];
	while (!pserver->m_exit) {
		fd_set rfds = m_fds;// 监听读取的数据

		if (select(0, &rfds, NULL, NULL, &tv) <= 0) {
			continue;
		}
		for (u_int i = 0; i < rfds.fd_count; ++i) {
			SOCKET tskt = rfds.fd_array[i];
			if (tskt == pserver->m_skt) {//有新的客户端请求连接
				SOCKET cskt = accept(pserver->m_skt, NULL, NULL);
				if (cskt == INVALID_SOCKET) {
					printf("[server] accept error ...%d\n", GetLastError());
					continue;
				}
				printf("[server] accept success %d...\n", cskt);
				FD_SET(cskt, &m_fds);
				continue;
			}
			memset(buf, 0, sizeof(buf));
			int irecv = recv(tskt, buf, sizeof(buf), 0);//接受浏览器请求的消息
			if (irecv > 0) {
				dispatch_msg(&m_fds, pserver->m_skt, buf, strlen(buf) + 1);// 处理接受的消息
			}
			else {
				FD_CLR(tskt, &m_fds);
				closesocket(tskt);
			}
		}
	}
	pserver->Stop();
}

void Server::Stop() {
	closesocket(m_skt);//关闭套接字
	WSACleanup();//清理数据
}