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
	if (!inet_ntop(AF_INET, &(sa_in->sin_addr), ping->ipv4,\
			sizeof(ping->ipv4)))
		cleanup(ping, "Failed to process address");
}

void		get_socket(t_ping *ping)
{
	t_addrinfo			*ai;
	t_timeval			tv_out;
	int					ttl;

	ttl = 64;
	ai = ping->addrinfo;
	tv_out.tv_sec = ping->packet_delay;
	tv_out.tv_usec = 0;
	if ((ping->sockfd = socket(ai->ai_family, ai->ai_socktype,\
			ai->ai_protocol)) < 0)
		cleanup(ping, "Failed to create socket");
	if (setsockopt(ping->sockfd, SOL_IP, IP_TTL,\
			&ttl, sizeof(ttl)) < 0)
		cleanup(ping, "TTL: Failed to set socket options");
	if (setsockopt(ping->sockfd, SOL_SOCKET, SO_RCVTIMEO,\
			(const char*)&tv_out, sizeof(tv_out)) < 0)
		cleanup(ping, "Timeout: Failed to set socket options");
}

bool	check_condition(t_ping *ping)
{
	if (ping->packet_count == 0)
		return (false);
	ping->packet_count--;
	return (true);
}

unsigned short	checksum(void *ptr, size_t len)
{
	unsigned short	*tmp;
	unsigned int	sum;
	unsigned short	result;

	tmp = ptr;
	for (sum = 0; len > 1; len -= 2)
		sum += *tmp++;
	if (len == 1)
		sum += *(unsigned char*)ptr;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return (result);
}

void	get_packet(t_ping *ping)
{
	char	*msg;
	int		msg_size;

	//bzero(ping->packet, sizeof(ping->packet));
	ping->out_packet.hdr.type = ICMP_ECHO;
	ping->out_packet.hdr.un.echo.id = getpid();
	msg_size = ping->packet_size - sizeof(t_icmphdr);
	if (!(msg = ft_memalloc(msg_size)))
		cleanup(ping, MALLOC_FAILURE);
	ft_memset(msg, '*', msg_size - 1);
	ping->out_packet.msg = msg;
	ping->out_packet.hdr.un.echo.sequence++;
	ping->out_packet.hdr.checksum =\
		checksum(&ping->out_packet, sizeof(t_packet));
}

void	send_packet(t_ping *ping)
{
	if (sendto(ping->sockfd, &ping->out_packet, sizeof(t_packet), 0,\
			ping->addrinfo->ai_addr, sizeof(t_addrinfo)) <= 0)
	{
		cleanup(ping, "Failed to send packet");
	}
}

void	receive_packet(t_ping *ping)
{
	unsigned int	addrlen;

	addrlen = sizeof(t_addr);
	if  (recvfrom(ping->sockfd, &ping->in_packet, sizeof(t_packet), 0,\
			&ping->in_addr, &addrlen) <= 0)
	{
		dprintf(2, "%s: Failed to receive packet\n", ping->program_name);	
	}
}

int		main(int ac, char **av)
{
	t_ping		*ping;

	init(&ping, av);
	get_addr_info(ping);
	get_socket(ping);
	while (check_condition(ping))
	{
		get_packet(ping);
		send_packet(ping);
		receive_packet(ping);
		//send_packet(ping);
		//receive_packet(ping);
	}
	ft_printf("%s\n", ping->dst_name);
	ft_printf("%s\n", ping->ipv4);
	cleanup(ping, NULL);
}
