#include "malcolm.h"

int	set_socket(int proto, int type, int mode)
{
	int				sock;

	sock = socket(proto, type, htons(mode));
	if (sock < 0)
	{
		dprintf(2, "ft_malcolm: fail to create socket\n");
		return (-1);
	}
	return (sock);
}
