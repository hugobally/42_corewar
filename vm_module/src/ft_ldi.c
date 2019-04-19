#include "corewar.h"

t_errors		ft_ldi(t_core *core, t_process *process)
{
	t_params	params;
	int			p1;
	int			p2;
	int			pa[3];

	p1 = 0;
	p2 = 0;
	ft_bzero(pa, sizeof(int) * 3);
	params = process->params;
	if (ft_reg(process, &pa[0], &pa[1], &pa[2]) != ok)
		return (ok);
	if (pa[0] == REG)
		p1 = process->regs[params.p1 - 1];
	else if (pa[0] == DIR)
		p1 = params.p1;
	else if (pa[0] == IND)
		p1 = read_val(core, get_pc(process->pc + (params.p1 % IDX_MOD)), 4);
	if (pa[1] == REG)
		p2 = process->regs[params.p2 - 1];
	else if (pa[1] == DIR)
		p2 = params.p2;
	process->regs[params.p3 - 1] = read_val(core, get_pc(process->pc + ((p1 + p2) % IDX_MOD)), REG_SIZE);
	if (core->verbose & 4)
	{
		ft_printf("P%5d | ldi %d %d r%d\n",
			-process->regs[0],
			p1,
			p2,
			process->params.p3);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", p1, p2, p1 + p2, get_pc(process->pc + (p1 + p2) % IDX_MOD));
	}
	return (ok);
}
