#include "malcolm.h"

void	free_args(t_malcolm *mal)
{
	free(mal->s_ip);
	free(mal->s_maddr);
	free(mal->d_ip);
	free(mal->d_maddr);
	free(mal->pr.sacrecv);
}

void	init_malcolm(t_malcolm *mal)
{
	mal->s_maddr = NULL;
	mal->s_ip = NULL;
	mal->d_maddr = NULL;
	mal->d_ip = NULL;
	mal->pid = getpid() & 0xffff;
	mal->info = NULL;
	mal->ifap = NULL;
	mal->ifa = NULL;
}
