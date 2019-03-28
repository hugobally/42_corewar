#include <fcntl.h>
#include <unistd.h>
#include "corewar.h"

void	push_player(t_core *core, t_player *new)
{
	new->next = core->players;
	core->players = new;
}

/*
** Reste a tout compartimenter et a close le fd en cas d'erreur.
** Changer MEM_SIZE ici par max(CHAMP_MAX_SIZE, PROG_NAME_LENGTH, COMMENT_LENGTH)
*/

t_errors new_player(t_core *core, char *av)
{
	t_player	*new;
	char		buff[MEM_SIZE + 1];
	int			fd;

	ft_bzero(buff, MEM_SIZE + 1);
	if (!(new = (t_player*)ft_memalloc(sizeof(t_player))))
		return (falloc);
	if ((fd = open(av, O_RDONLY)) < 2)
		return (badopen);
	if (read(fd, buff, 4) < 4)
		return (badfile);
	if ((int)buff[0] != 0xea83f3)
		return (badfile);
	if (read(fd, buff, 128) < 128)
		return (badfile);
	if (!(new->name = ft_strdup(buff)))
		return (falloc);
	ft_bzero(buff, 128);
	if (read(fd, buff, 2048) < 2048)
		return (badfile);
	if (!(new->desc = ft_strdup(buff)))
		return (falloc);
	ft_bzero(buff, 2048);
	if ((new->size = read(new->fd, buff, MEM_SIZE)) < 0)
		return (badfile);
	if (!(new->proc = malloc(sizeof(new->size))))
		return (falloc);
	ft_memcpy(new->proc, buff, new->size);
	if (read(fd, buff, MEM_SIZE) > 0)
		return (badfile);
	close(fd);
	push_player(core, new);
	return (ok);
}
