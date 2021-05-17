#include "malcolm.h"

int	check_ip(char *ip)
{
	int	i;
	int	n;
	int	w;

	i = 0;
	n = 0;
	w = 1;
	while (ip[i])
	{
		if (ip[i] == '.' )
		{
			if (n == 0 || n > 3)
				return (1);
			n = 0;
			w++;
		}
		else if (ip[i] > '9' || ip[i] < '0')
			return (1);
		else
			n++;
		i++;
	}
	return (w < 4 || w > 4);
}

int	check_mac(char *mac)
{
	int	i;
	int	n;
	int	w;

	i = 0;
	n = 0;
	w = 1;
	while (mac[i])
	{
		if (mac[i] == ':')
		{
			if (n > 2 || n < 2)
				return (1);
			n = 0;
			w++;
		}
		else if (!(mac[i] >= '0' && mac[i] <= '9') && \
			!(mac[i] >= 'A' && mac[i] <= 'F') && \
			!(mac[i] >= 'a' && mac[i] <= 'a'))
			return (1);
		else
			n++;
		i++;
	}
	return (w < 6 || w > 6);
}

int	get_args(t_malcolm *mal, int ac, char **av)
{
	if (ac < 5 || ac > 5)
		return (err_ret("bad number of arguments", NULL, 1));
	mal->s_ip = ft_strdup(av[1]);
	mal->s_maddr = ft_strupper(ft_strdup(av[2]));
	mal->d_ip = ft_strdup(av[3]);
	mal->d_maddr = ft_strupper(ft_strdup(av[4]));
	/*
	if (check_ip(mal->s_ip))
		return (err_ret("ip address malformed", mal->s_ip, 1));
	if (check_ip(mal->d_ip))
		return (err_ret("ip address malformed", mal->s_ip, 1));
	*/
	if (check_mac(mal->s_maddr))
		return (err_ret("mac address malformed", mal->s_maddr, 1));
	if (check_mac(mal->d_maddr))
		return (err_ret("mac address malformed", mal->d_maddr, 1));
	return (0);
}
