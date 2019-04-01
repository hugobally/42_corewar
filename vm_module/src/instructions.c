#include "corewar.h"

int 		ft_live(t_core *core, t_process *process)
{
	int			player;
	t_params	params;

	params = process->params;
	process->is_alive = 1;
	core->last_live_done_by = params.p1;
	core->nbr_live++;
	player = params.p1;
	return (player);
}

int			ft_load(t_core *core, t_process *process)
{
	t_params params;
	unsigned char bytecode;
	int p1;
	int r;

	params = process->params;
	bytecode = params.bytecode;
	p1 = ft_type_param(bytecode, 1);
	r = params.p2;
	if (p1 == 3)
		process->regs[r - 1] = params.p1;
	else if (p1 == 2)
		process->regs[r - 1] = core->arena[get_pc(process->pc + r % IDX_MOD)];
	process->carry = 1;
	return (0);
}

int			ft_store(t_core *core, t_process *process)
{
	t_params params;
	unsigned char bytecode;
	int p2;
	int r;

	params = process->params;
	bytecode = params.bytecode;
	p2 = ft_type_param(bytecode, 2);
	r = params.p1;
	if (p2 == REG)
		process->regs[params.p2 - 1] = (int)process->regs[params.p1 - 1];
	else if (p2 == IND)
		core->arena[get_pc(process->pc + params.p1 % IDX_MOD)] = process->regs[params.p1 - 1];
	return (0);
}

int			ft_add(t_core *core, t_process *process)
{
	t_params params;

	params = process->params;
	process->regs[params.p3 - 1] = process->regs[params.p2 - 1] + process->regs[params.p1 - 1];
	return(0);
}