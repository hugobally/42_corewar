#include "corewar.h"
#include "graph.h"
#include <stdlib.h>

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
	// ft_putendl("Kill_process IN");
	while (tmp != NULL)
	{
		if (tmp->is_alive == false)
		{
			// ft_printf("killed, %d\n", tmp->player);
			if (pre)
				pre->next = next;
			else
				core->process = next;
			//free(tmp);
		}
		else
		{
			// ft_printf("not killed, %d\n", tmp->player);
			tmp->is_alive = false;
		}
		pre = tmp;
		tmp = tmp->next;
		if (tmp != NULL)
			next = tmp->next;
	}
	check_delta(core);
	// ft_putendl("Kill_process OUT");
}

t_errors	call_instructions(t_core *core)
{
	t_process	*tmp;
	t_errors	res;

	//ft_printf("call_instruction IN\n");
	tmp = core->process;
	while (tmp != NULL)
	{
		//ft_printf("start of loop \n");
		if (tmp->remaining_cycles != 0)
		{
			--tmp->remaining_cycles;
			//ft_printf("call_instruction MID\n");
		}
		else
			if ((res = ft_instructions(core, tmp)) != ok)
				return (res);
		//ft_printf("end of loop \n");
		tmp = tmp->next;
	}
	//ft_printf("call_instruction OUT\n");
	return (ok);
}

void		find_winner(t_core *core)
{
	t_player	*tmp;

	tmp = core->players;
	while (tmp && tmp->p != core->last_live_done_by)
		tmp = tmp->next;
	if (tmp && core->winner)
		ft_printf("The magnificent winner is %s\n", tmp->head.prog_name);
	else
		ft_printf("No one has won\n");
}

t_errors	the_game(t_core *core)
{
	t_process	*proc;
	uint32_t	cycles;
	int			res;

	cycles = core->max_cycle_to_die;
	proc = core->process;
	while (proc)
	{
		//if (controls(core->graph))
		//	return (f1_exit);
		// ft_printf("Start of the loop: cycles %d\n", cycles);
		//if (!core->graph->pause)
		//{
			--cycles;
			if (cycles > 0)
			{
				if ((res = call_instructions(core)) != ok)
					return (res);
			}
			else
			{
				while (cycles <= 0 && proc)
				{
					kill_process(core);
				// ft_printf("Got out of kill_process max_cycle :%d\n", core->max_cycle_to_die);
					cycles = core->max_cycle_to_die;
					proc = core->process;
				}
			}
			if (core->dump != 0)
			{
				if (--core->dump == 0)
				{
					hexdump(core);
					return (ok) ;
				}
			}
		//}
	}
	find_winner(core);
	return (ok);
}
