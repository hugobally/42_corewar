/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:58:00 by hbally            #+#    #+#             */
/*   Updated: 2019/04/22 15:58:01 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"
#include "errors.h"
#include "macros.h"
#include "asm.h"

void			template_init(t_token *template, t_toktype type, t_line *line)
{
	ft_bzero(template, sizeof(t_token));
	template->type = type;
	if (line->str && line->str[0])
	{
		template->pos = line->num | (((uint32_t)(line->index) + 1u) << 16);
		if (line->index == 0 || ft_iswhitespace(line->str[line->index - 1]))
			template->pad |= PAD_LEFT;
	}
}

void			get_right_pad(t_token *template, t_line *line)
{
	if (line->str && line->str[0])
	{
		if (line->str[line->index + 1] == '\0'
				|| ft_iswhitespace(line->str[line->index + 1]))
			template->pad |= PAD_RIGHT;
	}
}

t_code			token_add(t_tokenlst *lst, const t_token *template,
									const size_t value_size)
{
	t_token		*new;

	if (!(new = (t_token*)ft_memalloc(sizeof(t_token))))
		return (error_handler(malloc, 0, 0));
	new->value = template->value;
	new->type = template->type;
	new->pos = template->pos;
	new->pad = template->pad;
	new->previous = lst->end;
	if (!lst->start)
		lst->start = new;
	if (lst->end)
		lst->end->next = new;
	lst->end = new;
	lst->byte_size += value_size;
	if (lst->byte_size > MAX_INPUT_FILE_SIZE)
		return (error_handler(filesize, 0, 0));
	return (done);
}
