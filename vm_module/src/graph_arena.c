/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:07:36 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/26 14:16:12 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	write_on_arena(int addr, int v, int champ, t_graph *g)
{
	int		col;
	int		row;

	get_col_row(addr, &col, &row);
	wattron(g->arena_win, COLOR_PAIR(champ + PLAYER_DIFF));
	mvwprintw(g->arena_win, row, col, "%.2hhx", v);
	wattroff(g->arena_win, COLOR_PAIR(champ + PLAYER_DIFF));
}

void	add_proc_champ(t_core *c)
{
	unsigned int	i;
	t_player		*tmp;

	tmp = c->players;
	while (tmp)
	{
		i = 0;
		while (i < tmp->head.prog_size)
		{
			write_on_arena(tmp->orig_pc + i, tmp->proc[i], tmp->p, c->graph);
			if (i == 0)
				add_procces_to_arena(tmp->orig_pc, c->graph);
			i++;
		}
		tmp = tmp->next;
	}
}

void	create_arena_win(t_core *c)
{
	int		i;
	int		row;
	int		col;

	i = 0;
	col = 2;
	row = 1;
	c->graph->arena_win = create_new_win(ARENA_ROW, ARENA_COL, 0, 0);
	mvwprintw(c->graph->arena_win, 0, (ARENA_COL / 2) - 11,
			"%s", " - ARENA - ");
	init_pair(EMPTY, COLOR_BLACK, -1);
	wattron(c->graph->arena_win, COLOR_PAIR(EMPTY));
	while (i < MEM_SIZE)
	{
		mvwprintw(c->graph->arena_win, row, col, "%s", "00 ");
		col += 3;
		if (col > 192)
		{
			row += 1;
			col = 2;
		}
		i++;
	}
	wattroff(c->graph->arena_win, COLOR_PAIR(EMPTY));
	add_proc_champ(c);
}
