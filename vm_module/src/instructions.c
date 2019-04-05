#include "corewar.h"

int 		ft_live(t_core *core, t_process *process)
{
	int			player;
	t_params	params;

	params = process->params;
	ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	process->is_alive = true;
	core->last_live_done_by = params.p1;
	core->nbr_live++;
	player = params.p1;
	ft_printf("Live done by %d or by %d tot nb_live %d\n ", player, process->regs[0], core->nbr_live);
	return (player);
}

int			ft_load(t_core *core, t_process *process)
{
	t_params params;
	unsigned char bytecode;
	int p1;
	int r;

	ft_printf("ft_load IN by %d\n", process->regs[0]);
	params = process->params;
	ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	bytecode = params.bytecode;
	p1 = ft_type_param(bytecode, 1);
	r = params.p2;
	if (p1 == 3)
		process->regs[r - 1] = params.p1;
	else if (p1 == 2)
		process->regs[r - 1] = core->arena[get_pc(process->pc + r % IDX_MOD)];
	process->carry = 1;
	ft_printf("ft_load OUT by %d\n", process->regs[0]);
	return (0);
}

int			ft_store(t_core *core, t_process *process)
{
	t_params params;
	unsigned char bytecode;
	int p2;
	int r;

	ft_printf("ft_store IN by %d\n", process->regs[0]);
	params = process->params;
	ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	bytecode = params.bytecode;
	p2 = ft_type_param(bytecode, 2);
	r = params.p1;
	if (p2 == REG)
		process->regs[params.p2 - 1] = (int)process->regs[params.p1 - 1];
	else if (p2 == IND)
		core->arena[get_pc(process->pc + params.p1 % IDX_MOD)] = process->regs[params.p1 - 1];
	ft_printf("ft_store OUT\n");
	return (0);
}

int			ft_add(t_core *core, t_process *process)
{
	t_params params;

	ft_printf("ft_add IN by %d\n", process->regs[0]);
	(void)core;
	params = process->params;
	ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	process->regs[params.p3 - 1] = process->regs[params.p2 - 1] + process->regs[params.p1 - 1];
	ft_printf("ft_add OUT by %d\n", process->regs[0]);
	return(0);
}
