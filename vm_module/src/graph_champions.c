/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_champions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:43:59 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/24 16:07:35 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	print_champions(t_graph *g, t_player *p)
{
	t_player	*tmp;
	int			i;

	i = 1;
	tmp = p;
	while (tmp)
	{
		wattron(g->champ_win, COLOR_PAIR(tmp->p + PLAYER_DIFF));
		mvwprintw(g->champ_win, i, 2, "%-20s%-30.30s%10s",
			p->head.prog_name, p->head.comment,
			p->is_alive ? "ALIVE" : "DEAD");
		tmp = tmp->next;
		i++;
	}
}

void	create_champions_win(t_graph *g, t_player *p)
{
	g->champ_win = create_new_win(CHAMP_ROW, CHAMP_COL,
			INFO_COL + CTRL_COL, ARENA_ROW);
	mvwprintw(g->champ_win, 0, (CHAMP_COL / 2) - 9, " - CHAMPIONS - ");
	print_champions(g, p);
}
