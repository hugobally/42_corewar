
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
		p->remaining_cycles = g_op_tab[p->instruction - 1].cycles - 2;
	}
	else
		p->instruction = 0;
}

void			ft_verbose_dump(t_core *c, t_process *p)
{
	int		i;

	i = -1;
	while (++i < p->opsize)
		ft_printf("%.2x ", c->arena[get_pc(p->pc + i)]);
	ft_putchar('\n');
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
		{
			return (res);
		}
		p->loading = 0;
		//set instruction et params a 0
	}
	if ((p->instruction != zjmp || !p->carry)
			|| (p->instruction == zjmp && p->carry == false))
	{
		if (core->visu)
			move_proccess_on_arena(p->pc, get_pc(p->pc + p->opsize), core->graph);
		if ((p->opsize > 1 || p->instruction) && core->verbose & 16)
		{
			ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", p->opsize, p->pc, get_pc(p->pc + p->opsize));
			ft_verbose_dump(core, p);
		}
		p->pc = get_pc(p->pc += p->opsize);
	}
	return (ok);
}
