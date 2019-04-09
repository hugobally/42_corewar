/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:16:25 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/09 16:16:27 by tlesven          ###   ########.fr       */
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
	create_arena_win(g);
	create_controls_win(g);
	create_infos_win(g);
	create_process_win(g);
	create_registers_win(g);
	create_champions_win(g);
	return (g);
}

void		free_graph(t_graph *g)
{
	ft_memdel((void*)&g);
}
