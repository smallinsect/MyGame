#pragma once

#include "common.h"

class Server{
public:
	void Init(u_short port);
	static void Run(void* lpParam);
	void Stop();
private:
	SOCKET m_skt;       // �������׽���
	sockaddr_in m_addr; // ��������Ϣ
	u_short m_port;     // �������˿�
	bool m_exit;        // �˳�������
};

