#include "malcolm.h"

/*
static struct addrinfo	*get_addr_info(t_malcolm *mal)
{
	mal->info = reverse_dns_info(mal->dest_name, NULL, AF_INET, 0);
	if (!info)
		return (NULL);
	mal->dest_ip = set_inetaddr(info->ai_addr);
	mal->pr.sasend = mal->info->ai_addr;
	mal->pr.sacrecv = malloc(mal->info->ai_addrlen);
	mal->pr.salen = mal->info->ai_addrlen;
	ft_bzero(mal->pr.sacrecv, mal->info->ai_addrlen);
	return (info);
}

static int	read_loop(t_malcolm *mal)
{
	char	sendbuf[BUFSIZE];
	char	recvbuf[BUFSIZE];

	signal(SIGINT, &catch_sigint);
	send_pckt(&sendbuf);
	recv_pckt(&recvbuf);
	return (0);
}
*/

void	send_arp_broadcast(t_malcolm *mal)
{
	ssize_t		ret;
	t_arp		*arp;
	char		buf[BUFSIZE];

	arp = (t_arp *)buf;
	//ft_memcpy(arp->s_mac, (unsigned char *)LLADDR((struct sockaddr_dl *)mal->ifa->ifa_addr), 6);
	//ft_memcpy(arp->d_mac, (unsigned char *)LLADDR((struct sockaddr_dl *)mal->ifa->ifa_dstaddr), 6);
	arp->etype = htons(ETH_P_ARP);
	arp->htype = htons(1);
	arp->ptype = htons(ETH_P_IP);
	arp->hlen = 6;
	arp->plen = 4;
	arp->opcode = htons(ARPOP_REQUEST);
	arp->sender_mac = 0;
	arp->sender_ip = inet_addr(mal->s_ip);
	arp->target_mac = 0;
	arp->target_ip = inet_addr(mal->d_ip);
	ret = sendto(mal->sockfd, buf, sizeof(ip) + sizeof(t_arphdr), mal->ifa->ifa_dstaddr, sizeof(mal->ifa->ifa_dstaddr));
	printf("send %zu\n", ret);
}

int	malcolm(t_malcolm *mal)
{
    struct ifaddrs *ifap;

	if (!reverse_dns_info(mal->d_ip, NULL, AF_INET, 0))
		return (-2);
	ifap = get_interface(mal);
	if (!ifap)
		return (-3);
	if (mal->ifa)
	{
		printf("Found available interface : %s\n", ifa->ifa_name);
		mal->sockfd = set_socket(mal, ETH_P_ARP);
		if (mal->sockfd <= 0)
			return (-4);
		send_arp_broadcast(mal);		
	}
	/*
	if (!get_addr_info(mal))
		return (-2);
	
	mal->sockfd = set_socket(mal);
	if (!mal->sockfd)
		return (-3);
	read_loop(mal);
	freeaddrinfo(mal->info);
	*/
	freeifaddrs(ifap);
	return (1);
}
