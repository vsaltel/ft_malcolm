#include "malcolm.h"

void	catch_sigint(int signal)
{
	(void)signal;
	dprintf(2, "SIGINT received : Exiting program...\n");
	if (g_mal.info)
		freeaddrinfo(g_mal.info);
	if (g_mal.ifap)
		freeifaddrs(mal->ifap);
	free_args(&g_mal);
	exit(1);
}
