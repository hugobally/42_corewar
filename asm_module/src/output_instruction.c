/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_instruction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:57:49 by hbally            #+#    #+#             */
/*   Updated: 2019/04/22 15:57:51 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "types.h"
#include "macros.h"
#include "asm.h"

static uint32_t		store_value(t_token *token, t_op *op,
									int32_t val, uint8_t *buffer)
{
	uint32_t		val_size;

	if (token->type == reg)
		val_size = 1;
	else if (token->type == ind_num || token->type == ind_label
				|| op->compact)
		val_size = 2;
	else
		val_size = 4;
	ft_memcpy(buffer, (uint8_t*)(&val) + (4 - val_size), val_size);
	return (val_size);
}

static int32_t		convert_value(t_token *token, uint32_t offset,
									t_label **label_tab)
{
	int32_t			val;
	char			*string;

	string = token->value;
	if (token->type == reg)
		val = ft_atoui(&(string[1]));
	else if (token->type == dir_label || token->type == ind_label)
		val = label_tab_fetch(token, label_tab)->offset - (int32_t)offset;
	else
	{
		val = (int32_t)ft_atoui(&(string[string[0] == '-']));
		if (string[0] == '-')
			val *= -1;
	}
	val = reverse_endian(val);
	return (val);
}

static int32_t		get_encoding(t_token *token, t_op *op, uint8_t *buffer)
{
	uint8_t			i;
	uint8_t			encoding;
	uint8_t			code;

	encoding = 0;
	i = 0;
	while (i < op->param_num)
	{
		if (token->type == dir_num || token->type == dir_label)
			code = DIR_CODE;
		else if (token->type == ind_num || token->type == ind_label)
			code = IND_CODE;
		else
			code = REG_CODE;
		encoding |= code << (6 - 2 * i);
		token = token->next->next;
		i++;
	}
	buffer[1] = encoding;
	return (2);
}

t_code				write_instruction(t_token *token, t_label **label_tab,
											t_file *file, uint32_t *offset)
{
	t_op			*op;
	int32_t			opsize;
	uint8_t			i;
	uint8_t			buffer[2 + 3 * DIR_SIZE];
	int32_t			val;

	op = find_op(token->value);
	buffer[0] = op->opcode;
	token = token->next;
	opsize = op->has_ocp ? get_encoding(token, op, buffer) : 1;
	i = 0;
	while (i < op->param_num)
	{
		val = convert_value(token, *offset, label_tab);
		opsize += store_value(token, op, val, &(buffer[opsize]));
		token = token->next->next;
		i++;
	}
	*offset += opsize;
	if (file != DUMMY_WRITE)
		return (write(file->out_fd, buffer, opsize) != -1 ? done : error);
	else
		return (done);
}
