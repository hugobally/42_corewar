/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:05:07 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/11 17:16:31 by tlesven          ###   ########.fr       */
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

void	pause(t_graph *g)
{
	g->pause = g->pause ? 0 : 1;
	mvwprintw(g->ctrl_win, 4, 2, "%-25s%-10s%s", "PAUSE:",
			g->pause ? "ON": "OFF", "[' ']");
	wrefresh(g->ctrl_win);
}

int		controls(t_graph *g)
{
	int		ch;

	ch = getch();
	if (ch == ERR)
		return (0);
	else if (ch == KEY_F(1))
		return (1);
	else if (ch == 'o')
		down_fps(g);
	else if (ch == 'p')
		up_fps(g);
	else if (ch == 'k')
		down_laps(g);
	else if (ch == 'l')
		up_laps(g);
	else if (ch == ' ')
		pause(g);
	return (0);
}

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
