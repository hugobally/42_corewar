#include "corewar.h"
#include "graph.h"

t_errors		ft_zjmp(t_core *core, t_process *process)
{
	t_params	params;

	//ft_printf("zjump IN by %d\n", process->regs[0]);
	params = process->params;
	//ft_printf("params p1:%d, p2:%d, p3:%d, pc:%d\n", params.p1, params.p2, params.p3, process->pc);
	(void)core;
	if (process->carry == true)
	{
		if (core->visu)
			move_proccess_on_arena(process->pc, process->pc + process->params.p1, core->graph);
		process->pc = process->pc + process->params.p1;
	}
	//ft_printf("zjump OUT by %d, process->pc %d\n", process->regs[0], process->pc);
	return (ok);
}

t_errors		ft_ldi(t_core *core, t_process *process)
{
	t_params	params;
	int			p1;
	int			p2;
	int			pa[3];

	p1 = 0;
	p2 = 0;
	ft_bzero(pa, sizeof(int) * 3);
	params = process->params;
	if (ft_reg(process, &pa[0], &pa[1], &pa[2]) != ok)
		return (ok);
	if (pa[0] == REG)
		p1 = read_val(core, get_pc(process->pc + (process->regs[params.p1 - 1] % IDX_MOD)), 4);
	else if (pa[0] == DIR)
		p1 = read_val(core, get_pc(process->pc + (params.p1 % IDX_MOD)), 4);
	else if (pa[0] == IND)
		p1 = read_val(core, get_pc(process->pc + (read_val(core,
			get_pc(process->pc + (params.p1 % IDX_MOD)), 4)) % IDX_MOD), 4);
	if (pa[1] == REG)
		p2 = process->regs[params.p2 - 1];
	else if (pa[1] == DIR)
		p2 = params.p2;
	process->regs[params.p3 - 1] = read_val(core, get_pc(process->pc + ((p1 + p2) % IDX_MOD)), 4);
	return (ok);

	// t_params 	params;
	// int 		p1;
	// int			p2;
	// int			p3;
	// int			ret;

	// //ft_printf("ldi IN by %d\n", process->regs[0]);
	// params = process->params;
	// //ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	// if ((ret = ft_reg(process, &p1, &p2, &p3)) != ok)
	// 	return (ok);
	// if (p1 == REG)
	// {
	// 	if (p2 == REG)
	// 		process->regs[params.p3 - 1] = read_val(core, get_pc(process->pc + (process->regs[params.p1 - 1] + process->regs[params.p2 - 1]) % IDX_MOD), 4);
	// 	if (p2 == DIR)
	// 		process->regs[params.p3 - 1] = read_val(core, get_pc(process->pc + (process->regs[params.p1 - 1] + params.p2) % IDX_MOD), 4);
	// }
	// if (p1 == DIR)
	// {
	// 	if (p2 == REG)
	// 		process->regs[params.p3 - 1] = read_val(core, get_pc(process->pc + (params.p1 + process->regs[params.p2 - 1]) % IDX_MOD), 4);
	// 	if (p2 == DIR)
	// 		process->regs[params.p3 - 1] = read_val(core, get_pc(process->pc + (params.p1 + params.p2) % IDX_MOD), 4);
	// }
	// if (p1 == IND)
	// {
	// 	if (p2 == REG)
	// 		process->regs[params.p3 - 1] = read_val(core, get_pc(process->pc + (read_val(core, get_pc(process->pc + params.p1 % IDX_MOD), 4) + process->regs[params.p2 - 1]) % IDX_MOD), 4);
	// 	if (p2 == DIR)
	// 		process->regs[params.p3 - 1] = read_val(core, get_pc(process->pc + (read_val(core, get_pc(process->pc + params.p1 % IDX_MOD), 4) + params.p2) % IDX_MOD), 4);
	// }
	// //ft_printf("ldi OUT by %d\n", process->regs[0]);
	// return (ok);
}

