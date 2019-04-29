/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:36:00 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 15:07:24 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "graph.h"
#include <stdlib.h>

void		cur_is_dead(t_core *core, t_process *pre, t_process *cur)
{
	if (pre)
		pre->next = cur->next;
	else
		core->process = cur->next;
	if (cur->next)
		cur->next->previous = pre;
	if (core->verbose & 8)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
	cur->pro_name, core->loop - cur->last_live,
	core->max_cycle_to_die);
	if (core->visu)
	{
		remove_procces_to_arena(cur->pc, core);
		erase_process(core);
	}
	free(cur);
	cur = NULL;
}

void		kill_process(t_core *core, t_process *pre, t_process *cur)
{
	t_player *tmp;

	while (cur != NULL)
	{
		if (cur->is_alive == false || core->max_cycle_to_die < 0)
			cur_is_dead(core, pre, cur);
		else
		{
			cur->is_alive = false;
			pre = cur;
		}
		if (pre != NULL)
			cur = pre->next;
		else
			cur = core->process;
		if (cur)
			cur->previous = pre;
	}
	tmp = core->players;
	ft_not_alive(tmp);
	if (core->visu)
		print_champions(core);
	check_delta(core);
}

int			ft_killed_or_not(t_core *core, t_process *proc, uint32_t *i)
{
	if (core->cycles <= 0 && proc)
	{
		kill_process(core, NULL, core->process);
		core->cycles = core->max_cycle_to_die;
		proc = core->process;
	}
	if (++*i == core->sdump)
		*i = hexdump(core, 1);
	if (core->flags & FLAG_DUMP)
		if (--core->dump <= 0 && proc)
			return (hexdump(core, 0));
	return (1);
}

t_errors	ft_compress(t_core *core, t_process *proc, uint32_t *i)
{
	t_errors	res;

	game_refresh(core);
	core->loop++;
	if (core->verbose & 2)
		ft_printf("It is now cycle %d\n", core->loop);
	game_fps(core);
	core->cycles = core->cycles - 1;
	if ((res = call_instructions(core)) != ok)
		return (res);
	proc = core->process;
	if ((res = ft_killed_or_not(core, proc, i)) == 0)
		return (du);
	return (ok);
}

t_errors	the_game(t_core *core)
{
	t_process	*proc;
	int			res;
	uint32_t	i;

	i = 0;
	core->cycles = core->max_cycle_to_die;
	proc = core->process;
	if (core->flags & FLAG_SDUMP)
		hexdump(core, 1);
	while (proc)
	{
		game_mutex(core);
		if (core->visu && core->graph->pause)
			;
		else
		{
			if ((res = ft_compress(core, proc, &i)) != ok)
				return (res);
			proc = core->process;
		}
	}
	find_winner(core);
	return (ok);
}
