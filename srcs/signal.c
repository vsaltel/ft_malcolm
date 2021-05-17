#include "malcolm.h"

void	catch_sigint(int signal)
{
	(void)signal;
	dprintf(2, "SIGINT received : Exiting program...\n");
	free_args(&g_mal);
	exit(1);
}
