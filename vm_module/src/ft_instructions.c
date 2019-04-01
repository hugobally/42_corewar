#include "corewar.h"

int			ft_instructions(t_core *core, t_process *process)
{
	int op;

	if (process->remaining_cycles != 0)
		return (0);
	op = process->instruction;
	g_op_inst_tab[op](core, process);
	process->instruction = 0;
	process->pc += process->instruction_size;
	read_instructions(core, process);
	return (0);
}