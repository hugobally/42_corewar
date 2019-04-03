#include <unistd.h>
#include "libft.h"
#include "types.h"
#include "macros.h"
#include "asm.h"

static uint32_t	get_param(t_token *token, uint32_t now,
							t_label **label_tab, uint8_t *buffer)
{//ENDIAN
	int32_t		val;
	uint32_t	val_size;

	if (token->type == dir_label || token->type == ind_label)
		val = label_tab_fetch(token, label_tab)->offset - (int32_t)now;
	else if (token->type != reg)
		val = ft_atoi(token->value);
	else
		val = ft_atoi(&(token->value[1]));
	val = reverse_endian(val);//
	if (token->type == reg)
		val_size = 1;
	else if (token->type == ind_num || token->type == ind_label)
		val_size = 2;
	else
		val_size = 4;
	ft_memcpy(buffer, (uint8_t*)&val + (4 - val_size), val_size);
	return (val_size);
}

static uint8_t	get_encoding(t_token *token, uint8_t param_num)
{
	uint8_t		param;
	uint8_t		encoding;
	uint8_t		code;

	encoding = 0;
	param = 0;
	while (param < param_num)
	{
		if (token->type == dir_num || token->type == dir_label)
			code = DIR_CODE;
		else if (token->type == ind_num || token->type == ind_label)
			code = IND_CODE;
		else
			code = REG_CODE;
		encoding |= code << (6 - 2 * param);
		token = token->next->next;
		param++;
	}
	return (encoding);
}

t_code			write_instruction(t_token *token, t_label **label_tab,
									t_file *file, uint32_t *offset)
{
	t_op		*op;
	int32_t		index;
	uint8_t		param;
	uint8_t		buffer[2 + 3 * DIR_SIZE];

	op = find_op(token->value);
	buffer[0] = op->opcode;
	index = 1;
	if (op->has_ocp)
		buffer[index++] = get_encoding(token->next, op->param_num);
	param = 0;
	token = token->next;
	while (param < op->param_num)
	{
		param++;
		index += get_param(token, *offset, label_tab, &(buffer[index]));
		token = token->next->next;
	}
	*offset += index;
	if (file != DUMMY_WRITE)
		return (write(file->out_fd, buffer, index) != -1 ? done : error);
	return (done);
}
