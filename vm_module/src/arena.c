#include "corewar.h"

void		add_process(t_player *pl, t_core *core, uint32_t pc)
{
	ft_memcpy(&core->arena[pc], pl->proc, pl->head.prog_size);
	pl->orig_pc = pc;
}

t_errors	make_arena(t_core *core)
{
	int			cur;
	t_player	*pl;
	t_errors	ret;

	cur = 0;
	pl = core->players;
	core->max_cycle_to_die = CYCLE_TO_DIE;
	core->max_checks = MAX_CHECKS;
	while (pl)
	{
		add_process(pl, core, cur);
		core->last_live_done_by = pl->p;
		if ((ret = make_process(core, cur, pl)) != ok)
			return (ret);
		pl = pl->next;
		cur += MEM_SIZE / core->nb_players;
	}
	return (ok);
}
