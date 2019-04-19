#include "corewar.h"

t_errors				ft_lfork(t_core *core, t_process *process)
{
	t_params	params;
	t_process	*new_process;

	(void)core;
	params = process->params;
	if (!(new_process = ft_memalloc(sizeof(t_process))))
		return (falloc);
	ft_memcpy(new_process, process, sizeof(t_process));
	new_process->pc = get_pc(new_process->pc + params.p1);
	new_process->loading = 0;
	push_process(core, new_process);
	if (core->verbose & 4)
		ft_printf("P%5d | lfork %d (%d)\n", -process->regs[0], process->params.p1, process->params.p1);
	return (ok);
}
