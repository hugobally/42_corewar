#include "corewar.h"

int			ft_zjmp(t_core *core, t_process *process)
{
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
			process->regs[params.p3 - 1] = core->arena + ((process->regs[params.p1 - 1] + process->regs[params.p2 - 1]) % IDX_MOD);
		if (p2 == DIR)
			process->regs[params.p3 - 1] = core->arena + ((process->regs[params.p1 - 1] + params.p2) % IDX_MOD);
	}
	if (p1 == DIR)
	{
		if (p2 == REG)
			process->regs[params.p3 - 1] = core->arena + ((params.p1 + process->regs[params.p2 - 1]) % IDX_MOD);
		if (p2 == DIR)
			process->regs[params.p3 - 1] = core->arena + ((params.p1 + params.p2) % IDX_MOD);
	}
	if (p1 == IND)
	{
		if (p2 == REG)
			process->regs[params.p3 - 1] = core->arena + ((core->arena[process->pc + params.p1 % IDX_MOD] + process->regs[params.p2 - 1]) % IDX_MOD);
		if (p2 == DIR)
			process->regs[params.p3 - 1] = core->arena + ((core->arena[process->pc + params.p1 % IDX_MOD] + params.p2) % IDX_MOD);
	}
}

int			ft_sti(t_core *core, t_process *process)
{
	t_params	params;
	int			p2;
	int			p3;

	params = process->params;
	p2 = ft_type_param(params.bytecode, 2);
	p3 = ft_type_param(params.bytecode, 3);
	if (p2 == REG)
	{
		if (p3 == REG)
			core->arena[process->regs[params.p2] + process->regs[params.p3]] = process->regs[params.p1];
		if (p3 == DIR)
			core->arena[process->regs[params.p2] + params.p3] = process->regs[params.p1];
	}

}