#ifndef COREWAR_H
# define COREWAR_H
# include <stdint.h>

typedef enum			e_errors
{
	ok,
	falloc,
	badarg,
	badchamp
}						t_errors;

typedef	struct			s_player
{
	unsigned int		p;
	char				*name;
	char				*desc;
	struct s_player		*next;
}						t_player;

typedef struct			s_process
{
	unsigned int		pc;
	t_bool				carry;
	void				(*f)(struct s_core *core, struct s_process *process);
	uint8_t				regs[REG_N][REG_SIZE];

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

t_errors				get_arguments(t_core *core, int ac, char **av);

#endif
