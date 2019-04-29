/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_prog.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:00:55 by hbally            #+#    #+#             */
/*   Updated: 2019/04/29 14:00:07 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "errors.h"
#include "types.h"

static uint8_t		is_valid_param(t_token *token, uint8_t ref)
{
	if (((token->type == dir_num || token->type == dir_label)
			&& (ref & T_DIR))
		|| ((token->type == ind_num || token->type == ind_label)
			&& (ref & T_IND))
		|| (token->type == reg && (ref & T_REG)))
		return (1);
	else
		return (0);
}

static t_code		parse_parameters(t_token *node, t_label **label_tab)
{
	t_op			*op;
	uint8_t			i;

	i = 0;
	op = find_op(node->value);
	while (i++ < op->param_num)
	{
		node = node->next;
		if (!is_valid_param(node, op->param_types[i - 1]))
			return (error_handler(param_invalid, find_before(node, opcode), 0));
		if ((node->type == dir_label || node->type == ind_label)
				&& !(label_tab_fetch(node, label_tab)))
			return (error_handler(label_no_match, node, 0));
		node = node->next;
		if ((i < op->param_num && node->type != char_sep)
				|| (i == op->param_num && node->type != char_eol))
			return (error_handler(param_invalid, find_before(node, opcode), 0));
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

static void			parse_line(t_tokenlst *lst, t_label **label_tab,
							t_header *header)
{
	if (lst->now->type == label)
	{
		label_tab_fetch(lst->now, label_tab)->offset = header->prog_size;
		lst->now = lst->now->next;
	}
	if (lst->now->type != char_eol)
	{
		if (parse_instruction(lst, label_tab) != error)
			write_instruction(lst->now, label_tab, DUMMY_WRITE,
								&(header->prog_size));
	}
	lst->now = skip_eol(lst->now);
}

t_code				syntax_prog(t_tokenlst *lst, t_label **ltab, t_header *h)
{
	t_bool			warning_triggered;

	warning_triggered = false;
	lst->now = lst->prog_start;
	if (!lst->now)
		return (error_handler(no_instructions, 0, 0));
	while (lst->now)
	{
		parse_line(lst, ltab, h);
		if (h->prog_size > CHAMP_MAX_SIZE && warning_triggered == false)
		{
			error_handler(bytesize, lst->now, 0);
			warning_triggered = true;
		}
		if (h->prog_size > MAX_OUTPUT_BYTE_SIZE)
			return (error_handler(output_max_size, 0, 0));
	}
	return (done);
}
