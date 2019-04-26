/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:05:07 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/26 15:47:54 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	controls2(t_core *c, int ch)
{
	if (ch == 'n' && c->graph->selected_proc->previous)
	{
		c->graph->selected_proc = c->graph->selected_proc->previous;
		print_process(c);
		print_registers(c->graph);
		wrefresh(c->graph->reg_win);
		wrefresh(c->graph->pro_win);
	}
	else if (ch == 'm' && c->graph->selected_proc->next)
	{
		c->graph->selected_proc = c->graph->selected_proc->next;
		print_process(c);
		print_registers(c->graph);
		wrefresh(c->graph->reg_win);
		wrefresh(c->graph->pro_win);
	}
}

int		controls(t_core *c)
{
	int		ch;
	t_graph *g = c->graph; //ARETIRER

	ch = getch();
	if (ch == ERR)
		return (0);
	else if (ch == 'q')
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
		pause_game(g);
	controls2(c, ch);
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
	mvwprintw(g->ctrl_win, 5, 2, "%-35s%s", "QUIT:", "['q']");
}
