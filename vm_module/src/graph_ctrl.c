/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:05:07 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/29 11:07:57 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "graph.h"

extern pthread_cond_t g_condition;
extern pthread_cond_t g_condition2;
extern pthread_mutex_t g_mutex;

void	process_select_down(t_core *c)
{
	if (!c->graph->pause)
	{
		c->graph->proc_aff = true;
		pthread_mutex_lock(&g_mutex);
		pthread_cond_wait(&g_condition, &g_mutex);
	}
	c->graph->selected_proc = c->graph->selected_proc->previous;
	print_process(c);
	print_registers(c->graph);
	wrefresh(c->graph->reg_win);
	wrefresh(c->graph->pro_win);
	if (!c->graph->pause)
	{
		pthread_cond_signal(&g_condition2);
		pthread_mutex_unlock(&g_mutex);
		c->graph->proc_aff = false;
	}
}

void	process_select_up(t_core *c)
{
	if (!c->graph->pause)
	{
		c->graph->proc_aff = true;
		pthread_mutex_lock(&g_mutex);
		pthread_cond_wait(&g_condition, &g_mutex);
	}
	c->graph->selected_proc = c->graph->selected_proc->next;
	print_process(c);
	print_registers(c->graph);
	wrefresh(c->graph->reg_win);
	wrefresh(c->graph->pro_win);
	if (!c->graph->pause)
	{
		pthread_cond_signal(&g_condition2);
		pthread_mutex_unlock(&g_mutex);
	}
	c->graph->proc_aff = false;
}

int		controls(t_core *c)
{
	int		ch;

	ch = getch();
	if (ch == ERR)
		return (0);
	else if (ch == 'q')
		return (1);
	else if (ch == 'o')
		down_fps(c->graph);
	else if (ch == 'p')
		up_fps(c->graph);
	else if (ch == 'k')
		down_laps(c->graph);
	else if (ch == 'l')
		up_laps(c->graph);
	else if (ch == ' ')
		pause_game(c->graph);
	else if (ch == 'n' && c->graph->selected_proc->previous)
		process_select_down(c);
	else if (ch == 'm' && c->graph->selected_proc->next)
		process_select_up(c);
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
