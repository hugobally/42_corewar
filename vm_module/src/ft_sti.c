#include "corewar.h"

static void			ft_verbose(t_core *core, t_process *process, int p1, int p2)
{
	int	final;

	final = process->pc + (p1 + p2) % IDX_MOD;
	if (core->verbose & 4)
	{
		ft_printf("P%5d | sti r%d %d %d\n",
			process->pro_name,
			process->params.p1,
			p1,
			p2);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			p1, p2, p1 + p2, final);
	}
}

t_errors			ft_sti(t_core *core, t_process *process)
{
	int			p1;
	int			p2;
	int			pa[3];

	p1 = 0;
	p2 = 0;
	ft_bzero(pa, sizeof(int) * 3);
	if (ft_reg(process, &pa[0], &pa[1], &pa[2]) != ok)
		return (ok);
	if (pa[1] == REG)
		p1 = process->regs[process->params.p2 - 1];
	else if (pa[1] == DIR)
		p1 = process->params.p2;
	else if (pa[1] == IND)
		p1 = read_val(core,
			get_pc(process->pc + (process->params.p2 % IDX_MOD)), 4);
	if (pa[2] == REG)
		p2 = process->regs[process->params.p3 - 1];
	else if (pa[2] == DIR)
		p2 = process->params.p3;
	if (core->visu)
		core->graph->tmp_player = process->player;
	write_val(core, get_pc(process->pc + ((p1 + p2) % IDX_MOD)), 4,
	process->regs[process->params.p1 - 1]);
	ft_verbose(core, process, p1, p2);
	return (ok);
}
