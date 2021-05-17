#include "malcolm.h"

static void	display_addr(char *smac, char *sip, char *dmac, char *dip)
{
	printf("An ARP request has been broadcast.\n");
	printf("\tsource mac address : %s\n"
		"\tsource IP address : %s\n", smac, sip);
	printf("\ttarget mac address : %s\n"
		"\ttarget IP address : %s\n", dmac, dip);
}

static int	check_addr(t_malcolm *mal, t_arp *arp)
{
	char		*mac[2];
	char		*ip[2];
	int			ret;

	ret = 0;
	mac[0] = mac_strconv(arp->sender_mac);
	ip[0] = ip_strconv(arp->sender_ip);
	if (!ft_strcmp(mac[0], mal->d_maddr) && \
		!ft_strcmp(ip[0], mal->d_ip))
	{
		mac[1] = mac_strconv(arp->target_mac);
		ip[1] = ip_strconv(arp->target_ip);
		display_addr(mac[0], ip[0], mac[1], ip[1]);
		ft_multifree(&mac[1], &ip[1], NULL);
		ret = 1;
	}
	ft_multifree(&mac[0], &ip[0], NULL);
	return (ret);
}

int	recv_arp(t_malcolm *mal, char *buf)
{
	t_arp		*arp;
	ssize_t		ret;

	ret = recvfrom(mal->sockfd, buf, BUFSIZE, 0, mal->d_addr, &mal->d_addrlen);
	arp = (t_arp *)(buf);
	if (ret >= (ssize_t)(sizeof(t_arp)) && \
		ntohs(arp->etype) == ETH_P_ARP && \
		ntohs(arp->opcode) == ARPOP_REQUEST && \
		check_addr(mal, arp))
		return (1);
	if (mal->v)
		dprintf(2, "packet received but not the expected one (%ld len)\n", ret);
	return (0);
}
