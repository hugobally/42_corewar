#include "corewar.h"

t_errors	make_arena(t_core *core)
{
	if (!(core->arena = ft_memalloc(MEM_SIZE)))
		return (falloc);
	core->max_cycle_to_die = CYCLE_TO_DIE;
	
}
