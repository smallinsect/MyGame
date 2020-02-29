#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char *argv[]){
	if(argc < 3){
		printf("./a 192.168.3.18 8888");
		exit(1);
	}
	int skt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(skt == -1){
		printf("[client] socket error ...\n");
		exit(1);
	}
	printf("[client] socket success ...\n");

	//服务器的信息
	sockaddr_in saddr = {0};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(atoi(argv[2]));
	saddr.sin_addr.s_addr = inet_addr(argv[1]);
	int saddrLen = sizeof(saddr);

	//连接服务器
	if(connect(skt, (sockaddr *)&saddr, saddrLen) == -1){
		printf("[client] connect error ...\n");
		exit(1);
	}
	printf("[client] connect success ...\n");

	char buf[1024];
	while(true){
		printf(">>");
		scanf("%s", buf);
		if(send(skt, buf, 1024, 0) == -1){
			printf("[client] send error ...%s\n", buf);
			exit(1);
		}
		printf("[client] send success ...%s\n", buf);
		if(recv(skt, buf, 1024, 0) == -1){
			printf("[client] recv error ...\n");
			exit(1);
		}
		printf("[client] recv success ...\n");
		printf("%s\n", buf);
	}

	close(skt);
	return 0;
}
