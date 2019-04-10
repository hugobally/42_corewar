/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:47:56 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/10 16:57:37 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	make_win(t_core *c)
{
	create_arena_win(c->graph);
	create_controls_win(c->graph);
	create_infos_win(c->graph, c);
	create_process_win(c->graph, c->process);
	create_registers_win(c->graph);
	create_champions_win(c->graph, c->players);
/*	while(c->process)
	{
		ft_printf("process->p :%d", c->process->player);
		c->process = c->process->next;
	}*/
}
