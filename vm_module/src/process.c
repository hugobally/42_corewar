#include "corewar.h"

void		push_process(t_core *core, t_process *new)
{
	new->next = core->process;
	core->process = new;
}

/*
** Reste a initialiser les valeurs.
*/

t_errors	make_process(t_core *core, uint32_t pc)
{
	t_process	*new;

	if (!(new = ft_memalloc(sizeof(t_process))))
		return (falloc);
	new->pc = pc;
	push_process(core, new);
	return (ok);
}
