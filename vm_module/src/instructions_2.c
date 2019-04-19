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

	//ft_printf("ft_and IN, carry is %d reg[%d] is %d\n", process->carry, process->params.p2, process->regs[process->params.p2 - 1]);
	//ft_printf("params.p1 %d, params.p2 %d, params.p3 %d\n", process->params.p1, process->params.p2, process->params.p3);
	ft_bzero(pa, sizeof(int) * 3);
	if (ft_reg(process, &pa[0], &pa[1], &pa[2]) != ok)
		return (ok);
	//ft_printf("pa[0] %d, pa[1] %d, pa[2] %d\n", pa[0], pa[1], pa[2]);
	p1 = ft_get_params(core, process, process->params.p1, pa[0]);
	p2 = ft_get_params(core, process, process->params.p2, pa[1]);
	//ft_printf("p1 %d, p2 %d\n", p1, p2);
	process->regs[process->params.p3 - 1] = p1 & p2;
	ft_carry(process, process->regs[process->params.p3 - 1]);
	//ft_printf("p3 %d\n", process->regs[process->params.p3 - 1]);
	//ft_printf("ft_and OUT, carry is %d\n", process->carry);
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
