/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:16:49 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/29 15:09:27 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "corewar.h"
#include "libft.h"
#include "graph.h"

int		init_ncurse(void)
{
	initscr();
	curs_set(0);
	if (has_colors() == FALSE)
		return (no_color);
	start_color();
	raw();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	noecho();
	refresh();
	use_default_colors();
	signal(SIGWINCH, NULL);
	init_pair(CHAMP1, COLOR_RED, -1);
	init_pair(CHAMP2, COLOR_BLUE, -1);
	init_pair(CHAMP3, COLOR_GREEN, -1);
	init_pair(CHAMP4, COLOR_YELLOW, -1);
	init_pair(P1, COLOR_RED, COLOR_WHITE);
	init_pair(P2, COLOR_BLUE, COLOR_WHITE);
	init_pair(P3, COLOR_GREEN, COLOR_WHITE);
	init_pair(P4, COLOR_YELLOW, COLOR_WHITE);
	init_pair(P, COLOR_BLACK, COLOR_WHITE);
	init_pair(PS, COLOR_BLACK, COLOR_CYAN);
	return (0);
}

int		make_graph(t_core *c)
{
	int		err;

	if ((err = init_ncurse()))
		return (err);
	c->graph = init_graph();
	if (!c->graph)
		return (falloc);
	c->graph->selected_proc = c->process;
	return (0);
}
