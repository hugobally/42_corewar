/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_labels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:56:17 by hbally            #+#    #+#             */
/*   Updated: 2019/04/22 15:56:51 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macros.h"
#include "types.h"
#include "errors.h"
#include "libft.h"
#include "libcorewar.h"
#include "asm.h"

static void		check_label_badchar(t_token *token)
{
	uint32_t	i;

	i = 0;
	while (token->value[i])
	{
		if (!strchr(LABEL_CHARS, token->value[i]))
			error_handler(label_badchar, token, 0);
		i++;
	}
}

void			find_labels(t_token *token)
{
	if (token->type == char_label)
	{
		if (token->previous && token->previous->type == unknown
				&& !(token->pad & PAD_LEFT))
		{
			check_label_badchar(token->previous);
			token->previous->type = label;
		}
		else if (token->next && token->next->type == unknown
					&& !(token->pad & PAD_RIGHT))
		{
			check_label_badchar(token->next);
			if (token->previous && token->previous->type == char_dir)
				token->next->type = dir_label;
			else
				token->next->type = ind_label;
		}
		else
			error_handler(label_badformat, token, 0);
	}
}
