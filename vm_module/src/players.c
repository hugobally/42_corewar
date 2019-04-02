#include <fcntl.h>
#include <unistd.h>
#include "corewar.h"

uint32_t	reverse_endian(uint32_t	num)
{
	uint32_t	swapped;

	swapped = ((num>>24)&0xff);
	swapped |= ((num<<8)&0xff0000);
	swapped |= ((num>>8)&0xff00);
	swapped |= ((num<<24)&0xff000000);
	return (swapped);
}

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
	ft_printf("TEST_READ_PROC_IN\n");
	if (read(fd, new->proc, new->head.prog_size) < new->head.prog_size)
		return (badfile);
	if (read(fd, NULL, 1) > 0)
		return (badfile);
	ft_printf("READ_PROC_OUT\n");
	return (ok);
}

#include <stdlib.h>

t_errors	read_header(int fd, t_player *new)
{
	ft_printf("Read : %d\n", read(fd, new, sizeof(header_t)));
	ft_printf("%d\n", sizeof(header_t));
	new->head.magic = reverse_endian(new->head.magic);
	new->head.prog_size = reverse_endian(new->head.prog_size);
	ft_printf("Magic : %x\nProg size : %x\n", new->head.magic, new->head.prog_size);
	ft_printf("TEST_READ_HEADER\n");
	ft_printf("Magic : %u\nProg name : %s\nProg_size : %u\nComment : %s\n", new->head.magic, new->head.prog_name, new->head.prog_size, new->head.comment);
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
