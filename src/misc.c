#include "ft_ping.h"

/*
** TODO STDERR for errors
** TODO Usage
*/
void	cleanup(t_ping *ping, const char *format, ...)
{
	va_list args;
	char	*ext_format;
	
	if (!ping)
		exit (EXIT_FAILURE);
	if (format && (ext_format = ft_powerjoin("%s: %s\n", ping->program_name, format)))
	{
		va_start(args, format);
		vdprintf(STDERR_FILENO, ext_format, args);
		va_end(args);
		ft_strdel(&ext_format);
	}
	exit (EXIT_SUCCESS);
}

void	init(t_ping **ping, char **av)
{
	t_ping		*ret;
	
	if (!av[1])
		cleanup (NULL, "There will be usage. May be");
	if (!(ret = ft_memalloc(sizeof(t_ping))))
		cleanup (NULL, MALLOC_FAILURE);
	ret->program_name = av[0];
	ret->dst_name = av[1];
	*ping = ret;
}
