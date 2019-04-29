/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:03:13 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/29 14:59:37 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	print_infos(t_core *c)
{
	mvwprintw(c->graph->info_win, 1, 2, "%-25s%15d", "CYCLE:", c->loop + 1);
	mvwprintw(c->graph->info_win, 2, 2, "%-25s%15d", "CYCLE_MOD:",
			c->cycles);
	mvwprintw(c->graph->info_win, 3, 2, "%-25s%15d", "CYCLE_TO_DIE:",
			c->max_cycle_to_die);
}

void	create_infos_win(t_graph *g, t_core *c)
{
	g->info_win = create_new_win(INFO_ROW, INFO_COL, CTRL_COL, ARENA_ROW);
	mvwprintw(g->info_win, 0, (INFO_COL / 2) - 6, " - INFOS - ");
	print_infos(c);
}
