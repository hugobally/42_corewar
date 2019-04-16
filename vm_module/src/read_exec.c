
#include "corewar.h"
#include "graph.h"

static void		get_opcode(t_core *core, t_process *p)
{
	uint32_t		opcode;

	p->opsize = 1;
	opcode = (uint32_t)core->arena[get_pc(p->pc)];
	if (opcode > 0 && opcode <= ((sizeof(g_op_tab) / sizeof(t_op)) - 1))
	{
		p->instruction = opcode;
		p->remaining_cycles = g_op_tab[p->instruction - 1].cycles;
	}
	else
		p->instruction = 0;
}

t_errors		ft_instructions(t_core *core, t_process *p)
{
	t_errors 	res;
	
	if (p->loading == 0)
	{
		get_opcode(core, p);
		if (p->instruction)
		{
			p->loading = 1;
			return (ok);
		}
	}
	else
	{
		store_parameters(core, p);
		if ((res = g_op_inst_tab[p->instruction](core, p)) != ok)
			return (res);
		p->loading = 0;
		//set instruction et params a 0
	}
	if ((p->instruction != zjmp)
			|| (p->instruction == zjmp && p->carry == false))
	{
		if (core->visu)
			move_proccess_on_arena(p->pc, get_pc(p->pc + p->opsize), core->graph);
		p->pc = get_pc(p->pc += p->opsize);
	}
	return (ok);
}
