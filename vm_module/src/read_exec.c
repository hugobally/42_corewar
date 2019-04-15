
#include "corewar.h"
#include "graph.h"

t_errors		ft_instructions(t_core *core, t_process *process)
{
	int op;
	t_errors res;
	t_op *tab;

	//ft_printf("ft_instructions IN %d\n", process->instruction);
	if (process->remaining_cycles != 0)
		return (0);
	read_instruction(core, process);
	if ((op = process->instruction) && (op <= 0 || op > 16))
		op = 0;
	if ((res = g_op_inst_tab[op](core, process)) != ok)
		return (res);
	//ft_printf("after fonction pc %d, inst %d, carry %d\n", process->pc, process->instruction, process->carry);
	if ((op != zjmp) || (op == zjmp && process->carry == false))
	{
		if (core->visu)
			move_proccess_on_arena(process->pc, get_pc(process->pc + process->opsize), core->graph);
		process->pc = get_pc(process->pc += process->opsize);
	}
	//ft_printf("after pc\n");
	//ft_printf("after jmp pc %d, inst %d, carry %d\n", process->pc, process->instruction, process->carry);
	read_instruction(core, process);
	//ft_printf("after read pc %d, inst %d, carry %d\n", process->pc, process->instruction, process->carry);
	if (process->instruction != 0)
	{
		tab = &(g_op_tab[process->instruction - 1]);
		//ft_printf("after tab tab->cycles %d\n", tab->cycles);
		process->remaining_cycles = tab->cycles;
	}
	//ft_printf("ft_instructions OUT remaing_cycles %d\n", process->remaining_cycles);
	return (ok);
}
