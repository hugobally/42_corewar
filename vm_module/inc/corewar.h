#ifndef COREWAR_H
# define COREWAR_H
# include <stdint.h>
# include <stdio.h>
# include "../../libft/inc/libft.h"
# include "../../libcorewar/inc/libcorewar.h"
# include <ncurses.h>

# define REG 1
# define DIR 2
# define IND 3


typedef enum			e_errors
{
	ok,
	falloc,
	badarg,
	badchamp,
	badfile,
	badopen,
	no_color,
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
	aff,
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
	header_t			head;
	int					p;
	unsigned char		proc[CHAMP_MAX_SIZE];
	struct s_player		*next;
}						t_player;

typedef struct			s_process
{
	unsigned int		pc;
	t_bool				carry;
	unsigned int		instruction;
	int					player;
	int					opsize;
	t_params			params;
	unsigned int		remaining_cycles;
	int32_t				regs[REG_NUMBER];
	t_bool				is_alive;
	struct s_process	*next;
}						t_process;

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
	int				nb_cycle;
	char			pause;
}					t_graph;

typedef struct			s_core
{
	unsigned char		arena[MEM_SIZE];
	int					next_player;
	int					nb_players;
	t_player			*players;
	t_process			*process;
	t_graph				*graph;
	unsigned int		dump;
	unsigned int		max_cycle_to_die;
	int					last_live_done_by;
	unsigned int		max_checks;
	unsigned int		nbr_live;
}             			t_core;


/*
** arguments.c
*/

t_errors				get_arguments(t_core *core, int ac, char **av);

/*
** players.c
*/

t_errors 				new_player(t_core *core, char *av);
t_errors				nb_player(t_core *core, t_player *new);
uint32_t				reverse_endian(uint32_t	num);

/*
** arena.c
*/

t_errors				make_arena(t_core *core);

/*
** process.c
*/

t_errors				make_process(t_core *core, uint32_t pc, t_player *pl);
void					push_process(t_core *core, t_process *new);

/*
** game.c
*/

t_errors				the_game(t_core *core);

/*
** Instructions
*/

t_errors				ft_instructions(t_core *core, t_process *process);
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


typedef t_errors		(*t_inst_tab)(t_core *, t_process *);
extern	t_inst_tab		g_op_inst_tab[17];

void					read_instruction(t_core *core, t_process *pro);
void					write_val(t_core *core, uint32_t pc, uint32_t size, int32_t val);
int32_t					read_val(t_core *core, uint32_t pc, uint32_t size);


int						get_pc(uint32_t i);

void					hexdump(t_core *core);

#endif
