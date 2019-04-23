#include "corewar.h"
#include "graph.h"
#include <stdlib.h>
#include <unistd.h> //ARETIERE AVEC USLEEP

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
	free(cur);
	cur = NULL;
}

void		kill_process(t_core *core, t_process *pre, t_process *cur)
{
	while (cur != NULL)
	{
		if (cur->is_alive == false)
		{
			cur_is_dead(core, pre, cur);
		}
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
	check_delta(core);
}

t_errors	the_game(t_core *core)
{
	t_process	*proc;
	int			cycles;
	int			res;
	uint32_t	i;
//	int			ch;

	i = 0;
	cycles = core->max_cycle_to_die;
	proc = core->process;
	//if (core->flags & FLAG_SDUMP)
	//	hexdump(core, 1);
	while (proc)
	{
		//core->loop++; OLD CORE LOOP
		if (core->verbose & 2)
			ft_printf("It is now cycle %d\n", core->loop);
		//if (visu_control(core, cycles))
		//	return (f1_exit);
		if (core->visu && core->graph->pause)
		{
		}
		else
		{
			core->loop++;
			usleep(100000 / core->graph->fps);
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
	find_winner(core);
	//while (core->visu && (ch = getch()) != KEY_F(1))
	//{
	//}
	return (ok);
}
