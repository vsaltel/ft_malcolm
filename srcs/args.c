#include "malcolm.h"

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

int	get_opt(t_malcolm *mal, char *arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'v')
			mal->v = 1;
		else if (arg[i] == 'l')
			mal->l = 1;
		else
			return (1);
		i++;
	}
	return (0);
}

int	get_args(t_malcolm *mal, int ac, char **av)
{
	int	i;

	if (ac < 5)
		return (err_ret("bad number of arguments", NULL, 1));
	i = 1;
	while (av[i][0] == '-')
	{
		if (get_opt(mal, av[i]))
			return (err_ret("bad option", NULL, 1));
		i++;
	}
	mal->s_name = ft_strdup(av[i++]);
	mal->s_maddr = ft_strupper(ft_strdup(av[i++]));
	mal->d_name = ft_strdup(av[i++]);
	mal->d_maddr = ft_strupper(ft_strdup(av[i++]));
	if (check_mac(mal->s_maddr))
		return (err_ret("mac address malformed", mal->s_maddr, 1));
	if (check_mac(mal->d_maddr))
		return (err_ret("mac address malformed", mal->d_maddr, 1));
	return (0);
}
