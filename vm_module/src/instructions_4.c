#include "corewar.h"

t_errors				ft_lldi(t_core *core, t_process *process)
{
	t_params params;
	int p1;
	int p2;

	ft_printf("lldi IN by %d\n", process->regs[0]);
	params = process->params;
	ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	p1 = ft_type_param(params.bytecode, 1);
	p2 = ft_type_param(params.bytecode, 2);
	if (p1 == REG)
	{
		if (p2 == REG)
			process->regs[params.p3 - 1] = *((int32_t*)&(core->arena[get_pc(process->regs[params.p1 - 1] + process->regs[params.p2 - 1])]));
		if (p2 == DIR)
			process->regs[params.p3 - 1] = *((int32_t*)&(core->arena[get_pc(process->regs[params.p1 - 1] + params.p2)]));
	}
	if (p1 == DIR)
	{
		if (p2 == REG)
			process->regs[params.p3 - 1] = *((int32_t*)&(core->arena[get_pc(params.p1 + process->regs[params.p2 - 1])]));
		if (p2 == DIR)
			process->regs[params.p3 - 1] = *((int32_t*)&(core->arena[get_pc(params.p1 + params.p2)]));
	}
	if (p1 == IND)
	{
		if (p2 == REG)
			process->regs[params.p3 - 1] = *((int32_t*)&(core->arena[get_pc(core->arena[process->pc + params.p1] + process->regs[params.p2 - 1])]));
		if (p2 == DIR)
			process->regs[params.p3 - 1] = *((int32_t*)&(core->arena[get_pc(core->arena[process->pc + params.p1] + params.p2)]));
	}
	ft_carry(process, process->regs[params.p3 - 1]);
	ft_printf("lldi OUT by %d\n", process->regs[0]);
	return (ok);
}

t_errors				ft_lfork(t_core *core, t_process *process)
{
	t_params	params;
	t_process	*new_process;

	ft_printf("lfork IN by %d\n", process->regs[0]);
	(void)core;
	params = process->params;
	ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	if (!(new_process = ft_memalloc(sizeof(t_process))))
		return (falloc);
	ft_memcpy(new_process, process, sizeof(t_process));
	new_process->pc = new_process->pc + params.p1;
	push_process(core, new_process);
	ft_printf("lfork OUT by %d\n", process->regs[0]);
	return (ok);
}

t_errors				ft_aff(t_core *core, t_process *process)
{
	t_params params;

	ft_printf("aff IN by %d\n", process->regs[0]);
	(void)core;
	params = process->params;
	ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	ft_putchar((char)process->regs[params.p1 - 1] % 256);
	ft_printf("aff OUT by %d\n", process->regs[0]);
	return (ok);
}

t_errors				ft_error(t_core *core, t_process *process)
{
	(void)core;
	(void)process;
	return (ok);
}