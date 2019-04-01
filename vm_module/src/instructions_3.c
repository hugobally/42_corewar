#include "corewar.h"

int			ft_zjmp(t_core *core, t_process *process)
{
	if (process->carry == true)
		process->pc = process->pc + process->params.p1;
	return (0);
}