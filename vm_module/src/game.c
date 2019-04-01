#include "corewar.h"

void		check_delta(t_core *core)
{
	if (--core->max_checks == 0 || core->nbr_live >= NBR_LIVE)
	{
		if (core->max_cycle_to_die > CYCLE_DELTA)
			core->max_cycle_to_die -= CYCLE_DELTA;
		else
			core->max_cycle_to_die = 0;
		core->max_checks = MAX_CHECKS;
	}
	core->nbr_live = 0;
}

void		kill_process(t_core *core)
{
	t_process	*pre;
	t_process	*tmp;
	t_process	*next;

	pre = NULL;
	tmp = core->process;
	next = tmp->next;
	while (tmp)
	{
		if (tmp->is_alive == false)
		{
			if (pre)
				pre->next = next;
			else
				core->process = next;
			free(tmp);
		}
		pre = tmp;
		tmp = tmp->next;
		next = tmp->next;
	}
	check_delta(core);
}

void		call_instructions(t_core *core)
{
	t_process	*tmp;

	tmp = core->process;
	while (tmp)
	{
		if (tmp->remaining_cycles)
			--tmp->remaining_cycles;
		else
			ft_instructions(core, tmp);
		tmp = tmp->next;
	}
}

void		find_winner(t_core *core)
{
	t_player	*tmp;

	tmp = core->players;
	while (tmp && tmp->p != core->last_live_done_by)
		tmp = tmp->next;
	ft_printf("The magnificent winner is %s\n", tmp->head.prog_name);
}

t_errors	the_game(t_core *core)
{
	t_process	*proc;
	uint32_t	cycles;

	cycles = core->max_cycle_to_die;
	proc = core->process;
	while (proc)
	{
		call_instructions(core);
		if (--cycles == 0)
		{
			kill_process(core);
			cycles = core->max_cycle_to_die;
		}
		proc = core->process;
	}
	find_winner(core);
	return (ok);
}
