/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-ru <rle-ru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:39:16 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 14:24:43 by rle-ru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "corewar.h"

uint32_t	reverse_endian(uint32_t num)
{
	uint32_t	swapped;

	swapped = ((num >> 24) & 0xff);
	swapped |= ((num << 8) & 0xff0000);
	swapped |= ((num >> 8) & 0xff00);
	swapped |= ((num << 24) & 0xff000000);
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
	new->next = NULL;
}

t_errors	read_proc(int fd, t_player *new)
{
	char		buff[1];

	if (read(fd, new->proc, new->head.prog_size) < new->head.prog_size)
		return (codesize);
	if (read(fd, buff, 1) > 0)
		return (codesize);
	return (ok);
}

t_errors	read_header(int fd, t_player *new)
{
	if ((int64_t)read(fd, new, sizeof(t_header)) < (int64_t)sizeof(t_header))
		return (filesmall);
	new->head.magic = reverse_endian(new->head.magic);
	new->head.prog_size = reverse_endian(new->head.prog_size);
	if (new->head.prog_size > CHAMP_MAX_SIZE)
		return (champlarge);
	if (new->head.prog_size == 0)
		return (badchamp);
	if (new->head.magic != COREWAR_EXEC_MAGIC)
		return (badmagic);
	new->next = NULL;
	return (ok);
}

t_errors	new_player(t_core *core, char *av)
{
	t_player	*new;
	int			fd;
	t_errors	ret;

	if (!(new = (t_player*)ft_memalloc(sizeof(t_player))))
		return (falloc);
	push_player(core, new);
	if ((fd = open(av, O_RDONLY)) < 2)
		return (badopen);
	if ((ret = read_header(fd, new)) != ok)
	{
		core->bad_size = new->head.prog_size;
		close(fd);
		return (ret);
	}
	if ((ret = read_proc(fd, new)) != ok)
	{
		close(fd);
		return (ret);
	}
	close(fd);
	if ((ret = nb_player(core, new)) != ok)
		return (ret);
	new->is_alive = true;
	return (ok);
}
