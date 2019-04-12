#include "corewar.h"

t_errors 		ft_live(t_core *core, t_process *process)
{
	int			player;
	t_params	params;

	params = process->params;
	//ft_printf("Live in\nparams p1:%d, p2:%d, p3:%d, pc:%d\n", params.p1, params.p2, params.p3, process->pc);
	process->is_alive = true;
	core->last_live_done_by = params.p1;
	core->nbr_live++;
	core->winner = 1;
	player = params.p1;
	//ft_printf("Live for %d BY %d tot nb_live %d\n", player, process->player, core->nbr_live);
	return (ok);
}

t_errors		ft_load(t_core *core, t_process *process)
{
	t_params 		params;
	int 			p1;
	int				p2;
	int				p3;
	int				ret;

	//ft_printf("ft_load IN by %d\n", process->regs[0]);
	params = process->params;
	//ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	if ((ret = ft_reg(process, &p1, &p2, &p3)) != ok)
		return (ok);
	if (p1 == DIR)
		process->regs[params.p2 - 1] = params.p1;
	else if (p1 == IND)
		process->regs[params.p2 - 1] = read_val(core, get_pc(process->pc + params.p1 % IDX_MOD), 4);
	ft_carry(process, process->regs[params.p2 - 1]);
	//ft_printf("ft_load OUT by %d\n", process->regs[0]);
	return (ok);
}

t_errors		ft_store(t_core *core, t_process *process)
{
	t_params 		params;
	int				p1;
	int 			p2;
	int				p3;
	int				ret;

	//ft_printf("ft_store IN by %d\n", process->regs[0]);
	params = process->params;
	//ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	if ((ret = ft_reg(process, &p1, &p2, &p3)) != ok)
		return (ok);
	if (p2 == REG)
		process->regs[params.p2 - 1] = (int)process->regs[params.p1 - 1];
	else if (p2 == IND)
		write_val(core, get_pc(process->pc + params.p2 % IDX_MOD), 4, process->regs[params.p1 - 1]);
	//ft_printf("ft_store OUT\n");
	return (ok);
}

t_errors		ft_add(t_core *core, t_process *process)
{
	t_params	params;
	int			p1;
	int			p2;
	int			p3;
	int			ret;

	//ft_printf("ft_add IN by %d\n", process->regs[0]);
	(void)core;
	params = process->params;
	//ft_printf("params p1:%d, p2:%d, p3:%d\n", params.p1, params.p2, params.p3);
	if ((ret = ft_reg(process, &p1, &p2, &p3)) != ok)
		return (ok);
	process->regs[params.p3 - 1] = process->regs[params.p2 - 1] + process->regs[params.p1 - 1];
	ft_carry(process, process->regs[params.p3 - 1]);
	//ft_printf("ft_add OUT by %d\n", process->regs[0]);
	return(ok);
}
