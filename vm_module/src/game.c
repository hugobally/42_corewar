#include "corewar.h"
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
	//ft_putendl("Kill_process IN");
	while (tmp != NULL)
	{
		if (tmp->is_alive == false)
		{
			ft_printf("killed, %d\n", tmp->regs[0]);
			if (pre)
				pre->next = next;
			else
				core->process = next;
			//free(tmp);
		}
		else
		{
			ft_printf("not killed, %d\n", tmp->regs[0]);
			tmp->is_alive = false;
		}
		pre = tmp;
		tmp = tmp->next;
		if (tmp != NULL)
			next = tmp->next;
	}
	check_delta(core);
	ft_putendl("Kill_process OUT");
}

void		call_instructions(t_core *core)
{
	t_process	*tmp;

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
			ft_instructions(core, tmp);
		//ft_printf("end of loop \n");
		tmp = tmp->next;
	}
}

void		find_winner(t_core *core)
{
	t_player	*tmp;

	tmp = core->players;
	while (tmp && tmp->p != core->last_live_done_by)
		tmp = tmp->next;
	ft_printf("The magnificent winner is %s\n", tmp ? tmp->head.prog_name : "Ta soeur");
}

t_errors	the_game(t_core *core)
{
	t_process	*proc;
	uint32_t	cycles;

	cycles = core->max_cycle_to_die;
	proc = core->process;
	while (proc)
	{
		//ft_printf("Start of the loop: cycles %d\n", cycles);
		call_instructions(core);
		//ft_putendl("Called instructions");
		if (--cycles == 0)
		{
			kill_process(core);
			ft_putendl("Got out of kill_process");
			cycles = core->max_cycle_to_die;
		}
		proc = core->process;
		if (core->dump != 0)
			if (--core->dump == 0)
			{
				hexdump(core);
				break ;
			}
	}
	find_winner(core);
	return (ok);
}
