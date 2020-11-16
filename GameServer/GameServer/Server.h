#pragma once

#include "common.h"

class Server{
public:
	void Init(u_short port);
	static void Run(void* lpParam);
	void Stop();
private:
	SOCKET m_skt;       // 服务器套接字
	sockaddr_in m_addr; // 服务器信息
	u_short m_port;     // 服务器端口
	bool m_exit;        // 退出服务器
};

