/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:11:16 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/02 13:53:37 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_H
# define GRAPH_H

# include <ncurses.h>

# define ARENA_COL 195 // HAVE TO CHANGE, MEM_SIZE
# define ARENA_ROW 66 // HAVE TO CHANGE, MEM_SIZE

# define CTRL_COL 195
# define CTRL_ROW 7

typedef struct		s_graph
{
	WINDOW			*arena_win;
	WINDOW			*ctrl_win;
}					t_graph;

t_graph				*init_graph(void);
void				free_graph(t_graph *g);
#endif
