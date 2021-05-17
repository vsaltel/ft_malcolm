#include "malcolm.h"

t_malcolm	g_mal;

int	main(int argc, char **argv)
{
	int	ret;

	if (getuid() != 0)
	{
		printf("ft_malcolm: need root privilege\n");
		return (1);
	}
	init_malcolm(&g_mal);
	signal(SIGINT, &catch_sigint);
	if (get_args(&g_mal, argc, argv))
	{
		free_args(&g_mal);
		return (1);
	}
	ret = malcolm(&g_mal);
	printf("Exiting program...\n");
	free_args(&g_mal);
	return (ret);
}
