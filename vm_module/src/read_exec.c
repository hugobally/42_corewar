
#include "corewar.h"
#include "graph.h"

t_errors		ft_instructions(t_core *core, t_process *process)
{
	int op;
	t_errors res;
	t_op *tab;

	if (process->remaining_cycles != 0)
		return (0);
	if (core->loop != 0)
		read_instruction(core, process, 1);
	if ((op = process->instruction) && (op <= 0 || op > 16))
		op = 0;
	if ((res = g_op_inst_tab[op](core, process)) != ok)
		return (res);
	if ((op != zjmp) || (op == zjmp && process->carry == false))
	{
		if (core->visu)
			move_proccess_on_arena(process->pc, get_pc(process->pc + process->opsize), core->graph);
		process->pc = get_pc(process->pc += process->opsize);
	}
	read_instruction(core, process, 1);
	if (process->instruction != 0)
	{
		tab = &(g_op_tab[process->instruction - 1]);
		process->remaining_cycles = tab->cycles;
	}
	return (ok);
}
