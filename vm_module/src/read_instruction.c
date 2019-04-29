/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:40:16 by alac              #+#    #+#             */
/*   Updated: 2019/04/29 13:40:17 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "graph.h"

void				write_val(t_core *core, uint32_t pc, uint32_t size,
								int32_t val)
{
	uint32_t		i;

	i = 0;
	size--;
	while (i <= size)
	{
		core->arena[get_pc(pc + size - i)] = *(((uint8_t*)&val) + i);
		if (core->visu)
		{
			write_on_arena(get_pc(pc + size - i), *(((uint8_t*)&val) + i),
			core->graph->tmp_player, core->graph);
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

static void			add_parameter(t_core *core, t_process *p, t_op *op,
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

static uint8_t		fake_bytecode(uint8_t code)
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

	ft_bzero(&(p->params), sizeof(t_params));
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
