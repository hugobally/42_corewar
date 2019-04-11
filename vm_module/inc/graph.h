/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:11:16 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/11 14:58:45 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_H
# define GRAPH_H

# include "corewar.h"
# include <ncurses.h>

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

WINDOW				*create_new_win(int h, int w, int x, int y);

int					init_ncurse(void);
int					make_graph(t_core *c);

void				make_win(t_core *c);

t_graph				*init_graph(void);
void				free_graph(t_graph *g);

void				create_champions_win(t_graph *g, t_player *p);
void				print_champions(t_graph *g, t_player *p);

void				create_registers_win(t_graph *g);

void				create_process_win(t_graph *g, t_process *p);

void				print_infos(t_graph *g, t_core *c, int cycle_mod);
void				create_infos_win(t_graph *g, t_core *c);

void				create_controls_win(t_graph *g);

void				write_on_arena(int addr, int v, int champ, t_graph *g);
void				add_procces_to_arena(int addr, t_graph *g);
void				remove_procces_to_arena(int addr, t_graph *g);
void				move_proccess_on_arena(int addr, int new_addr, t_graph *g);
void				create_arena_win(t_graph *g, t_player *p);

void				get_col_row(int addr, int *col, int *row);
WINDOW				*create_new_win(int h, int w, int x, int y);
#endif
