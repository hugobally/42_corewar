/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:56:11 by hbally            #+#    #+#             */
/*   Updated: 2019/04/22 15:56:14 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"
#include "errors.h"
#include "libcorewar.h"
#include "asm.h"

t_op				*find_op(char *string)
{
	uint8_t			index;

	index = 0;
	while (g_op_tab[index].name)
	{
		if (!ft_strcmp(string, g_op_tab[index].name))
			return (&(g_op_tab[index]));
		index++;
	}
	return (NULL);
}

void				find_opcodes(t_token *token)
{
	if (token->type == unknown && find_op(token->value))
		token->type = opcode;
}

void				find_commands(t_token *token)
{
	if (token->type == unknown && token->value[0] == '.')
	{
		if (!ft_strcmp(token->value, NAME_CMD_STRING))
			token->type = cmd_name;
		else if (!ft_strcmp(token->value, COMMENT_CMD_STRING))
			token->type = cmd_comment;
		else
		{
			token->type = cmd;
			error_handler(cmd_unknown, token, 0);
		}
	}
}
