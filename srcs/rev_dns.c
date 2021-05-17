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
	struct sockaddr_in  *sin;
	char                str[IP_STR_LEN];

	sin = (struct sockaddr_in *)info->ai_addr;
	if (!inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)))
		return (ft_strdup("CONVERTION_FAIL"));
	return (ft_strdup(str));
}

int	rev_mal_info(t_malcolm *mal)
{
	mal->d_info = reverse_dns_info(mal->d_name, NULL, AF_INET, 0);
	if (!mal->d_info)
	{
		printf("there\n");
		return (1);
	}
	mal->d_addr = mal->d_info->ai_addr;
	mal->d_addrlen = mal->d_info->ai_addrlen;
	mal->d_ip = set_inetaddr(mal->d_info);
	mal->d_info = reverse_dns_info(mal->s_name, NULL, AF_INET, 0);
	if (!mal->s_info)
		return (1);
	mal->s_ip = set_inetaddr(mal->s_info);
	return (0);
}
