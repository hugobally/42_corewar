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
	live,
	load,
	store,
	addition,
	soustration,
	and,
	or,
	xor,
	zjmp,
	ldi,
	sti,
	fork,
	lid,
	lldi,
	lfork,
	aff,
}						t_instruction;

typedef struct			s_params
{
	unsigned char		bytecode;
	short				p1;
	short				p2;
	short				p3;
}						t_params;

typedef	struct			s_player
{
	header_t			head;
	unsigned int		p;
	unsigned char		*proc;
	struct s_player		*next;
}						t_player;

typedef struct			s_process
{
	unsigned int		pc;
	t_bool				carry;
	unsigned int		instruction;
	unsigned int		remaining_cycles;
	t_params			params;
	uint8_t				regs[REG_NUMBER][REG_SIZE];
	int					is_alive[2];
	struct s_process	*next;
}						t_process;

typedef struct			s_core
{
	unsigned char		*arena;
	unsigned int		next_player;
	t_player			*players;
	t_process			*process;
	unsigned int		dump;
	unsigned int		max_cycle_to_die;

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

#endif
