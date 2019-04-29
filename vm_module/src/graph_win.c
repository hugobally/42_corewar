/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:47:56 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/29 14:26:16 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	make_win(t_core *c)
{
	create_arena_win(c);
	create_controls_win(c->graph);
	create_infos_win(c->graph, c);
	create_process_win(c);
	create_registers_win(c->graph);
	create_champions_win(c);
	refresh_all_wins(c);
}
