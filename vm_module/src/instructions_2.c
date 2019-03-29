#include "corewar.h"

int			ft_sub(t_core *core, t_process *process)
{
	t_params params;

	params = process->params;
	process->regs[params.p3 - 1][0] = process->regs[params.p1 - 1] - process->regs[params.p2 - 1];
	return(0);
}

int			ft_and(t_core *core, t_process *process)
{
	t_params	params;
	int 		p1;
	int			p2;
	int			p3;

	params = process->params;
	p1 = ft_type_param(params.bytecode, 1);
	p2 = ft_type_param(params.bytecode, 2);
	p3 = ft_type_param(params.bytecode, 3);
	
}