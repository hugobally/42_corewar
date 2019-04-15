#include "corewar.h"
#include "graph.h"
#include <stdlib.h>
#include <unistd.h>
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
	t_process	*cur;

	pre = NULL;
	cur = core->process;
	while (cur != NULL)
	//ft_putendl("Kill_process IN");
	{
		if (cur->is_alive == false)
		{
			//ft_printf("killed, %d\n", tmp->player);
			if (pre)
				pre->next = cur->next;
			else
				core->process = cur->next;
			free(cur);
			cur = NULL;
		}
		else
		{
			cur->is_alive = false;
			pre = cur;
			//ft_printf("not killed, %d\n", tmp->player);
		}
		if (pre != NULL)
			cur = pre->next;
		else
			cur = core->process;
	}
	check_delta(core);
	//ft_putendl("Kill_process OUT");
}

t_errors	call_instructions(t_core *core)
{
	t_process	*tmp;
	t_errors	res;

	//ft_printf("call_instruction IN\n");
	tmp = core->process;
	while (tmp != NULL)
	{
		if (tmp->remaining_cycles != 0)
		{
			--tmp->remaining_cycles;
			//ft_printf("call_instruction MID\n");
		}
		else
			if ((res = ft_instructions(core, tmp)) != ok)
				return (res);
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

t_errors	the_game(t_core *core)
{
	t_process	*proc;
	uint32_t	cycles;
	int			res;
	uint32_t	i;

	i = 0;
	cycles = core->max_cycle_to_die;
	proc = core->process;
	while (proc)
	{
		if (core->visu && controls(core->graph))
			return (f1_exit);
		if (core->visu && core->graph->pause)
			usleep(10000);
		else 
		{
			if (--cycles > 0)
			{
				if ((res = call_instructions(core)) != ok)
					return (res);
				proc = core->process;
			}
			else
				while (cycles <= 0 && proc)
				{
					kill_process(core);
					cycles = core->max_cycle_to_die;
					proc = core->process;
				}
			if (++i == core->sdump)
				i = hexdump(core, 1);
			if (core->flags & FLAG_DUMP)
				if (--core->dump == 0)
					return (hexdump(core, 0));
		}
	}
	int		ch;
	find_winner(core);
	while(core->visu && (ch = getch()) != KEY_F(1))
	{
	}
	return (ok);
}
