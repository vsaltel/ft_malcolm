#include "malcolm.h"

void	copy_bytes(uint8_t *dst, uint8_t *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

int	err_ret(char *err, char *arg, int ret)
{
	if (arg)
		dprintf(2, "ft_malcolm: %s : (%s)\n", err, arg);
	else
		dprintf(2, "ft_malcolm: %s\n", err);
	print_usage();
	return (ret);
}

void	print_usage(void)
{
	dprintf(2, "usage: ft_malcolm [-v] source_ip source_mac dest_ip dest_mac\n");
}
