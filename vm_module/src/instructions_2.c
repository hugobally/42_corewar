#include "corewar.h"

t_errors	ft_sub(t_core *core, t_process *process)
{
	t_params	params;
	int			p1;
	int			p2;
	int			p3;
	int			ret;

	//ft_printf("sub IN by %d\n", process->regs[0]);
	(void)core;
	params = process->params;
	//ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	if ((ret = ft_reg(process, &p1, &p2, &p3)) != ok)
		return (ok);
	process->regs[params.p3 - 1] = process->regs[params.p1 - 1] - process->regs[params.p2 - 1];
	ft_carry(process, process->regs[params.p3 - 1]);
	//ft_printf("sub OUT by %d\n", process->regs[0]);
	return(ok);
}

t_errors	ft_and(t_core *core, t_process *process)
{
	t_params	params;
	int 		p1;
	int			p2;
	int			p3;
	int			ret;

	//ft_printf("and IN by %d\n", process->regs[0]);
	params = process->params;
	//ft_printf("params p1:%d, p2:%d, p3:%d, bytecode: %x, pc:%d\n", params.p1, params.p2, params.p3, params.bytecode, process->pc);
	if ((ret = ft_reg(process, &p1, &p2, &p3)) != ok)
		return (ok);
	if (p1 == REG)
	{
		if (p2 == REG)
			process->regs[params.p3 - 1] = process->regs[params.p1 - 1] & process->regs[params.p2 - 1];
		if (p2 == DIR)
			process->regs[params.p3 - 1] = process->regs[params.p1 - 1] & params.p2;
		if (p2 == IND)
			process->regs[params.p3 - 1] = process->regs[params.p1 - 1] & core->arena[get_pc(process->pc + params.p2 % IDX_MOD)];
	}
	if (p1 == DIR)
	{
		if (p2 == REG)
			process->regs[params.p3 - 1] = params.p1 & process->regs[params.p2 - 1];
		if (p2 == DIR)
			process->regs[params.p3 - 1] = params.p1 & params.p2;
		if (p2 == IND)
			process->regs[params.p3 - 1] = params.p1 & core->arena[get_pc(process->pc + params.p2 % IDX_MOD)];
	}
	if (p1 == IND)
	{
		if (p2 == REG)
			process->regs[params.p3 - 1] = core->arena[get_pc(process->pc + params.p1 % IDX_MOD)] & process->regs[params.p2 - 1];
		if (p2 == DIR)
			process->regs[params.p3 - 1] = core->arena[get_pc(process->pc + params.p1 % IDX_MOD)] & params.p2;
		if (p2 == IND)
			process->regs[params.p3 - 1] = core->arena[get_pc(process->pc + params.p1 % IDX_MOD)] & core->arena[get_pc(process->pc + params.p2 % IDX_MOD)];
	}
	ft_carry(process, process->regs[params.p3 - 1]);
	//ft_printf("and OUT by %d\n", process->regs[0]);
	return (ok);
}

t_errors	ft_or(t_core *core, t_process *process)
{
	t_params	params;
	int 		p1;
	int			p2;
	int			p3;
	int			ret;

	//ft_printf("or IN by %d\n", process->regs[0]);
	params = process->params;
	//ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	if ((ret = ft_reg(process, &p1, &p2, &p3)) != ok)
		return (ok);
	if (p3 == REG)
	{
		if (p1 == REG)
		{
			if (p2 == REG)
				process->regs[params.p3 - 1] = process->regs[params.p1 - 1] | process->regs[params.p2 - 1];
			if (p2 == DIR)
				process->regs[params.p3 - 1] = process->regs[params.p1 - 1] | params.p2;
			if (p2 == IND)
				process->regs[params.p3 - 1] = process->regs[params.p1 - 1] | core->arena[get_pc(process->pc + params.p2 % IDX_MOD)];
		}
		if (p1 == DIR)
		{
			if (p2 == REG)
				process->regs[params.p3 - 1] = params.p1 | process->regs[params.p2 - 1];
			if (p2 == DIR)
				process->regs[params.p3 - 1] = params.p1 | params.p2;
			if (p2 == IND)
				process->regs[params.p3 - 1] = params.p1 | core->arena[get_pc(process->pc + params.p2 % IDX_MOD)];
		}
		if (p1 == IND)
		{
			if (p2 == REG)
				process->regs[params.p3 - 1] = core->arena[get_pc(process->pc + params.p1 % IDX_MOD)] | process->regs[params.p2 - 1];
			if (p2 == DIR)
				process->regs[params.p3 - 1] = core->arena[get_pc(process->pc + params.p1 % IDX_MOD)] | params.p2;
			if (p2 == IND)
				process->regs[params.p3 - 1] = core->arena[get_pc(process->pc + params.p1 % IDX_MOD)] | core->arena[get_pc(process->pc + params.p2 % IDX_MOD)];
		}
	}
	ft_carry(process, process->regs[params.p3 - 1]);
	//ft_printf("or OUT by %d\n", process->regs[0]);
	return(ok);
}

t_errors	ft_xor(t_core *core, t_process *process)
{
	t_params	params;
	int 		p1;
	int			p2;
	int			p3;
	int			ret;

	//ft_printf("xor IN by %d\n", process->regs[0]);
	params = process->params;
	//ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	if ((ret = ft_reg(process, &p1, &p2, &p3)) != ok)
		return (ok);
	if (p3 == REG)
	{
		if (p1 == REG)
		{
			if (p2 == REG)
				process->regs[params.p3 - 1] = process->regs[params.p1 - 1] ^ process->regs[params.p2 - 1];
			if (p2 == DIR)
				process->regs[params.p3 - 1] = process->regs[params.p1 - 1] ^ params.p2;
			if (p2 == IND)
				process->regs[params.p3 - 1] = process->regs[params.p1 - 1] ^ core->arena[get_pc(process->pc + params.p2 % IDX_MOD)];
		}
		if (p1 == DIR)
		{
			if (p2 == REG)
				process->regs[params.p3 - 1] = params.p1 ^ process->regs[params.p2 - 1];
			if (p2 == DIR)
				process->regs[params.p3 - 1] = params.p1 ^ params.p2;
			if (p2 == IND)
				process->regs[params.p3 - 1] = params.p1 ^ core->arena[get_pc(process->pc + params.p2 % IDX_MOD)];
		}
		if (p1 == IND)
		{
			if (p2 == REG)
				process->regs[params.p3 - 1] = core->arena[get_pc(process->pc + params.p1 % IDX_MOD)] ^ process->regs[params.p2 - 1];
			if (p2 == DIR)
				process->regs[params.p3 - 1] = core->arena[get_pc(process->pc + params.p1 % IDX_MOD)] ^ params.p2;
			if (p2 == IND)
				process->regs[params.p3 - 1] = core->arena[get_pc(process->pc + params.p1 % IDX_MOD)] ^ core->arena[get_pc(process->pc + params.p2 % IDX_MOD)];
		}
	}
	ft_carry(process, process->regs[params.p3 - 1]);
	//ft_printf("xor OUT by %d\n", process->regs[0]);
	return(ok);
}
