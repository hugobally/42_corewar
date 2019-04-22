#include "corewar.h"

t_errors	ft_live(t_core *core, t_process *process)
{
	t_player	*tmp;

	tmp = core->players;
	process->is_alive = true;
	while (tmp && tmp->p != process->params.p1)
		tmp = tmp->next;
	if (tmp && tmp->p == process->params.p1)
		core->last_live_done_by = process->params.p1;
	core->nbr_live++;
	core->winner = 1;
	process->last_live = core->loop;
	if (core->verbose & 4)
		ft_printf("P%5d | live %d\n", process->pro_name, process->params.p1);
	if (tmp && core->verbose & 1)
		ft_printf("Player %d (%s) is said to be alive\n",
			-process->params.p1, tmp->head.prog_name);
	return (ok);
}
