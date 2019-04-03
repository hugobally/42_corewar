#include "corewar.h"

int			ft_instructions(t_core *core, t_process *process)
{
	int op;

	ft_printf("ft_instructions IN %d\n", process->instruction);
	if (process->remaining_cycles != 0)
		return (0);
	op = process->instruction;
	ft_printf("avant fonction op %d\n", op);
	g_op_inst_tab[op](core, process);
	ft_printf("apres fonction\n");
	process->pc = get_pc(process->pc += process->instruction_size);
	read_instructions(core, process);
	ft_printf("ft_instructions OUT\n");
	return (0);
}
