#include "corewar.h"

int			ft_instructions(t_core *core, t_process *process)
{
	int op;

	if (process->remaining_cycles != 0)
		return (0);
	op = process->instruction;
	if (process->next)
		ft_printf("op %d\n", op);
	g_op_inst_tab[op](core, process);
	if (process->next)
		ft_printf("TEST avant %d\n", process->pc);
	process->pc = get_pc(process->pc += process->instruction_size);
	if (process->next)
		ft_printf("TEST apres %d\n", process->pc);
	if (process->next)
		ft_printf("Is_alive %d\n", process->is_alive);
	read_instructions(core, process);
	if (process->next)
		ft_printf("TEST post read %d\n", process->pc);
	
	return (0);
}
