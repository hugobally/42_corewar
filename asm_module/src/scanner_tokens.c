/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:58:09 by hbally            #+#    #+#             */
/*   Updated: 2019/04/23 14:22:11 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"
#include "errors.h"
#include "macros.h"
#include "asm.h"

t_code				token_single(const t_toktype type,
								t_line *line,
								t_tokenlst *lst)
{
	t_token		template;

	template_init(&template, type, line);
	get_right_pad(&template, line);
	line->index++;
	return (token_add(lst, &template, 1));
}

t_code				token_quote(const t_toktype type,
								t_line *l,
								t_tokenlst *lst)
{
	t_token		template;
	uint16_t	start;

	template_init(&template, type, l);
	if (!l->is_quote)
	{
		start = ++(l->index);
		l->is_quote = 1;
	}
	else
		start = l->index;
	while (l->str[l->index] && l->str[l->index] != QUOTE_CHAR)
		l->index++;
	template.value = ft_strsub(l->str, start, l->index - start);
	if (l->str[l->index] == QUOTE_CHAR)
	{
		l->index++;
		l->is_quote = 0;
		template.pad = END_QUOTE;
	}
	else
		template.pad = NO_END_QUOTE;
	return (token_add(lst, &template, ft_strlen(template.value)));
}

uint8_t				endofstr(char c)
{
	static int		endchar[8] = {
		COMMENT_CHAR,
		COMMENT_CHAR_2,
		LABEL_CHAR,
		DIRECT_CHAR,
		SEPARATOR_CHAR,
		QUOTE_CHAR,
		EOL_CHAR,
		0
	};
	int				i;

	i = 0;
	while (endchar[i] != 0)
	{
		if (c == endchar[i])
			return (1);
		i++;
	}
	return (ft_iswhitespace(c));
}

t_code				token_unknown(const t_toktype type,
											t_line *line,
											t_tokenlst *lst)
{
	t_token			template;
	uint16_t		start;

	template_init(&template, type, line);
	start = line->index;
	while (line->str[line->index + 1] && !endofstr(line->str[line->index + 1]))
		line->index++;
	get_right_pad(&template, line);
	template.value = ft_strsub(line->str, start, ++(line->index) - start);
	if (!(template.value))
		return (error_handler(malloc, 0, 0));
	else
		return (token_add(lst, &template, ft_strlen(template.value)));
}

t_code				token_unknown_wrapper(const t_toktype type,
												t_line *line,
												t_tokenlst *lst)
{
	if (ft_iswhitespace(line->str[line->index]))
	{
		line->index++;
		return (done);
	}
	else if (line->str[line->index] == COMMENT_CHAR
				|| line->str[line->index] == COMMENT_CHAR_2)
	{
		while (line->str[line->index])
			line->index++;
		return (done);
	}
	else
		return (token_unknown(type, line, lst));
}
