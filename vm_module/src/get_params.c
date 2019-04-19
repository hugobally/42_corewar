#include "corewar.h"

int			ft_get_params(t_core *core, t_process *process, int p, int type)
{
	if (type == REG)
		return (process->regs[p - 1]);
	else if (type == DIR)
		return (p);
	else if (type == IND)
		return (core->arena[get_pc(process->pc + (p % IDX_MOD))]);
	return (0);
}
