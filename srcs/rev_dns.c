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
	return (info);
}

char	*set_inetaddr(t_malcolm *mal, struct addrinfo *info)
{
	struct sockaddr_in  *sin;
	char                str[IP_STR_SIZE];

	sin = (struct sockaddr_in *)sa;
	if (!inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)))
		return (ft_strdup("CONVERTION_FAIL"));
	return (ft_strdup(str));
}
