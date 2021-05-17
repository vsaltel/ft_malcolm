#include "malcolm.h"

void	free_args(t_malcolm *mal)
{
	free(mal->s_name);
	free(mal->s_ip);
	free(mal->s_maddr);
	free(mal->d_name);
	free(mal->d_ip);
	free(mal->d_maddr);
	if (mal->ifap)
		freeifaddrs(mal->ifap);
	if (mal->s_info)
		freeaddrinfo(mal->s_info);
	if (mal->d_info)
		freeaddrinfo(mal->d_info);
}

void	init_malcolm(t_malcolm *mal)
{
	mal->s_maddr = NULL;
	mal->s_name = NULL;
	mal->s_ip = NULL;
	mal->d_name = NULL;
	mal->d_maddr = NULL;
	mal->d_ip = NULL;
	mal->pid = getpid() & 0xffff;
	mal->s_info = NULL;
	mal->d_info = NULL;
	mal->ifap = NULL;
	mal->ifa = NULL;
}
