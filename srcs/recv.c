#include "ping.h"

int	recv_arp(t_malcolm *mal, t_arp *arp)
{
	char		buf[BUFSIZE];
	ssize_t		ret;
	char		*mac;
	char		*ip;

	ret = recvfrom(mal->sockfd, buf, BUFSIZE, 0, mal->d_addr, &mal->d_addrlen);
	arp = (t_arp *)(buf + 14);
	if (ret >= (ssize_t)(14 + sizeof(t_arp)) &&
		ntohs(arp->opcode) == ARPOP_REQUEST)
	{
		mac = mac_strconv(arp->sender_mac);
		ip = ip_strconv(arp->sender_ip);
		printf("An ARP request has been broadcast.\n":);
		printf("\tsource mac address : %s\n"
				"\tsource IP address : %s\n", mac , ip);
		ft_multifree(&mac, &ip, NULL);	
		mac = mac_strconv(arp->target_mac);
		ip = ip_strconv(arp->target_ip);
		printf("\ttarget mac address : %s\n"
				"\ttarget IP address : %s\n", mac , ip);
		ft_multifree(&mac, &ip, NULL);	
		return (1);
	}
	return (0);
}
