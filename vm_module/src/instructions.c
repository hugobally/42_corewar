#include "corewar.h"

int 		ft_live(t_core *core, t_process *process)
{
	int player;

	process->is_alive = TRUE;
	player = *(process->params)->p1;
	return(player);
}

int			ft_instructions(t_core *core, t_process *process)
{
	int op;

	op = process->instruction;
	if (op = live)
		return(ft_live(core, process));
}