#include "corewar.h"
#include "graph.h"
#include <stdlib.h>
#include <unistd.h>

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

void		kill_process(t_core *core, t_process *pre, t_process *cur)
{
	//ft_printf("kill process IN\n");
	while (cur != NULL)
	{
		if (cur->is_alive == false)
		{
		//	ft_printf("killed\n");
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
			free(cur);
			cur = NULL;
		}
		else
		{
		//	ft_printf("not killed\n");
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
	check_delta(core);
}

t_errors	call_instructions(t_core *core)
{
	t_process	*tmp;
	t_errors	res;

	//ft_printf("call_instruction IN\n");
	tmp = core->process;
	while (tmp != NULL)
	{
		//ft_printf("remaining_cycles %d, carry is %d\n", tmp->remaining_cycles, tmp->carry);
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
	if (tmp)
		ft_printf("Contestant %d, \"%s\", has won !\n", -tmp->p, tmp->head.prog_name);
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

int		visu_control(t_core *c, int cycles)
{
	if (!c->visu)
		return (0);
	print_process(c->graph, c->process);
	if (controls(c->graph))
		return (f1_exit);
	if (!c->graph->pause)
	{
		c->graph->nb_cycle++;
		print_infos(c->graph, c, cycles);
	}
	return (0);
}

t_errors	the_game(t_core *core)
{
	t_process	*proc;
	int			cycles;
	int			res;
	uint32_t	i;

	i = 0;
	cycles = core->max_cycle_to_die;
	proc = core->process;
	if (core->flags & FLAG_SDUMP)
		hexdump(core, 1);
	while (proc)
	{
		core->loop++;
		if (core->verbose & 2)
			ft_printf("It is now cycle %d\n", core->loop);
		if (visu_control(core, cycles))
			return (f1_exit);
		if (core->visu && core->graph->pause)
		{
		}
		else 
		{
			//ft_printf("else cycles:%d\n", cycles);
			--cycles;
			if ((res = call_instructions(core)) != ok)
					return (res);
			proc = core->process;
			if (cycles <= 0 && proc)
			{
				kill_process(core, NULL, core->process);
				cycles = core->max_cycle_to_die;
				proc = core->process;
			}
			if (++i == core->sdump)
				i = hexdump(core, 1);
			if (core->flags & FLAG_DUMP)
				if (--core->dump <= 0 && proc)
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
