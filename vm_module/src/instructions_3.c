#include "corewar.h"

t_errors		ft_zjmp(t_core *core, t_process *process)
{
	t_params	params;

	ft_printf("zjump IN by %d\n", process->regs[0]);
	params = process->params;
	ft_printf("params p1:%d, p2:%d, p3:%d, pc:%d\n", params.p1, params.p2, params.p3, process->pc);
	(void)core;
	if (process->carry == true)
		process->pc = process->pc + process->params.p1;
	ft_printf("zjump OUT by %d, process->pc %d\n", process->regs[0], process->pc);
	return (ok);
}

t_errors		ft_ldi(t_core *core, t_process *process)
{
	t_params 	params;
	int 		p1;
	int			p2;
	int			p3;
	int			ret;

	ft_printf("ldi IN by %d\n", process->regs[0]);
	params = process->params;
	ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	if ((ret = ft_reg(params, &p1, &p2, &p3)) != ok)
		return (ret);
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
	ft_printf("ldi OUT by %d\n", process->regs[0]);
	return (ok);
}

t_errors			ft_sti(t_core *core, t_process *process)
{
	t_params	params;
	int			p1;
	int			p2;
	int			p3;
	int 		ret;

	ft_printf("ft_sti IN by %d\n", process->regs[0]);
	params = process->params;
	ft_printf("params p1:%d, p2:%d, p3:%d, bytecode:%x, pc:%d\n", params.p1, params.p2, params.p3, params.bytecode, process->pc);
	ft_printf("registre de p1 %d\n", process->regs[params.p1 - 1]);
	if ((ret = ft_reg(params, &p1, &p2, &p3)) != ok)
		return (ret);
	if (p2 == REG)
	{
		if (p3 == REG)
		{
			//*((int32_t*)&(core->arena[get_pc((process->regs[params.p2 - 1] + process->regs[params.p3 - 1]) % IDX_MOD)])) = process->regs[params.p1 - 1];
			write_val(core, get_pc(process->pc + (process->regs[params.p2 - 1] + process->regs[params.p3 - 1]) % IDX_MOD), 4, process->regs[params.p1 - 1]);
		}
		if (p3 == DIR)
		{	//*((int32_t*)&(core->arena[get_pc((process->regs[params.p2 - 1] + params.p3) % IDX_MOD)])) = process->regs[params.p1 - 1];
			write_val(core, get_pc(process->pc + (process->regs[params.p2 - 1] + params.p3) % IDX_MOD), 4, process->regs[params.p1 - 1]);
		}
	}
	if (p2 == DIR)
	{
		if (p3 == REG)
		{
			//*((int32_t*)&(core->arena[get_pc((params.p2 + process->regs[params.p3 - 1]) % IDX_MOD)])) = process->regs[params.p1 - 1];
			write_val(core, get_pc(process->pc + (params.p2 + process->regs[params.p3 - 1]) % IDX_MOD), 4, process->regs[params.p1 - 1]);
		}
		if (p3 == DIR)
		{
			//*((int32_t*)&(core->arena[get_pc((params.p2 + params.p3) % IDX_MOD)])) = process->regs[params.p1 - 1];
			write_val(core, get_pc(process->pc + (params.p2 + params.p3) % IDX_MOD), 4, process->regs[params.p1 - 1]);
			ft_printf("STOCK live arg %d\n", read_val(core, get_pc(process->pc + (params.p2 + params.p3) % IDX_MOD), 4));
		}
	}
	if (p2 == IND)
	{
		if (p3 == REG)
		{
			//*((int32_t*)&(core->arena[get_pc((core->arena[get_pc(process->pc + params.p2 % IDX_MOD)] + process->regs[params.p3 - 1]) % IDX_MOD)])) = process->regs[params.p1 - 1];
			write_val(core, get_pc(process->pc + (read_val(core, get_pc(process->pc + params.p2 % IDX_MOD), 4) + process->regs[params.p3 - 1]) % IDX_MOD), 4, process->regs[params.p1 - 1]);
		}
		if (p3 == DIR)
		{
			//*((int32_t*)&(core->arena[get_pc((core->arena[get_pc(process->pc + params.p2 % IDX_MOD)] + params.p3) % IDX_MOD)])) = process->regs[params.p1 - 1];
			write_val(core, get_pc(process->pc + (read_val(core, get_pc(process->pc + params.p2 % IDX_MOD), 4) + params.p3) % IDX_MOD), 4, process->regs[params.p1 - 1]);
		}
	}
	//hexdump(core);
	//getchar();
	ft_printf("ft_sti OUT by %d\n", process->regs[0]);
	return (ok);
}

t_errors			ft_fork(t_core *core, t_process *process)
{
	t_params	params;
	t_process	*new_process;

	ft_printf("fork IN by %d\n", process->regs[0]);
	params = process->params;
	ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	if (!(new_process = ft_memalloc(sizeof(t_process))))
		return (falloc);
	ft_memcpy(new_process, process, sizeof(t_process));
	new_process->pc = get_pc(new_process->pc + (params.p1 % IDX_MOD));
	push_process(core, new_process);
	ft_printf("fork OUT by %d\n", process->regs[0]);
	return (ok);
}

t_errors			ft_lld(t_core *core, t_process *process)
{
	t_params	params;
	int			p1;
	int			p2;
	int			p3;
	int			ret;


	ft_printf("lldi IN by %d\n", process->regs[0]);
	params = process->params;
	ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	p1 = ft_type_param(params.bytecode, 1);
	if ((ret = ft_reg(params, &p1, &p2, &p3)) != ok)
		return (ret);
	if (p1 == DIR)
		process->regs[params.p2 - 1] = params.p1;
	if (p1 == IND)
		//process->regs[params.p2 - 1] = *((int32_t*)&(core->arena[get_pc(process->pc + params.p1)]));
		process->regs[params.p2 - 1] = read_val(core, get_pc(process->pc + params.p1), 4);
	ft_carry(process, process->regs[params.p2 - 1]);
	ft_printf("lldi OUT by %d\n", process->regs[0]);
	return (ok);
}