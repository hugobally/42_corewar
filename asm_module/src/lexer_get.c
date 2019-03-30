/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:08:39 by hbally            #+#    #+#             */
/*   Updated: 2019/03/30 11:25:38 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libcorewar.h"
#include "types.h"
#include "macros.h"
#include "asm.h"

void			debug_printtokenlst(t_tokenlst *lst)
{
	t_token *node;
	node = lst->start;
	while (node)
	{
		ft_printf("%c | %s | %d, %d | %d\n", \
				(char)(node->type) != '\n' ? (char)(node->type) : '\\', \
				node->value ? node->value : "_____", \
				node->pos & 0x0000FFFFu, \
				(node->pos & 0xFFFF0000u) >> 16, \
				node->pad);
		node = node->next;
	}
}

/*
** Lexer Pass 1 : Acquire tokens as either
** 					1) special single char
**					2) anything else in between
**				  Comments and whitespace are discarded
**				  We store info about whitespace inside each token
*/

t_code					token_add(t_tokenlst *lst, const t_token *template,
									const size_t value_size)
{
	t_token				*new;
	static size_t		stored_size;

	if (!(new = (t_token*)ft_memalloc(sizeof(t_token))))
		return (error_handler(malloc, 0, 0));
	new->value = template->value;
	new->type = template->type;
	new->pos = template->pos;
	new->pad = template->pad;
	if (!lst->start)
		lst->start = new;
	if (lst->end)
		lst->end->next = new;
	lst->end = new;
	lst->size += 1;
	stored_size += value_size;
	if (lst->size > MAX_TOKEN_LIST_SIZE || stored_size > MAX_INPUT_FILE_SIZE)
		return (error_handler(filesize, 0, 0));
	return (done);
}

static t_code			dispatcher(t_line *line, t_tokenlst *lst)
{
	uint16_t			j;
	static t_dispatch	tab[5] =
	{
		{char_label, &token_single},
		{char_dir, &token_single},
		{char_sep, &token_single},
		{quote, &token_quote},
		{value_string, &token_str_wrapper}
	};

	j = 0;
	while (1)
	{
		if (line->str[line->index] == (char)(tab[j].type) || j == 4)
			return (tab[j].handler(tab[j].type, line, lst));
		j++;
	}
}

static t_code			process_line(t_line *line, t_tokenlst *lst)
{
	t_code	 		   	ret_code;

	line->index = 0;
	while (line->str[line->index])
		if ((ret_code = dispatcher(line, lst)) == error)
			break;
	if (ret_code == done)
		ret_code = token_single(char_eol, line, lst);
	ft_memdel((void**)&(line->str));
	return (ret_code);
}

t_code					lexer_get(const int fd)
{
	int32_t				ret;
	t_line				line;
	t_tokenlst			lst;

	ft_bzero(&lst, sizeof(t_tokenlst));
	ft_bzero(&line, sizeof(t_line));
	while ((ret = get_next_line(fd, &(line.str))) > 0)
	{
		if (process_line(&line, &lst) == error)
			return (lexer_exit(&lst, err));
		line.num++;
		if (line.num == 10) break;//debug
	}
	if (ret == -1)
		return (lexer_exit(&lst, read_crash));
	if (ret == -2)
		return (lexer_exit(&lst, read_linesize));
	debug_printtokenlst(&lst);
	//Call Lexer_Check
	return (lexer_exit(&lst, no_err)); //gnl avec -1 et null pour clean le static
}