#include "corewar.h"

int			ft_instructions(t_core *core, t_process *process)
{
	int op;

	if (process->remaining_cycles != 0)
		return (0);
	op = process->instruction;
	g_op_inst_tab[op](core, process);
	process->instruction = 0;
	process->pc = get_pc(process->pc += process->instruction_size);
	if (process->pc > 0
		&& process->pc < 5
		)
		ft_printf("pc : %d\n", process->pc);
	read_instructions(core, process);
	return (0);
}
