/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alac <alac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:41:37 by rle-ru            #+#    #+#             */
/*   Updated: 2019/04/29 14:00:07 by alac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <stdint.h>
# include "../../libft/inc/libft.h"
# include "../../libcorewar/inc/libcorewar.h"
# include <ncurses.h>

# define REG 1
# define DIR 2
# define IND 3
# define FLAG_DUMP 1
# define FLAG_SDUMP 2
# define FLAG_DUMP64 4

typedef enum			e_errors
{
	ok,
	falloc,
	badarg,
	badchamp,
	badfile,
	badopen,
	no_color,
	f1_exit,
	codesize,
	champlarge,
	filesmall,
	badmagic,
	badthread,
	du
}						t_errors;

typedef enum			e_instruction
{
	error,
	live,
	load,
	store,
	add,
	sub,
	and,
	or,
	xor,
	zjmp,
	ldi,
	sti,
	forky,
	lid,
	lldi,
	lforky,
	aff
}						t_instruction;

typedef struct			s_params
{
	unsigned char		bytecode;
	int					p1;
	int					p2;
	int					p3;
}						t_params;

typedef	struct			s_player
{
	t_header			head;
	int					p;
	unsigned char		proc[CHAMP_MAX_SIZE];
	struct s_player		*next;
	unsigned int		orig_pc;
	t_bool				has_lived;
	t_bool				is_alive;
}						t_player;

typedef struct			s_process
{
	unsigned int		pc;
	t_bool				carry;
	unsigned int		instruction;
	uint8_t				loading;
	int					player;
	int					opsize;
	t_params			params;
	unsigned int		remaining_cycles;
	int32_t				regs[REG_NUMBER];
	t_bool				is_alive;
	int					last_live;
	int					pro_name;
	struct s_process	*next;
	struct s_process	*previous;
}						t_process;

typedef struct			s_graph
{
	WINDOW				*arena_win;
	WINDOW				*ctrl_win;
	WINDOW				*info_win;
	WINDOW				*pro_win;
	WINDOW				*reg_win;
	WINDOW				*champ_win;
	int					fps;
	int					laps;
	int					nb_cycle;
	int					tmp_player;
	t_bool				pause;
	t_bool				proc_aff;
	t_process			*selected_proc;
}						t_graph;

typedef struct			s_core
{
	unsigned char		arena[MEM_SIZE];
	int					next_player;
	int					nb_players;
	t_player			*players;
	t_process			*process;
	t_graph				*graph;
	int					dump;
	int					max_cycle_to_die;
	int					last_live_done_by;
	int					winner;
	unsigned int		max_checks;
	unsigned int		nbr_live;
	t_bool				visu;
	uint32_t			sdump;
	uint8_t				flags;
	int					loop;
	int					cycles;
	int					verbose;
	t_bool				aff;
	int					nb_pro;
	char				*bad_arg;
	int					bad_size;
}						t_core;

/*
** Parsing
*/

t_errors				get_arguments(t_core *core, int ac, char **av);
t_errors				new_player(t_core *core, char *av);
t_errors				nb_player(t_core *core, t_player *new);
t_errors				make_arena(t_core *core);

/*
** Process
*/

t_errors				make_process(t_core *core, uint32_t pc, t_player *pl);
void					push_process(t_core *core, t_process *new);

/*
** Main loop
*/

t_errors				the_game(t_core *core);
void					ft_not_alive(t_player *tmp);
t_errors				call_instructions(t_core *core);
void					find_winner(t_core *core);
int						visu_control(t_core *c, int cycles);
void					check_delta(t_core *core);
t_errors				check_option_adj(t_core *c, char **av, int *i, int ac);
t_errors				ft_right_nb(char *s, t_core *core, int flag);
int						ft_nb_len(long nb);
void					ft_if_visu(t_core *core);

/*
** Instructions
*/

t_errors				ft_instructions(t_core *core, t_process *process);
void					store_parameters(t_core *core, t_process *p);
int						ft_type_param(unsigned char bytecode, int p);
t_errors				ft_error(t_core *core, t_process *process);
t_errors				ft_live(t_core *core, t_process *process);
t_errors				ft_load(t_core *core, t_process *process);
t_errors				ft_store(t_core *core, t_process *process);
t_errors				ft_add(t_core *core, t_process *process);
t_errors				ft_sub(t_core *core, t_process *process);
t_errors				ft_and(t_core *core, t_process *process);
t_errors				ft_or(t_core *core, t_process *process);
t_errors				ft_xor(t_core *core, t_process *process);
t_errors				ft_zjmp(t_core *core, t_process *process);
t_errors				ft_ldi(t_core *core, t_process *process);
t_errors				ft_sti(t_core *core, t_process *process);
t_errors				ft_fork(t_core *core, t_process *process);
t_errors				ft_lld(t_core *core, t_process *process);
t_errors				ft_lldi(t_core *core, t_process *process);
t_errors				ft_lfork(t_core *core, t_process *process);
t_errors				ft_aff(t_core *core, t_process *process);
void					ft_carry(t_process *process, int res);
t_errors				ft_reg(t_process *p, int *p1, int *p2, int *p3);
int						ft_get_params(t_core *c, t_process *pr, int p, int t);
typedef t_errors		(*t_inst_tab)(t_core *, t_process *);
extern	t_inst_tab		g_op_inst_tab[17];

void					read_instruction(t_core *c, t_process *p, int flag);
int32_t					read_val(t_core *core, uint32_t pc, uint32_t size);
void					write_val(t_core *core,
							uint32_t pc,
							uint32_t size,
							int32_t val);

/*
**	Tools
*/

int						get_pc(uint32_t i);
int						hexdump(t_core *core, int flag);
void					introduction(t_player *player);
int						ft_usage(char *exe_name, int ac);
uint32_t				reverse_endian(uint32_t	num);

#endif
