#include "corewar.h"

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
}

t_errors	the_game(t_core *core)
{
	t_process	*proc;
	uint32_t	cycles;

	cycles = core->max_cycle_to_die;
	proc = core->process;
	while (proc)
	{
		if (--cycles == 0)
		{
			kill_process(core);
			cycles = core->max_cycle_to_die;
		}
		proc = core->process;
	}
	return (ok);
}
