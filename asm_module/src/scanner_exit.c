/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:58:05 by hbally            #+#    #+#             */
/*   Updated: 2019/04/22 15:58:06 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "types.h"
#include "errors.h"
#include "libft.h"

void			token_del(t_token *token, t_tokenlst *lst)
{
	if (token->value)
		ft_memdel((void**)&(token->value));
	if (token->previous)
		token->previous->next = token->next;
	if (token->next)
		token->next->previous = token->previous;
	if (token == lst->end)
		lst->end = token->previous;
	if (token == lst->start)
		lst->start = token->next;
	token->next = NULL;
	token->previous = NULL;
	ft_memdel((void**)&(token));
}

t_code			scanner_exit(t_tokenlst *lst, t_errors code)
{
	if (lst)
	{
		lst->now = NULL;
		while (lst->start)
		{
			if (lst->start->value)
				ft_memdel((void**)&(lst->start->value));
			token_del(lst->start, lst);
		}
	}
	get_next_line(-1, 0);
	if (code == scanner_error)
		return (error);
	else if (code != no_error)
		return (error_handler(code, 0, 0));
	else
		return (done);
}
