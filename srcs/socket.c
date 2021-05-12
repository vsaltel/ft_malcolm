#include "malcolm.h"

int	set_socket(int proto, int type, int mode)
{
	int				sock;
	//int				ttl;

	sock = socket(proto, type, htons(mode));
	if (sock < 0)
	{
		dprintf(2, "ft_malcolm: fail to create socket\n");
		return (-1);
	}
	//ttl = DEFAULT_TTL;
	//setsockopt(sock, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
	return (sock);
}
