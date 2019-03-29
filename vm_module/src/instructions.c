#include "corewar.h"

int 		ft_live(t_core *core, t_process *process)
{
	int			player;
	t_params	params;

	params = process->params;
	process->is_alive[0] = 1;
	process->is_alive[1] = params.p1;
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
		process->regs[r - 1][0] = params.p1;
	else if (p1 == 2)
		process->regs[r - 1][0] = *(process->address + process->pc + r);
	process->carry = 1;
	return (0);
}

int			ft_instructions(t_core *core, t_process *process)
{
	int op;

	if (process->remaining_cycles != 0)
		return(0);
	process->remaining_cycles = -1;
	op = process->instruction;
	if (op = live)
		return (ft_live(core, process));
	if (op = load)
		return(ft_load(core, process));
}