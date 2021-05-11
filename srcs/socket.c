#include "malcolm.h"

int	set_socket(int mode)
{
	int				sock;
	//int				size;
	int				ttl;

	sock = socket(AF_PACKET, SOCK_RAW, htons(mode));
	if (sock < 0)
		return (err_ret("fail to create socket", NULL, -1));
	/*
	size = 60 * 1024;
	setsockopt (sock, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
	*/
	ttl = DEFAULT_TTL;
	setsockopt(sock, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
	return (sock);
}
