#pragma once

#include "common.h"

class ServerClient{
public:
	int RecvData();
	int SendData();
	int HandleData();

private:
	SOCKET m_skt;      //连接客户端套接字
	sockaddr_in m_addr;//连接客户端信息
};

