#include "malcolm.h"

int	malcolm(t_malcolm *mal)
{
	char			recvbuf[BUFSIZE];
	int				ret;

	mal->info = get_addr_info(mal, mal->d_ip);
	if (!mal->info)
		return (2);
	mal->ifap = get_interface(mal);
	if (!mal->ifap)
		return (3);
	if (mal->ifa)
	{
		printf("Found available interface : %s\n", mal->ifa->ifa_name);
		mal->sockfd = set_socket(AF_PACKET, SOCK_RAW, ETH_P_ARP);
		if (mal->sockfd <= 0)
			return (4);
		ret = 0;
		while (!ret)
			ret = recv_arp(mal, recvbuf);
		close(mal->sockfd);
		mal->sockfd = set_socket(AF_INET, SOCK_RAW, ETH_P_RARP);
		if (mal->sockfd <= 0)
			return (5);
		send_arp(mal, recvbuf);
		close(mal->sockfd);
	}
	freeifaddrs(mal->ifap);
	freeaddrinfo(mal->info);
	return (0);
}
