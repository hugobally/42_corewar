#include "corewar.h"

t_errors 		ft_live(t_core *core, t_process *process)
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
	if (core->verbose & 4)
		ft_printf("P%5d | live %d\n", -process->regs[0], process->params.p1);
	return (ok);
}
