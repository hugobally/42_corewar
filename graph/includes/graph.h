/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:11:16 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/02 17:40:24 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_H
# define GRAPH_H

# include <ncurses.h>

# define ARENA_COL 195 // HAVE TO CHANGE, MEM_SIZE
# define ARENA_ROW 66 // HAVE TO CHANGE, MEM_SIZE

# define CTRL_COL 58
# define CTRL_ROW 7

# define INFO_COL 44
# define INFO_ROW 7

# define PRO_COL 53
# define PRO_ROW 49

# define REG_COL 53
# define REG_ROW 17

typedef struct		s_graph
{
	WINDOW			*arena_win;
	WINDOW			*ctrl_win;
	WINDOW			*info_win;
	WINDOW			*pro_win;
	WINDOW			*reg_win;
	int				fps;
	int				laps;
	char			pause;
}					t_graph;

t_graph				*init_graph(void);
void				free_graph(t_graph *g);
#endif
