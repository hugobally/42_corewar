#include "corewar.h"

void		get_params3(t_core *core, t_process *pro, uint32_t i, uint8_t code)
{
	if (T_IND & g_op_tab[pro->instruction - 1].param_types[2])
		if (code & IND_CODE)
			pro->params.p1 = (int16_t)core->arena[i];
	if (T_DIR & g_op_tab[pro->instruction - 1].param_types[2])
		if (code & DIR_CODE)
			pro->params.p1 = (int32_t)core->arena[i];
	if (T_REG & g_op_tab[pro->instruction - 1].param_types[2])
		if (code & REG_CODE)
			pro->params.p1 = (int32_t)core->arena[i];
	if (code & T_IND)
	{
		pro->instruction_size += IND_SIZE;
		i += IND_SIZE;
	}
	else if (code & T_DIR)
	{
		pro->instruction_size += DIR_SIZE;
		i+= DIR_SIZE;
	}
}

int			get_params2(t_core *core, t_process *pro, uint32_t i, uint8_t code)
{
	if (T_IND & g_op_tab[pro->instruction - 1].param_types[1])
		if (code & IND_CODE)
			pro->params.p1 = (int16_t)core->arena[i];
	if (T_DIR & g_op_tab[pro->instruction - 1].param_types[1])
		if (code & DIR_CODE)
			pro->params.p1 = (int32_t)core->arena[i];
	if (T_REG & g_op_tab[pro->instruction - 1].param_types[1])
		if (code & REG_CODE)
			pro->params.p1 = (int32_t)core->arena[i];
	if (code & T_IND)
	{
		pro->instruction_size += IND_SIZE;
		i += IND_SIZE;
	}
	else if (code & T_DIR)
	{
		pro->instruction_size += DIR_SIZE;
		i+= DIR_SIZE;
	}
	return (i);
}

int			get_params1(t_core *core, t_process *pro, uint32_t i, uint8_t code)
{
	if (T_IND & g_op_tab[pro->instruction - 1].param_types[0])
		if (code & IND_CODE)
			pro->params.p1 = (int16_t)core->arena[i];
	if (T_DIR & g_op_tab[pro->instruction - 1].param_types[0])
		if (code & DIR_CODE)
			pro->params.p1 = (int32_t)core->arena[i];
	if (T_REG & g_op_tab[pro->instruction - 1].param_types[0])
		if (code & REG_CODE)
			pro->params.p1 = (int32_t)core->arena[i];
	if (code & T_IND)
	{
		pro->instruction_size += IND_SIZE;
		i += IND_SIZE;
	}
	else if (code & T_DIR)
	{
		pro->instruction_size += DIR_SIZE;
		i+= DIR_SIZE;
	}
	return (i);
}

void		get_params(t_core *core, t_process *pro, uint32_t i)
{
	uint8_t		code;

	code = pro->params.bytecode >> 6;
	if (!code)
	{
		pro->instruction = 0;
		pro->instruction_size = 1;
		return ;
	}
	i = get_params1(core, pro, i, pro->params.bytecode >> 6);
	i = get_params2(core, pro, i, pro->params.bytecode >> 4);
	get_params3(core, pro, i, pro->params.bytecode >> 2);
	pro->remaining_cycles = g_op_tab[pro->instruction - 1].cycles;
}

void		read_instructions(t_core *core, t_process *pro)
{
	uint32_t	i;

	pro->instruction = 0;
	pro->params.bytecode = 0;
	pro->params.p1 = 0;
	pro->params.p2 = 0;
	pro->params.p3 = 0;
	pro->instruction_size = 1;
	i = pro->pc;
	pro->instruction = core->arena[i] > 16 ? 0 : core->arena[i];
	if (pro->instruction)
		++i;
	if (pro->instruction != 0 && g_op_tab[pro->instruction - 1].has_ocp)
	{
		pro->params.bytecode = core->arena[i++];
		++pro->instruction_size;
		get_params(core, pro, i);
	}
	else if (pro->instruction != 0)
	{
		pro->params.p1 = (int32_t)core->arena[get_pc(i)];
		pro->instruction_size += DIR_SIZE;
	}
	// if (pro->instruction_size > 1)
}
