#include "malcolm.h"

static int	cmptab(char **tab, char *cmp)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!ft_strcmp(tab[i], cmp))
			return (0);
		i++;
	}
	return (1);
}

struct ifaddrs	*get_interface(t_malcolm *mal)
{
	struct ifaddrs		*ifap;
	struct ifaddrs		*ifa;
	char				**interfaces;

	if (getifaddrs(&ifap))
		return (NULL);
	interfaces = ft_strsplit(INTERFACES, ' ');
	ifa = ifap;
	while (ifa)
	{
		if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET)
		{
			if (!cmptab(interfaces, ifa->ifa_name))
			{
				mal->ifa = ifa;
				break ;
			}
		}
		ifa = ifa->ifa_next;
	}
	ft_tabfree(interfaces);
	return (ifap);
}
