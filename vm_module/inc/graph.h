/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:11:16 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/10 13:18:17 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_H
# define GRAPH_H

# include <ncurses.h>
# include "corewar.h"

# define ARENA_COL 195 // HAVE TO CHANGE, MEM_SIZE
# define ARENA_ROW 66 // HAVE TO CHANGE, MEM_SIZE

# define CTRL_COL 58
# define CTRL_ROW 7

# define INFO_COL 44
# define INFO_ROW 7

# define CHAMP_COL 64
# define CHAMP_ROW 7

# define PRO_COL 53
# define PRO_ROW 49

# define REG_COL 53
# define REG_ROW 17

enum				e_collors
{
	BASE,
	EMPTY,
	CHAMP1,
	CHAMP2,
	CHAMP3,
	CHAMP4,
	P1,
	P2,
	P3,
	P4
};

typedef struct		s_graph
{
	WINDOW			*arena_win;
	WINDOW			*ctrl_win;
	WINDOW			*info_win;
	WINDOW			*pro_win;
	WINDOW			*reg_win;
	WINDOW			*champ_win;
	int				fps;
	int				laps;
	char			pause;
}					t_graph;

WINDOW				*create_new_win(int h, int w, int x, int y);

void				init_ncurse(void);
int					make_graph(t_core *c);

t_graph				*init_graph(void);
void				free_graph(t_graph *g);

void				create_champions_win(t_graph *g);

void				create_registers_win(t_graph *g);

void				create_process_win(t_graph *g);

void				create_infos_win(t_graph *g);

void				create_controls_win(t_graph *g);

void				write_on_arena(int addr, int v, int champ, t_graph *g);
void				add_procces_to_arena(int addr, t_graph *g);
void				remove_procces_to_arena(int addr, t_graph *g);
void				move_proccess_on_arena(int addr, int new_addr, t_graph *g);
void				create_arena_win(t_graph *g);

void				get_col_row(int addr, int *col, int *row);
WINDOW				*create_new_win(int h, int w, int x, int y);
#endif
