#include "corewar.h"

t_errors		ft_instructions(t_core *core, t_process *process)
{
	int op;
	t_errors res;

	//ft_printf("ft_instructions IN %d\n", process->instruction);
	if (process->remaining_cycles != 0)
		return (0);
	if ((op = process->instruction) && (op <= 0 || op > 16))
		op = 0;
	if ((res = g_op_inst_tab[op](core, process)) != ok)
		return (res);
	process->pc = get_pc(process->pc += process->opsize);
	read_instruction(core, process);
	//ft_printf("ft_instructions OUT\n");
	return (ok);
}