t_errors			ft_sti(t_core *core, t_process *process)
{
	// t_params	params;

	// int			p1;
	// int			p2;
	// int			p3;
	// int			pa[3];

	// p1 = 0;
	// p2 = 0;
	// ft_bzero(pa, sizeof(int) * 3);
	// params = process->params;
	// if (ft_reg(process, &pa[0], &pa[1], &pa[2]) != ok)
	// 	return (ok);
	// if (pa[1] == REG)
	// 	p1 = process->pc + ;
	// else if (pa[1] == DIR)
	// else if (pa[1] == IND)
	// if (pa[2] == REG)
	// else if (pa[2] == DIR)

	// p3 = get_pc(process->pc + (p1 + p2) % IDX_MOD);
	// write_val(core, p3);


	t_params	params;
	int			p1;
	int			p2;
	int			p3;
	int 		ret;

	//ft_printf("ft_sti IN by %d\n", process->regs[0]);
	params = process->params;
	//ft_printf("params p1:%d, p2:%d, p3:%d, bytecode:%x, pc:%d\n", params.p1, params.p2, params.p3, params.bytecode, process->pc);
	//ft_printf("registre de p1 %d\n", process->regs[params.p1 - 1]);
	if ((ret = ft_reg(process, &p1, &p2, &p3)) != ok)
		return (ok);
	if (p2 == REG)
	{
		if (p3 == REG)
			write_val(core, get_pc(process->pc + (process->regs[params.p2 - 1] + process->regs[params.p3 - 1]) % IDX_MOD), 4, process->regs[params.p1 - 1], process->player);
		if (p3 == DIR)
			write_val(core, get_pc(process->pc + (process->regs[params.p2 - 1] + params.p3) % IDX_MOD), 4, process->regs[params.p1 - 1], process->player);
	}
	if (p2 == DIR)
	{
		if (p3 == REG)
			write_val(core, get_pc(process->pc + (params.p2 + process->regs[params.p3 - 1]) % IDX_MOD), 4, process->regs[params.p1 - 1], process->player);
		if (p3 == DIR)
			write_val(core, get_pc(process->pc + (params.p2 + params.p3) % IDX_MOD), 4, process->regs[params.p1 - 1], process->player);
	}
	if (p2 == IND)
	{
		if (p3 == REG)
			write_val(core, get_pc(process->pc + (read_val(core, get_pc(process->pc + params.p2 % IDX_MOD), 4) + process->regs[params.p3 - 1]) % IDX_MOD), 4, process->regs[params.p1 - 1], process->player);
		if (p3 == DIR)
			write_val(core, get_pc(process->pc + (read_val(core, get_pc(process->pc + params.p2 % IDX_MOD), 4) + params.p3) % IDX_MOD), 4, process->regs[params.p1 - 1], process->player);
	}
	//ft_printf("ft_sti OUT by %d\n", process->regs[0]);
	return (ok);
}

t_errors			ft_fork(t_core *core, t_process *process)
{
	t_params	params;
	t_process	*new_process;

	//ft_printf("fork IN by %d, pc at %d\n", process->player, process->pc);
	params = process->params;
	//ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	if (!(new_process = ft_memalloc(sizeof(t_process))))
		return (falloc);
	ft_memcpy(new_process, process, sizeof(t_process));
	new_process->pc = get_pc(new_process->pc + (params.p1 % IDX_MOD));
	new_process->loading = 0;
	push_process(core, new_process);
	//ft_printf("fork OUT by %d\n", process->regs[0]);
	return (ok);
}

t_errors			ft_lld(t_core *core, t_process *process)
{
	t_params	params;
	int			p1;
	int			p2;
	int			p3;
	int			ret;


	//ft_printf("lldi IN by %d\n", process->regs[0]);
	params = process->params;
	//ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	p1 = ft_type_param(params.bytecode, 1);
	if ((ret = ft_reg(process, &p1, &p2, &p3)) != ok)
		return (ok);
	if (p1 == DIR)
		process->regs[params.p2 - 1] = params.p1;
	if (p1 == IND)
		process->regs[params.p2 - 1] = read_val(core, get_pc(process->pc + params.p1), 4);
	ft_carry(process, process->regs[params.p2 - 1]);
	//ft_printf("lldi OUT by %d\n", process->regs[0]);
	return (ok);
}
