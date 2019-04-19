#include "corewar.h"

t_errors				ft_aff(t_core *core, t_process *process)
{
	t_params	params;
	int			p1;
	int			p2;
	int			p3;
	int			ret;

	(void)core;
	params = process->params;
	if ((ret = ft_reg(process, &p1, &p2, &p3)) != ok)
		return (ok);
	if (core->aff)
		ft_printf("Aff: %c\n", process->regs[params.p1 - 1] % 256);
	return (ok);
}
