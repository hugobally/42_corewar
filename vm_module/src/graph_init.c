/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:16:49 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/10 12:32:09 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "corewar.h"
#include "libft.h"
#include "graph.h"
#include "op.h"

int		init_ncurse(void)
{
	initscr();
	curs_set(0);
	if(has_colors() == FALSE)
		return(no_color);
	start_color();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	refresh();
	use_default_colors();
	init_pair(CHAMP1, COLOR_RED, -1);
	init_pair(CHAMP2, COLOR_BLUE, -1);
	init_pair(CHAMP3, COLOR_GREEN, -1);
	init_pair(CHAMP4, COLOR_YELLOW, -1);
	init_pair(P1, COLOR_RED, COLOR_WHITE);
	init_pair(P2, COLOR_BLUE, COLOR_WHITE);
	init_pair(P3, COLOR_GREEN, COLOR_WHITE);
	init_pair(P4, COLOR_YELLOW, COLOR_WHITE);
}


int		make_graph(t_core *c)
{
	int		err;
	t_graph	*g;


	if (err = init_ncurse())
		return (err);
	c->graph = init_graph();
	if (!c->graph)
		return (falloc);
	/*int i = 0;
	while (i++ < MEM_SIZE)
		write_on_arena(i, i, 2, g);
	add_procces_to_arena(1, g);
	move_proccess_on_arena(1, 56, g);
	while((ch = getch()) != KEY_F(1))
	{
	}
	free_graph(g);
	endwin();*/
	return (0);
}
