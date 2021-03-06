#include "malcolm.h"

static void	print_input(t_malcolm *mal)
{
	printf("Input :\n");
	printf("source mac address : %s\n"
		"source IP address : %s\n", mal->s_maddr, mal->s_ip);
	printf("dest mac address : %s\n"
		"dest IP address : %s\n", mal->d_maddr, mal->d_ip);
}

static int	rev_mal_info(t_malcolm *mal)
{
	mal->d_info = reverse_dns_info(mal->d_name, NULL, AF_INET, 0);
	if (!mal->d_info)
		return (1);
	mal->d_addr = mal->d_info->ai_addr;
	mal->d_addrlen = mal->d_info->ai_addrlen;
	mal->d_ip = set_inetaddr(mal->d_info);
	if (!mal->d_ip)
		return (1);
	mal->s_info = reverse_dns_info(mal->s_name, NULL, AF_INET, 0);
	if (!mal->s_info)
		return (1);
	mal->s_ip = set_inetaddr(mal->s_info);
	if (!mal->s_ip)
		return (1);
	return (0);
}

static int	exec(t_malcolm *mal)
{
	char	recvbuf[BUFSIZE];
	int		ret;

	mal->sockfd = set_socket(AF_PACKET, SOCK_RAW, ETH_P_ARP);
	if (mal->sockfd <= 0)
		return (4);
	ret = 0;
	while (!ret)
		ret = recv_arp(mal, recvbuf);
	close(mal->sockfd);
	mal->sockfd = set_socket(AF_INET, SOCK_PACKET, ETH_P_RARP);
	if (mal->sockfd <= 0)
		return (5);
	send_arp(mal, recvbuf);
	close(mal->sockfd);
	return (0);
}

int	malcolm(t_malcolm *mal)
{
	int		ret;

	if (rev_mal_info(mal))
		return (3);
	if (mal->v)
		print_input(mal);
	mal->ifap = get_interface(mal);
	if (!mal->ifap)
		return (4);
	ret = 0;
	if (mal->ifa)
	{
		printf("Found available interface : %s\n", mal->ifa->ifa_name);
		if (mal->l)
		{
			while (!ret)
				ret = exec(mal);
		}
		else
			ret = exec(mal);
	}
	return (ret);
}
