#include "corewar.h"

int			ft_zjmp(t_core *core, t_process *process)
{
	(void)core;
	if (process->carry == true)
		process->pc = process->pc + process->params.p1;
	return (0);
}

int			ft_ldi(t_core *core, t_process *process)
{
	t_params params;
	int p1;
	int p2;

	params = process->params;
	p1 = ft_type_param(params.bytecode, 1);
	p2 = ft_type_param(params.bytecode, 2);
	if (p1 == REG)
	{
		if (p2 == REG)
			process->regs[params.p3 - 1] = core->arena[get_pc((process->regs[params.p1 - 1] + process->regs[params.p2 - 1]) % IDX_MOD)];
		if (p2 == DIR)
			process->regs[params.p3 - 1] = core->arena[get_pc((process->regs[params.p1 - 1] + params.p2) % IDX_MOD)];
	}
	if (p1 == DIR)
	{
		if (p2 == REG)
			process->regs[params.p3 - 1] = core->arena[get_pc((params.p1 + process->regs[params.p2 - 1]) % IDX_MOD)];
		if (p2 == DIR)
			process->regs[params.p3 - 1] = core->arena[get_pc((params.p1 + params.p2) % IDX_MOD)];
	}
	if (p1 == IND)
	{
		if (p2 == REG)
			process->regs[params.p3 - 1] = core->arena[get_pc((core->arena[process->pc + params.p1 % IDX_MOD] + process->regs[params.p2 - 1]) % IDX_MOD)];
		if (p2 == DIR)
			process->regs[params.p3 - 1] = core->arena[get_pc((core->arena[process->pc + params.p1 % IDX_MOD] + params.p2) % IDX_MOD)];
	}
	return (0);
}

int			ft_sti(t_core *core, t_process *process)
{
	t_params	params;
	int			p2;
	int			p3;

	ft_printf("ft_sti IN\n");
	params = process->params;
	p2 = ft_type_param(params.bytecode, 2);
	p3 = ft_type_param(params.bytecode, 3);
	if (p2 == REG)
	{
		if (p3 == REG)
			core->arena[get_pc((process->regs[params.p2] + process->regs[params.p3]) % IDX_MOD)] = process->regs[params.p1];
		if (p3 == DIR)
			core->arena[get_pc((process->regs[params.p2] + params.p3) % IDX_MOD)] = process->regs[params.p1];
	}
	if (p2 == DIR)
	{
		if (p3 == REG)
			core->arena[get_pc((params.p2 + process->regs[params.p3]) % IDX_MOD)] = process->regs[params.p1];
		if (p3 == DIR)
			core->arena[get_pc((params.p2 + params.p3) % IDX_MOD)] = process->regs[params.p1];
	}
	if (p2 == IND)
	{
		if (p3 == REG)
			core->arena[get_pc((core->arena[get_pc(process->pc + params.p2 % IDX_MOD)] + process->regs[params.p3]) % IDX_MOD)] = process->regs[params.p1];
		if (p3 == DIR)
			core->arena[get_pc((core->arena[get_pc(process->pc + params.p2 % IDX_MOD)] + params.p3) % IDX_MOD)] = process->regs[params.p1];
	}
	ft_printf("ft_sti OUT\n");
	return (0);
}

int			ft_fork(t_core *core, t_process *process)
{
	t_params	params;
	t_process	*new_process;

	params = process->params;
	if (!(new_process = ft_memalloc(sizeof(t_process))))
		return (-1);
	ft_memcpy(new_process, process, sizeof(t_process));
	new_process->pc = new_process->pc + (params.p1 % IDX_MOD);
	push_process(core, new_process);
	return (0);
}

int			ft_lld(t_core *core, t_process *process)
{
	t_params	params;
	int			p1;

	params = process->params;
	p1 = ft_type_param(params.bytecode, 1);
	if (p1 == DIR)
		process->regs[params.p2 - 1] = params.p1;
	if (p1 == IND)
		process->regs[params.p2 - 1] = core->arena[get_pc(process->pc + params.p1 % IDX_MOD)];
	return (0);
}