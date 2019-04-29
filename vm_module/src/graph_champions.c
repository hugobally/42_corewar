/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_champions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:43:59 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/29 15:09:04 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	print_champions(t_core *c)
{
	t_player	*tmp;
	int			i;

	i = 1;
	tmp = c->players;
	while (tmp)
	{
		wattron(c->graph->champ_win, COLOR_PAIR(tmp->p + PLAYER_DIFF));
		mvwprintw(c->graph->champ_win, i, 2, "%-20.20s%-30.30s%10s",
			tmp->head.prog_name, tmp->head.comment,
			tmp->is_alive ? "ALIVE" : "DEAD");
		if (!c->process && tmp->p == c->last_live_done_by)
			mvwprintw(c->graph->champ_win, i, 2, "%-20.20s%-30.30s%10s",
			tmp->head.prog_name, tmp->head.comment,
			"WINNER");
		tmp = tmp->next;
		i++;
	}
}

void	create_champions_win(t_core *c)
{
	c->graph->champ_win = create_new_win(CHAMP_ROW, CHAMP_COL,
			INFO_COL + CTRL_COL, ARENA_ROW);
	mvwprintw(c->graph->champ_win, 0, (CHAMP_COL / 2) - 9,
			" - CHAMPIONS - ");
	print_champions(c);
}
