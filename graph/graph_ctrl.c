/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:05:07 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/09 14:29:49 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	create_controls_win(t_graph *g)
{
	g->ctrl_win = create_new_win(CTRL_ROW, CTRL_COL, 0, ARENA_ROW);
	mvwprintw(g->ctrl_win, 0, (CTRL_COL / 2) - 8, " - CONTROLS - ");
	mvwprintw(g->ctrl_win, 1, 2, "%-25s%-10d%s",
			"FRAME PER SECOND:", g->fps, "[ << 'o'] ['p' >> ]");
	mvwprintw(g->ctrl_win, 2, 2, "%-25s%-10d%s",
			"LAPS PER FRAME:", g->laps, "[ << 'k'] ['l' >> ]");
	mvwprintw(g->ctrl_win, 3, 2, "%-35s%s",
			"LIST OF PROCESS:", "[ << 'n'] ['m' >> ]");
	mvwprintw(g->ctrl_win, 4, 2, "%-25s%-10s%s", "PAUSE:", "ON", "[' ']");
	mvwprintw(g->ctrl_win, 5, 2, "%-35s%s", "QUIT:", "['F1']");
	wrefresh(g->ctrl_win);
}
