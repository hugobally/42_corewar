/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:39:42 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 13:39:43 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ft_carry(t_process *process, int res)
{
	if (res == 0)
		process->carry = true;
	if (res != 0)
		process->carry = false;
}

void		push_process(t_core *core, t_process *new)
{
	new->next = core->process;
	if (core->process)
		core->process->previous = new;
	core->process = new;
}

t_errors	make_process(t_core *core, uint32_t pc, t_player *pl)
{
	t_process	*new;

	if (!(new = ft_memalloc(sizeof(t_process))))
		return (falloc);
	new->pro_name = ++core->nb_pro;
	new->pc = pc;
	new->regs[0] = pl->p;
	new->player = pl->p;
	push_process(core, new);
	return (ok);
}

t_errors	nb_player_spec(t_core *core, t_player *new)
{
	int			nb;
	t_player	*player;

	player = core->players;
	nb = core->next_player;
	while (player != NULL)
	{
		if (player->p == -nb)
			return (badarg);
		player = player->next;
	}
	core->next_player = 0;
	new->p = -nb;
	return (ok);
}

t_errors	nb_player(t_core *core, t_player *new)
{
	int			nb;
	t_player	*start;
	t_player	*player;

	nb = -1;
	player = core->players;
	start = player;
	if (core->next_player)
		return (nb_player_spec(core, new));
	while (player)
	{
		if (player->p == nb)
		{
			nb--;
			player = start;
		}
		player = player->next;
	}
	new->p = nb;
	return (ok);
}
