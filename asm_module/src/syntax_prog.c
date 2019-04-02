#include "asm.h"
#include "errors.h"
#include "types.h"

#include "libft.h"// debug
#include <stdio.h>

t_token				*find_before(t_token *start, t_toktype type)
{
	t_token			*node;

	node = start;
	while (node)
	{
		if (node->type == type)
			return (node);
		node = node->previous;
	}
	return (start);
}

static uint8_t		is_valid_param(t_token *token, uint8_t ref,
									t_label **label_tab)
{
	uint8_t			status;

	status = 0;
	if (((token->type == dir_num || token->type == dir_label)
			&& (ref & T_DIR))
		|| ((token->type == ind_num || token->type == ind_label)
			&& (ref & T_IND))
		|| (token->type == reg && (ref & T_REG)))
		status = 1;
	if ((token->type == dir_label || token->type == ind_label)
			&& !(label_tab_fetch(token, label_tab)))
	{
		error_handler(label_no_match, token, 0);
		status = 0;
	}
	return (status);
}

/*
** TODO better error handling in parse_parameters
*/ 

static t_code		parse_parameters(t_token *node, t_label **label_tab)//
{
	t_op			*op;
	uint8_t			i;

	i = 0;
	op = find_op(node->value);
	while (i++ < op->param_num)
	{
		node = node->next;
		if (!is_valid_param(node, op->param_types[i - 1], label_tab))
			return (error_handler(param_invalid,
									find_before(node, opcode), 0));
		node = node->next;
		if ((i < op->param_num && node->type != char_sep)
				|| (i == op->param_num && node->type != char_eol))
			return (error_handler(param_invalid,
									find_before(node, opcode), 0));
	}
	return (done);
}

static t_code		parse_instruction(t_tokenlst *lst, t_label **label_tab)
{
	t_code			status;

	if (lst->now->type != opcode)
	{
		status = error;
		if (lst->now->type != unknown)
			error_handler(expected_opcode, lst->now, 0);
	}
	else
		status = parse_parameters(lst->now, label_tab);
	return (status);
}

void				parse_line(t_tokenlst *lst, t_label **label_tab,
							header_t *header)
{
	if (lst->now->type == label)
	{
		label_tab_fetch(lst->now, label_tab)->offset = header->prog_size;
		lst->now = lst->now->next;
	}
	if (lst->now->type != char_eol)
	{
		if (parse_instruction(lst, label_tab) != error)
			header->prog_size += 1;//output_instruction(opcode_token, query);
		while (lst->now->type != char_eol)
			lst->now = lst->now->next;
	}
	lst->now = lst->now->next;
}

t_code				syntax_prog(t_tokenlst *lst,
							t_label **label_tab, 
							header_t *header)
{
	lst->now = lst->prog_start;
	if (!lst->now)
		return (error_handler(no_instructions, 0, 0));
	while (lst->now)
	{
		parse_line(lst, label_tab, header);
		if (header->prog_size > CHAMP_MAX_SIZE
				|| header->prog_size > MAX_OUTPUT_BYTE_SIZE)
			return (error_handler(bytesize, lst->now, 0));
	}
	return (done);
}