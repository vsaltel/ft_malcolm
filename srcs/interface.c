#include "malcolm.h"

struct ifaddrs	*get_interface(t_malcolm *mal)
{
    struct ifaddrs *ifap;
    struct ifaddrs *ifa;
    struct sockaddr_in *sa;
    char *addr;

	if (getifaddrs(&ifap))
		return (NULL);
	sa = NULL;
	ifa = ifap;
	while (ifa)
	{
		if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET)
		{
			sa = (struct sockaddr_in *)ifa->ifa_addr;
			addr = inet_ntoa(sa->sin_addr);
			if (!ft_strncmp(addr, mal->s_ip, 3))
			{
				mal->ifa = ifa;
				break;
			}
		}
		ifa = ifa->ifa_next;
	}
	return (ifap);
}
