#include <fcntl.h>
#include <unistd.h>
#include "corewar.h"

void		push_player(t_core *core, t_player *new)
{
	new->next = core->players;
	core->players = new;
}

t_errors	read_proc(int fd, t_player *new)
{
	if (!(new->proc = malloc(new->head.prog_size)))
		return (falloc);
	if (read(fd, new->proc, new->head.prog_size) < new->head.prog_size)
		return (badfile);
	return (ok);
}

t_errors	read_header(int fd, t_player *new)
{
	char	buff[sizeof(header_t)];

	if (read(fd, buff, sizeof(header_t)) < sizeof(header_t))
		return (badfile);
	ft_memcpy(new, buff, sizeof(header_t));
	return (ok);
}

t_errors	new_player(t_core *core, char *av)
{
	t_player	*new;
	int			fd;
	t_errors	ret;

	if (!(new = (t_player*)ft_memalloc(sizeof(t_player))))
		return (falloc);
	if ((fd = open(av, O_RDONLY)) < 2)
		return (badopen);
	if ((ret = read_header(fd, new)) != ok)
	{
		close(fd);
		return (ret);
	}
	if ((ret = read_proc(fd, new)) != ok)
	{
		close(fd);
		return (ret);
	}
	close(fd);
	push_player(core, new);
	return (ok);
}
