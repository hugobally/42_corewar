/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_move_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:57:40 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/24 14:59:08 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	add_procces_to_arena(int addr, t_graph *g)
{
	int		col;
	int		row;
	chtype	c;

	get_col_row(addr, &col, &row);
	c = (mvwinch(g->arena_win, row, col) & A_COLOR) / 256;
	if (c == EMPTY)
		mvwchgat(g->arena_win, row, col, 2, A_NORMAL, P, NULL);
	else
		mvwchgat(g->arena_win, row, col, 2, A_NORMAL, c + 4, NULL);
}

void	remove_procces_to_arena(int addr, t_graph *g)
{
	int		col;
	int		row;
	chtype	c;

	get_col_row(addr, &col, &row);
	c = (mvwinch(g->arena_win, row, col) & A_COLOR) / 256;
	if (c == P)
		mvwchgat(g->arena_win, row, col, 2, A_NORMAL, EMPTY, NULL);
	else
		mvwchgat(g->arena_win, row, col, 2, A_NORMAL, c - 4, NULL);
}

void	move_proccess_on_arena(int addr, int new_addr, t_graph *g)
{
	remove_procces_to_arena(addr, g);
	add_procces_to_arena(new_addr, g);
}
