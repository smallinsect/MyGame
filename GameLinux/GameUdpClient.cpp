#include <stdio.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[]){

	//客户端创建套接字
	int skt = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	//需要连接的服务器端的信息
	sockaddr_in saddr = {0};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8888);
	saddr.sin_addr.s_addr = inet_addr("192.168.3.18");

	char buf[1024];
	while(true){
		printf(">>");
		scanf("%s", buf);
		//向服务端发送数据
		sendto(skt, buf, 1024, 0, (sockaddr *)&saddr, sizeof(saddr));
		//接受服务端的信息
		recvfrom(skt, buf, 1024, 0, NULL, NULL);
		printf("[server] %s\n", buf);
	}
	
	close(skt);
	return 0;
}
