/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:07:36 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/10 14:20:22 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	write_on_arena(int addr, int v, int champ, t_graph *g)
{
	int		col;
	int		row;

	get_col_row(addr, &col, &row);
	wattron(g->arena_win, COLOR_PAIR(champ));
	mvwprintw(g->arena_win, row, col, "%.2hhx", v);
	wattroff(g->arena_win, COLOR_PAIR(champ));
	wrefresh(g->arena_win);
}

/*
 * int mvwchgat(WINDOW *win, int y, int x, int n, attr_t attr,
 *              short color, const void *opts);
 * chtype mvwinch(WINDOW *win, int y, int x);
 */

void	add_procces_to_arena(int addr, t_graph *g)
{
	int		col;
	int		row;
	chtype	c;

	get_col_row(addr, &col, &row);
	c = (mvwinch(g->arena_win, row, col) & A_COLOR) / 256;
	mvwchgat(g->arena_win, row, col, 2, A_NORMAL, c + 4, NULL);
	wrefresh(g->arena_win);
}

void	remove_procces_to_arena(int addr, t_graph *g)
{
	int		col;
	int		row;
	chtype	c;

	get_col_row(addr, &col, &row);
	c = (mvwinch(g->arena_win, row, col) & A_COLOR) / 256;
	mvwchgat(g->arena_win, row, col, 2, A_NORMAL, c - 4, NULL);
	wrefresh(g->arena_win);
}

void	move_proccess_on_arena(int addr, int new_addr, t_graph *g)
{
	remove_procces_to_arena(addr, g);
	add_procces_to_arena(new_addr, g);
}

void	create_arena_win(t_graph *g)
{
	int		i;
	int		row;
	int		col;

	i = 0;
	col = 2;
	row = 1;
	g->arena_win = create_new_win(ARENA_ROW, ARENA_COL, 0, 0);
	mvwprintw(g->arena_win, 0, (ARENA_COL / 2) - 11, "%s", " - ARENA - ");
	init_pair(EMPTY, COLOR_BLACK, -1);
	wattron(g->arena_win, COLOR_PAIR(EMPTY));
	while (i < MEM_SIZE)
	{
		mvwprintw(g->arena_win, row, col, "%s", "00 ");
		col += 3;
		if (col > 192)
		{
			row += 1;
			col = 2;
		}
		i++;
	}
	wattroff(g->arena_win, COLOR_PAIR(EMPTY));
	wrefresh(g->arena_win);
}
