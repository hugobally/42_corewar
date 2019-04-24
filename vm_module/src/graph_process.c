/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:01:27 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/24 17:07:17 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "graph.h"

void	print_process(t_graph *g, t_process *p)
{
	t_process	*tmp;
	int			i;
	int			col;
	int			row;
	const char	*instr[18] = {"error", "live", "load", "store", "add",
		"sub", "and", "or", "xor", "zjmp", "ldi", "sti", "fork", "lid",
		"lldi", "lforky", "aff"};

	i = 1;
	tmp = p;
	werase(g->pro_win);
	while (tmp)
	{
		get_col_row(tmp->pc, &col, &row);
		if (tmp == g->selected_proc)
			wattron(g->pro_win, COLOR_PAIR(tmp->player + PLAYER_DIFF + 4));
		else
			wattron(g->pro_win, COLOR_PAIR(tmp->player + PLAYER_DIFF));
		mvwprintw(g->pro_win, i, 2,
			"#%-5d%-2.2dx%-2.2d [%c][%c]%7s in%4d laps.",
			i, row - 1, col - 2, tmp->is_alive ? 'L' : ' ',
			tmp->carry ? 'C' : ' ', instr[tmp->instruction],
			tmp->remaining_cycles);
		usleep(120);
		tmp = tmp->next;
		++i;
	}
}

void	create_process_win(t_graph *g, t_process *p)
{
	g->pro_win = create_new_win(PRO_ROW, PRO_COL, ARENA_COL, 0);
	mvwprintw(g->pro_win, 0, (PRO_COL / 2) - 7, " - PROCESS - ");
	print_process(g, p);
}
