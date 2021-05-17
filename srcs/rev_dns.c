#include "malcolm.h"

struct addrinfo	*reverse_dns_info(char *host, char *serv, int family,
	int socktype)
{
	struct addrinfo	*res;
	struct addrinfo	hints;

	ft_memset(&hints, 0, sizeof hints);
	hints.ai_family = family;
	hints.ai_socktype = socktype;
	hints.ai_flags = AI_CANONNAME;
	if (getaddrinfo(host, serv, &hints, &res) != 0)
	{
		dprintf(2, "ft_malcolm: Unknow host : %s\n", host);
		return (NULL);
	}
	return (res);
}

char	*set_inetaddr(struct addrinfo *info)
{
	struct sockaddr_in	*sin;

	sin = (struct sockaddr_in *)info->ai_addr;
	return (ip_strconv((uint8_t *)&sin->sin_addr));
}
