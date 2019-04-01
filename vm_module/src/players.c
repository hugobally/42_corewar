#include <fcntl.h>
#include <unistd.h>
#include "corewar.h"

void		push_player(t_core *core, t_player *new)
{
	t_player	*tmp;

	tmp = core->players;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		core->players = new;
}

t_errors	read_proc(int fd, t_player *new)
{
	if (read(fd, new->proc, new->head.prog_size) < new->head.prog_size)
		return (badfile);
	if (read(fd, NULL, 1) > 0)
		return (badfile);
	return (ok);
}

t_errors	read_header(int fd, t_player *new)
{
	if (read(fd, (unsigned char*)new, sizeof(header_t)) < (ssize_t)sizeof(header_t))
		return (badfile);
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
	new->p = core->next_player ? core->next_player : 1;
	push_player(core, new);
	++core->nb_players;
	return (ok);
}
