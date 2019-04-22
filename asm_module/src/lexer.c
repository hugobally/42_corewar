/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:55:25 by hbally            #+#    #+#             */
/*   Updated: 2019/04/22 15:55:55 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "types.h"
#include "errors.h"

void				tokens_foreach(t_tokenlst *lst, void (*action)(t_token*))
{
	t_token			*node;

	node = lst->start;
	while (node)
	{
		action(node);
		node = node->next;
	}
}

t_code				lexer(t_tokenlst *lst, t_file *file)
{
	tokens_foreach(lst, &find_labels);
	tokens_foreach(lst, &find_opcodes);
	tokens_foreach(lst, &find_registers);
	tokens_foreach(lst, &find_commands);
	tokens_foreach(lst, &find_num);
	if (tokens_clear(lst) == error)
		return (error);
	else
		return (syntax(lst, file));
}
