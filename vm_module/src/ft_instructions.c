#include "corewar.h"

int			ft_instructions(t_core *core, t_process *process)
{
	int op;

	//ft_printf("ft_instructions IN %d\n", process->instruction);
	if (process->remaining_cycles != 0)
		return (0);
	op = process->instruction;
	g_op_inst_tab[op](core, process);
	process->pc = get_pc(process->pc += process->opsize);
	read_instruction(core, process);
	//ft_printf("ft_instructions OUT\n");
	return (0);
}
