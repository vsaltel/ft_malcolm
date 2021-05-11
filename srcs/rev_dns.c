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

struct addrinfo	*get_addr_info(t_malcolm *mal, char *host)
{
	struct addrinfo	*info;

	info = reverse_dns_info(host, NULL, AF_INET, 0);
	if (!info)
		return (NULL);
	mal->d_addr = info->ai_addr;
	mal->d_addrlen = info->ai_addrlen;
	return (info);
}
