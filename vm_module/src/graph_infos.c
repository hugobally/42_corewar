/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:03:13 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/09 14:22:21 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "graph.h"

void	create_infos_win(t_graph *g)
{
	g->info_win = create_new_win(INFO_ROW, INFO_COL, CTRL_COL, ARENA_ROW);
	mvwprintw(g->info_win, 0, (INFO_COL / 2) - 6, " - INFOS - ");
	mvwprintw(g->info_win, 1, 2, "%-25s%15d", "CYCLE:", 10000);
	mvwprintw(g->info_win, 2, 2, "%-25s%15d", "CYCLE_MOD:", 45);
	mvwprintw(g->info_win, 3, 2, "%-25s%15d", "CYCLE_TO_DIE:", CYCLE_TO_DIE);
	wrefresh(g->info_win);
}
