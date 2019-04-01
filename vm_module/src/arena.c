#include "corewar.h"

void		add_process(t_player *pl, t_core *core, uint32_t pc)
{
	ft_memcpy(&core->arena[pc], pl->proc, pl->head.prog_size);
}

/*
**	Manque la repartition des pc.
*/

t_errors	make_arena(t_core *core)
{
	t_player	*pl;
	t_errors	ret;

	pl = core->players;
	core->max_cycle_to_die = CYCLE_TO_DIE;
	core->max_checks = MAX_CHECKS;
	while (pl)
	{
		add_process(pl, core, 10);
		if ((ret = make_process(core, 10)) != ok)
			return (ret);
		pl = pl->next;
	}
	return (ok);
}
