/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:07:36 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/23 15:36:07 by tlesven          ###   ########.fr       */
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
//	wrefresh(g->arena_win);
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
	//if (g->selected_proc->pc == (unsigned)addr)
	//	mvwchgat(g->arena_win, row, col, 2, A_NORMAL, PS, NULL);
	if (c == EMPTY)
		mvwchgat(g->arena_win, row, col, 2, A_NORMAL, P, NULL);
	else
		mvwchgat(g->arena_win, row, col, 2, A_NORMAL, c + 4, NULL);
//	wrefresh(g->arena_win);
}

void	remove_procces_to_arena(int addr, t_graph *g)
{
	int		col;
	int		row;
	chtype	c;

	get_col_row(addr, &col, &row);
	c = (mvwinch(g->arena_win, row, col) & A_COLOR) / 256;
	//if (g->selected_proc->pc == (unsigned)addr)
	//	mvwchgat(g->arena_win, row, col, 2, A_NORMAL, g->selected_proc->player + PLAYER_DIFF, NULL);
	if (c == P)
		mvwchgat(g->arena_win, row, col, 2, A_NORMAL, EMPTY, NULL);
	else
		mvwchgat(g->arena_win, row, col, 2, A_NORMAL, c - 4, NULL);
//	wrefresh(g->arena_win);
}

void	move_proccess_on_arena(int addr, int new_addr, t_graph *g)
{
	//t_bool is_select;

	//is_select = FALSE;
	//if ((unsigned)addr == g->selected_proc->pc)
	//	is_select = TRUE;
	remove_procces_to_arena(addr, g);
	add_procces_to_arena(new_addr, g);
}

void	add_proc_champ(t_graph *g, t_player *p)
{
	unsigned int	i;
	t_player		*tmp;

	tmp = p;
	while (tmp)
	{
		i = 0;
		while(i < p->head.prog_size)
		{
			write_on_arena(tmp->orig_pc + i, tmp->proc[i], tmp->p, g);
			if (i == 0)
				add_procces_to_arena(tmp->orig_pc, g);
			i++;
		}
		tmp = tmp->next;
	}
}

void	create_arena_win(t_graph *g, t_player *p)
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
	add_proc_champ(g, p);
//	wrefresh(g->arena_win);
}
