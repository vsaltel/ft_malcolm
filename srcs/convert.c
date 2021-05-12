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
	buf[17] = '\0';
	return (buf);
}

char	*ip_strconv(const uint8_t *bytes)
{
	char	*buf;
	int		i;
	int		y;

	i = 0;
	y = 0;
	buf = malloc(16)
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
		y += 5;
	}
	buf[y - 1] = '\0';
	return (buf);
}

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
