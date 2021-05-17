#include "malcolm.h"

char	*ip_strconv(const uint8_t *bytes)
{
	char	*buf;
	int		i;
	int		y;

	i = 0;
	y = 0;
	buf = malloc(16);
	while (i < 4 && y < 16)
	{
		if (i != 0)
			buf[y - 1] = '.';
		if (bytes[i] >= 100)
			buf[y] = bytes[i] / 100 + '0';
		else
			y--;
		if (bytes[i] >= 10)
			buf[y + 1] = bytes[i] / 10 % 10 + '0';
		else
			y--;
		buf[y + 2] = bytes[i] % 10 + '0';
		i += 1;
		y += 4;
	}
	buf[y - 1] = '\0';
	return (buf);
}

void	set_ip_addr(char *src, uint8_t *dst, int len)
{
	int		i;
	char	**tab;

	tab = ft_strsplit(src, '.');
	i = 0;
	while (i < len && tab[i])
	{
		dst[i] = dectoint(tab[i]);
		i++;
	}
	ft_tabfree(tab);
}
