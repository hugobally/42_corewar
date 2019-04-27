#include "corewar.h"
#include "graph.h"
#include <stdlib.h>
#include <unistd.h> //ARETIERE AVEC USLEEP
#include <pthread.h>

extern pthread_cond_t g_condition;
extern pthread_cond_t g_condition2;
extern pthread_mutex_t g_mutex;

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
	while (tmp)
	{
		if (tmp->has_lived == false)
			tmp->is_alive = false;
		tmp->has_lived = false;
		tmp = tmp->next;
	}
	check_delta(core);
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
		if (core->visu && core->graph->proc_aff)
		{
			pthread_mutex_lock (&g_mutex);
			pthread_cond_signal (&g_condition);
			pthread_cond_wait(&g_condition2, &g_mutex);
			 pthread_mutex_unlock (&g_mutex);
		}
		if (core->visu && core->graph->pause)
			;
		else
		{
			if (core->visu)
			{
				refresh_all_wins(core);
				print_process(core);
				print_infos(core);
			}
			core->loop++;
			if (core->verbose & 2)
				ft_printf("It is now cycle %d\n", core->loop);
			if (core->visu)
				usleep(1000000 / core->graph->fps);
			core->cycles = core->cycles - 1;
			if ((res = call_instructions(core)) != ok)
				return (res);
			proc = core->process;
			if (core->cycles <= 0 && proc)
			{
				kill_process(core, NULL, core->process);
				core->cycles = core->max_cycle_to_die;
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
	return (ok);
}
