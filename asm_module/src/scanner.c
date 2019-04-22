/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:57:55 by hbally            #+#    #+#             */
/*   Updated: 2019/04/22 15:57:56 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"
#include "errors.h"
#include "macros.h"
#include "asm.h"

static t_code			dispatcher(t_line *line, t_tokenlst *lst)
{
	uint16_t			j;
	static t_dispatch	tab[5] = {
		{char_label, &token_single},
		{char_dir, &token_single},
		{char_sep, &token_single},
		{quote, &token_quote},
		{0, 0}
	};

	if (line->is_quote)
		return (token_quote(quote, line, lst));
	j = 0;
	while (tab[j].handler)
	{
		if (line->str[line->index] == (char)(tab[j].type))
			return (tab[j].handler(tab[j].type, line, lst));
		j++;
	}
	return (token_unknown_wrapper(unknown, line, lst));
}

static t_code			process_line(t_line *line, t_tokenlst *lst)
{
	t_code				ret_code;

	line->index = 0;
	ret_code = done;
	if (line->str[0])
	{
		while (line->str[line->index])
			if ((ret_code = dispatcher(line, lst)) == error)
				break ;
	}
	if (ret_code == done)
		ret_code = token_single(char_eol, line, lst);
	ft_memdel((void**)&(line->str));
	return (ret_code);
}

t_code					scanner(t_file *file)
{
	int32_t				ret;
	t_line				line;
	t_tokenlst			lst;

	ft_bzero(&lst, sizeof(t_tokenlst));
	ft_bzero(&line, sizeof(t_line));
	while ((ret = get_next_line(file->fd, &(line.str))) > 0)
	{
		line.num++;
		if (process_line(&line, &lst) == error)
			return (scanner_exit(&lst, scanner_error));
	}
	if (ret < 0)
		return (scanner_exit(&lst, ret));
	if (lexer(&lst, file) == error)
		return (scanner_exit(&lst, lexer_error));
	else
		return (scanner_exit(&lst, no_error));
}
