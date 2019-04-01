#include "corewar.h"

int			ft_sub(t_core *core, t_process *process)
{
	t_params params;

	params = process->params;
	process->regs[params.p3 - 1][0] = process->regs[params.p1 - 1] - process->regs[params.p2 - 1];
	return(0);
}

int			ft_and(t_core *core, t_process *process)
{
	t_params	params;
	int 		p1;
	int			p2;
	int			p3;

	params = process->params;
	p1 = ft_type_param(params.bytecode, 1);
	p2 = ft_type_param(params.bytecode, 2);
	p3 = ft_type_param(params.bytecode, 3);
	if (p3 == REG)
	{
		if (p1 == REG)
		{
			if (p2 == REG)
				process->regs[params.p3 - 1] = process->regs[params.p1 - 1] & process->regs[params.p2 - 1];
			if (p2 == DIR)
				process->regs[params.p3 - 1] = process->regs[params.p1 - 1] & params.p2;
			if (p2 == IND)
				process->regs[params.p3 - 1] = process->regs[params.p1 - 1] & core->arena[process->pc + params.p2 % IDX_MOD];
		}
		if (p1 == DIR)
		{
			if (p2 == REG)
				process->regs[params.p3 - 1] = params.p1 & process->regs[params.p2 - 1];
			if (p2 == DIR)
				process->regs[params.p3 - 1] = params.p1 & params.p2;
			if (p2 == IND)
				process->regs[params.p3 - 1] = params.p1 & core->arena[process->pc + params.p2 % IDX_MOD];
		}
		if (p1 == IND)
		{
			if (p2 == REG)
				process->regs[params.p3 - 1] = core->arena[process->pc + params.p1 % IDX_MOD] & process->regs[params.p2 - 1];
			if (p2 == DIR)
				process->regs[params.p3 - 1] = core->arena[process->pc + params.p1 % IDX_MOD] & params.p2;
			if (p2 == IND)
				process->regs[params.p3 - 1] = core->arena[process->pc + params.p1 % IDX_MOD] & core->arena[process->pc + params.p2 % IDX_MOD];
		}
	}
	return(0);
}

int			ft_or(t_core *core, t_process *process)
{
	t_params	params;
	int 		p1;
	int			p2;
	int			p3;

	params = process->params;
	p1 = ft_type_param(params.bytecode, 1);
	p2 = ft_type_param(params.bytecode, 2);
	p3 = ft_type_param(params.bytecode, 3);
	if (p3 == REG)
	{
		if (p1 == REG)
		{
			if (p2 == REG)
				process->regs[params.p3 - 1] = process->regs[params.p1 - 1] | process->regs[params.p2 - 1];
			if (p2 == DIR)
				process->regs[params.p3 - 1] = process->regs[params.p1 - 1] | params.p2;
			if (p2 == IND)
				process->regs[params.p3 - 1] = process->regs[params.p1 - 1] | core->arena[process->pc + params.p2 % IDX_MOD];
		}
		if (p1 == DIR)
		{
			if (p2 == REG)
				process->regs[params.p3 - 1] = params.p1 | process->regs[params.p2 - 1];
			if (p2 == DIR)
				process->regs[params.p3 - 1] = params.p1 | params.p2;
			if (p2 == IND)
				process->regs[params.p3 - 1] = params.p1 | core->arena[process->pc + params.p2 % IDX_MOD];
		}
		if (p1 == IND)
		{
			if (p2 == REG)
				process->regs[params.p3 - 1] = core->arena[process->pc + params.p1 % IDX_MOD] | process->regs[params.p2 - 1];
			if (p2 == DIR)
				process->regs[params.p3 - 1] = core->arena[process->pc + params.p1 % IDX_MOD] | params.p2;
			if (p2 == IND)
				process->regs[params.p3 - 1] = core->arena[process->pc + params.p1 % IDX_MOD] | core->arena[process->pc + params.p2 % IDX_MOD];
		}
	}
	return(0);
}

int			ft_xor(t_core *core, t_process *process)
{
	t_params	params;
	int 		p1;
	int			p2;
	int			p3;

	params = process->params;
	p1 = ft_type_param(params.bytecode, 1);
	p2 = ft_type_param(params.bytecode, 2);
	p3 = ft_type_param(params.bytecode, 3);
	if (p3 == REG)
	{
		if (p1 == REG)
		{
			if (p2 == REG)
				process->regs[params.p3 - 1] = process->regs[params.p1 - 1] ^ process->regs[params.p2 - 1];
			if (p2 == DIR)
				process->regs[params.p3 - 1] = process->regs[params.p1 - 1] ^ params.p2;
			if (p2 == IND)
				process->regs[params.p3 - 1] = process->regs[params.p1 - 1] ^ core->arena[process->pc + params.p2 % IDX_MOD];
		}
		if (p1 == DIR)
		{
			if (p2 == REG)
				process->regs[params.p3 - 1] = params.p1 ^ process->regs[params.p2 - 1];
			if (p2 == DIR)
				process->regs[params.p3 - 1] = params.p1 ^ params.p2;
			if (p2 == IND)
				process->regs[params.p3 - 1] = params.p1 ^ core->arena[process->pc + params.p2 % IDX_MOD];
		}
		if (p1 == IND)
		{
			if (p2 == REG)
				process->regs[params.p3 - 1] = core->arena[process->pc + params.p1 % IDX_MOD] ^ process->regs[params.p2 - 1];
			if (p2 == DIR)
				process->regs[params.p3 - 1] = core->arena[process->pc + params.p1 % IDX_MOD] ^ params.p2;
			if (p2 == IND)
				process->regs[params.p3 - 1] = core->arena[process->pc + params.p1 % IDX_MOD] ^ core->arena[process->pc + params.p2 % IDX_MOD];
		}
	}
	return(0);
}