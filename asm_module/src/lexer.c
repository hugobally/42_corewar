/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:08:39 by hbally            #+#    #+#             */
/*   Updated: 2019/03/28 19:30:27 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libcorewar.h"
#include "types.h"

t_code					token_add(t_tokenlst *lst, t_token template)
{
	t_token		*new;

	if (!(new = (t_token*)ft_memalloc(sizeof(t_token))))
		return (error_handler(malloc));
	new->value = value;
	new->type = type;
	new->line_num = line_num;
	if (!lst->start)
		lst->start = new;
	if (lst->end)
		lst->end->next = new;
	lst->end = new;
}

static t_code			dispatcher(static char *line, uint64_t pos,
									int16_t *index, t_tokenlst *lst)
{
	static t_dispatch	tab[6] =
	{
		{COMMENT_CHAR, &token_comment},
		{LABEL_CHAR, &token_single},
		{DIRECT_CHAR, &token_single},
		{SEPARATOR_CHAR, &token_single},
		{QUOTE_CHAR, &token_single},
		{0, &token_string}
	}
	uint16_t			j;

	j = 0;
	while (1)
	{
		if (line[*index] == tab[j].character || j == 5)
			return (tab[j].handler(line, pos, index, lst));
		j++;
	}
}

static t_code			process_line(static char *line, uint64_t pos,
			 	   					t_tokenlst *lst)
{
	t_code	 		   	ret_code;
	uint16_t 	   		index;

	index = 0;
	while (line[index])
		if ((ret_code = dispatcher(*line, line_num, &index, lst)) == error)
			break;
	ft_memdel((void**)&line);
	if (ret_code == done)
		token_newline(pos, &index, lst);
	return (ret_code);
}

/*
** Lexer Pass 1 : Acquire tokens as either
** 					1) special single char
**					2) anything else in between
**				  + get info about whitespace around each token
*/

t_code					lexer_1(static int fd)
{
	int32_t				ret;
	char				*line;
	uint64_t			line_num;
	t_tokenlst			lst;

	line_num = 0;
	ft_bzero(&lst, sizeof(t_tokenlst));
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (process_line(line, line_num, &lst) == error)
			return (error);
		line_num++;
	}
	if (ret == -1)
		return (lexer_exit(&lst, read)); //gnl avec -1 et null pour clean le statichhh
	//call lexer_pass2
	return (lexer_exit(&lst, no_error)); //gnl avec -1 et null pour clean le static
}
