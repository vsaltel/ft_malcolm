#include "malcolm.h"

void	catch_sigint(int signal)
{
	(void)signal;
	if (g_mal.info)
		freeaddrinfo(g_mal.info);
	free_args(&g_mal);
	exit(1);
}
