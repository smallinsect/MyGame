

#include "common.h"



bool g_bExit;

void start(void* lpParam);
void clear(SOCKET skt);
void dispatch_msg(fd_set* pfds, SOCKET skt, char* buf, int len);

int main(int argc, char* argv[]) {

	SOCKET m_skt = init(8000);

	
	while (true) {
		if (_kbhit()) {
			if (_getch() == VK_SPACE) {
				g_bExit;
				break;
			}
		}
		Sleep(500);
	}

	return 0;
}

void start(void* lpParam) {

}

void clear(SOCKET skt) {
}

void dispatch_msg(fd_set* pfds, SOCKET skt, char* buf, int len) {
	for (u_int i = 0; i < pfds->fd_count; i++) {
		SOCKET tskt = pfds->fd_array[i];
		if (tskt == skt) {
			continue;
		}
		if (send(tskt, buf, len, 0) <= 0) {
			printf("[server] send error ...%d\n", GetLastError());
		}
	}
}