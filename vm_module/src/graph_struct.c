/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:16:25 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/27 11:35:13 by tlesven          ###   ########.fr       */
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
	g->selected_proc = NULL;
	g->proc_aff = false;
	return (g);
}

void		free_graph(t_graph *g)
{
	ft_memdel((void*)&g);
}
