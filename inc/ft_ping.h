#ifndef FT_PING_H
# define FT_PING_H

# include "libft.h"
# include <stdlib.h>		//exit (!?)
# include <stdio.h>
# include <stdarg.h>		//va_start, va_end
# include <arpa/inet.h>		//inet_ntop, inet_pton
# include <string.h>		//strdup
# include <sys/types.h>		//getadrinfo
# include <sys/socket.h>	//getadrinfo
# include <netdb.h>			//getadrinfo

# define EXIT_FAILURE		1
# define EXIT_SUCCESS		0
# define MALLOC_FAILURE		"Malloc failed"

typedef struct sockaddr		t_addr;
typedef struct sockaddr_in	t_sa_in;
typedef struct addrinfo		t_addrinfo;


typedef struct 			s_ping
{
	char				*program_name;
	char				*dst_name;
	char				ipv4[INET_ADDRSTRLEN];
	int					sockfd;
	t_addrinfo			*addrinfo;
}						t_ping;

void	init(t_ping **ping, char **av);
void	cleanup(t_ping *ping, const char *format, ...);
#endif
