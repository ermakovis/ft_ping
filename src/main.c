#include "ft_ping.h"

/*
**	TODO Reverse dns_lookup
*/

void		get_addr_info(t_ping *ping)
{
	t_addrinfo			hint;
	t_sa_in				*sa_in;	

	bzero(&hint, sizeof(t_addrinfo));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_RAW;
	hint.ai_protocol = IPPROTO_ICMP;
	if (getaddrinfo(ping->dst_name, NULL, &hint, &ping->addrinfo) != 0)
		cleanup(ping, "%s: No such host", ping->dst_name);
	sa_in = (t_sa_in*)ping->addrinfo->ai_addr;
	if (!inet_ntop(AF_INET, &(sa_in->sin_addr), ping->ipv4, sizeof(ping->ipv4)))
		cleanup(ping, "Failed to process address");
}

void		create_socket(t_ping *ping)
{
	t_addrinfo			*ai;
	int					incl;

	incl = 1;
	ai = ping->addrinfo;
	if ((ping->sockfd = socket(ai->ai_family, ai->ai_socktype,\
			ai->ai_protocol)) < 0)
		cleanup(ping, "Failed to create socket");
	if (setsockopt(ping->sockfd, IPPROTO_ICMP, IP_HDRINCL,\
			&incl, sizeof(incl)) < 0)
		cleanup(ping, "Failed to set socket options");
}

int		main(int ac, char **av)
{
	t_ping		*ping;

	init(&ping, av);
	get_addr_info(ping);
	create_socket(ping);
	cleanup(ping, NULL);
}
