#include "corewar.h"

int				ft_lldi(t_core *core, t_process *process)
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
			process->regs[params.p3 - 1] = core->arena + get_pc(process->regs[params.p1 - 1] + process->regs[params.p2 - 1]);
		if (p2 == DIR)
			process->regs[params.p3 - 1] = core->arena + get_pc(process->regs[params.p1 - 1] + params.p2);
	}
	if (p1 == DIR)
	{
		if (p2 == REG)
			process->regs[params.p3 - 1] = core->arena + get_pc(params.p1 + process->regs[params.p2 - 1]);
		if (p2 == DIR)
			process->regs[params.p3 - 1] = core->arena + get_pc(params.p1 + params.p2);
	}
	if (p1 == IND)
	{
		if (p2 == REG)
			process->regs[params.p3 - 1] = core->arena + get_pc(core->arena[process->pc + params.p1] + process->regs[params.p2 - 1]);
		if (p2 == DIR)
			process->regs[params.p3 - 1] = core->arena + get_pc(core->arena[process->pc + params.p1] + params.p2);
	}
}

int			ft_lfork(t_core *core, t_process *process)
{
	t_params	params;
	t_process	*new_process;

	params = process->params;
	if (!(new_process = ft_memalloc(sizeof(t_process))))
		return (-1);
	ft_memcpy(new_process, process, sizeof(t_process));
	new_process->pc = new_process->pc + params.p1;
	push_process(core, new_process);
	return (0);
}