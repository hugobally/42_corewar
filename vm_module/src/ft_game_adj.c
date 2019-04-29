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
	if (tmp)
		ft_printf("Contestant %d, \"%s\", has won !\n",
		-tmp->p, tmp->head.prog_name);
}

int			ft_count_process(t_process *process)
{
	int i;

	i = 0;
	while (process != NULL)
	{
		process = process->next;
		i++;
	}
	return (i);
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
