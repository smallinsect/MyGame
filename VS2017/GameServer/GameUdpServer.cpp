//#define WIN32_LEAN_AND_MEAN
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <windows.h>
//#include <winsock2.h>
//#pragma comment(lib, "ws2_32.lib")
//
//int main(int argc, char *argv[]) {
//	WSADATA wd;
//	WSAStartup(MAKEWORD(2, 2), &wd);
//
//	//�����׽���
//	SOCKET skt = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//
//	sockaddr_in saddr = {0};
//	saddr.sin_family = AF_INET;
//	saddr.sin_port = htons(8888);
//	saddr.sin_addr.s_addr = htonl(INADDR_ANY);//����IP
//	//���׽��ֺͶ˿ڡ�ip��
//	bind(skt, (sockaddr *)&saddr, sizeof(saddr));
//
//	//���ӿͻ��˵���Ϣ
//	sockaddr_in caddr = {0};
//	int caddrLen = sizeof(caddr);
//	char buf[1024];
//	while (true) {
//		//���ܿͻ�����Ϣ
//		recvfrom(skt, buf, 1024, 0, (sockaddr *)&caddr, &caddrLen);
//		printf("[client] ip:%s port:%d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));
//		printf("[client] %s\n", buf);
//		sendto(skt, buf, 1024, 0, (sockaddr *)&caddr, caddrLen);
//	}
//
//	WSACleanup();
//	system("pause");
//	return 0;
//}