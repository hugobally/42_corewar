/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:56:00 by hbally            #+#    #+#             */
/*   Updated: 2019/04/22 15:56:05 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "types.h"

static void				clear_labelchar(t_tokenlst *lst)
{
	t_token				*node;
	t_token				*next;

	node = lst->start;
	while (node)
	{
		next = node->next;
		if (node->type == char_label)
			token_del(node, lst);
		node = next;
	}
}

static void				clear_dirchar(t_tokenlst *lst)
{
	t_token				*node;
	t_token				*next;

	node = lst->start;
	while (node)
	{
		next = node->next;
		if (node->type == char_dir)
		{
			if ((node->pad & PAD_RIGHT) || !node->next
					|| (node->next->type != dir_num
						&& node->next->type != char_label))
				error_handler(dir_badformat, node, 0);
			token_del(node, lst);
		}
		node = next;
	}
}

static t_code			check_empty(t_token *node)
{
	uint8_t				found_instruction;

	found_instruction = 0;
	while (node)
	{
		if (node->type == opcode)
			found_instruction = 1;
		node = node->next;
	}
	if (!found_instruction)
		return (error_handler(no_instructions, 0, 0));
	else
		return (done);
}

t_code					tokens_clear(t_tokenlst *lst)
{
	clear_dirchar(lst);
	clear_labelchar(lst);
	return (check_empty(lst->start));
}
