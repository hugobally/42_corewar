#include "corewar.h"

t_errors				ft_lldi(t_core *core, t_process *process)
{
	t_params 	params;
	int 		p1;
	int 		p2;
	int			p3;
	int 		ret;

	//ft_printf("lldi IN by %d\n", process->regs[0]);
	params = process->params;
	//ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	if ((ret = ft_reg(process, &p1, &p2, &p3)) != ok)
		return (ok);
	if (p1 == REG)
	{
		if (p2 == REG)
			process->regs[params.p3 - 1] = read_val(core, get_pc(process->regs[params.p1 - 1] + process->regs[params.p2 - 1]), 4);
		if (p2 == DIR)
			process->regs[params.p3 - 1] = read_val(core, get_pc(process->regs[params.p1 - 1] + params.p2), 4);
	}
	if (p1 == DIR)
	{
		if (p2 == REG)
			process->regs[params.p3 - 1] = read_val(core, get_pc(params.p1 + process->regs[params.p2 - 1]), 4);
		if (p2 == DIR)
			process->regs[params.p3 - 1] = read_val(core, get_pc(params.p1 + params.p2), 4);
	}
	if (p1 == IND)
	{
		if (p2 == REG)
			process->regs[params.p3 - 1] = read_val(core, get_pc(read_val(core, get_pc(process->pc + params.p1), 4) + process->regs[params.p2 - 1]), 4);
		if (p2 == DIR)
			process->regs[params.p3 - 1] = read_val(core, get_pc(read_val(core, get_pc(process->pc + params.p1), 4) + params.p2), 4);
	}
	ft_carry(process, process->regs[params.p3 - 1]);
	//ft_printf("lldi OUT by %d\n", process->regs[0]);
	return (ok);
}

t_errors				ft_lfork(t_core *core, t_process *process)
{
	t_params	params;
	t_process	*new_process;

	//ft_printf("lfork IN by %d\n", process->regs[0]);
	(void)core;
	params = process->params;
	//ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	if (!(new_process = ft_memalloc(sizeof(t_process))))
		return (falloc);
	ft_memcpy(new_process, process, sizeof(t_process));
	new_process->pc = get_pc(new_process->pc + params.p1);
	new_process->loading = 0;
	push_process(core, new_process);
	//ft_printf("lfork OUT by %d\n", process->regs[0]);
	return (ok);
}

t_errors				ft_aff(t_core *core, t_process *process)
{
	t_params	params;
	int			p1;
	int			p2;
	int			p3;
	int			ret;

	//ft_printf("aff IN r1 %d, r2 %d, r3 %d \n", process->regs[0], process->regs[1], process->regs[2]);
	(void)core;
	params = process->params;
	//ft_printf("params p1:%d, p2:%d, p3:%d, pc:%d\n", params.p1, params.p2, params.p3, process->pc);
	if ((ret = ft_reg(process, &p1, &p2, &p3)) != ok)
		return (ok);
	//ft_printf("AFF :%d\n", process->regs[params.p1 - 1] % 256);
	//ft_printf("aff OUT by %d\n", process->regs[0]);
	return (ok);
}

t_errors				ft_error(t_core *core, t_process *process)
{
	(void)core;
	(void)process;
	return (ok);
}

t_errors				ft_reg(t_process *p, int *p1, int *p2, int *p3)
{
	*p1 = ft_type_param(p->params.bytecode, 1);
	*p2 = ft_type_param(p->params.bytecode, 2);
	*p3 = ft_type_param(p->params.bytecode, 3);
	if (*p1 == REG)
		if (p->params.p1 <= 0 || p->params.p1 > REG_NUMBER)
			return ((p->opsize = 1));
	if (*p2 == REG)
		if (p->params.p2 <= 0 || p->params.p2 > REG_NUMBER)
			return ((p->opsize = 1));
	if (*p3 == REG)
		if (p->params.p3 <= 0 || p->params.p3 > REG_NUMBER)
			return ((p->opsize = 1));
	return (ok);
}
