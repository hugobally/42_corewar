/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:16:51 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/26 15:49:10 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	refresh_all_wins(t_core *c)
{
	wrefresh(c->graph->ctrl_win);
	wrefresh(c->graph->pro_win);
	wrefresh(c->graph->reg_win);
	wrefresh(c->graph->info_win);
	if (!(c->loop % c->graph->laps))
	{
		wrefresh(c->graph->arena_win);
		wrefresh(c->graph->champ_win);
	}
}

WINDOW	*create_new_win(int h, int w, int x, int y)
{
	WINDOW	*win;

	win = newwin(h, w, y, x);
	box(win, 0, 0);
	return (win);
}

void	get_col_row(int addr, int *col, int *row)
{
	addr += 1;
	*row = addr / 64;
	*col = (addr % 64) - 1;
	if (*col == -1)
	{
		*col = 63;
		*row -= 1;
	}
	*col = *col + 2 + (*col * 2);
	*row += 1;
}
