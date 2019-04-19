#include "corewar.h"

t_errors		ft_store(t_core *core, t_process *process)
{
	t_params 		params;
	int				p1;
	int 			p2;
	int				p3;
	int				ret;

	params = process->params;
	if ((ret = ft_reg(process, &p1, &p2, &p3)) != ok)
		return (ok);
	if (p2 == REG)
		process->regs[params.p2 - 1] = (int)process->regs[params.p1 - 1];
	else if (p2 == IND)
		write_val(core, get_pc(process->pc + params.p2 % IDX_MOD), 4, process->regs[params.p1 - 1], process->player);
	if (core->verbose & 4)
		ft_printf("P%5d | st r%d %d\n", -process->regs[0], process->params.p1, process->params.p2);
	return (ok);
}
