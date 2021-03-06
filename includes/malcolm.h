#ifndef MALCOLM_H
# define MALCOLM_H

# define BUFSIZE 1500
# define IP_STR_SIZE 129
# define PING_TTL 64
# define RECV_TIMEOUT 1
# define IP_STR_LEN 17
# define IP_LEN 4
# define MAC_LEN 6
# define INTERFACES "en0 enp0s3"

# include <stdio.h>
# include <signal.h>
# include <netdb.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <ifaddrs.h>
# include <netinet/if_ether.h>
# include <netpacket/packet.h>

# include "libft.h"

typedef struct s_arp
{
	uint8_t			s_mac[MAC_LEN];
	uint8_t			d_mac[MAC_LEN];
	uint16_t		etype;
	uint16_t		htype;
	uint16_t		ptype;
	uint8_t			hlen;
	uint8_t			plen;
	uint16_t		opcode;
	uint8_t			sender_mac[MAC_LEN];
	uint8_t			sender_ip[IP_LEN];
	uint8_t			target_mac[MAC_LEN];
	uint8_t			target_ip[IP_LEN];
}				t_arp;

typedef struct s_pckt
{
	struct ip		*ip;
	void			*content;
}				t_pckt;

typedef struct s_malcolm
{
	int				v;
	int				l;
	struct addrinfo	*s_info;
	struct addrinfo	*d_info;
	struct ifaddrs	*ifap;
	struct ifaddrs	*ifa;
	char			*s_name;
	char			*s_maddr;
	char			*s_ip;
	char			*d_name;
	char			*d_maddr;
	char			*d_ip;
	struct sockaddr	*d_addr;
	socklen_t		d_addrlen;
	int				sockfd;
	pid_t			pid;
}				t_malcolm;

extern t_malcolm	g_mal;

/*
** srcs/args.c
*/

int				get_args(t_malcolm *ping, int ac, char **av);

/*
** srcs/args_utils.c
*/

void			free_args(t_malcolm *mal);
void			init_malcolm(t_malcolm *mal);

/*
** srcs/malcolm.c
*/

int				malcolm(t_malcolm *mal);

/*
** srcs/recv.c
*/

int				recv_arp(t_malcolm *mal, char *buf);

/*
** srcs/rev_dns.c
*/

struct addrinfo	*reverse_dns_info(char *host, char *serv,
					int family, int socktype);
char			*set_inetaddr(struct addrinfo *info);

/*
** srcs/send.c
*/

void			send_arp(t_malcolm *mal, char *recvbuf);

/*
** srcs/convert.c
*/

int				hextoint(const char *str);
int				dectoint(const char *str);

/*
** srcs/ip_utils.c
*/

char			*ip_strconv(const uint8_t *bytes);
void			set_ip_addr(char *src, uint8_t *dst, int len);

/*
** srcs/mac_utils.c
*/

char			*mac_strconv(const uint8_t *bytes);
void			set_mac_addr(char *src, uint8_t *dst, int len);

/*
** srcs/socket.c
*/

int				set_socket(int proto, int type, int mode);

/*
** srcs/interface.c
*/

struct ifaddrs	*get_interface(t_malcolm *mal);

/*
** srcs/signal.c
*/

void			catch_sigint(int signal);

/*
** srcs/utils.c
*/

void			copy_bytes(uint8_t *dst, uint8_t *src, int len);
void			print_usage(void);
int				err_ret(char *err, char *arg, int ret);

#endif
