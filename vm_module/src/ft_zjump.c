#include "corewar.h"
#include "graph.h"

t_errors		ft_zjmp(t_core *core, t_process *process)
{
	t_params	params;

	if (core->verbose & 4)
		ft_printf("P%5d | zjmp %d %s\n", process->pro_name,
		process->params.p1, process->carry ? "OK" : "FAILED");
	params = process->params;
	(void)core;
	if (process->carry == true)
	{
		if (core->visu)
			move_proccess_on_arena(process->pc,
			process->pc + process->params.p1, core->graph);
		process->pc = get_pc(process->pc + process->params.p1 % IDX_MOD);
	}
	return (ok);
}
