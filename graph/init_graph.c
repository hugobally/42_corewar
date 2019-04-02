/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 14:29:22 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/02 13:57:12 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"
#include "op.h"

WINDOW	*create_new_win(int h, int w, int x, int y)
{
	WINDOW	*win;

	win = newwin(h, w, y, x);
	box(win, 0 , 0);
	wrefresh(win);
	return (win);
}

void	init_ncurse(void)
{
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	refresh();
	//CHEKC COLOR AND EXIT
}

void	create_arena_win(t_graph *g)
{
	int		i;
	int		row;
	int		col;

	i = 0;
	col = 2;
	row = 1;
	g->arena_win = create_new_win(ARENA_ROW, ARENA_COL, 0, 0);
	mvwprintw(g->arena_win, 0, (ARENA_COL / 2) - 11, "%s", " - ARENA - ");
	while(i < MEM_SIZE)
	{
		mvwprintw(g->arena_win,row,col, "%s", "00 ");
		col += 3;
		if (col > 192)
		{
			row += 1;
			col = 2;
		}
		i++;
	}
	wrefresh(g->arena_win);
}

void	create_control_win(t_graph *g)
{
	g->ctrl_win = create_new_win(CTRL_ROW, CTRL_COL, 0, ARENA_ROW);
	mvwprintw(g->ctrl_win, 0, (CTRL_COL / 2) - 13," - CONTROL - ");
	mvwprintw(g->ctrl_win, 1, 1, "FRAME PER SECOND: %10d [ << 'o'] ['p' >> ]", 32);
	mvwprintw(g->ctrl_win, 2, 1, "LAPS PER FRAME: %10d [ << 'o'] ['p' >> ]", 32);
	mvwprintw(g->ctrl_win, 3, 1, "LIST OF PROCESS: %10d [ << 'o'] ['p' >> ]", 32);
	mvwprintw(g->ctrl_win, 4, 1, "PAUSE: %10d [ << 'o'] ['p' >> ]", 32);
	mvwprintw(g->ctrl_win, 5, 1, "%-10s%s","QUIT", "['F1']");
	wrefresh(g->ctrl_win);
}

int		main(void)
{
	int		ch;
	t_graph	*g;

	init_ncurse();
	g = init_graph();
	create_arena_win(g);
	create_control_win(g);
	while((ch = getch()) != KEY_F(1))
	{

	}
	free_graph(g);
	endwin();
	return (0);
}
