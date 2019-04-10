/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:01:27 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/10 16:47:30 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	print_process(t_graph *g, t_process *p)
{
	t_process	*tmp;
	int			i;
	int			col;
	int			row;

	i = 1;
	tmp = p;
	while (tmp)
	{//CHANGER L"ACTION
		get_col_row(tmp->pc, &col, &row);
		wattron(g->pro_win, COLOR_PAIR(tmp->player + 2));
		mvwprintw(g->pro_win, i, 2, "#%-5d%-2.2dx%-2.2d [%c][%c]%5d in%4d laps.",
			i, row, col, tmp->is_alive ? 'L' : ' ', 
			tmp->carry ? 'C' : ' ', tmp->instruction, tmp->remaining_cycles);
		tmp = tmp->next;
		++i;
	}
}

void	create_process_win(t_graph *g, t_process *p)
{
	g->pro_win = create_new_win(PRO_ROW, PRO_COL, ARENA_COL, 0);
	mvwprintw(g->pro_win, 0, (PRO_COL / 2) - 7, " - PROCESS - ");
	print_process(g, p);
	wrefresh(g->pro_win);
}
