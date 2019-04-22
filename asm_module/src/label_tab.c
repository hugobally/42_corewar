/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbally <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:54:11 by hbally            #+#    #+#             */
/*   Updated: 2019/04/22 15:55:20 by hbally           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"
#include "asm.h"

/*
** Access
*/

t_label				*label_tab_fetch(t_token *token, t_label **label_tab)
{
	uint32_t		index;

	index = 0;
	if (!*label_tab)
		return (NULL);
	while ((*label_tab)[index].token)
	{
		if (!ft_strcmp(token->value, (*label_tab)[index].token->value))
			return (&((*label_tab)[index]));
		index++;
	}
	return (NULL);
}

/*
** Buid
*/

static uint32_t		get_tabsize(t_tokenlst *lst)
{
	t_token			*node;
	uint32_t		tabsize;

	tabsize = 0;
	node = lst->start;
	while (node)
	{
		if (node->type == label)
			tabsize++;
		node = node->next;
	}
	return (tabsize);
}

static void			check_duplicate_label(t_token *token, t_label **label_tab)
{
	uint32_t		index;

	index = 0;
	while ((*label_tab)[index].token)
	{
		if (!ft_strcmp(token->value, (*label_tab)[index].token->value))
			error_handler(label_duplicate, token, 0);
		index++;
	}
}

t_code				build_label_tab(t_tokenlst *lst, t_label **label_tab)
{
	t_token			*node;
	uint32_t		size;
	uint32_t		index;

	if (!(size = get_tabsize(lst)))
		return (done);
	if (!(*label_tab = (t_label*)ft_memalloc((size + 1u) * sizeof(t_label))))
		return (error_handler(malloc, 0, 0));
	index = 0;
	node = lst->start;
	while (node)
	{
		if (node->type == label)
		{
			check_duplicate_label(node, label_tab);
			(*label_tab)[index].token = node;
			index++;
		}
		node = node->next;
	}
	return (done);
}
