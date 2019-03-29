/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 13:54:37 by hbally            #+#    #+#             */
/*   Updated: 2019/03/29 16:59:19 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"
#include "macros.h"
#include "asm.h"

void			template_init(t_token *template, t_toktype type, t_line *line)
{
	ft_bzero(template, sizeof(t_token));
	template->type = type;
	template->pos = line->num | (((uint32_t)(line->index) + 1u) << 16);
	if (line->index == 0 || ft_iswhitespace(line->str[line->index - 1]))
		template->pad |= PAD_LEFT;
}

void			get_right_pad(t_token *template, t_line *line)
{
	if (line->str[line->index + 1] == '\0'
			|| ft_iswhitespace(line->str[line->index + 1]))
		template->pad |= PAD_RIGHT;
}

t_code			token_single(const t_toktype type,
								t_line *line,
								t_tokenlst *lst)
{
	t_token		template;

	template_init(&template, type, line);
	get_right_pad(&template, line);
	line->index++;
	return (token_add(lst, &template));
}

t_code			token_newline(t_line *line, t_tokenlst *lst)
{
	t_token		template;

	template_init(&template, char_eol, line);
	return (token_add(lst, &template));
}

t_code			token_quote(const t_toktype type,
								t_line *line,
								t_tokenlst *lst)
{
}
