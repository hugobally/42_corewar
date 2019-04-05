#include "corewar.h"

void				add_parameter(t_core *core, t_process *p, t_op *op,
									uint8_t index)
{
	uint8_t			type;
	uint8_t			*val;

	val = &(core->arena[get_pc(p->pc + p->opsize)]);
	type = (p->params.bytecode & (0xC0 >> index * 2)) >> (6 - index * 2);
	if (type == REG_CODE)
	{
		*(&(p->params.p1) + index) = (int32_t)(*val);
		p->opsize += REG_SIZE;
	}
	else if (type == IND_CODE || (type == DIR_CODE && op->compact))
	{
		*(&(p->params.p1) + index) = (int32_t)*((int16_t*)val);
		p->opsize += IND_SIZE;
	}
	else if (type == DIR_CODE)
	{
		*(&(p->params.p1) + index) = *((int32_t*)val);
		p->opsize += DIR_SIZE;
	}
	if ((type == REG_CODE && !(op->param_types[index] & T_REG))
			|| (type == IND_CODE && !(op->param_types[index] & T_IND))
			|| (type == DIR_CODE && !(op->param_types[index] & T_DIR))
			|| type == 0)
		p->instruction = 0;
}

uint8_t				fake_bytecode(uint8_t code)
{
	if (code & T_REG)
		return (0x55);
	else if (code & T_DIR)
		return (0xAA);
	else
		return (0xFF);
}

void				store_parameters(t_core *core, t_process *p)
{
	uint8_t			index;
	t_op			*op;

	op = &(g_op_tab[p->instruction - 1]);
	if (op->has_ocp)
	{
		p->params.bytecode = core->arena[get_pc(p->pc + p->opsize)];
		p->opsize++;
	}
	index = 0;
	while (index < op->param_num)
	{
		if (!(op->has_ocp))
			p->params.bytecode = fake_bytecode(op->param_types[index]);
		add_parameter(core, p, op, index);
		index++;
	}
}

void				read_instruction(t_core *core, t_process *p)
{
	ft_bzero(&(p->params), sizeof(t_params));
	p->opsize = 1;
	if (core->arena[get_pc(p->pc)] > (sizeof(g_op_tab) / sizeof(t_op)) - 1)
	{
		p->instruction = core->arena[get_pc(p->pc)];
		store_parameters(core, p);
	}
	else
		p->instruction = 0;
}
