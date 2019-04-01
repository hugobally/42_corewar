#ifndef COREWAR_H
# define COREWAR_H
# include <stdint.h>
# include "../../libft/inc/libft.h"
# include "../../libcorewar/inc/libcorewar.h"

# define REG 1
# define IND 2
# define DIR 3


typedef enum			e_errors
{
	ok,
	falloc,
	badarg,
	badchamp,
	badfile,
	badopen
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
	unsigned int		remaining_cycles;
	t_params			params;
	int32_t				regs[REG_NUMBER];
	t_bool				is_alive;
	int					instruction_size;
	struct s_process	*next;
}						t_process;

typedef struct			s_core
{
	unsigned char		arena[MEM_SIZE];
	int					next_player;
	int					nb_players;
	t_player			*players;
	t_process			*process;
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

/*
** arena.c
*/

t_errors				make_arena(t_core *core);

/*
** process.c
*/

t_errors				make_process(t_core *core, uint32_t pc);

/*
** game.c
*/

t_errors				the_game(t_core *core);

/*
** Instructions
*/

int						ft_instructions(t_core *core, t_process *process);
int						ft_type_param(unsigned char bytecode, int p);
int						ft_error(t_core *core, t_process *process);
int 					ft_live(t_core *core, t_process *process);
int						ft_load(t_core *core, t_process *process);
int						ft_store(t_core *core, t_process *process);
int						ft_add(t_core *core, t_process *process);
int						ft_sub(t_core *core, t_process *process);
int						ft_and(t_core *core, t_process *process);
int						ft_or(t_core *core, t_process *process);
int						ft_xor(t_core *core, t_process *process);
int						ft_zjmp(t_core *core, t_process *process);
int						ft_ldi(t_core *core, t_process *process);
int						ft_sti(t_core *core, t_process *process);
int						ft_fork(t_core *core, t_process *process);
int						ft_lld(t_core *core, t_process *process);
int						ft_lldi(t_core *core, t_process *process);
int						ft_lfork(t_core *core, t_process *process);
int						ft_aff(t_core *core, t_process *process);


typedef int				(*t_inst_tab)(t_core *, t_process *);
extern	t_inst_tab		g_op_inst_tab[17];



int						get_pc(uint32_t i);

#endif
