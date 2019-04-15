#include "corewar.h"
#include "graph.h"
#include "libft.h" //DEBUG
#include <stdlib.h> //DEBUG

void				write_val(t_core *core, uint32_t pc, uint32_t size,
								int32_t val, int player)
{
	uint32_t		i;

	i = 0;
	size--;
	while (i <= size)
	{
		core->arena[get_pc(pc + size - i)] = *(((uint8_t*)&val) + i);
		if (core->visu)
		{
			write_on_arena(get_pc(pc + size - i), *(((uint8_t*)&val) + i), player, core->graph);
		}
		i++;
	}
}

int32_t				read_val(t_core *core, uint32_t pc, uint32_t size)
{
	uint32_t		i;
	uint32_t		val;

	val = 0;
	i = 0;
	while (i < size)
	{
		val = val << 8;
		val |= ((uint32_t)core->arena[get_pc(pc + i)]);
		i++;
	}
	if (size == 2)
		return ((int32_t)(int16_t)val);
	else
		return ((int32_t)val);
}

static void				add_parameter(t_core *core, t_process *p, t_op *op,
									uint8_t index)
{
	uint8_t			type;

	type = (p->params.bytecode & (0xC0 >> index * 2)) >> (6 - index * 2);
	if (type == REG_CODE)
	{
		*(&(p->params.p1) + index) = read_val(core, p->pc + p->opsize, 1);
		p->opsize += 1;
	}
	else if (type == IND_CODE || (type == DIR_CODE && op->compact))
	{
		*(&(p->params.p1) + index) = read_val(core, p->pc + p->opsize, 2);
		p->opsize += 2;
	}
	else if (type == DIR_CODE)
	{
		*(&(p->params.p1) + index) = read_val(core, p->pc + p->opsize, 4);
		p->opsize += 4;
	}
	if ((type == REG_CODE && !(op->param_types[index] & T_REG))
			|| (type == IND_CODE && !(op->param_types[index] & T_IND))
			|| (type == DIR_CODE && !(op->param_types[index] & T_DIR))
			|| type == 0)
		p->instruction = 0;
}

static uint8_t			fake_bytecode(uint8_t code)
{
	if (code & T_REG)
		return (0x55);
	else if (code & T_DIR)
		return (0xAA);
	else
		return (0xFF);
}

static void				store_parameters(t_core *core, t_process *p)
{
	uint8_t			index;
	t_op			*op;

	op = &(g_op_tab[p->instruction - 1]);
	//ft_printf("op name is '%s'\n", op->name);
	if (op->has_ocp)
	{
		p->params.bytecode = core->arena[get_pc(p->pc + p->opsize)];
		p->opsize++;
	}
	//ft_printf("bytecode is %#x\n", p->params.bytecode);
	index = 0;
	while (index < op->param_num)
	{
		if (!(op->has_ocp))
			p->params.bytecode = fake_bytecode(op->param_types[index]);
		add_parameter(core, p, op, index);
		index++;
	}
	//ft_printf("params : %d -- %d -- %d\n", p->params.p1, p->params.p2, p->params.p3);
	//ft_printf("opcode is %d\n", p->instruction);
}

void				read_instruction(t_core *core, t_process *p)
{
	ft_bzero(&(p->params), sizeof(t_params));
	p->opsize = 1;
	//ft_printf("--- READ INSTRUCTION ---\n");
	if (core->arena[get_pc(p->pc)] && (core->arena[get_pc(p->pc)]
			<= (sizeof(g_op_tab) / sizeof(t_op)) - 1))
	{
		p->instruction = core->arena[get_pc(p->pc)];
		store_parameters(core, p);
	}
	else
		p->instruction = 0;
	//ft_printf("PC points to %p, value : %#x\n", &(core->arena[get_pc(p->pc + p->opsize)]), core->arena[get_pc(p->pc + p->opsize)]);
	//ft_printf("--- END READ INSTRUCTION ---\n");
	//exit(0);
}
