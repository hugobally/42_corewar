/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlesven <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:11:16 by tlesven           #+#    #+#             */
/*   Updated: 2019/04/29 15:09:56 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_H
# define GRAPH_H

# include "corewar.h"
# include <ncurses.h>

# define ARENA_COL 195
# define ARENA_ROW 66

# define CTRL_COL 58
# define CTRL_ROW 7

# define INFO_COL 44
# define INFO_ROW 7

# define CHAMP_COL 64
# define CHAMP_ROW 7

# define PRO_COL 53
# define PRO_ROW 49

# define REG_COL 60
# define REG_ROW 17

# define PLAYER_DIFF 6

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
	P4,
	P,
	PS
};

WINDOW				*create_new_win(int h, int w, int x, int y);

int					init_thread(t_core *c);

int					init_ncurse(void);
int					make_graph(t_core *c);

void				game_mutex(t_core *c);
void				game_refresh(t_core *c);
void				game_fps(t_core *c);

void				make_win(t_core *c);

t_graph				*init_graph(void);
void				free_graph(t_graph *g);

void				create_champions_win(t_core *c);
void				print_champions(t_core *c);

void				print_registers(t_graph *g);
void				create_registers_win(t_graph *g);

void				print_process(t_core *c);
void				erase_process(t_core *c);
void				create_process_win(t_core *c);

void				print_infos(t_core *c);
void				create_infos_win(t_graph *g, t_core *c);

void				up_laps(t_graph *g);
void				down_laps(t_graph *g);
void				up_fps(t_graph *g);
void				down_fps(t_graph *g);
void				pause_game(t_graph *g);

int					controls(t_core *c);
void				create_controls_win(t_graph *g);

void				write_on_arena(int addr, int v, int champ, t_graph *g);
void				add_procces_to_arena(int addr, t_graph *g);
void				remove_procces_to_arena(int addr, t_core *c);
void				move_proccess_on_arena(int addr, int new_addr, t_core *c);
void				create_arena_win(t_core *c);

void				refresh_all_wins(t_core *c);
void				get_col_row(int addr, int *col, int *row);
WINDOW				*create_new_win(int h, int w, int x, int y);
#endif
