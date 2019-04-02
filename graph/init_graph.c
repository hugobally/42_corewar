/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 14:29:22 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/02 18:09:45 by tlesven          ###   ########.fr       */
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
	start_color();
	use_default_colors();
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
	init_pair(1, COLOR_BLACK, -1);
	wattron(g->arena_win, COLOR_PAIR(1));
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
	wattroff(g->arena_win, COLOR_PAIR(1));
	//wattroff(g->arena_win, ,COLOR_PAIR(1));
	wrefresh(g->arena_win);
}

void	create_controls_win(t_graph *g)
{
	g->ctrl_win = create_new_win(CTRL_ROW, CTRL_COL, 0, ARENA_ROW);
	mvwprintw(g->ctrl_win, 0, (CTRL_COL / 2) - 8," - CONTROLS - ");
	mvwprintw(g->ctrl_win, 1, 2,"%-25s%-10d%s", 
			"FRAME PER SECOND:", g->fps, "[ << 'o'] ['p' >> ]");
	mvwprintw(g->ctrl_win, 2, 2, "%-25s%-10d%s",
			"LAPS PER FRAME:", g->laps, "[ << 'k'] ['l' >> ]");
	mvwprintw(g->ctrl_win, 3, 2, "%-35s%s",
			"LIST OF PROCESS:",  "[ << 'n'] ['m' >> ]");
	mvwprintw(g->ctrl_win, 4, 2, "%-25s%-10s%s","PAUSE:", "ON", "[' ']");
	mvwprintw(g->ctrl_win, 5, 2, "%-35s%s","QUIT:", "['F1']");
	wrefresh(g->ctrl_win);
}
void	create_infos_win(t_graph *g)
{
	g->info_win = create_new_win(INFO_ROW, INFO_COL, CTRL_COL, ARENA_ROW);
	mvwprintw(g->info_win, 0, (INFO_COL / 2) - 6," - INFOS - ");
	mvwprintw(g->info_win, 1, 2, "%-25s%15d", "CYCLE:", 10000);
	mvwprintw(g->info_win, 2, 2, "%-25s%15d", "CYCLE_MOD:", 45);
	mvwprintw(g->info_win, 3, 2, "%-25s%15d", "CYCLE_TO_DIE:", CYCLE_TO_DIE);
	wrefresh(g->info_win);
}

void	create_process_win(t_graph *g)
{
	g->pro_win = create_new_win(PRO_ROW, PRO_COL, ARENA_COL, 0);
	mvwprintw(g->pro_win, 0, (PRO_COL / 2) - 7, " - PROCESS - ");
	mvwprintw(g->pro_win, 1, 2, "#%-5d%-2dx%-2d [%c][%c]%5s in%4d laps.",
			1, 33,25,'L','C',"zjmp",14);
	mvwprintw(g->pro_win, 2, 2, "#%-5d%-2dx%-2d [%c][%c]%5s in%4d laps.",
			2, 1,25,'L','C',"zjmp",14);
	wrefresh(g->pro_win);
}

void	create_registers_win(t_graph *g)
{
	g->reg_win = create_new_win(REG_ROW, REG_COL, ARENA_COL, PRO_ROW);
	mvwprintw(g->reg_win, 0, (REG_COL / 2) - 9, " - REGISTERS - ");
	mvwprintw(g->reg_win, 1, 2, "REGISTER [0] = %5d", -1);
	mvwprintw(g->reg_win, 3, 2, "REGISTER [1] = %5d", 0);
	mvwprintw(g->reg_win, 5, 2, "REGISTER [2] = %5d", 568);
	mvwprintw(g->reg_win, 7, 2, "REGISTER [3] = %5d", 485);
	mvwprintw(g->reg_win, 9, 2, "REGISTER [4] = %5d", 245);
	mvwprintw(g->reg_win, 11, 2, "REGISTER [5] = %5d", 1);
	mvwprintw(g->reg_win, 13, 2, "REGISTER [6] = %5d", 0);
	mvwprintw(g->reg_win, 15, 2, "REGISTER [7] = %5d", 0);
	mvwprintw(g->reg_win, 1, 30, "REGISTER [8] = %5d", -1);
	mvwprintw(g->reg_win, 3, 30, "REGISTER [9] = %5d", 0);
	mvwprintw(g->reg_win, 5, 30, "REGISTER [10] = %5d", 568);
	mvwprintw(g->reg_win, 7, 30, "REGISTER [11] = %5d", 485);
	mvwprintw(g->reg_win, 9, 30, "REGISTER [12] = %5d", 245);
	mvwprintw(g->reg_win, 11, 30, "REGISTER [13] = %5d", 1);
	mvwprintw(g->reg_win, 13, 30, "REGISTER [14] = %5d", 0);
	mvwprintw(g->reg_win, 15, 30, "REGISTER [15] = %5d", 0);
	wrefresh(g->reg_win);
}

int		main(void)
{
	int		ch;
	t_graph	*g;

	init_ncurse();
	g = init_graph();
	create_arena_win(g);
	create_controls_win(g);
	create_infos_win(g);
	create_process_win(g);
	create_registers_win(g);
	while((ch = getch()) != KEY_F(1))
	{

	}
	free_graph(g);
	endwin();
	return (0);
}
