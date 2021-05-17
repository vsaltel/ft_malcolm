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
	//char				str[IP_STR_LEN];

	sin = (struct sockaddr_in *)info->ai_addr;
	/*
	if (!inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)))
		return (NULL);
	return (ft_strdup(str));
	*/
	return (ip_strconv((uint8_t *)&sin->sin_addr));
}
