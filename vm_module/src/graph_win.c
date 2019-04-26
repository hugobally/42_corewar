/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:47:56 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/26 13:33:31 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	make_win(t_core *c)
{
	create_arena_win(c);
	create_controls_win(c->graph);
	create_infos_win(c->graph, c);
	create_process_win(c->graph, c->process);
	create_registers_win(c->graph);
	create_champions_win(c->graph, c->players);
}
