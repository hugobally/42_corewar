#include "corewar.h"

int			ft_instructions(t_core *core, t_process *process)
{
	int op;

	if (process->remaining_cycles != 0)
		return(0);
	op = process->instruction;
	if (op == live)
		ft_live(core, process);
	if (op == load)
		ft_load(core, process);
	if (op == store)
		ft_store(core, process);
	if (op == add)
		ft_add(core, process);
	if (op == sub)
		ft_sub(core, process);
	if (op == and)
		ft_and(core, process);
	if (op == or)
		ft_or(core, process);
}