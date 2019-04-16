#include "corewar.h"

t_errors	ft_sub(t_core *core, t_process *process)
{
	t_params	params;
	int			p1;
	int			p2;
	int			p3;

	(void)core;
	params = process->params;
	if (ft_reg(process, &p1, &p2, &p3) != ok)
		return (ok);
	process->regs[params.p3 - 1] = process->regs[params.p1 - 1]
		- process->regs[params.p2 - 1];
	ft_carry(process, process->regs[params.p3 - 1]);
	return (ok);
}

t_errors	ft_and(t_core *core, t_process *process)
{
	int			p1;
	int			p2;
	int			pa[3];

	ft_bzero(pa, sizeof(int) * 3);
	if (ft_reg(process, &pa[0], &pa[1], &pa[2]) != ok)
		return (ok);
	p1 = ft_get_params(core, process, process->params.p1, pa[0]);
	p2 = ft_get_params(core, process, process->params.p2, pa[1]);
	process->regs[process->params.p3 - 1] = p1 & p2;
	ft_carry(process, process->regs[process->params.p3 - 1]);
	return (ok);
}

t_errors	ft_or(t_core *core, t_process *process)
{
	int			p1;
	int			p2;
	int			pa[3];

	ft_bzero(pa, sizeof(int) * 3);
	if (ft_reg(process, &pa[0], &pa[1], &pa[2]) != ok)
		return (ok);
	p1 = ft_get_params(core, process, process->params.p1, pa[0]);
	p2 = ft_get_params(core, process, process->params.p2, pa[1]);
	process->regs[process->params.p3 - 1] = p1 | p2;
	ft_carry(process, process->regs[process->params.p3 - 1]);
	return (ok);
}

t_errors	ft_xor(t_core *core, t_process *process)
{
	int			p1;
	int			p2;
	int			pa[3];

	ft_bzero(pa, sizeof(int) * 3);
	if (ft_reg(process, &pa[0], &pa[1], &pa[2]) != ok)
		return (ok);
	p1 = ft_get_params(core, process, process->params.p1, pa[0]);
	p2 = ft_get_params(core, process, process->params.p2, pa[1]);
	process->regs[process->params.p3 - 1] = p1 ^ p2;
	ft_carry(process, process->regs[process->params.p3 - 1]);
	return (ok);
}
