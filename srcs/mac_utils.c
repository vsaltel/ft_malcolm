#include "malcolm.h"

static char	bytetochar(uint8_t byte)
{
	if (byte >= 10)
		return (byte - 10 + 'A');
	else
		return (byte + '0');
}

char	*mac_strconv(const uint8_t *bytes)
{
	char	*buf;
	int		i;
	int		y;

	i = 0;
	y = 0;
	buf = malloc(18);
	while (i < 6 && y < 18)
	{
		if (i != 0)
			buf[y - 1] = ':';
		buf[y] = bytetochar(bytes[i] / 16);
		buf[y + 1] = bytetochar(bytes[i] % 16);
		y += 3;
		i += 1;
	}
	buf[y - 1] = '\0';
	return (buf);
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
