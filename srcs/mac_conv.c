#include "malcolm.h"

int		hextoint(const char *str)
{
	size_t	i;
	int	res;

	res = 0;
	i = 0;
	while (i < ft_strlen(str))
	{
		res *= 16;
		if(str[i] >= 'a' && str[i] <= 'f')
			res += (str[i] - 'a' + 10);
		else if(str[i] >= 'A' && str[i] <= 'F')
			res += (str[i] - 'A' + 10);
		else if(str[i] >= '0' && str[i] <= '9')
			res += (str[i] - '0');
		else
			return (-1);
		i++;
	}
	return (res);
}

void	set_mac_addr(char *src, uint8_t *dst, int len)
{
	int		i;
	char	**tab;

	tab = ft_strsplit(src, ':');
	i = 0;	
	while (i < len && tab[i])
	{
		dst[i] = hextoint(tab[i]);
		i++;
	}
	ft_tabfree(tab);
}
