/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_ctrl_actions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:19:39 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/30 09:46:35 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	up_laps(t_graph *g)
{
	if (g->laps == 1024)
		return ;
	g->laps *= 2;
	mvwprintw(g->ctrl_win, 2, 2, "%-25s%-10d%s",
			"LAPS PER FRAME:", g->laps, "[ << 'k'] ['l' >> ]");
	wrefresh(g->ctrl_win);
}

void	down_laps(t_graph *g)
{
	if (g->laps == 1)
		return ;
	g->laps /= 2;
	mvwprintw(g->ctrl_win, 2, 2, "%-25s%-10d%s",
			"LAPS PER FRAME:", g->laps, "[ << 'k'] ['l' >> ]");
	wrefresh(g->ctrl_win);
}

void	up_fps(t_graph *g)
{
	if (g->fps == 256)
		return ;
	g->fps *= 2;
	mvwprintw(g->ctrl_win, 1, 2, "%-25s%-10d%s",
			"FRAME PER SECOND:", g->fps, "[ << 'o'] ['p' >> ]");
	wrefresh(g->ctrl_win);
}

void	down_fps(t_graph *g)
{
	if (g->fps == 1)
		return ;
	g->fps /= 2;
	mvwprintw(g->ctrl_win, 1, 2, "%-25s%-10d%s",
			"FRAME PER SECOND:", g->fps, "[ << 'o'] ['p' >> ]");
	wrefresh(g->ctrl_win);
}

void	pause_game(t_graph *g)
{
	g->pause = g->pause ? 0 : 1;
	mvwprintw(g->ctrl_win, 4, 2, "%-25s%-10s%s", "PAUSE:",
			g->pause ? "ON" : "OFF", "[' ']");
	if (g->pause)
		wrefresh(g->ctrl_win);
}
