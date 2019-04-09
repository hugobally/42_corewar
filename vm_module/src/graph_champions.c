/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_champions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:43:59 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/09 14:24:12 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	create_champions_win(t_graph *g)
{
	g->champ_win = create_new_win(CHAMP_ROW, CHAMP_COL,
			INFO_COL + CTRL_COL, ARENA_ROW);
	mvwprintw(g->champ_win, 0, (CHAMP_COL / 2) - 9, " - CHAMPIONS - ");
	wattron(g->champ_win, COLOR_PAIR(CHAMP1));
	mvwprintw(g->champ_win, 1, 2, "%-20s%-30.30s%10s",
			"Nom du champion", "je suis la description", "ALIVE");
	wattron(g->champ_win, COLOR_PAIR(CHAMP2));
	mvwprintw(g->champ_win, 2, 2, "%-20s%-30.30s%10s",
			"Coucou", "je sais dire bonjour dans 58 langues :D", "ALIVE");
	wattron(g->champ_win, COLOR_PAIR(CHAMP3));
	mvwprintw(g->champ_win, 3, 2, "%-20s%-30.30s%10s",
			"Lolol", "haha", "WINNNER");
	wattron(g->champ_win, COLOR_PAIR(CHAMP4));
	mvwprintw(g->champ_win, 4, 2, "%-20s%-30.30s%10s",
			"MAIS", "BOUHOUHOU", "DEAD");
	wrefresh(g->champ_win);
}
