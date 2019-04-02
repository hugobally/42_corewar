/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:32:49 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/02 15:05:50 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "graph.h"

t_graph		*init_graph(void)
{
	t_graph		*g;

	g = (t_graph*)ft_memalloc(sizeof(t_graph));
	g->fps = 32;
	g->laps = 1;
	g->pause = 1;
	return (g);
}

void		free_graph(t_graph *g)
{
	ft_memdel((void*)&g);
}
