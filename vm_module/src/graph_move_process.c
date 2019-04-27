/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_move_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:57:40 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/27 14:27:29 by tlesven          ###   ########.fr       */
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
	else if (c > CHAMP4)
		return ;
	else
		mvwchgat(g->arena_win, row, col, 2, A_NORMAL, c + 4, NULL);
}

t_bool	is_another_process(int addr, t_process *p)
{
	t_process	*tmp;
	int			i;

	i = 0;
	tmp = p;
	while (tmp)
	{
		if (tmp->pc == (unsigned)addr)
			i++;
		if (i == 2)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	remove_procces_to_arena(int addr, t_core *c)
{
	int		col;
	int		row;
	chtype	ch;

	if (is_another_process(addr, c->process))
		return ;
	get_col_row(addr, &col, &row);
	ch = (mvwinch(c->graph->arena_win, row, col) & A_COLOR) / 256;
	if (ch == P)
		mvwchgat(c->graph->arena_win, row, col, 2, A_NORMAL, EMPTY, NULL);
	else if (ch == EMPTY || ch < P1)
		return ;
	else
		mvwchgat(c->graph->arena_win, row, col, 2, A_NORMAL, ch - 4, NULL);
}

void	move_proccess_on_arena(int addr, int new_addr, t_core *c)
{
	remove_procces_to_arena(addr, c);
	add_procces_to_arena(new_addr, c->graph);
}
