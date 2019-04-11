/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:16:51 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/11 14:58:11 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

WINDOW	*create_new_win(int h, int w, int x, int y)
{
	WINDOW	*win;

	win = newwin(h, w, y, x);
	box(win, 0, 0);
	wrefresh(win);
	return (win);
}

void	get_col_row(int addr, int *col, int *row)
{
	addr += 1;
	*row = addr / 64;
	*col = (addr % 64) - 1;
	if (*col == -1)
	{
		*col = 63;
		*row -= 1;
	}
	*col = *col + 2 + (*col * 2);
	*row += 1;
}
