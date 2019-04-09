/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:01:27 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/09 14:25:29 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	create_process_win(t_graph *g)
{
	g->pro_win = create_new_win(PRO_ROW, PRO_COL, ARENA_COL, 0);
	mvwprintw(g->pro_win, 0, (PRO_COL / 2) - 7, " - PROCESS - ");
	wattron(g->pro_win, COLOR_PAIR(CHAMP1));
	mvwprintw(g->pro_win, 1, 2, "#%-5d%-2.2dx%-2.2d [%c][%c]%5s in%4d laps.",
			1, 33, 25, 'L', 'C', "zjmp", 14);
	wattron(g->pro_win, COLOR_PAIR(CHAMP2));
	mvwprintw(g->pro_win, 2, 2, "#%-5d%-2.2dx%-2.2d [%c][%c]%5s in%4d laps.",
			2, 1, 25, 'L', 'C', "zjmp", 14);
	wattron(g->pro_win, COLOR_PAIR(CHAMP3));
	mvwprintw(g->pro_win, 3, 2, "#%-5d%-2.2dx%-2.2d [%c][%c]%5s in%4d laps.",
			3, 1, 25, 'L', 'C', "zjmp", 14);
	wattron(g->pro_win, COLOR_PAIR(CHAMP4));
	mvwprintw(g->pro_win, 4, 2, "#%-5d%-2.2dx%-2.2d [%c][%c]%5s in%4d laps.",
			4, 1, 25, 'L', 'C', "zjmp", 14);
	wrefresh(g->pro_win);
}
