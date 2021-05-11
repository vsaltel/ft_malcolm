#include "malcolm.h"

unsigned short	checksum(void *b, int len)
{
	unsigned short	*buf;
	unsigned int	sum;
	unsigned short	result;

	buf = b;
	sum = 0;
	while (len > 1)
	{
		sum += *buf++;
		len -= 2;
	}
	if (len == 1)
		sum += *(unsigned char *)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return (result);
}

int		err_ret(char *err, char *arg, int ret)
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
	dprintf(2, "usage: ft_malcolm source_ip source_mac dest_ip dest_mac\n");
}
