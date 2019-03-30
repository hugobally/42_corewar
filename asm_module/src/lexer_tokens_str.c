/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 16:14:00 by hbally            #+#    #+#             */
/*   Updated: 2019/03/30 12:25:37 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"
#include "macros.h"
#include "asm.h"

static uint8_t		endofstr(char c)
{
	return (c == COMMENT_CHAR
				|| c == LABEL_CHAR
				|| c == DIRECT_CHAR
				|| c == SEPARATOR_CHAR
				|| c == QUOTE_CHAR
				|| ft_iswhitespace(c));
}

static t_code		token_str(const t_toktype type,
								t_line *line,
								t_tokenlst *lst)
{
	t_token			template;
	uint16_t		start;

	template_init(&template, type, line);
	start = line->index;
	while (line->str[line->index + 1] && !endofstr(line->str[line->index + 1]))
	{
		ft_printf("looking at char -%c-\n", line->str[line->index + 1]);
		line->index++;
		if (line->index - start > MAX_TOKEN_STR_SIZE)
			return (error_handler(strsize, 0, line));
	}
	get_right_pad(&template, line);
	template.value = ft_strsub(line->str, start, ++(line->index) - start);
	if (!(template.value))
		return (error_handler(malloc, 0, 0));
	else
		return (token_add(lst, &template, ft_strlen(template.value)));
}

t_code				token_str_wrapper(const t_toktype type,
										t_line *line,
										t_tokenlst *lst)
{
	if (ft_iswhitespace(line->str[line->index]))
		line->index++;
	else if (line->str[line->index] == '#')
	{
		while (line->str[line->index])
			line->index++;
	}
	else
		return (token_str(type, line, lst));
	return (done);
}
