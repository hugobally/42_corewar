/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:58:56 by hbally            #+#    #+#             */
/*   Updated: 2019/04/29 14:00:07 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "errors.h"
#include "types.h"
#include "asm.h"

static uint8_t		is_duplicate(t_toktype type, t_tokenlst *l, int reset)
{
	static int		found_name;
	static int		found_comment;

	if (reset == 1)
	{
		found_name = 0;
		found_comment = 0;
		return (0);
	}
	if (type == cmd_name)
		found_name++;
	if (type == cmd_comment)
		found_comment++;
	if (found_name > 1 || found_comment > 1)
	{
		error_handler(header_duplicate, l->now->previous, 0);
		return (1);
	}
	return (0);
}

static uint8_t		is_valid_size(size_t len, size_t to_add,
									t_toktype t, t_tokenlst *l)
{
	t_code			status;

	len += to_add;
	status = done;
	if (t == cmd_name && len > PROG_NAME_LENGTH)
		status = error_handler(header_namesize, l->now, 0);
	else if (t == cmd_comment && len > COMMENT_LENGTH)
		status = error_handler(header_commentsize, l->now, 0);
	return (status != error ? 1 : 0);
}

static t_toktype	is_valid_cmd(t_tokenlst *l)
{
	t_toktype		type;

	if (!l->now || !(l->now->type == cmd_name || l->now->type == cmd_comment))
	{
		error_handler(header_missing, 0, 0);
		return (unknown);
	}
	if (!(l->now->next && l->now->next->type == quote))
	{
		error_handler(header_noquote, l->now, 0);
		return (unknown);
	}
	type = l->now->type;
	l->now = l->now->next;
	return (type);
}

static t_code		copy_val(t_tokenlst *l, char *dst, t_toktype type)
{
	size_t			len;

	len = 0;
	if (is_duplicate(type, l, 0))
		return (error);
	while (l->now)
	{
		if (l->now->type == char_eol && is_valid_size(len, 1, type, l))
			dst[len++] = '\n';
		else if (l->now->type == quote)
		{
			if (!is_valid_size(len, ft_strlen(l->now->value), type, l))
				return (error);
			ft_strcpy(&(dst[len]), l->now->value);
			len += ft_strlen(l->now->value);
			if (l->now->pad == END_QUOTE)
				return (done);
		}
		l->now = l->now->next;
	}
	return (error_handler(badquote, l->now, 0));
}

t_code				get_header(t_tokenlst *l, t_header *h)
{
	int				cmd_count;
	t_toktype		t;

	cmd_count = 0;
	is_duplicate(unknown, NULL, 1);
	l->now = (l->start->type == char_eol) ? skip_eol(l->start) : l->start;
	while (l->now && cmd_count < 2)
	{
		if ((t = is_valid_cmd(l)) == unknown)
			return (error);
		if (copy_val(l, t == cmd_name ? h->prog_name : h->comment, t) == error)
			return (error);
		if (l->now->next && l->now->next->type != char_eol)
			return (error_handler(expected_eol, l->now, 0));
		l->now = skip_eol(l->now);
		cmd_count++;
	}
	if (cmd_count < 2)
		return (error_handler(header_missing, 0, 0));
	if (h->prog_name[0] == '\0')
		return (error_handler(badquote, find_before(l->now, cmd_name), 0));
	l->prog_start = l->now;
	return (done);
}
