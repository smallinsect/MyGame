#pragma once

#include "common.h"

class ServerClient{
public:
	int RecvData();
	int SendData();
	int HandleData();

private:
	SOCKET m_skt;      //���ӿͻ����׽���
	sockaddr_in m_addr;//���ӿͻ�����Ϣ
};

