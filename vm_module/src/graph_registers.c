/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_registers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:56:55 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/16 12:02:59 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	print_registers(t_graph *g)
{
	
	mvwprintw(g->reg_win, 1, 2, "REGISTER [0] = %5d", g->selected_proc->regs[0]);
	mvwprintw(g->reg_win, 3, 2, "REGISTER [1] = %5d", g->selected_proc->regs[1]);
	mvwprintw(g->reg_win, 5, 2, "REGISTER [2] = %5d", g->selected_proc->regs[2]);
	mvwprintw(g->reg_win, 7, 2, "REGISTER [3] = %5d", g->selected_proc->regs[3]);
	mvwprintw(g->reg_win, 9, 2, "REGISTER [4] = %5d", g->selected_proc->regs[4]);
	mvwprintw(g->reg_win, 11, 2, "REGISTER [5] = %5d", g->selected_proc->regs[5]);
	mvwprintw(g->reg_win, 13, 2, "REGISTER [6] = %5d", g->selected_proc->regs[6]);
	mvwprintw(g->reg_win, 15, 2, "REGISTER [7] = %5d", g->selected_proc->regs[7]);
	mvwprintw(g->reg_win, 1, 30, "REGISTER [8] = %5d", g->selected_proc->regs[8]);
	mvwprintw(g->reg_win, 3, 30, "REGISTER [9] = %5d", g->selected_proc->regs[9]);
	mvwprintw(g->reg_win, 5, 30, "REGISTER [10] = %5d", g->selected_proc->regs[10]);
	mvwprintw(g->reg_win, 7, 30, "REGISTER [11] = %5d", g->selected_proc->regs[11]);
	mvwprintw(g->reg_win, 9, 30, "REGISTER [12] = %5d", g->selected_proc->regs[12]);
	mvwprintw(g->reg_win, 11, 30, "REGISTER [13] = %5d", g->selected_proc->regs[13]);
	mvwprintw(g->reg_win, 13, 30, "REGISTER [14] = %5d", g->selected_proc->regs[14]);
	mvwprintw(g->reg_win, 15, 30, "REGISTER [15] = %5d", g->selected_proc->regs[15]);
	wrefresh(g->reg_win);
}

void	create_registers_win(t_graph *g)
{
	g->reg_win = create_new_win(REG_ROW, REG_COL, ARENA_COL, PRO_ROW);
	mvwprintw(g->reg_win, 0, (REG_COL / 2) - 9, " - REGISTERS - ");
	print_registers(g);
	wrefresh(g->reg_win);
}
