/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:01:27 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/27 14:28:39 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "graph.h"

void	erase_process(t_core *c)
{
	werase(c->graph->pro_win);
	create_process_win(c);
}

void	print_process(t_core *c)
{
	t_process	*tmp;
	int			i;
	int			col;
	int			row;
	const char	*instr[18] = {"error", "live", "load", "store", "add",
		"sub", "and", "or", "xor", "zjmp", "ldi", "sti", "fork", "lid",
		"lldi", "lfork", "aff"};

	i = 1;
	tmp = c->process;
	while (tmp && i < 48)
	{
		get_col_row(tmp->pc, &col, &row);
		if (tmp == c->graph->selected_proc)
			wattron(c->graph->pro_win, COLOR_PAIR(tmp->player +
						PLAYER_DIFF + 4));
		else
			wattron(c->graph->pro_win, COLOR_PAIR(tmp->player + PLAYER_DIFF));
		mvwprintw(c->graph->pro_win, i, 2,
			"#%-5d%-2.2dx%-2.2d [%c][%c]%7s in%4d laps.", i, row - 1,
			(col - 2) / 3, tmp->is_alive ? 'L' : ' ', tmp->carry ? 'C' : ' ',
			instr[tmp->instruction], tmp->remaining_cycles);
		tmp = tmp->next;
		++i;
	}
}

void	create_process_win(t_core *c)
{
	c->graph->pro_win = create_new_win(PRO_ROW, PRO_COL, ARENA_COL, 0);
	mvwprintw(c->graph->pro_win, 0, (PRO_COL / 2) - 7, " - PROCESS - ");
	print_process(c);
}
