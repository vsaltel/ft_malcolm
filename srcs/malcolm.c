#include "malcolm.h"

/*
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

void	recv_arp(t_malcolm *mal)
{
	char		buf[BUFSIZE];
	ssize_t		ret;

	printf("wait to recv\n");
	ret = recvfrom(mal->sockfd, buf, BUFSIZE, 0, mal->d_addr, &mal->d_addrlen);
	printf("recv %zu\n", ret);
}

/*
void	send_arp(t_malcolm *mal)
{
	ssize_t		ret;
	t_arp		*arp;
	char		buf[BUFSIZE];

	arp = (t_arp *)buf;
	arp->etype = htons(ETH_P_ARP);
	arp->htype = htons(1);
	arp->ptype = htons(ETH_P_IP);
	arp->hlen = 6;
	arp->plen = 4;
	arp->opcode = htons(ARPOP_REQUEST);
	set_mac_addr(mal->s_maddr, arp->sender_mac, 6);
	arp->sender_ip = inet_addr(mal->s_ip);
	set_mac_addr(mal->d_maddr, arp->target_mac, 6);
	arp->target_ip = inet_addr(mal->d_ip);
	ret = sendto(mal->sockfd, buf, sizeof(t_arp), 0, mal->ifa->ifa_dstaddr, sizeof(mal->ifa->ifa_dstaddr));
	printf("send %zu\n", ret);
}
*/

int	malcolm(t_malcolm *mal)
{
    struct ifaddrs *ifap;

	mal->info = get_addr_info(mal, mal->d_ip);
	if (!mal->info)
		return (-2);
	ifap = get_interface(mal);
	if (!ifap)
		return (-3);
	if (mal->ifa)
	{
		printf("Found available interface : %s\n", mal->ifa->ifa_name);
		mal->sockfd = set_socket(ETH_P_ARP);
		if (mal->sockfd <= 0)
			return (-4);
		recv_arp(mal);
		//send_arp(mal);
	}
	/*
	if (!get_addr_info(mal))
		return (-2);
	
	mal->sockfd = set_socket(mal);
	if (!mal->sockfd)
		return (-3);
	read_loop(mal);
	*/
	freeifaddrs(ifap);
	freeaddrinfo(mal->info);
	return (1);
}
