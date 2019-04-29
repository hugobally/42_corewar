/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:58:46 by hbally            #+#    #+#             */
/*   Updated: 2019/04/29 14:00:07 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "errors.h"
#include "types.h"
#include "asm.h"

t_token				*find_before(t_token *start, t_toktype type)
{
	t_token			*node;

	node = start;
	while (node)
	{
		if (node->type == type)
			return (node);
		node = node->previous;
	}
	return (start);
}

t_token				*skip_eol(t_token *node)
{
	if (node)
	{
		if (node->type != char_eol)
			while (node && node->type != char_eol)
				node = node->next;
		while (node && node->type == char_eol)
			node = node->next;
		return (node);
	}
	return (NULL);
}

t_code				syntax(t_tokenlst *lst, t_file *file)
{
	t_header		header;
	t_label			*label_tab;

	label_tab = NULL;
	ft_bzero(&header, sizeof(t_header));
	header.magic = COREWAR_EXEC_MAGIC;
	if (get_header(lst, &header) == error)
		return (syntax_exit(&label_tab, parser_error));
	build_label_tab(lst, &label_tab);
	syntax_prog(lst, &label_tab, &header);
	if (error_handler(query, 0, 0) != error)
	{
		if (!header.prog_size)
			return (syntax_exit(&label_tab, parser_error));
		if (output_file(lst, &label_tab, &header, file) == error)
			return (syntax_exit(&label_tab, write_crash));
	}
	return (syntax_exit(&label_tab, no_error));
}
