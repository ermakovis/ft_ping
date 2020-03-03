#ifndef FT_PING_H
# define FT_PING_H

# include "libft.h"
# include <stdlib.h>			//exit (!?)
# include <stdio.h>
# include <stdarg.h>			//va_start, va_end
# include <arpa/inet.h>			//inet_ntop, inet_pton
# include <stdbool.h>			//true, false
# include <string.h>			//strdup
# include <sys/types.h>			//getadrinfo
# include <sys/socket.h>		//getadrinfo
# include <netdb.h>				//getadrinfo
# include <netinet/ip_icmp.h>	//struct icmphdr

// TODO Get system's TTL value
# define EXIT_FAILURE		1
# define EXIT_SUCCESS		0
# define MALLOC_FAILURE		"Malloc failed"
# define DEF_PACKET_COUNT	4
# define DEF_PACKET_SIZE	65
# define DEF_PACKET_DELAY	1

typedef struct sockaddr		t_addr;
typedef struct sockaddr_in	t_sa_in;
typedef struct addrinfo		t_addrinfo;
typedef struct timeval		t_timeval;
typedef struct icmphdr		t_icmphdr;

typedef struct				s_packet
{
	t_icmphdr				hdr;
	char					*msg;
}							t_packet;

typedef struct 				s_ping
{
	char					*program_name;
	char					*dst_name;
	char					ipv4[INET_ADDRSTRLEN];
	int						sockfd;
	int						packet_size;
	int						packet_count;
	int						packet_delay;
	t_packet				out_packet;
	t_packet				in_packet;
	t_addr					in_addr;
	t_addrinfo				*addrinfo;
}							t_ping;

void						init(t_ping **ping, char **av);
void						cleanup(t_ping *ping, const char *format, ...);
#endif
