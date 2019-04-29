/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_adj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:32:32 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 14:56:24 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "graph.h"

void		ft_not_alive(t_player *tmp)
{
	while (tmp)
	{
		if (tmp->has_lived == false)
			tmp->is_alive = false;
		tmp->has_lived = false;
		tmp = tmp->next;
	}
}

t_errors	call_instructions(t_core *core)
{
	t_process	*tmp;
	t_errors	res;

	tmp = core->process;
	while (tmp != NULL)
	{
		if (tmp->remaining_cycles != 0)
		{
			--tmp->remaining_cycles;
		}
		else
		{
			if ((res = ft_instructions(core, tmp)) != ok)
				return (res);
		}
		tmp = tmp->next;
	}
	return (ok);
}

void		find_winner(t_core *core)
{
	t_player	*tmp;

	tmp = core->players;
	while (tmp && tmp->p != core->last_live_done_by)
		tmp = tmp->next;
	if (core->visu && tmp)
	{
		print_champions(core);
		refresh_all_wins(core);
	}
	else if (tmp)
		ft_printf("Contestant %d, \"%s\", has won !\n",
		-tmp->p, tmp->head.prog_name);
}

void		check_delta(t_core *core)
{
	if (--core->max_checks == 0 || core->nbr_live >= NBR_LIVE)
	{
		core->max_cycle_to_die -= CYCLE_DELTA;
		core->max_checks = MAX_CHECKS;
		if (core->verbose & 2)
			ft_printf("Cycle to die is now %d\n", core->max_cycle_to_die);
	}
	core->nbr_live = 0;
}
